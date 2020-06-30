// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <ctime>
#include <string>
#include <map>

using namespace std;

void merge(vector<int>& vec, const int l1, const int r1, const int l2, const int r2);
void mergeSort(vector<int>& vec, const int l, const int r);
void merge(vector<int>& vec, int& shiftCount, const int l1, const int r1, const int l2, const int r2);
void mergeSort(vector<int>& vec, int& shiftCount, const int l, const int r);
void countShiftsForInsertionSort();

// TODO: reference additional headers your program requires here
