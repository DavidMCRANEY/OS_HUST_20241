#include <iostream>
#include <fcntl.h>              // For O_* constants, shm_open (add Realtime extension lib)
#include <unistd.h>             // For ftruncate(), fork
#include <sys/mman.h>           // For mmap, shm_unlink (add Realtime extension lib)
#include <sys/types.h>          // For pid_t
#include <sys/wait.h>           // For wait compose O_CREAT, O_RDWR

#define SHM_NAME "my-shm"       // Shared memory name
#define SHM_SIZE (1)            // 1 * sizeof(smem)

typedef struct t_Share_Memory {
    int x, y, z;    // x, y: get from keyboard, z = x + y
    int ready;      // init == 0
} smem;

/********************************************************************************
* Prototype
********************************************************************************/
/* init memory to save a struct t_Share_Memory */
int init_ShareMemory(const char* name, int size, int* sid);

/* init 'ready = 0' */
int init_smemToShm(int sid);

/* user modifies x, y */
void input_xy(smem* p);

/********************************************************************************
* Code
********************************************************************************/
int main() {
    // variable
    int shmid;                  // save id of shared memory
    pid_t childPID = -1;         // check parent or child or failed init proc

    // init sharing memory
    if (init_ShareMemory(SHM_NAME, SHM_SIZE, &shmid)) {
        return 1;
    }

    // init ready = 0
    if (init_smemToShm(shmid)) {
        return 2;
    }

    // init child process
    childPID = fork();
    if (childPID == -1) {  // init failed, parent does
        std::cerr << "[ERR] Failed to init child process\n";
        return 3;
    } else if (childPID == 0) {  // child process
        smem* p = (smem*)mmap(nullptr, sizeof(smem), PROT_WRITE, MAP_SHARED, shmid, 0);
        while (p->ready == 0) {
            // polling until ready == 1
            continue;
        }
        // while ready == 1 -> z = x + y -> ready = 0
        p->z = p->x + p->y;
        // set ready = 0
        p->ready = 0;
    } else {  // parent process
        smem* p = (smem*)mmap(nullptr, sizeof(smem), PROT_WRITE, MAP_SHARED, shmid, 0);
        // get x, y
        input_xy(p);
        // then set ready = 1
        p->ready = 1;
        // polling to wait child to calculate
        while (p->ready == 1) {
            continue;
        }
        // print z
        std::cout << "\n[z = " << p->z << "]\n";
        // wait for child to finish
        wait(nullptr);
        // end shared memory
        shm_unlink(SHM_NAME);
    }

    // exit ok
    return 0;
}

/* init memory, size */
int init_ShareMemory(const char* name, int size, int* sid) {
    int code;
    *sid = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    // check init mem
    if (*sid == -1) {  // error
        std::cerr << "[ERR] Failed to open shared memory\n";
        return 1;
    }
    // allocate memory size
    code = ftruncate(*sid, size * sizeof(smem));
    if (code == -1) {
        std::cerr << "[ERR] Failed to modify memory\n";
        return 2;
    }
    // everything ok
    return 0;
}

/* add a struct smem to shared memory */
int init_smemToShm(int sid) {
    smem* p = (smem*)mmap(nullptr, sizeof(smem), PROT_WRITE, MAP_SHARED, sid, 0);
    if ((void*)p == MAP_FAILED) { // explicitly convert pointer to (void*) type, before comparasion to MAP_FAILED, same type
        return 1;
    }
    // init ready = 0
    p->ready = 0;
    return 0;
}
/* user modify x, y */
void input_xy(smem* p) {
    std::cout << "\nInput x, y: ";
    std::cin >> p->x >> p->y;
}