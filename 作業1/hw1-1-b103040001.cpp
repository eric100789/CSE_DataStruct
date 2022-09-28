#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

/*
Author: B103040001 孫世諭
Date: Sept. 8,2022
Purpose: 製作N階(N為奇數)的魔方陣(magic square)
*/

// quick function to get the index i should place
int get_num(int now , int level , int num)
{
    // if out of the array return now-num
    if(now-num < 0 || now-num > level-1) return level-num;
    else return now-num;
}

int main()
{
    int level;
    
    for(int level = 1 ; level <= 9 ; level +=2)
    {
        // dynamic array (so i can use varible to control)
        int ** arr = new int* [level];
        // all is 0 at first
        for(int i=0 ; i<level ; i++)
        {
            arr[i] = new int [level]{0};
        }

        //get the place of the middle and start
        int now_row = 0 , now_col = level/2;

        for(int i=1 ; i<=level*level ; i++)
        {
            // place i on arr[now_row][now_col]
            arr[now_row][now_col] = i;

            // if the place i get from get_num function is 0 replace it
            if(arr[get_num(now_row,level,1)][get_num(now_col,level,1)] == 0 ) 
            {
                now_row = get_num(now_row,level,1);
                now_col = get_num(now_col,level,1);
            }
            // if not, only change now_row (get_num -1)
            else
            {
                now_row = get_num(now_row,level,-1);
            }
        }

        // print the cube i created.
        for(int i=0 ; i<level ; i++)
        {
            for(int j=0 ; j<level ; j++)
            {
                printf("%d\t",arr[i][j]);
            }
            cout << endl;
        }
        cout << endl;
        // delete dynamic array
        for(int j=0 ; j<level ; j++) delete arr[j];
        delete arr;
    }



    return 0;
}