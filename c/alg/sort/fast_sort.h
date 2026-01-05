#ifndef FAST_SORT_H
#define FAST_SORT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sorts an array of double precision floats in ascending order.
 * Optimized for small to medium sized arrays (e.g. < 1000 items).
 * 
 * @param arr The array of doubles to sort.
 * @param n   The number of elements in the array.
 */
void fast_sort(double* arr, int n);

#ifdef __cplusplus
}
#endif

#endif // FAST_SORT_H