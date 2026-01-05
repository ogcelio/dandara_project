#include "fast_sort.h"

// Threshold to switch to insertion sort. 
// Small arrays are sorted faster with simple insertion sort due to lower overhead.
#define INSERTION_SORT_THRESHOLD 16

static void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

static void insertion_sort(double* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        double key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static int median_of_three(double* arr, int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] < arr[left]) swap(&arr[left], &arr[mid]);
    if (arr[right] < arr[left]) swap(&arr[left], &arr[right]);
    if (arr[right] < arr[mid]) swap(&arr[mid], &arr[right]);
    return mid;
}

static void quick_sort_recursive(double* arr, int left, int right) {
    while (left < right) {
        // Switch to insertion sort for small partitions
        if (right - left < INSERTION_SORT_THRESHOLD) {
            insertion_sort(arr, left, right);
            break;
        }

        // Median-of-three pivot selection
        // This sorts left, mid, right indices to ensure a good pivot
        median_of_three(arr, left, right);
        
        // Pivot is now the median value, located at mid
        double pivot = arr[left + (right - left) / 2];
        
        int i = left;
        int j = right;
        
        // Standard partition
        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        // Tail call optimization: recurse on the smaller partition
        if (j - left < right - i) {
            quick_sort_recursive(arr, left, j);
            left = i;
        } else {
            quick_sort_recursive(arr, i, right);
            right = j;
        }
    }
}

void fast_sort(double* arr, int n) {
    if (n > 1) {
        quick_sort_recursive(arr, 0, n - 1);
    }
}