// ChanoeTowers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void moveTower(vector<list<int>>& positions, const int n, const int wantedPos, const int currPos, const int freePos)
{
   if (n > 1)
   {
      moveTower(positions, n - 1, freePos, currPos, wantedPos);//    freePos, wantedPos, currPos);
      positions[currPos].erase(positions[currPos].begin()); //check!
      positions[wantedPos].push_front(n);
      
      if (n > 2)
      {
         moveTower(positions, n - 1, wantedPos, freePos, currPos);
      }
      else
      {
         positions[freePos].erase(positions[freePos].begin()); //check!
         positions[wantedPos].push_front(n-1);
      }
   }
   else
   {
      positions[currPos].erase(positions[currPos].begin()); //check!
      positions[wantedPos].push_front(1);  
   }
}

int main()
{
   vector<list<int>> positions(3);
   positions[0] = list<int>({ 1,2,3,4,5,6 });

   moveTower(positions, positions[0].size(), 2, 0, 1);
    return 0;


}

