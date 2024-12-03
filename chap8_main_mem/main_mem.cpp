#include <iostream>
#include <bitset>
#include <cstring>
#include <list>

using namespace std;

const int OFFSET_BITS = 3;
const int PAGE_NUM_BITS = 5;
const int FRAME_NUM_BITS = 13;
const int PAGE_TABLE_SIZE = 1 << PAGE_NUM_BITS; // = 2 mũ( page_num_bits)
const int TLB_SIZE = 4;

typedef bitset<PAGE_NUM_BITS> PageNumber;
typedef bitset<FRAME_NUM_BITS> FrameNumber;
typedef bitset<OFFSET_BITS> OffsetNumber;
typedef bitset<PAGE_NUM_BITS + OFFSET_BITS> LogicalAddress;
typedef bitset<FRAME_NUM_BITS + OFFSET_BITS> PhysicalAddress;


// the page table
FrameNumber PT[PAGE_TABLE_SIZE];

// the TLB
pair<PageNumber, FrameNumber> TLB[TLB_SIZE];
int lastTLBEntry = 0;


// Returns physical address in `pa` and whether the TLB is hit in `TLBhit`
// Trả về địa chỉ vật lý vào biến `pa` và có sử dụng TLB hay không trong biết `TLBhit`
void MMU_translate(LogicalAddress la, PhysicalAddress& pa, bool& TLBhit) {
	// TODO BEGIN
	
    // Tách địa chỉ logic thành số trang (PageNumber) và offset (OffsetNumber)
    PageNumber pageNum;
    OffsetNumber offset;
    for (int i = 0; i < PAGE_NUM_BITS; i++) {
        pageNum[i] = la[i + OFFSET_BITS];
    }
    for (int i = 0; i < OFFSET_BITS; i++) {
        offset[i] = la[i];
    }

    // Tìm trong TLB
    TLBhit = false;
    FrameNumber frameNum;
    for (int i = 0; i < TLB_SIZE; i++) {
        if (TLB[i].first == pageNum) {
            frameNum = TLB[i].second;
            TLBhit = true;
            break;
        }
    }

    // Nếu không tìm thấy trong TLB, tra cứu bảng trang
    if (!TLBhit) {
        frameNum = PT[pageNum.to_ulong()]; // Lấy frame từ Page Table

        // Thêm vào TLB (cơ chế FIFO cho TLB)
        TLB[lastTLBEntry] = make_pair(pageNum, frameNum);
        lastTLBEntry = (lastTLBEntry + 1) % TLB_SIZE; // Vòng lặp chỉ số TLB
    }

    // Ghép frame number với offset để tạo địa chỉ vật lý
    for (int i = 0; i < FRAME_NUM_BITS; i++) {
        pa[i + OFFSET_BITS] = frameNum[i];
    }
    for (int i = 0; i < OFFSET_BITS; i++) {
        pa[i] = offset[i];
    }
}

	// TODO END

int main(int argc, const char** argv) {
	list<LogicalAddress> accessList;

	if (argc <= 1 || strcmp(argv[1], "-i") != 0) {
		for (int i = 0; i < PAGE_TABLE_SIZE; i++)
			PT[i] = (i + 37) * (i + 3) + 231;

		for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
			int n = ((i + 13) * (i + 7) + 891) % PAGE_TABLE_SIZE,
				m = ((i + 21) * (i + 17) + 533) % PAGE_TABLE_SIZE;
			auto t = PT[m];
			PT[m] = PT[n];
			PT[n] = t;
		}

		srand(47261);
		for (int i = 0; i < PAGE_TABLE_SIZE * 5; i++) {
			int a = (rand() % PAGE_TABLE_SIZE) << OFFSET_BITS;
			int n = rand() % 20;
			for (int j = 0; j < n; j++)
				accessList.push_back(LogicalAddress(a + rand() % (1 << OFFSET_BITS)));
		}

	} else {
		for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
			int f;
			cin >> f;
			PT[i] = f;
		}

		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			LogicalAddress la;
			cin >> la;
			accessList.push_back(la);
		}
	}

	for (int i = 0; i < TLB_SIZE; i++)
		TLB[i] = make_pair(PageNumber(i), PT[i]);

	int TLBhitcount = 0;
	for (auto la : accessList) {
		PhysicalAddress pa;
		bool TLBhit;
		MMU_translate(la, pa, TLBhit);

		if (TLBhit) TLBhitcount++;

		cout << la << " --> " << pa << " " << TLBhit << endl;
	}

	cout << "TLB hit rate: " << (TLBhitcount * 100. / accessList.size()) << "%" << endl;
	
	return 0;
}