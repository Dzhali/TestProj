// TestSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void mergeSort(vector<int>& vec, const int l, const int r)
{
   if (l < r)
   {
      const int middle = (l + r) / 2;
      mergeSort(vec, l, middle);
      mergeSort(vec, middle + 1, r);
      std::merge(&vec[0] + l, &vec[0] + middle, &vec[0] + (middle + 1), &vec[0] + r,vec.begin());
  
      //merge(vec, l, middle, middle + 1, r);
   }
}

void merge(vector<int>&  vec, const int l1, const int r1, const int l2, const int r2)
{
   vector<int> vecTmp;
   vecTmp.reserve(r2 - l1 + 1);

   int iter1 = l1;
   int iter2 = l2;

   while (iter1 <= r1 && iter2 <= r2)
   {
      if (vec[iter1] <= vec[iter2])
      {
         vecTmp.push_back(vec[iter1]);
         ++iter1;
      }
      else
      {
         vecTmp.push_back(vec[iter2]);
         ++iter2;
      }
   }


   while (iter1 <= r1)
   {
      vecTmp.push_back(vec[iter1]);
      ++iter1;
   }
   while (iter2 <= r2)
   {
      vecTmp.push_back(vec[iter2]);
      ++iter2;
   }
   int j = 0;
   for (int i = l1; i <= r2; ++i, ++j)
   {
      vec[i] = vecTmp[j];
   }

}


void mergeSort(vector<int>& vec, int& shiftCount, const int l, const int r)
{
   if (r > l)
   {
      const int middle = (l + r) / 2;
      mergeSort(vec, shiftCount, l, middle);
      mergeSort(vec, shiftCount, middle + 1, r);
      merge(vec, shiftCount, l, middle, middle + 1, r);
   }
}
void merge(vector<int>& vec, int& shiftCount, const int l1, const int r1, const int l2, const int r2)
{
   vector<int> mergedTmp;
   mergedTmp.reserve(r2 - l1 + 1);

   int iter1 = l1;
   int iter2 = l2;
   
   while (iter1 <= r1 && iter2 <= r2)
   {
      if (vec[iter1] <= vec[iter2])
      {
         mergedTmp.push_back(vec[iter1]);
         ++iter1;
      }
      else
      {
         mergedTmp.push_back(vec[iter2]);
         ++iter2;
         shiftCount += r1 - iter1 + 1;
      }
   }

   while (iter1 <= r1)
   {
      mergedTmp.push_back(vec[iter1]);
      ++iter1;
   }

   while (iter2 <= r2)
   {
      mergedTmp.push_back(vec[iter2]);
      ++iter2;
   }

   int j = 0;
   for (int i = l1; i <= r2; ++i)
   {
      vec[i] = mergedTmp[j];
      ++j;
   }
}
void countShiftsForInsertionSort()
{
   vector<int> vec = { 1, 1 ,1 ,2, 2, };
   int shiftCount = 0;
   mergeSort(vec, /*shiftCount,*/ 0, vec.size() - 1);

   for (int& elem : vec)
   {
      cout << elem << ' ';
   }

   cout << endl << shiftCount;
   cout << endl;
}

int squaredComplexitySearch(const vector<int>& originalVec, const vector<int>& shuffledVec)
//можно улучшить:
//1) сортировкой второго массива квик сортом или мердж сортом так что поиск станет log(n), а общая сложность nlog(n)
//2) отсортировать оба массива и идти параллельно вдоль каждого пока не встретим не равные элементы. Также сложность nlog(n), но будет работать корректно также для случая с неуникальными элементами
{
   const int start = clock();
   bool found = false;
   int result = -1;
   for (const int& original : originalVec) 
   {
      found = false;
      for (const int& shuffle : shuffledVec)
      {
         if (shuffle == original)//found elem
         {
            found = true;
            break;
         }
      }

      if (!found)
      {
       result = original;
       break;
      }
   }
   const int end = clock();
   const int time = (end - start) / CLOCKS_PER_SEC;
   cout << "O(n^2) : " << time << endl;
   
   return result;
}

int linearComplexitySearch(const vector<int>& originalVec, const vector<int>& shuffledVec)//hash table
//улучшить сразу декриментя элементы из ориджинал век на втором проходе. 
//как только получим элемент меньше 0, то значит данный ключ и есть недостающий
//так не будет необходимости во втором проходе
{
   const int start = clock();
   unordered_map<int,int> hashArray;

   int result = -1;
   for (const int& a : originalVec)
   {
      hashArray[a] += 1;
   }
   for (const int& a : shuffledVec)
   {
      hashArray[a] += 1;
   }

   bool found = false;
   for (unordered_map<int, int>::iterator iter = hashArray.begin();
      !found && iter != hashArray.end(); ++iter)
   {
      if ((iter->second & 1) % 2 == 1) //found odd element
      {
         result = iter->first;
         found = true;
      }
   }

   const int end = clock();
   const int time = (end - start) / CLOCKS_PER_SEC;
   cout << "O(n) : " << time << endl;

   return result;
}

int bestLinearSearch(const vector<int>& originalVec, const vector<int>& shuffledVec) // XOR 
{
   const int start = clock();
   int result = 0;

   for (const int& a : originalVec)
   {
      result ^= a;
   }

   for (const int& a : shuffledVec)
   {
      result ^= a;
   }

   const int end = clock();
   const int time = (end - start) / CLOCKS_PER_SEC;
   cout << "O(n) : " << time << endl;
   return result;
}

int bestLinearCommutativSum(const vector<int>& originalVec, const vector<int>& shuffledVec)
{
   const int start = clock();

   int result = 0;
   const int size = shuffledVec.size();
   for (int i = 0; i < size; ++i)
   {
      result += (originalVec[i] - shuffledVec[i]);
   }
   result += originalVec[size];

   const int end = clock();
   const int time = (end - start) / CLOCKS_PER_SEC;
   cout << "O(n) : " << time << endl;
   return result;
}

int lostElementSearch()
{
   const int size = 10000000;
   const int interval = 100;
   vector<int> originalVec(size,0);
 
   for (int& a : originalVec)
   {
      a = rand() % interval;
   }  
   
   vector<int> shuffledVec(originalVec.begin(), originalVec.end() - 1);
   random_shuffle(shuffledVec.begin(), shuffledVec.end());

   const int res = linearComplexitySearch(originalVec, shuffledVec);
   //const int res2 = squaredComplexitySearch(originalVec, shuffledVec);
   const int res3 = bestLinearSearch(originalVec, shuffledVec);
   const int res4 = bestLinearCommutativSum(originalVec, shuffledVec);
   return res3;

   //// RES  ////
   /*Interval 100          10000    */
   /*N        1000000      1.000.000       10.000.000   */
   /*O(n)     7-8 sec      10 sec         92            */
   /*O(n^2)   19-20 sec    1854 sec                   */
   /*XOR                                  3            */
   /*Comutat                              4            */
}
int main()
{
	
	std::cout<<"First commit\n";
	std::cout<<"Second commit\n";
	std::cout<<"3d that will not go to commit\n";
	
   char a1;
   char b =  '\0';
   int check = atoi(&a1);
   check = atoi(&b);
   string g;

   vector<int> vec = {10,4,22,17,-1,0,0,3};
   //1.  sort()
   //2.  stable_sort()
   //3. make_heap(vec.begin(), vec.end());
   // sort_heap(vec.begin(), vec.end());  (in pair with make hip)
   //

   map<string, int> strMap;
   strMap.insert(make_pair("a", 1));
   strMap.erase("a");
   strMap.insert({ "abc", 123 });
   strMap["ab"] = 12;
   typedef map<string, int>::iterator mapIter;
   mapIter foundIt = strMap.find("abc");
   if (strMap.end() != foundIt)
   {
      int& res = (*foundIt).second;
   }
   using mapIterC11 = map<string, int>::iterator;

   for (mapIterC11 mapIterC11Inst = strMap.begin(); mapIterC11Inst != strMap.end(); ++mapIterC11Inst)
   {
      cout << mapIterC11Inst->first;
      cout << mapIterC11Inst->second;
   }

   ////
   struct equalChecker
   {
      bool operator()(const string& first, const string& second) const
      {
         return first == second;        
      }
   };
   unordered_multimap<string, string,std::hash<string>,equalChecker> strMultiMap;
   strMultiMap.insert({ "Mimi","Mi" });
   strMultiMap.insert({ "Mimi", "Mish" });
   strMultiMap.insert({ "Cat", "No" });
   strMultiMap.insert({ "Ms", "No" });
   std::pair<unordered_multimap<string, string>::iterator, unordered_multimap<string, string>::iterator> mimiRange
               = strMultiMap.equal_range("Mimi");

   unordered_map<string, int> hash;
   hash["first"] = 1;
   hash.insert({ "sec", 2 });
   hash.insert({ "tri", 3 });
   hash["first"] = 11;
   hash.erase("sec");





   lostElementSearch();
   int a;
   cin >> a;
   return 0;
}

