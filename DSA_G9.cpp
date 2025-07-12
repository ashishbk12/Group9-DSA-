#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// =-=-=-=-=-) Quick Sort (=-=-=-=-=-
int partitionArr(vector<int>& arr, int start, int end) {
    int pivotValue = arr[end];
    int smallerIndex = start - 1;
    for(int current = start; current < end; current++) {
        if(arr[current] < pivotValue) {
            smallerIndex++;
            swap(arr[smallerIndex], arr[current]);
        }
    }
    swap(arr[smallerIndex + 1], arr[end]);
    return smallerIndex + 1;
}

void quickSortArr(vector<int>& arr, int start, int end) {
    if(start < end) {
        int pivotIndex = partitionArr(arr, start, end);
        quickSortArr(arr, start, pivotIndex - 1);
        quickSortArr(arr, pivotIndex + 1, end);
    }
}

// =-=-=-=-=-) Merge sort (=-=-=-=-=-
void mergeArr(vector<int>& arr, int left, int middle, int right) {
    int sizeLeft = middle - left + 1;
    int sizeRight = right - middle;
    vector<int> leftArr(sizeLeft), rightArr(sizeRight);

    for(int i = 0; i < sizeLeft; i++) leftArr[i] = arr[left + i];
    for(int j = 0; j < sizeRight; j++) rightArr[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while(i < sizeLeft && j < sizeRight) {
        if(leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while(i < sizeLeft) arr[k++] = leftArr[i++];
    while(j < sizeRight) arr[k++] = rightArr[j++];
}

void mergeSortArr(vector<int>& arr, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSortArr(arr, left, mid);
        mergeSortArr(arr, mid + 1, right);
        mergeArr(arr, left, mid, right);
    }
}


// =-=-=-=-=-) Binary Search (=-=-=-=-=-
int binarySearchArr(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) return mid;
        else if(arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}


// =-=-=-=-=-) Exponential Sort (=-=-=-=-=-
int exponentialSearchArr(const vector<int>& arr, int target) {
    if(arr[0] == target) return 0;
    int bound = 1;
    while(bound < arr.size() && arr[bound] <= target) {
        bound *= 2;
    }
    int left = bound / 2;
    int right = min(bound, (int)arr.size());
    for(int i = left; i < right; i++) {
        if(arr[i] == target) return i;
    }
    return -1;
}


// =-=-=-=-=-) Main Function (=-=-=-=-=-
int main() {
    int n, searchKey;
    cout << "Hey There!! How many elements do you want to generate? (Limit is 1000): ";
    cin >> n;

    if(n > 1000) {
        cout << "\nNOOOOOO!! Limit is 1000 elements. Please try again.\n";
        return 1;
    }

    vector<int> arr(n);

    srand(time(0));
    for(int i = 0; i < n; i++) {
        arr[i] = 1 + rand() % 99;
    }

    cout << "\nHere are the generated numbers:\n";
    for(int num : arr) cout << num << " ";
    cout << endl;

    // =-=-=-=-=-) Quick Sort (=-=-=-=-=-
    vector<int> quickSorted = arr;
    auto startQuick = high_resolution_clock::now();
    quickSortArr(quickSorted, 0, quickSorted.size() - 1);
    auto stopQuick = high_resolution_clock::now();
    auto timeQuick = duration_cast<microseconds>(stopQuick - startQuick);

    // =-=-=-=-=-) Merge Sort (=-=-=-=-=-
    vector<int> mergeSorted = arr;
    auto startMerge = high_resolution_clock::now();
    mergeSortArr(mergeSorted, 0, mergeSorted.size() - 1);
    auto stopMerge = high_resolution_clock::now();
    auto timeMerge = duration_cast<microseconds>(stopMerge - startMerge);

    cout << "\nQuick Sort:\n";
    for(int num : quickSorted) cout << num << " ";
    cout << "\nQuick Sort runTime: " << timeQuick.count() << " ms\n";

    cout << "\nMerge Sort:\n";
    for(int num : mergeSorted) cout << num << " ";
    cout << "\nMerge Sort runTime: " << timeMerge.count() << " ms\n";

    cout << "\nEnter elements to search: ";
    cin >> searchKey;

    // =-=-=-=-=-) Binary Search (=-=-=-=-=-
    auto startBinary = high_resolution_clock::now();
    int binaryResult = binarySearchArr(mergeSorted, searchKey);
    auto stopBinary = high_resolution_clock::now();
    auto timeBinary = duration_cast<microseconds>(stopBinary - startBinary);

    // =-=-=-=-=-) Exponential Search (=-=-=-=-=-
    auto startExponential = high_resolution_clock::now();
    int exponentialResult = exponentialSearchArr(mergeSorted, searchKey);
    auto stopExponential = high_resolution_clock::now();
    auto timeExponential = duration_cast<microseconds>(stopExponential - startExponential);

    cout << "\nBinary Search Result: ";
    if(binaryResult != -1) cout << "Found at index " << binaryResult;
    else cout << "Not Found";
    cout << " | Time: " << timeBinary.count() << " ms";

    cout << "\nExponential Search Result: ";
    if(exponentialResult != -1) cout << "Found";
    else cout << "Not Found";
    cout << " | Time: " << timeExponential.count() << " ms\n";

    return 0;
}
