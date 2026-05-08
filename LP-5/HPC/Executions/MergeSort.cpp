#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>

using namespace std;

// ---------------- MERGE FUNCTION ----------------

void merge(vector<int>& arr, int l, int m, int r) {

    vector<int> temp;

    int left = l;
    int right = m + 1;

    while(left <= m && right <= r) {

        if(arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left <= m) {
        temp.push_back(arr[left]);
        left++;
    }

    while(right <= r) {
        temp.push_back(arr[right]);
        right++;
    }

    for(int i = l; i <= r; i++) {
        arr[i] = temp[i - l];
    }
}

// ---------------- SEQUENTIAL MERGE SORT ----------------

void sequentialMergeSort(vector<int>& arr, int l, int r) {

    if(l < r) {

        int m = l + (r - l) / 2;

        sequentialMergeSort(arr, l, m);

        sequentialMergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// ---------------- PARALLEL MERGE SORT ----------------

void parallelMergeSort(vector<int>& arr, int l, int r) {

    if(l < r) {

        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {

            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main() {

    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> original(n);

    cout << "Enter the elements:\n";

    for(int i = 0; i < n; i++) {
        cin >> original[i];
    }

    // Separate copies for fair comparison

    vector<int> seqArr = original;
    vector<int> parArr = original;

    // ---------------- SEQUENTIAL MERGE SORT ----------------

    double seqStart = omp_get_wtime();

    sequentialMergeSort(seqArr, 0, n - 1);

    double seqEnd = omp_get_wtime();

    // ---------------- PARALLEL MERGE SORT ----------------

    double parStart = omp_get_wtime();

    parallelMergeSort(parArr, 0, n - 1);

    double parEnd = omp_get_wtime();

    // ---------------- DISPLAY RESULTS ----------------

    cout << "\nSorted Array using Sequential Merge Sort:\n";

    for(int num : seqArr) {
        cout << num << " ";
    }

    cout << "\n";

    cout << "\nSorted Array using Parallel Merge Sort:\n";

    for(int num : parArr) {
        cout << num << " ";
    }

    cout << "\n";

    // ---------------- TIME CALCULATION ----------------

    double seqTime = seqEnd - seqStart;

    double parTime = parEnd - parStart;

    // ---------------- PERFORMANCE OUTPUT ----------------

    cout << "\nSequential Merge Sort Time: "
         << seqTime << " seconds";

    cout << "\nParallel Merge Sort Time: "
         << parTime << " seconds";

    return 0;
}

/*
OUTPUT :-

Enter the number of elements: 10
Enter the elements:
45 12 89 3 56 78 1 99 23 67

Sorted Array using Sequential Merge Sort:
1 3 12 23 45 56 67 78 89 99 

Sorted Array using Parallel Merge Sort:
1 3 12 23 45 56 67 78 89 99 

Sequential Merge Sort Time: 0 seconds
Parallel Merge Sort Time: 0.00300002 seconds

*/