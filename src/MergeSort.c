/*
 * MergeSort.c
 *
 *  Created on: 4 sept. 2018
 *      Author: MA
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MergeSort.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Internal function declaration
 ******************************************************************************/
static void merge(uint32_t* A, const uint32_t p, const uint32_t q,
		const uint32_t r);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t L[MERGESORT_SUBARRAY_MAX_LEN], R[MERGESORT_SUBARRAY_MAX_LEN];

/*******************************************************************************
 * Public function
 ******************************************************************************/
void MergeSort(uint32_t* nt, const uint32_t p, const uint32_t r) {
	if (p < r) {
		uint32_t q = (p + r) / 2;

		MergeSort(nt, p, q);
		MergeSort(nt, q + 1, r);
		merge(nt, p, q, r);
	}
}

/*******************************************************************************
 * Internal function
 ******************************************************************************/
static void merge(uint32_t* A, const uint32_t p, const uint32_t q,
		const uint32_t r) {
	uint32_t n1 = q - p + 1;
	uint32_t n2 = r - q;
	uint32_t i = 0, j = 0, k = 0;

	for (i = 0; i < n1; i++) {
		L[i] = A[p + i];
	}

	for (j = 0; j < n2; j++) {
		R[j] = A[q + j + 1];
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = p; // Initial index of merged subarray

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	 are any */
	while (i < n1) {
		A[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	 are any */
	while (j < n2) {
		A[k] = R[j];
		j++;
		k++;
	}
}
