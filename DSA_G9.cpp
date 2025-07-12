#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;




// -=-=-=-=-=-=)Function to generate n random integers(=-=-=-=-=-=-=
vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // range 0 to 999
    }
    return arr;
}





// -=-=-=-=-=-=)Quick Sort(=-=-=-=-=-=-=
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}






// -=-=-=-=-=-=)Merge Sort(=-=-=-=-=-=-=
void merge(vector<int>& arr, int left, int mid, int right) {
    int i = left, j = mid + 1;
    vector<int> temp;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[left + k] = temp[k];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}







// -=-=-=-=-=-=)Binary Search(=-=-=-=-=-=-=
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}







// -=-=-=-=-=-=)Exponential Search(=-=-=-=-=-=-=
int exponentialSearch(const vector<int>& arr, int target) {
    if (arr[0] == target) return 0;
    int i = 1;
    while (i < arr.size() && arr[i] <= target)
        i *= 2;
    int left = i / 2;
    int right = min(i, (int)arr.size() - 1);
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}







// -=-=-=-=-=-=)Display Array(=-=-=-=-=-=-=
void displayArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}






int main() {
    int n, choice, target;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> originalArray = generateRandomArray(n);

    cout << "\nGenerated Array:\n";
    displayArray(originalArray);

    vector<int> quickSortedArray = originalArray;
    auto start = high_resolution_clock::now();
    quickSort(quickSortedArray, 0, n - 1);
    auto end = high_resolution_clock::now();
    cout << "\nQuick Sorted Array:\n";
    displayArray(quickSortedArray);
    cout << "Quick Sort Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    vector<int> mergeSortedArray = originalArray;
    start = high_resolution_clock::now();
    mergeSort(mergeSortedArray, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "\nMerge Sorted Array:\n";
    displayArray(mergeSortedArray);
    cout << "Merge Sort Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    cout << "\nEnter element to search: ";
    cin >> target;

    // -=-=-=-=-=-=)Binary Search(=-=-=-=-=-=-=
    start = high_resolution_clock::now();
    int indexB = binarySearch(mergeSortedArray, target);
    end = high_resolution_clock::now();
    if (indexB != -1)
        cout << "Binary Search: Element found at index " << indexB << "\n";
    else
        cout << "Binary Search: Element not found.\n";
    cout << "Binary Search Time: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    // -=-=-=-=-=-=)Exponential Search(=-=-=-=-=-=-=
    start = high_resolution_clock::now();
    int indexE = exponentialSearch(mergeSortedArray, target);
    end = high_resolution_clock::now();
    if (indexE != -1)
        cout << "Exponential Search: Element found at index " << indexE << "\n";
    else
        cout << "Exponential Search: Element not found.\n";
    cout << "Exponential Search Time: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    return 0;
}