/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/* 
 * File:   main.c
 * Author: Kervin Francois
 *
 * Created on February 24, 2025, 10:17 AM
 */

 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <cmath>
 #include <algorithm>
 
 using namespace std;
 
// Structure to store process details
struct Process {
    int processId;
    int startingAddress;
    int processSizeMB;
    int unusedSpaceMB;
};

// Function to allocate memory to processes
void userMemoryAllocation() {
    const int TOTAL_PAGES = 100; // Total available memory pages
    const int PAGE_SIZE_MB = 160; // Each page size in MB
    const int START_ADDRESS = 2000; // Starting memory address
    
    vector<int> memory(TOTAL_PAGES, -1); // Memory representation, -1 means free
    vector<Process> processList; // List to store allocated processes
    
    int currentAddress = START_ADDRESS; // Initialize starting address
    int processId = 1; // Process ID counter
    
    // Allocate memory to processes until no sufficient space is left
    while (std::count(memory.begin(), memory.end(), -1) > 0) {
        int processSizePages = rand() % 30 + 1; // Generate random pages between 1-30
        int processSizeMB = processSizePages * 80; // Convert to MB
        int pagesNeeded = ceil(static_cast<double>(processSizeMB) / PAGE_SIZE_MB); // Calculate required pages
        
        // Check if enough memory is available
        if (std::count(memory.begin(), memory.end(), -1) < pagesNeeded) {
            break; // Stop allocation if not enough space
        }
        
        int allocatedPages = 0;
        // Allocate memory pages to the process
        for (int i = 0; i < TOTAL_PAGES; i++) {
            if (memory[i] == -1) { // If page is free
                memory[i] = processId; // Assign process ID to the page
                allocatedPages++;
                if (allocatedPages == pagesNeeded) break; // Stop when enough pages are allocated
            }
        }
        
        int totalAllocatedMemoryMB = pagesNeeded * PAGE_SIZE_MB; // Total memory allocated
        int unusedSpaceMB = totalAllocatedMemoryMB - processSizeMB; // Calculate unused space
        
        // Store process information
        processList.push_back({processId, currentAddress, processSizeMB, unusedSpaceMB});
        
        currentAddress += totalAllocatedMemoryMB; // Update starting address for next process
        processId++; // Increment process ID
    }
    
    // Print Summary Report
    cout << "\nSummary Report" << endl;
    cout << "Process Id   Starting Address   Size (MB)   Unused Space (MB)" << endl;
    for (const auto& process : processList) {
        cout << process.processId << "\t" << process.startingAddress << "\t\t" 
             << process.processSizeMB << "\t\t" << process.unusedSpaceMB << endl;
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    userMemoryAllocation(); // Run memory allocation simulation
    return 0;
}
