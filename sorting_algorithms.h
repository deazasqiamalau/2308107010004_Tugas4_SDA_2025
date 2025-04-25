/**
 * sorting_algorithms.h
 * Implementation of various sorting algorithms for performance analysis
 */

 #ifndef SORTING_ALGORITHMS_H
 #define SORTING_ALGORITHMS_H
 
 #include <stdlib.h>
 #include <string.h>
 
 /**
  * Bubble Sort
  * Repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.
  * Complexity: O(n²) time, O(1) space
  */
 void bubble_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *)) {
     unsigned char *a = (unsigned char *)arr;
     unsigned char *temp = (unsigned char *)malloc(size);
     
     for (size_t i = 0; i < n - 1; i++) {
         for (size_t j = 0; j < n - i - 1; j++) {
             void *elem1 = (void *)(a + j * size);
             void *elem2 = (void *)(a + (j + 1) * size);
             
             if (compare(elem1, elem2) > 0) {
                 memcpy(temp, elem1, size);
                 memcpy(elem1, elem2, size);
                 memcpy(elem2, temp, size);
             }
         }
     }
     
     free(temp);
 }
 
 /**
  * Selection Sort
  * Finds the minimum element from the unsorted part and places it at the beginning.
  * Complexity: O(n²) time, O(1) space
  */
 void selection_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *)) {
     unsigned char *a = (unsigned char *)arr;
     unsigned char *temp = (unsigned char *)malloc(size);
     
     for (size_t i = 0; i < n - 1; i++) {
         size_t min_idx = i;
         
         for (size_t j = i + 1; j < n; j++) {
             void *current_min = (void *)(a + min_idx * size);
             void *current_elem = (void *)(a + j * size);
             
             if (compare(current_elem, current_min) < 0) {
                 min_idx = j;
             }
         }
         
         if (min_idx != i) {
             void *elem1 = (void *)(a + i * size);
             void *elem2 = (void *)(a + min_idx * size);
             
             memcpy(temp, elem1, size);
             memcpy(elem1, elem2, size);
             memcpy(elem2, temp, size);
         }
     }
     
     free(temp);
 }
 
 /**
  * Insertion Sort
  * Builds sorted array one element at a time by repeatedly taking the next element
  * and inserting it into its correct position.
  * Complexity: O(n²) time, O(1) space
  */
 void insertion_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *)) {
     unsigned char *a = (unsigned char *)arr;
     unsigned char *key = (unsigned char *)malloc(size);
     
     for (size_t i = 1; i < n; i++) {
         memcpy(key, a + i * size, size);
         int j = i - 1;
         
         while (j >= 0 && compare(a + j * size, key) > 0) {
             memcpy(a + (j + 1) * size, a + j * size, size);
             j--;
         }
         
         memcpy(a + (j + 1) * size, key, size);
     }
     
     free(key);
 }
 
 /**
  * Helper function for merge sort - merges two subarrays
  */
 void merge(unsigned char *arr, size_t l, size_t m, size_t r, size_t size, int (*compare)(const void *, const void *)) {
     size_t i, j, k;
     size_t n1 = m - l + 1;
     size_t n2 = r - m;
     
     // Create temporary arrays
     unsigned char *L = (unsigned char *)malloc(n1 * size);
     unsigned char *R = (unsigned char *)malloc(n2 * size);
     
     // Copy data to temporary arrays
     for (i = 0; i < n1; i++)
         memcpy(L + i * size, arr + (l + i) * size, size);
     
     for (j = 0; j < n2; j++)
         memcpy(R + j * size, arr + (m + 1 + j) * size, size);
     
     // Merge the temporary arrays back
     i = 0;
     j = 0;
     k = l;
     
     while (i < n1 && j < n2) {
         if (compare(L + i * size, R + j * size) <= 0) {
             memcpy(arr + k * size, L + i * size, size);
             i++;
         } else {
             memcpy(arr + k * size, R + j * size, size);
             j++;
         }
         k++;
     }
     
     // Copy remaining elements of L if any
     while (i < n1) {
         memcpy(arr + k * size, L + i * size, size);
         i++;
         k++;
     }
     
     // Copy remaining elements of R if any
     while (j < n2) {
         memcpy(arr + k * size, R + j * size, size);
         j++;
         k++;
     }
     
     free(L);
     free(R);
 }
 
 /**
  * Helper function for merge sort - recursive implementation
  */
 void merge_sort_recursive(unsigned char *arr, size_t l, size_t r, size_t size, int (*compare)(const void *, const void *)) {
     if (l < r) {
         size_t m = l + (r - l) / 2;
         
         merge_sort_recursive(arr, l, m, size, compare);
         merge_sort_recursive(arr, m + 1, r, size, compare);
         
         merge(arr, l, m, r, size, compare);
     }
 }
 
 /**
  * Merge Sort
  * Divides the array into halves, sorts them recursively, then merges them.
  * Complexity: O(n log n) time, O(n) space
  */
 void merge_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *)) {
     unsigned char *a = (unsigned char *)arr;
     
     if (n > 1) {
         merge_sort_recursive(a, 0, n - 1, size, compare);
     }
 }
 
 /**
  * Helper function for quick sort - partitions the array around a pivot
  */
 size_t partition(unsigned char *arr, size_t low, size_t high, size_t size, int (*compare)(const void *, const void *)) {
     // Using the last element as pivot
     void *pivot = (void *)(arr + high * size);
     size_t i = low - 1;
     unsigned char *temp = (unsigned char *)malloc(size);
     
     for (size_t j = low; j < high; j++) {
         void *current = (void *)(arr + j * size);
         
         if (compare(current, pivot) <= 0) {
             i++;
             
             // Swap arr[i] and arr[j]
             void *elem1 = (void *)(arr + i * size);
             void *elem2 = (void *)(arr + j * size);
             
             memcpy(temp, elem1, size);
             memcpy(elem1, elem2, size);
             memcpy(elem2, temp, size);
         }
     }
     
     // Swap arr[i+1] and arr[high] (pivot)
     void *elem1 = (void *)(arr + (i + 1) * size);
     void *elem2 = (void *)(arr + high * size);
     
     memcpy(temp, elem1, size);
     memcpy(elem1, elem2, size);
     memcpy(elem2, temp, size);
     
     free(temp);
     return i + 1;
 }
 
 /**
  * Helper function for quick sort - recursive implementation
  */
 void quick_sort_recursive(unsigned char *arr, size_t low, size_t high, size_t size, int (*compare)(const void *, const void *)) {
     if (low < high) {
         size_t pi = partition(arr, low, high, size, compare);
         
         // Avoid underflow for pi = 0
         if (pi > 0) {
             quick_sort_recursive(arr, low, pi - 1, size, compare);
         }
         quick_sort_recursive(arr, pi + 1, high, size, compare);
     }
 }
 
 /**
  * Quick Sort
  * Selects a 'pivot' element and partitions the array around the pivot.
  * Complexity: O(n log n) average, O(n²) worst case time, O(log n) space
  */
 void quick_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *)) {
     unsigned char *a = (unsigned char *)arr;
     
     if (n > 1) {
         quick_sort_recursive(a, 0, n - 1, size, compare);
     }
 }
 
 /**
  * Shell Sort
  * Variation of insertion sort that allows exchanges of elements that are far apart.
  * Uses a gap sequence to determine spacing between compared elements.
  * Complexity: Depends on gap sequence, generally O(n log² n) time, O(1) space
  */
 void shell_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *)) {
     unsigned char *a = (unsigned char *)arr;
     unsigned char *temp = (unsigned char *)malloc(size);
     
     // Using Knuth's sequence: h = h*3 + 1
     size_t h = 1;
     while (h < n / 3) {
         h = 3 * h + 1;
     }
     
     while (h >= 1) {
         for (size_t i = h; i < n; i++) {
             memcpy(temp, a + i * size, size);
             size_t j = i;
             
             while (j >= h && compare(a + (j - h) * size, temp) > 0) {
                 memcpy(a + j * size, a + (j - h) * size, size);
                 j -= h;
             }
             
             memcpy(a + j * size, temp, size);
         }
         
         h /= 3;
     }
     
     free(temp);
 }
 
 #endif // SORTING_ALGORITHMS_H