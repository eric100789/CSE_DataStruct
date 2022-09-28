#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
Author: B103040001 孫世諭
Date: Sept. 12,2022
Purpose: 一個nxn的西洋棋盤上，騎士(knight)置於某位置(x,y)，撰寫一個程式以便找出此騎士(n2-1)次移動的順序，而每個格子只拜訪過一次（使用遞迴）。
*/

// to count how many times knight have walked
int Now = 0;

// define a function to walk and recursive

/*
now_i is recording y position
now_j is recording x position
n is recording n ( n*n array )
arr is recording array
*/
void walk(int now_i , int now_j , int n , int ** arr)
{
    // no out of array
    if(now_i >= n || now_i<0 || now_j>=n || now_j<0) return;
    // dont walk the place the knight had walked
    if(arr[now_i][now_j] != 0 ) return; 

    // walked, so add 1
    Now++;
    
    // now counting
    arr[now_i][now_j] = Now;
    // walk from K1 to K8
    walk(now_i-2 , now_j+1 , n , arr); //K1
    walk(now_i-1 , now_j+2 , n , arr); //K2
    walk(now_i+1 , now_j+2 , n , arr); //K3
    walk(now_i+2 , now_j+1 , n , arr); //K4
    walk(now_i+2 , now_j-1 , n , arr); //K5
    walk(now_i+1 , now_j-2 , n , arr); //K6
    walk(now_i-1 , now_j-2 , n , arr); //K7
    walk(now_i-2 , now_j-1 , n , arr); //k8
    if( Now == n*n ) return; // stop recursiving

    // if all of above step cannot working, back to last step and NOW--
    Now--; 
    // make it into zero
    arr[now_i][now_j] = 0;
    return;

}

int main()
{
    int n ; // n is matrix's n
    int ** arr; // dynamic array's size can change if n changed.
    bool flag = true;

    for(n=1 ; n<=6 ; n++)
    {
        flag = true;
        Now = 0;
        arr = new int*[n];
        for(int i=0 ; i<n ; i++)
        {
            arr[i] = new int[n] ;
            for(int j = 0 ; j<n ; j++)
            {
                // all is 0 at first
                arr[i][j] = 0;
            }
        }

        // walk start at (1,1) = arr[0][0]
        walk(0,0,n,arr);

        // if walk finished and there is a zero in array means no solution
        for(int i=0 ; i<n ; i++)
        {
            for(int j=0 ; j<n ; j++)
            {
                if(arr[i][j] == 0)
                {
                    cout << "no solution" << endl;
                    flag = false;
                    break;
                }
            }
            if(!flag) break;
        }

        if(flag)
        {
            // print answer
            for(int i=0 ; i<n ; i++)
            {
                for(int j=0 ; j<n ; j++)
                {
                    printf("\t%d",arr[i][j]);
                }
                cout << endl;
            }
        }
        cout << endl;
        for(int i=0 ; i<n ; i++) delete arr[i];
    }
    


    

    return 0;
}