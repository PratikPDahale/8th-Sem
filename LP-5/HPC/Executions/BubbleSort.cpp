#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>

using namespace std;

// ---------------- SEQUENTIAL BUBBLE SORT ----------------

void sequentialBubbleSort(vector<int>& arr, int n) {

    for(int i = 0; i < n - 1; i++) {

        for(int j = 0; j < n - i - 1; j++) {

            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- PARALLEL BUBBLE SORT ----------------
// Odd-Even Transposition Sort using OpenMP

void parallelBubbleSort(vector<int>& arr, int n) {

    for(int i = 0; i < n; i++) {

        int start = i % 2;

        #pragma omp parallel for
        for(int j = start; j < n - 1; j += 2) {

            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++) {
        cin >> original[i];
    }

    // Create separate copies for fair comparison
    vector<int> seqArr = original;
    vector<int> parArr = original;

    // ---------------- SEQUENTIAL SORT ----------------

    clock_t seqStart = clock();

    sequentialBubbleSort(seqArr, n);

    clock_t seqEnd = clock();

    // ---------------- PARALLEL SORT ----------------

    double parStart = omp_get_wtime();

    parallelBubbleSort(parArr, n);

    double parEnd = omp_get_wtime();

    // ---------------- DISPLAY SORTED ARRAY ----------------

    cout << "\nSorted Array (Sequential Bubble Sort):\n";

    for(int num : seqArr) {
        cout << num << " ";
    }

    cout << "\n";

    cout << "\nSorted Array (Parallel Bubble Sort):\n";

    for(int num : parArr) {
        cout << num << " ";
    }

    cout << "\n";

    // ---------------- TIME CALCULATION ----------------

    double seqTime =
        double(seqEnd - seqStart) / CLOCKS_PER_SEC;

    double parTime =
        parEnd - parStart;

    // ---------------- PERFORMANCE OUTPUT ----------------

    cout << "\nSequential Bubble Sort Time: "
         << seqTime << " seconds";

    cout << "\nParallel Bubble Sort Time: "
         << parTime << " seconds";

    return 0;
}

/*
OUTPUT :-

Enter number of elements: 15
Enter elements:
45 12 89 3 56 78 1 99 23 67 10 5 34 88 2

Sorted Array (Sequential Bubble Sort):
1 2 3 5 10 12 23 34 45 56 67 78 88 89 99 

Sorted Array (Parallel Bubble Sort):
1 2 3 5 10 12 23 34 45 56 67 78 88 89 99 

Sequential Bubble Sort Time: 0 seconds
Parallel Bubble Sort Time: 0.00199986 seconds

*/