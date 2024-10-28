// // sjn standard for 'shortest job first' or 'shortest job next' (non preemptive)
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// The structure stores information about each process
struct Process {
    int id;         
    int arrivalTime; 
    int burstTime;   
    int startTime;   
};

// Comparison function based on burst time and arrival time (for non-preemptive SJF)
bool compareProcess(const Process &a, const Process &b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.burstTime < b.burstTime;
    return a.arrivalTime < b.arrivalTime;
}

// Function that implements the SJF(SJN) algorithm (non-preemptive)
void sjfScheduling(vector<Process> &processes) {
    int currentTime = 0; // Current time in the system
    vector<Process> schedule; // List of scheduled processes

    // Sort processes by arrival time and burst time
    sort(processes.begin(), processes.end(), compareProcess);

    while (!processes.empty()) {
        int idx = -1;
        int minBurst = INT_MAX;

        // Find the process with the smallest burst time that can run at the current time
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurst) {
                minBurst = processes[i].burstTime;
                idx = i;
            }
        }

        // If no process arrives, shift the system time to the arrival time of the next process
        if (idx == -1) {
            currentTime = processes[0].arrivalTime;
            continue;
        }

        // Select the process to run next
        Process &proc = processes[idx];
        proc.startTime = currentTime;
        currentTime += proc.burstTime;

        // Save the running schedule of the selected process
        schedule.push_back(proc);

        // Remove process from the list
        processes.erase(processes.begin() + idx);
    }

    // Print the running schedule of each process
    cout << "Process\tStart Time\tBurst Time\n";
    for (const auto &proc : schedule) {
        cout << "P" << proc.id << "\t" << proc.startTime << "\t\t" << proc.burstTime << endl;
    }
}

int main() {
    // Initialize processes with available information: ID, arrival time, burst time
    vector<Process> processes = {
        {1, 0, 8},
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5}
    };

    // Implement the SJF algorithm
    sjfScheduling(processes);

    return 0;
}
