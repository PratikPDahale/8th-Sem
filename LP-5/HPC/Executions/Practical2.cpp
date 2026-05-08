#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>

using namespace std;


void bubbleSort(vector<int> & arr, int length){
    for(int i = 0; i < length; i++){
        int start = i % 2;

        #pragma omp parallel for
        for(int j = start; j < length - 1; j += 2){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(vector<int> & arr, int l, int m, int r){
    vector<int> temp;
    int left = l;
    int right = m + 1;

    while(left <= m && right <= r){
        if(arr[left] <= arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left <= m){
        temp.push_back(arr[left]);
        left++;
    }

    while(right <= r){
        temp.push_back(arr[right]);
        right++;
    }

    for(int i = l; i <= r; i++){
        arr[i] = temp[i - l];
    }
}

void mergeSort(vector<int>& arr, int l, int r){
    if(l < r){
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);

            #pragma omp section
            mergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main() {

    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> original(n);

    cout << "Enter the elements: ";

    for(int i = 0; i < n; i++){
        cin >> original[i];
    }

    // Create separate copies
    vector<int> bubbleArr = original;
    vector<int> mergeArr = original;

    // ---------------- BUBBLE SORT ----------------

    clock_t bubbleStart = clock();

    bubbleSort(bubbleArr, n);

    clock_t bubbleEnd = clock();

    cout << "\nSorted array using Bubble Sort:\n";

    for(int num : bubbleArr){
        cout << num << " ";
    }

    cout << endl;

    // ---------------- MERGE SORT ----------------

    clock_t mergeStart = clock();

    mergeSort(mergeArr, 0, n - 1);

    clock_t mergeEnd = clock();

    cout << "\nSorted array using Merge Sort:\n";

    for(int num : mergeArr){
        cout << num << " ";
    }

    cout << endl;

    // ---------------- TIME CALCULATION ----------------

    double bubbleDuration =
        double(bubbleEnd - bubbleStart) / CLOCKS_PER_SEC;

    double mergeDuration =
        double(mergeEnd - mergeStart) / CLOCKS_PER_SEC;

    cout << "\nBubble Sort Time: "
         << bubbleDuration << " seconds" << endl;

    cout << "Merge Sort Time: "
         << mergeDuration << " seconds" << endl;

    return 0;
}