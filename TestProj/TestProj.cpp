// TestProj.cpp : Defines the entry point for the console application.
//
//проверить также в первом случае отбрасывается конст для Т в указателе как и в ссылках
#include "stdafx.h"
#include <unordered_map>
#include <set>

/////////// template

template<typename First, typename Second, typename Third>
void TemplateFunc(Second p1, Third p2)
{
   if (p2)
   {
      First result = (First)0;
   }
}
template<typename First, typename Second, typename Third>
void TemplateFunc2(Second p1)
{
   if (p1)
   {
      First result = (First)0;
   }
}

template<typename First, typename Second, typename Third>
void TemplateFunc2_2(Third p1)
{
   First result;
   if (p1)
   {
      result = (First)0;
   }
}

template<typename First, typename Second, typename Third>
First TemplateFunc3(Third p1)
{
   First result;
   if (p1)
   {
      result = (First)0;
   }
   return result;
}
//////////// template

mutex mtx;
mutex mtx2;
void Func(char a)
{
   cout << a << endl;
}

void sharedPrint(string thrd, int n)
{
   std::lock(mtx2, mtx);
   lock_guard<mutex> lock_gard(mtx,std::adopt_lock);
   lock_guard<mutex> lock_gard2(mtx2, std::adopt_lock);
   
   //mtx.lock();
   cout << thrd << " "<< n <<endl;
   //mtx.unlock();
}

void sharedPrint2(string thrd, int n)
{
   std::lock(mtx, mtx2);
   lock_guard<mutex> lock_gard2(mtx2, std::adopt_lock);
   lock_guard<mutex> lock_gard(mtx, std::adopt_lock);
   //mtx.lock();
   cout << thrd << " " << n << endl;
   //mtx.unlock();
}
void Function(string thrd)
{
   for (int i = 0; i < 100; i++)
      sharedPrint(thrd, i);
}

void funcToBind(int n, char str[], int size, int& res)
{
   str = "NTR"; //won't change after function exit 
   //str[0] = 'N';  //will change after function exit
   //str[2] = 'R';
   cout << str << endl;
   res = size - n;
}

// Complete the organizingContainers function below.
string organizingContainers(vector<vector<int>> container) 
{
   const int n = container.size();
   vector<uint64_t> columnSum(n, 0);
   vector<uint64_t> linesSum(n, 0);

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         linesSum[i] += (uint64_t)container[i][j];
         columnSum[j] += (uint64_t)container[i][j];
      }
   }

   uint64_t maxLineSum = 0;

   for_each(linesSum.begin(), linesSum.end(),
      [&maxLineSum](uint64_t &elem) {maxLineSum = max(maxLineSum, elem);
   });

   unordered_map<uint64_t, uint8_t> checkArr;

   for (int i = 0; i < n; i++) 
   {
      checkArr[linesSum[i]] += 1;
   }

   for (int i = 0; i < n; i++) 
   {
       checkArr[columnSum[i]] += 1;
   }

   for (unordered_map<uint64_t, uint8_t>::iterator iter = checkArr.begin();
         iter!= checkArr.end(); ++iter)
   {
      if ((iter->second & 1) == 1) // if odd
      {
         return "Impossible";
      } 
   }

   return "Possible";
}
// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles)
{
   struct SEquation
   {
      int k;
      int b;
   };
   //////----------------  1,2 ------------------- //////////
   //(-1,1), k = -1
   const int leftEqPointX = c_q - 1;
   const int leftEqPointY = r_q + 1;
   const int leftK = -1;
   const int leftB = ((r_q + leftEqPointY) - leftK*(c_q + leftEqPointX)) / 2;
   const SEquation leftEquation = { leftK, leftB };

   //(1,1), k = 1
   const int rightEqPointX = c_q + 1;
   const int rightEqPointY = r_q + 1;
   const int rightK = 1;
   const int rightB = ((r_q + rightEqPointY) - rightK*(c_q + rightEqPointX)) / 2;
   const SEquation rightEquation = { rightK, rightB };

   vector<SEquation> diagonalsEquations = { leftEquation, rightEquation };

   //////-------------  3 ищем пересечение с каждой из осей ------------ //////////

   vector<int> edgeValues = { 1, n };
   struct SPoint
   {
      int x;
      int y;

      bool operator==(const SPoint& p1)
      {
         return (this->x == p1.x && this->y == p1.y);
      }
   };
   vector<vector<SPoint>> diagonalIntersections;
   diagonalIntersections.resize(diagonalsEquations.size());

   for (int eqIndex = 0; eqIndex < diagonalsEquations.size(); eqIndex++)
   {
      for (int i = 0; i < edgeValues.size(); i++)
      {
         const int y = diagonalsEquations[eqIndex].k * edgeValues[i] +
            diagonalsEquations[eqIndex].b;
         const int x = (edgeValues[i] - diagonalsEquations[eqIndex].b) /
            diagonalsEquations[eqIndex].k;

         const SPoint p1 = { edgeValues[i], y };
         if (y > 0 && y <= n
            && diagonalIntersections[eqIndex].end()
            == std::find(diagonalIntersections[eqIndex].begin(), diagonalIntersections[eqIndex].end(), p1))
         {
            diagonalIntersections[eqIndex].push_back({ edgeValues[i], y });
         }

         const SPoint p2 = { x, edgeValues[i]};
         if (x > 0 && x <= n && y!=edgeValues[i]
            && diagonalIntersections[eqIndex].end()
            == std::find(diagonalIntersections[eqIndex].begin(), diagonalIntersections[eqIndex].end(), p2))
         {
            diagonalIntersections[eqIndex].push_back({ x, edgeValues[i] });
         }
      }
   }

   //////-------------  4 считаем клетки в диагоналях ------------ /////////////
   int resultNumOfCells = 0;
   for (int i = 0; i<diagonalIntersections.size(); i++)
   {
      //assert(diagonalIntersections[i].size() == 2)

      if (diagonalIntersections[i].size() == 2)
      {
         const int dist1 = abs(diagonalIntersections[i][0].x - diagonalIntersections[i][1].x);
         const int dist2 = abs(diagonalIntersections[i][0].y - diagonalIntersections[i][1].y);

         //assert(dist1 == dist2)

         if (dist1 == dist2)
         {
            resultNumOfCells += dist1;
         }
      }
      else
      {
         cout << "WRONG\n";

      }
   }

   resultNumOfCells += 2 * (n - 1); //добавили клетки по вертикали и горизонтали

                                    //////-------------  5 отнимаем припятствия ------------ ////////

   int maxLeft = 0;
   int maxRight = 0;
   int maxUp = 0;
   int maxDown = 0;

   int maxUpLeft = 0;
   int maxUpRight = 0;
   int maxDownRight = 0;
   int maxDownLeft = 0;

   for (int i = 0; i<obstacles.size(); i++)
   {
      const int obstX = obstacles[i][1];
      const int obstY = obstacles[i][0];

      if (obstX == c_q) // vertical line
      {
         if (obstY > r_q)
         {
            maxUp = std::max(maxUp, ((n - obstY) + 1));
         }
         else if (obstY < r_q)
         {
            maxDown = std::max(maxDown, obstY);
         }
      }
      else if (obstY == r_q) //horizontal
      {
         if (obstX > c_q)
         {
            maxRight = std::max(maxRight, ((n - obstX) + 1));
         }
         else if (obstX < c_q)
         {
            maxLeft = std::max(maxLeft, obstX);
         }
      }
      else//work with diagonal variant
      {
         bool found = false;
         for (int eqIndx = 0; !found && eqIndx<diagonalsEquations.size(); eqIndx++)
         {
            const SEquation& currDiagonal = diagonalsEquations[eqIndx];

            const int obsValueInDiagonal = currDiagonal.k*obstX + currDiagonal.b;

            if (obstY == obsValueInDiagonal)
            {
               found = true;
               // 1понять с какими пересекается++
               //координату отличную от координаты оси пересечения брать за число которое нужно отнимать
               //
               for (int pointIndex = 0; pointIndex < 2; pointIndex++) {
                  const SPoint &interPoint =
                     diagonalIntersections[eqIndx][pointIndex];

                  if ((1 == interPoint.x/* && 1 != interPoint.y*/) &&
                     (obstX < c_q)) // OY
                  {
                     if (obstY > r_q) {
                        maxUpLeft = std::max(maxUpLeft, obstX);
                     }
                     else {
                        maxDownLeft = std::max(maxDownLeft, obstX);
                     }

                  }
                  else if ((1 == interPoint.y /*&& 1 != interPoint.x*/) &&
                     (obstY < r_q)) // OX
                  {
                     if (obstX > c_q) {
                        maxDownRight = std::max(maxDownRight, obstY);
                     }
                     else {
                        maxDownLeft = std::max(maxDownLeft, obstY);
                     }
                  }
                  else if ((n == interPoint.y/* && n != interPoint.x*/) &&
                     (obstY > r_q)) // NX
                  {
                     if (obstX > c_q) {
                        maxUpRight = std::max(maxUpRight, (n - obstY) + 1);
                     }
                     else {
                        maxUpLeft = std::max(maxUpLeft, (n - obstY) + 1);
                     }
                  }
                  else if ((n == interPoint.x /*&& n != interPoint.y*/) &&
                     (obstX > c_q)) // NY
                  {
                     if (obstY > r_q) {
                        maxUpRight = std::max(maxUpRight, (n - obstX) + 1);
                     }
                     else {
                        maxDownRight = std::max(maxDownRight, (n - obstX) + 1);
                     }
                  }

                  else
                  {
                     cout << "WRONG\n";

                  }
               }
            }
         }
      }
   }

   //посчитать все по диагоналям и отнять!
   resultNumOfCells -= (maxUp + maxDown + maxRight + maxLeft);
   resultNumOfCells -= (maxUpLeft + maxUpRight + maxDownLeft + maxDownRight);


   return resultNumOfCells;
}

vector<string> split_string(string input_string) {
   string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
      return x == y && x == ' ';
   });

   input_string.erase(new_end, input_string.end());

   while (input_string[input_string.length() - 1] == ' ') {
      input_string.pop_back();
   }

   vector<string> splits;
   char delimiter = ' ';

   size_t i = 0;
   size_t pos = input_string.find(delimiter);

   while (pos != string::npos) {
      splits.push_back(input_string.substr(i, pos - i));

      i = pos + 1;
      pos = input_string.find(delimiter, i);
   }

   splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

   return splits;
}

//передавать - н, факториал бейз - число до которого опускаемся в рекурсии - в обычном случае это нуль
//возврат - бейз на котором мы остановились возвращаться из рекурсии, частичный факториал

uint64_t fact(uint64_t N, uint64_t baseToStopAt, uint64_t& baseReturnWasStoped)
{
   if (N < 0) // если пользователь ввел отрицательное число
      return 0; // возвращаем ноль
   if (N == baseToStopAt) // если пользователь ввел ноль,
      return 1; // возвращаем факториал от нуля - не удивляетесь, но это 1 =)
   else // Во всех остальных случаях
   {
      const std::uint64_t factRes = fact(N - 1, baseToStopAt, baseReturnWasStoped);
      const std::uint64_t possibleFactRes = N * factRes;
      const std::uint64_t devider = possibleFactRes / factRes;
      if (devider == N)
      {
         return possibleFactRes; // делаем рекурсию.
      }
      else
      {
         if (0 == baseReturnWasStoped)
         {
            baseReturnWasStoped = N;
         }
         return factRes;
      }
   }
}

int shortPalindrome(string s)
{
   unordered_multimap<char, int> hashTable;
   typedef unordered_multimap<char, int>::const_iterator hashIter;
   const int size = s.size();
   for (int i = 0; i < size; ++i)
   {
      hashTable.insert({ s[i],i });
   }

   int totalPolindromeCount = 0;
   char prevKey = '0';
   for (hashIter iter = hashTable.begin(); iter != hashTable.end(); ++iter)
   {
      if (prevKey != iter->first)
      {
         prevKey = iter->first;
         std::pair<hashIter, hashIter> range = hashTable.equal_range(iter->first);

         hashIter currKeyRangeIter = range.first;
         int currRangeSize = 0;
         for (; currKeyRangeIter != range.second; ++currKeyRangeIter)
         {
            ++currRangeSize;

            hashIter nextIter = currKeyRangeIter;
            ++nextIter;

            while (nextIter != range.second) //check all pairs in main range
            {
               const int startInterval = currKeyRangeIter->second;
               const int endInterval = nextIter->second;
               
               char internalPrevKey = '0';

               for (hashIter internalIter = hashTable.begin(); //теперь ходим по всем остальным и ищем есть ли входящие 
                  internalIter != hashTable.end(); ++internalIter)
               {
                  if (internalIter->first != iter->first && internalIter->first != internalPrevKey)
                  {
                     internalPrevKey = internalIter->first;

                     std::pair<hashIter, hashIter> internalRange =
                        hashTable.equal_range(internalIter->first);

                     int numInInternalRange = 0;
                     for (hashIter internalRangeIter = internalRange.first;
                        internalRangeIter != internalRange.second;
                        ++internalRangeIter)
                     {
                        if (internalRangeIter->second > startInterval
                           && internalRangeIter->second < endInterval)
                        {
                           ++numInInternalRange;
                        }
                     }

                     if (numInInternalRange > 1) //ПРОВЕРЯТЬ ГРАНИЧНЫЕ УСЛОВИЯ
                     {
                        uint64_t largeRecBase = 0;
                        uint64_t smallRecBase = 0;
                        uint64_t largeRecStop = -1;
                        uint64_t smallRecStop = -1;
                        double res = 1;

                        while (largeRecStop != 0 || smallRecStop != 0)
                        {
                           uint64_t largeRec = 1;
                           if (largeRecStop != 0)
                           {
                              largeRecStop = 0;
                              largeRec = fact(numInInternalRange, largeRecBase, largeRecStop);
                           }
                           uint64_t smallRec = 1;
                           if (smallRecStop != 0)
                           {
                              smallRecStop = 0;
                              smallRec = fact(numInInternalRange - 2, smallRecBase, smallRecStop);
                           }

                           res *= (static_cast<double>(largeRec) / static_cast<double>(smallRec));

                           largeRecBase = largeRecStop;
                           smallRecBase = smallRecStop;

                        }
                        res /= static_cast<double>(2);
                        //вычисляем сколько установок по 2
                    //    const int currCombinationsCount
                      //     = fact(numInInternalRange) / (2 * fact(numInInternalRange - 2));

                        totalPolindromeCount += res;
                     }
                  }
               }
               ++nextIter;
            }
         }

         if (4 == currRangeSize)
         {
            ++totalPolindromeCount;
         }
         else if (currRangeSize > 4)
         {
            //передавать - н, факториал бейз - число до которого опускаемся в рекурсии - в обычном случае это нуль
            //возврат - бейз на котором мы остановились возвращаться из рекурсии, частичный факториал

            uint64_t largeRecBase = 0;
            uint64_t smallRecBase = 0;
            uint64_t largeRecStop = -1;
            uint64_t smallRecStop = -1;
            double res = 1;

            while (largeRecStop != 0 || smallRecStop != 0)
            {
               uint64_t largeRec = 1;
               if (largeRecStop != 0)
               {
                  largeRecStop = 0;
                  largeRec = fact(currRangeSize, largeRecBase, largeRecStop);
               }
               uint64_t smallRec = 1;
               if (smallRecStop != 0)
               {
                  smallRecStop = 0;
                  smallRec = fact(currRangeSize - 4, smallRecBase, smallRecStop);
               }         
              
               res *= (static_cast<double>(largeRec) / static_cast<double>(smallRec));

               largeRecBase = largeRecStop;
               smallRecBase = smallRecStop;
            }
            res /= static_cast<double>(24);

            totalPolindromeCount += res;
         }
      }
   }

   return totalPolindromeCount;
}

int bruteForcePalindrome(const string& s)
{
   const int size = s.size();

   int result = 0;
   for (int i = 0; i < size; ++i)
   {
      for (int j = i + 1; j < size; ++j)
      {
         for (int k = j + 1; k < size; ++k)
         {
            for (int m = k + 1; m < size; ++m)
            {
               if (s[i] == s[m] && s[j] == s[k])
               {
                  ++result;
               }
            }
         }
      }
   }
   return result;
}



int manakerAlgorithm(const string s)
{
   const int size = s.size();
   vector<int> d2(size, 0);
   int l = 0, r = -1;

   for (int i = 0; i < size; ++i)
   {
      int k = (i > r ? 0 
               : min(d2[l + r - i + 1], r - i + 1)) + 1;
      while (i + k - 1 < size && i - k >= 0 && s[i + k - 1] == s[i - k])  
            ++k;
      
      d2[i] = --k;
      if (i + k - 1 > r)
         l = i - k, r = i + k - 1;
   }

   return d2[3];
}

bool lessFunc(const string& lVal, const string& rVal)
{
   return (lVal.length() < rVal.length());
}

void findPair (const vector<int>& array, 
               const int deltaIndex, const int deltaValue, 
               int& resI, int& resJ)
{
   resI = -1;
   resJ = -1;

   map<int, int> window;
   typedef map<int, int>::iterator windowIterator;
   for (int i = 0; i<deltaIndex; ++i)
   {
      window.insert(make_pair(array[i], i));
   }

   int i = deltaIndex;
   bool found = false;
   do
   {
      //1 check
      windowIterator lowerBound = window.lower_bound(deltaValue);
      //определить индекс лоуер баунд
      //int lowerBoundIndex = i - std::distance(lowerBound, window.end());  //???

      for (map<int, int>::const_iterator it = lowerBound; !found && (it != window.end()); ++it) //завести локальный итератор
      {
         int valToSearch = (it->first - deltaValue); //case for module!!!
         int secValToSearch = (it->first + deltaValue);
         int lowerBoundIndex = it->second;

         windowIterator foundIt = window.find(valToSearch);
         foundIt = (window.end() != foundIt) ? foundIt : window.find(secValToSearch);
         if (foundIt != window.end())//определить индекс найденного элемента
         {
            found = true;
            int foundIndex = foundIt->second;// i - std::distance(foundIt, window.end());  ///????

            resI = foundIndex > lowerBoundIndex ? lowerBoundIndex : foundIndex;
            resJ = foundIndex > lowerBoundIndex ? foundIndex : lowerBoundIndex;
         }

      }
      //2 move window
      if (i < array.size())
      {
         //find elem with index (i - deltaIndex) - this is the smallest index in current window
         const int minIndex = i - deltaIndex;
         int keyToDelete = -1;
         for (windowIterator it = window.begin(); (-1 == keyToDelete) && it != window.end(); ++it)
         {
            if (minIndex == it->second)
            {
               keyToDelete = it->first;
            }
         }
         window.erase(keyToDelete);//????
         window.insert(make_pair(array[i], i));
      }

      //3 increment i
      ++i;
   } while ((i < array.size()) && !found);
}
int minimumLoss(const vector<long>& price)
{
   set<long> priceSet;
   long minLoss = LONG_MAX;

   const int size = price.size();
   priceSet.insert(price.front());
   for (int i = 1; (minLoss > 1) && (i < size); ++i)
   {
      set<long>::const_iterator higherPrices = priceSet.upper_bound(price[i]);

      if (higherPrices != priceSet.end())
      {
         if ((*higherPrices - price[i]) < minLoss)
         {
            minLoss = (*higherPrices - price[i]);
         }
      }
      priceSet.insert(price[i]);
   }
   return static_cast<int>(minLoss);
}
int main()
{
   NULL;
   nullptr_t;

   UINT32_MAX;
   INT32_MAX;
   UINT64_MAX;

   vector<int> lilisArr = { 4,2,10,3,1,15,0 };
   map<int, int> arrMap;
   const int lSize = lilisArr.size();
   for (int i = 0; i<lSize; ++i)
   {
      arrMap.insert(make_pair(lilisArr[i], i));
   }



   vector<long> specialArray_ = {5,10,3 };
   int minLoss = minimumLoss(specialArray_);

   /// ---- /////
   
   const int deltaVal = 5;
   const int deltaIndex = 3;
   vector<int> specialArray = { 5,10,3 };
   int resI, resJ;
   findPair(specialArray, deltaIndex, deltaVal, resI, resJ);



   //// --- custom comparator --- ////
   struct myComp
   {
     const bool operator()(const string& lVal, const string& rVal) const
      {
         return (lVal.length() < rVal.length());
      }
   };
   myComp compInstance;
   
   function<bool(const string&, const string&)> lessFunction = std::bind(lessFunc, placeholders::_1, placeholders::_2);
   //map<string, int, function<bool(const string&, const string&)> > customComparatorMap(lessFunction);
   map<string, int,myComp> customComparatorMap(compInstance);
   customComparatorMap["aaa"] = 3;
   customComparatorMap["a"] = 1;
   customComparatorMap["aa"] = 2;

   //function +
   //functor +
   //lambda
   //pointer 
   ////////////////////
   //1
   TemplateFunc<int16_t>(int(5), double(10));
   TemplateFunc<int16_t,int,double>(int(5), double(10));

   //2

   //TemplateFunc2<int16_t,double>(int(5)); no - так как элемент который можем не указать в середине - он должен ьыть в конце списка
   TemplateFunc2<int16_t,int, double>(int(5));
   TemplateFunc2_2<int16_t, double>(int(5)); //yes!

   //3
   double r = TemplateFunc3<double, int>(float(11));
   r = TemplateFunc3<double, int,float>(float(11));

   vector<int> right = { 1,2,3,4,5 };
   vector<int> reversed(right.rbegin(), right.rend());
   copy(right.begin() + right.size() / 2, right.end(), reversed.begin());

   int data[5] = { 4,5,6,10, 12 };
   reversed.insert(reversed.begin(), data, data + 5);

   vector<int>::iterator iter(reversed.begin());
   for (int i = 0; i < 5; ++i)
   {
       iter = reversed.insert(iter, data[i]);
   }

   reversed.resize(10);
   reversed.assign(right.rbegin(), right.rend());
   reversed.insert(reversed.end(), right.rbegin(), right.rend());
   copy(reversed.begin(), reversed.end(), ostream_iterator<int>(cout,", " ));
   cout << endl;
   copy(reversed.rbegin(), reversed.rend(), ostream_iterator<int>(cout, ", "));

   cout << endl;
   istringstream inRight("12345");
   copy(istreambuf_iterator<char>(inRight), istreambuf_iterator<char>(), ostream_iterator<char>(cout, ", "));

   //baabababaaaababbbbbbabbbbabbbaaabaaabbbbaabbbbbbab
   //abababaaabab_bbbbabbbbabbbaaabaabbbbaa
   string ss("akakak");
  // const int resPol = manakerAlgorithm(ss);
   //_aabbbbbbbbaaaaaaaaaaabbbbbbbaaaaaaaa
   const int shPol =         shortPalindrome("aabbbbbbbbaaaaaaaaaaabbbbbbbaaaaaaaa");
   const int checkRes = bruteForcePalindrome("aabbbbbbbbaaaaaaaaaaabbbbbbbaaaaaaaa");


   unordered_multimap<char, int> hashTable;
   typedef unordered_multimap<char, int>::const_iterator hashIter;
   hashTable.insert({ 'a', 0 });

   hashTable.insert({ 'b', 0 });

   hashTable.insert({ 'a', 1});

  // hashTable.insert({ 'a', 10 });

   hashTable.insert({ 'b', 13 });

   hashTable.insert({ 'c', 2});

   std::pair<hashIter, hashIter>  range = hashTable.equal_range('a');

   hashIter currKeyRangeIter = range.first;
   hashIter nextIter = currKeyRangeIter;
   ++nextIter;
   const int size =std::distance(range.first,range.second);

   for (hashIter iter = range.first; iter != range.second; ++iter)
   {
      cout << " " << iter->second;
   }

   string nk_temp;
   getline(cin, nk_temp);

   vector<string> nk = split_string(nk_temp);

   int n = stoi(nk[0]);

   int k = stoi(nk[1]);

   string r_qC_q_temp;
   getline(cin, r_qC_q_temp);

   vector<string> r_qC_q = split_string(r_qC_q_temp);

   int r_q = stoi(r_qC_q[0]);

   int c_q = stoi(r_qC_q[1]);

   vector<vector<int>> obstacles(k);
   for (int i = 0; i < k; i++) {
      obstacles[i].resize(2);

      for (int j = 0; j < 2; j++) {
         cin >> obstacles[i][j];
      }

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }

   int result = queensAttack(n, k, r_q, c_q, obstacles);

   cout << result << "\n";

///////////////////////////////////////////////


   int q;
   cin >> q;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   for (int q_itr = 0; q_itr < q; q_itr++)
   {
      int n;
      cin >> n;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      vector<vector<int>> container(n);
      for (int i = 0; i < n; i++) {
         container[i].resize(n);

         for (int j = 0; j < n; j++) {
            cin >> container[i][j];
         }

         cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }

      string result = organizingContainers(container);

      cout << result << "\n";
   }








   const int a = 10;
   int tR[a] = { 0 };
   tR[0] = 14;
   tR[5] = 20;

   const int maxTR = std::max(std::initializer_list<int>(tR, &(tR[9])));

   cout << 10;
   thread t1(Function, "t1");
  
   for (int i = 0; i < 100; i++)
      sharedPrint2("Main", i);

   t1.join();

   std::vector<int> v = { 2, 3, 3 };
   std::vector<int> v1 = std::move(v); // the value of v is unspecified

   //task 1 
   //find pair in a sorted! array with specified sum
   
   //1)O(n^2)
   //2 loops: first from start to end of array, second from start to end 
   //comparing a sum of each existing pair
  
   //2) O(n * log(n))
   //fix 1 element 
   //perform binary search for number (sum - fixed_element)

   //3) O(n)
   //fix element at the start and at the end
   //get sum of fixed 
   //if curr_sum > sum, move right element to left
   //if curr_sum < sum, move left element to right
   //if curr_sum == sum, pair found

   //task 2
   //find pair in a  notsorted! array with specified sum

   //1) O(n)
  /* for each element search for it in complemets unordered set
   if found pair exists (indices are index of curr elem and index of found elem)
   else add (sum - curr_value) to the set */

   vector<int> arr;
   unordered_set<int> complements;
   int sum = 0;
   for (int i = 0; i < arr.size(); i++)
   {
      if (complements.find(arr[i]) != complements.end())
      {
         //found
         //values are arr[i] and  (sum - arr[i])
         break;
      }
      else
      {
         complements.insert(sum - arr[i]);
      }
   }

   //// ----------------- FOR_EACH -------------------- ////
 //1 lambda 
   vector<int> vec = { 1,2,10,9,3 };
   for_each(vec.begin(), vec.end(), [](int& n) {n -= 2; });

   for (int n : vec)
   {
      cout << n << " ";
   }

   cout << endl;

  //2 struct/class
   //2.1 what if there's no copy construct but we return object - here's everything ok, 
   //default copy construct
   struct SCheck
   {
      void operator()(int& n)
      {
         cout << ((n % 2) == 0 ? "pair" : "not pair")<<endl;
         if ((n % 2) == 0)
         {
            A = n;
         }
      }
   private:
      int A;
   };

   SCheck sCheck = for_each(vec.begin(), vec.end(), SCheck());
   SCheck s2(sCheck);
//   можно ли поинтер на функцию передать в фор ич
   //работа с плейсходреами
   //что если передать в парметр ссылки не стд реф а просто переменную
 //  cout <<sCheck.A<<endl;

   //1
   int res;
   char s[] = "str";
   function<void(/*int, char*,int,int&*/)> func = std::bind(funcToBind, 4, s, 12, std::ref(res)); //все замечательно. Если без стд реф, то по ссылке не передастся!
   function<void(int, char[] /*char*,int,int&*/)> func1 = std::bind(funcToBind, 1,  placeholders::_2, placeholders::_1, std::ref(res));

   auto func3 = std::bind(funcToBind, 1, placeholders::_3, placeholders::_1, std::ref(res));

   func();
   func1(3,s);
   func3(10, 15, s, 16);

   for_each(vec.begin(), vec.end(), std::bind(funcToBind,13, s, 10, placeholders::_1));
   for_each(vec.begin(), vec.end(), std::bind(funcToBind, placeholders::_1, s, 10, res));

   
   cout << s << endl;

    return 0;
}
