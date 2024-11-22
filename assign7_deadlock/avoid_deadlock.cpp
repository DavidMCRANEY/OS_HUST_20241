#include <iostream>
#include <cstring>

using namespace std;

const int MAX_PROCESSES = 50;
const int MAX_RESOURCES = 50;

typedef int ProcessArray[MAX_PROCESSES];
typedef int ResourceArray[MAX_RESOURCES];
typedef int AllocationArray[MAX_PROCESSES][MAX_RESOURCES];

struct SystemInfo {
	int n, m; // n: number of processes; m: number of resources types
	ResourceArray Available;
	AllocationArray Max, Allocation;
};


// returns true if the system is in safe state
bool isSystemSafe(const SystemInfo& s) {
	// TODO: deadlock avoidance

	// Copy Available resources to Work
    ResourceArray Work;
    for (int j = 0; j < s.m; j++) {
        Work[j] = s.Available[j];
    }

    // Initialize Finish array to false for all processes
    bool Finish[MAX_PROCESSES] = {false};

    // Calculate the Need matrix
    AllocationArray Need;
    for (int i = 0; i < s.n; i++) {
        for (int j = 0; j < s.m; j++) {
            Need[i][j] = s.Max[i][j] - s.Allocation[i][j];
        }
    }

    // Iterate to find a safe sequence
    int completed = 0; // Count of completed processes
    while (completed < s.n) {
        bool found = false;

        for (int i = 0; i < s.n; i++) {
            if (!Finish[i]) { // Process not yet finished
                bool canAllocate = true;

                // Check if Need[i] <= Work for all resource types
                for (int j = 0; j < s.m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Simulate allocation by adding allocated resources to Work
                    for (int j = 0; j < s.m; j++) {
                        Work[j] += s.Allocation[i][j];
                    }
                    Finish[i] = true; // Mark process as finished
                    completed++;      // Increment completed processes count
                    found = true;     // A process was successfully allocated
                }
            }
        }

        // If no process was allocated in this iteration, system is not safe
        if (!found) {
            return false;
        }
    }

    // If all processes are completed, system is in a safe state
    return true;
}
	// END TODO


// returns true if it is safe to allow process Ti to make the request
bool isRequestSafe(const SystemInfo& s, int Ti, ResourceArray Request) {
	// TODO: deadlock avoidance

	// Check if Request is valid
    for (int j = 0; j < s.m; j++) {
        if (Request[j] > s.Available[j] || Request[j] > s.Max[Ti][j] - s.Allocation[Ti][j]) {
            // Request exceeds available resources or exceeds maximum need
            return false;
        }
    }

    // Simulate allocation
    SystemInfo temp = s; // Create a temporary copy of the system
    for (int j = 0; j < s.m; j++) {
        temp.Available[j] -= Request[j];
        temp.Allocation[Ti][j] += Request[j];
        temp.Max[Ti][j] -= Request[j];
    }

    // Check if the system is in a safe state after allocation
    return isSystemSafe(temp);
	// END TODO
}


// returns -1 if the system is deadlock free, or the LOWEST index of the processes in deadlock
int findFirstDeadlockedProcess(const SystemInfo& s, AllocationArray Request) {
	// TODO: deadlock detection
	return -1;
	// END TODO
}






template <typename T>
void assignArray(T* a, initializer_list<T> l) {
	size_t i = 0;
	for (auto li : l)
		a[i++] = li;
}

void assignAllocationArray(AllocationArray a, initializer_list<initializer_list<int>> l) {
	size_t i = 0;
	for (auto li : l)
		assignArray(a[i++], li);
}


void deadlockAvoidance(int argc, const char** argv) {
	SystemInfo s;
	ResourceArray Requests[3];
	int RequestTi[3];

	if (argc <= 1 || strcmp(argv[1], "-i") != 0) {
		s.n = 5;
		s.m = 3;
		assignArray(s.Available, {3, 3, 2});
		assignAllocationArray(s.Max, {
			{7, 5, 3},
			{3, 2, 2},
			{9, 0, 2},
			{2, 2, 2},
			{4, 3, 3}});
		assignAllocationArray(s.Allocation, {
			{0, 1, 0},
			{2, 0, 0},
			{3, 0, 2},
			{2, 1, 1},
			{0, 0, 2}});
		
		assignArray(RequestTi, {1, 4, 0});
		assignArray(Requests[0], {1, 0, 2});
		assignArray(Requests[1], {3, 3, 0});
		assignArray(Requests[2], {0, 2, 0});

	} else {
		cin >> s.n >> s.m;

		int i, j;
		for (i = 0; i < s.n; i++)
			cin >> s.Available[i];

		for (i = 0; i < s.n; i++)
			for (j = 0; j < s.m; j++)
				cin >> s.Max[i][j];

		for (i = 0; i < s.n; i++)
			for (j = 0; j < s.m; j++)
				cin >> s.Allocation[i][j];
	}

	cout << "System safety: " << isSystemSafe(s) << endl;

	for (int i = 0; i < 3; i++)
		cout << "Request safety: " << isRequestSafe(s, RequestTi[i], Requests[i]) << endl;
}


void deadlockDetection(int argc, const char** argv) {
	SystemInfo s;
	AllocationArray Request;

	if (argc <= 1 || strcmp(argv[1], "-i") != 0) {
		s.n = 5;
		s.m = 3;
		assignArray(s.Available, {0, 0, 0});
		assignAllocationArray(s.Allocation, {
			{0, 1, 0},
			{2, 0, 0},
			{3, 0, 3},
			{2, 1, 1},
			{0, 0, 2}});
		
		assignAllocationArray(Request, {
			{0, 0, 0},
			{2, 0, 2},
			{0, 0, 0},
			{1, 0, 0},
			{0, 0, 2}});

	} else {
		cin >> s.n >> s.m;

		int i, j;
		for (i = 0; i < s.n; i++)
			cin >> s.Available[i];

		for (i = 0; i < s.n; i++)
			for (j = 0; j < s.m; j++)
				cin >> s.Allocation[i][j];

		for (i = 0; i < s.n; i++)
			for (j = 0; j < s.m; j++)
				cin >> Request[i][j];
	}

	cout << "Deadlock process: " << findFirstDeadlockedProcess(s, Request) << endl;
}


int main(int argc, const char** argv) {
	// TODO: gỡ chú thích một trong 2 dòng dưới đây tuỳ theo bài được giao:
	deadlockAvoidance(argc, argv);
	//deadlockDetection(argc, argv);
	// END TODO

	return 0;
}