#include <iostream>
#include <vector>

using namespace std;

// Function to find the best disk for a given file
int findBestDisk(const vector<int>& t, int fileSize, int m) {
    int bestDisk = -1;
    int maxSpace = -1;

    // Iterate through each disk
    for (int j = 0; j < m; ++j) {
        // Check if the disk can hold the file and has the most available space so far
        if (t[j] >= fileSize && t[j] > maxSpace) {
            bestDisk = j;
            maxSpace = t[j];
        }
    }

    return bestDisk;
}

// Greedy file storage algorithm
vector<int> greedyFileStorage(int n, const vector<int>& s, int m, vector<int>& t) {
    vector<int> map(n, -1);  // To store the mapping of files to disks (-1 means not assigned)

    // Iterate over each file
    for (int i = 0; i < n; ++i) {
        int bestDisk = findBestDisk(t, s[i], m);

        // If a valid disk is found, assign the file to that disk
        if (bestDisk != -1) {
            map[i] = bestDisk;  // Store the disk index in map
            t[bestDisk] -= s[i]; // Reduce the remaining space on that disk
        } else {
            // If no valid disk is found, print an error and return empty
            cout << "Error: No disk found with enough space for file " << i + 1 << endl;
            return {};
        }
    }

    return map;  // Return the mapping of files to disks
}

int main() {
    int n = 4;  // Number of files
    vector<int> s = {200, 500, 300, 150};  // File sizes in MB

    int m = 3;  // Number of disks
    vector<int> t = {600, 700, 300};  // Disk storage capacities in MB

    // Perform greedy file storage
    vector<int> map = greedyFileStorage(n, s, m, t);

    // Check if a valid mapping was returned
    if (!map.empty()) {
        cout << "File to disk mapping (0-based index):" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "File " << i + 1 << " -> Disk " << map[i] << endl;
        }
    }

    return 0;
}
