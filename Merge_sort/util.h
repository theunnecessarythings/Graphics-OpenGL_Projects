/*
 * util.h
 *
 *  Created on: 12-Sep-2017
 *      Author: sree
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <random>
#include <helper_cuda.h>
#include <sys/time.h>
#include <climits>
#include <algorithm>

const int range_from = 0;
const int range_to = INT_MAX;
std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> distr(range_from, range_to);

#define min(a, b) (a < b ? a : b)

int len;
//get the time in microseconds
timeval tStart;
int tm() {
	timeval tEnd;
	gettimeofday(&tEnd, 0);
	int t = (tEnd.tv_sec - tStart.tv_sec) * 1000000 + tEnd.tv_usec
			- tStart.tv_usec;
	tStart = tEnd;
	return t;
}

// read data
typedef struct {
	int v;
	void* next;
} LinkNode;

//generate data
int genArray(int** arr) {
	tm();
	int v, size = 0;
	LinkNode* node = 0;
	LinkNode* first = 0;
	while (len--) {
		v = distr(generator);
		LinkNode* next = new LinkNode();
		next->v = v;
		if (node)
			node->next = next;
		else
			first = next;
		node = next;
		size++;
	}

	if (size) {
		*arr = new int[size];
		LinkNode* node = first;
		int i = 0;
		while (node) {
			(*arr)[i++] = node->v;
			node = (LinkNode*) node->next;
		}

	}

	return size;
}

// calculate the id of the current thread
__device__ unsigned int getIdx(dim3* threads, dim3* blocks) {
	int x;
	return threadIdx.x + threadIdx.y * (x = threads->x) + threadIdx.z * (x *=
			threads->y) + blockIdx.x * (x *= threads->z) + blockIdx.y * (x *=
			blocks->z) + blockIdx.z * (x *= blocks->y);
}

void display(int *data, int size) {
	std::sort(data, data + size);
	for(int i = 0; i < size; i++)
		std::cout << data[i] << "\n";
}

#endif /* UTIL_H_ */
