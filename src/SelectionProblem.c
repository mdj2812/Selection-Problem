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
#define	USE_BUBBLE_SORT 0
#define	USE_MERGE_SORT 1
#define USE_QUICK_SORT 1

#define N (1000000)
#define K (N / 2)

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Internal function declaration
 ******************************************************************************/
static uint32_t bubbleSortSelect(void);
static uint32_t mergeSortSelect(void);
static uint32_t quickSortSelect(void);

static void generateRandomNumberTable(uint32_t* nt, const uint32_t len);
static int cmpfunc(const void * a, const void * b);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static unsigned int table[N];
static unsigned int sortTable[N];

/*******************************************************************************
 * Public function
 ******************************************************************************/
int main() {
	struct timeb start, end;
	uint32_t diff;
	uint32_t result = 0;
	uint32_t i = 0;

	generateRandomNumberTable(table, N);

	// TODO: add operation here
#if USE_BUBBLE_SORT
	for (i = 0; i< N; i++) {
		sortTable[i] = table[i];
	}

	ftime(&start);

	result = bubbleSortSelect();

	ftime(&end);
	diff = (uint32_t) (1000.0 * (end.time - start.time)
			+ (end.millitm - start.millitm));

	printf("bubbleSortSelect took %u milliseconds\r\n", diff);
	printf("The %dth biggest number is: %d\r\n", K, result);
#endif

#if USE_MERGE_SORT
	for (i = 0; i< N; i++) {
		sortTable[i] = table[i];
	}

	ftime(&start);

	result = mergeSortSelect();

	ftime(&end);
	diff = (uint32_t) (1000.0 * (end.time - start.time)
			+ (end.millitm - start.millitm));

	printf("mergeSortSelect took %u milliseconds\r\n", diff);
	printf("The %dth biggest number is: %d\r\n", K, result);
#endif

#if USE_QUICK_SORT
	for (i = 0; i< N; i++) {
		sortTable[i] = table[i];
	}

	ftime(&start);

	result = quickSortSelect();

	ftime(&end);
	diff = (uint32_t) (1000.0 * (end.time - start.time)
			+ (end.millitm - start.millitm));

	printf("quickSortSelect took %u milliseconds\r\n", diff);
	printf("The %dth biggest number is: %d\r\n", K, result);
#endif

	return EXIT_SUCCESS;
}

/*******************************************************************************
 * Internal function
 ******************************************************************************/
#pragma GCC diagnostic ignored "-Wunused-function"
static uint32_t bubbleSortSelect(void) {
	BubbleSort_Desc(sortTable, N);

	return sortTable[K - 1];
}

static uint32_t mergeSortSelect(void) {
	MergeSort(sortTable, 0, N - 1);

	return sortTable[N - K];
}

static uint32_t quickSortSelect(void) {
	qsort(sortTable, N, sizeof(unsigned int), cmpfunc);

	return sortTable[N - K];
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
	return (*(int*) a - *(int*) b);
}

