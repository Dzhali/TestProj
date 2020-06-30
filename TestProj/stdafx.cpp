// stdafx.cpp : source file that includes just the standard includes
// TestProj.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//
//#include <algorithm>
//#include <bits/stdc++.h>
//#include <initializer_list>
//#include <string>
//
//using namespace std;
//
//// Complete the organizingContainers function below.
//string organizingContainers(vector<vector<int>> container) {
//   const int n = container.size();
//   vector<unsigned long long int> columnSum(n, 0);
//   vector<unsigned long long int> linesSum(n, 0);
//
//   for (int i = 0; i < n; i++) {
//      for (int j = 0; j < n; j++) {
//         linesSum[i] += (unsigned long long int)container[i][j];
//         columnSum[j] += (unsigned long long int)container[i][j];
//      }
//   }
//
//   unsigned long long int maxLineSum = 0;
//
//   for_each(linesSum.begin(), linesSum.end(),
//      [&maxLineSum](unsigned long long int &elem) {maxLineSum = max(maxLineSum, elem);
//   });
//
//   //  const int maxLineSum =
//   //  max(initializer_list<int>(linesSum, &(linesSum[n-1])));
//
//   vector<unsigned long long int> checkArr(maxLineSum + 1, 0);
//
//   for (int i = 0; i < n; i++) {
//      checkArr[linesSum[i]] += 1;
//   }
//
//   for (int i = 0; i < n; i++) {
//      if (columnSum[i] >= checkArr.size()) {
//         return "Impossible";
//      }
//      else {
//         checkArr[columnSum[i]] += 1;
//      }
//   }
//
//   for (int i = 0; i < checkArr.size(); i++) {
//      if ((checkArr[i] & 1) == 1) // if odd
//      {
//         return "Impossible";
//      }
//   }
//
//   return "Possible";
//}
