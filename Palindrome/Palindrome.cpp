// Palindrome.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Hash
{
private:
   vector<int64_t> prefixHash;
   vector<int64_t> suffixHash;
  
   vector<int64_t> simpleNumbers;
   const int64_t SimpleBase;

   const string& str;

   vector<int> oddCount;
   vector<int> evenCount;
public:

   Hash(const string& inStr)
      :SimpleBase(2)
      ,str(inStr)
   {
      const int size = str.size();
      prefixHash.resize(size, 0);
      suffixHash.resize(size, 0);

      oddCount.resize(size, 0);
      evenCount.resize(size, 0);
   }
   inline long long Hash::getHash(int indLeft, int indRight) const
   {
      return prefixHash[indRight] - (indLeft > 0 ? prefixHash[indLeft - 1] : 0);
   }

   inline long long Hash::getRevHash(int indLeft, int indRight) const
   {
      return suffixHash[indLeft] - (indRight < suffixHash.size() - 1 ? suffixHash[indRight + 1] : 0);
   }

   void Hash::PrepareSimpleNumbers()
   {
      if (str.length() > simpleNumbers.size())
      {
         size_t oldSize = simpleNumbers.size();
         simpleNumbers.resize(str.length());
         simpleNumbers[0] = 1LL;
         for (int i = (oldSize+1); i < simpleNumbers.size(); ++i)
            simpleNumbers[i] = simpleNumbers[i - 1] * SimpleBase;
      }
   }

   void Hash::CountingPrefixHash()
   {
      prefixHash[0] = str[0];
      for (int i = 1; i < prefixHash.size(); ++i)
      {
         prefixHash[i] = prefixHash[i - 1] + str[i] * simpleNumbers[i];
      }
   }

   void Hash::CountingSuffixHash()
   {
      suffixHash[suffixHash.size() - 1] = str[str.length() - 1];
      for (int i = (int)str.length() - 2, j = 1; i >= 0; --i, ++j)
      {
         suffixHash[i] = suffixHash[i + 1] + str[i] * simpleNumbers[j];
      }
   }

   bool Hash::isPalindrome(int indLeft, int indRight) const
   {
      return getHash(indLeft, indRight) * simpleNumbers[prefixHash.size() - indRight - 1] ==
         getRevHash(indLeft, indRight) * simpleNumbers[indLeft];
   }

   void Hash::CountingOdd()
   {
      for (int i = 0; i < oddCount.size(); i++)
      {
         int indLeft = 1, indRight = min(i + 1, static_cast<int> (oddCount.size() - i));
         while (indLeft <= indRight)
         {
            int middle = (indLeft + indRight) / 2;
            if (isPalindrome(i - middle + 1, i + middle - 1))
            {
               oddCount[i] = middle - 1;
               indLeft = middle + 1;
            }
            else
            {
               indRight = middle - 1;
            }
         }
      }
   }

   void Hash::CountingEven()
   {
      for (int i = 0; i < evenCount.size(); i++)
      {
         int indLeft = 1, indRight = min(i, static_cast<int> (evenCount.size() - i));
         while (indLeft <= indRight)
         {
            int middle = (indLeft + indRight) / 2;
            if (isPalindrome(i - middle, i + middle - 1))
            {
               evenCount[i] = middle;
               indLeft = middle + 1;
            }
            else
            {
               indRight = middle - 1;
            }
         }
      }
   }

   long long Hash::operator()()
   {
      int64_t cntPalindromes = 0;

      PrepareSimpleNumbers();
      CountingPrefixHash();
      CountingSuffixHash();
      CountingOdd();
      CountingEven();
      for (int i = 0; i < str.length(); ++i)
      {
         cntPalindromes += oddCount[i] + evenCount[i];
      }
      return cntPalindromes;
   }
};
int main()
{
   string str("akakak");
   Hash hasher(str);
   hasher();
   return 0;
}

