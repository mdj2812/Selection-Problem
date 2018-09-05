/*
 ============================================================================
 Name        : SelectionProblem.c
 Author      : Martin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BubbleSort.h"
#include "MergeSort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys\timeb.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define	USE_BUBBLE_SORT 1
#define	USE_MERGE_SORT 0
#define USE_QUICK_SORT 0

#define N (1000000)
#define K (500000)

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Internal function declaration
 ******************************************************************************/
static uint32_t bubbleSortSelect(const uint32_t len, const uint32_t index);
static uint32_t mergeSortSelect(const uint32_t len, const uint32_t index);
static uint32_t quickSortSelect(const uint32_t len, const uint32_t index);

static void generateRandomNumberTable(uint32_t* nt, const uint32_t len);
static int cmpfunc(const void * a, const void * b);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t table[N];

/*******************************************************************************
 * Public function
 ******************************************************************************/
int main() {
	struct timeb start, end;
	uint32_t diff;
	uint32_t result = 0;

	generateRandomNumberTable(table, N);

	ftime(&start);

	// TODO: add operation here
#if USE_BUBBLE_SORT
	result = bubbleSortSelect(N, K);
#elif USE_MERGE_SORT
	result = mergeSortSelect(N, K);
#elif USE_QUICK_SORT
	result = quickSortSelect(N, K);
#endif

	ftime(&end);
	diff = (uint32_t) (1000.0 * (end.time - start.time)
			+ (end.millitm - start.millitm));

	printf("Operation took %u milliseconds\r\n", diff);
	printf("The %dth biggest number is: %d", K, result);

	return EXIT_SUCCESS;
}

/*******************************************************************************
 * Internal function
 ******************************************************************************/
#pragma GCC diagnostic ignored "-Wunused-function"
static uint32_t bubbleSortSelect(const uint32_t len, const uint32_t index) {
	BubbleSort_Desc(table, len);

	return table[index - 1];
}

static uint32_t mergeSortSelect(const uint32_t len, const uint32_t index) {
	if (len > MERGESORT_SUBARRAY_MAX_LEN * 2) {
		return 0;
	}

	MergeSort(table, 0, len - 1);

	return table[len - index + 1];
}

static uint32_t quickSortSelect(const uint32_t len, const uint32_t index) {
	qsort(table, len, sizeof(uint32_t), cmpfunc);

	return table[len - index + 1];
}
#pragma GCC diagnostic pop

static void generateRandomNumberTable(uint32_t* nt, const uint32_t len) {
	srand(time(0));

	for (uint32_t i = 0; i < len; i++) {
		nt[i] = rand();
		nt[i] = (nt[i] << 16) | rand();
	}
}

static int cmpfunc(const void * a, const void * b) {
	return (*(uint32_t*) a - *(uint32_t*) b);
}

