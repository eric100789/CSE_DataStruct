#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/*
Author: B103040001 孫世諭
Date: Sept. 11,2022
Purpose: 一個nxn的西洋棋盤上，騎士(knight)置於某位置(x,y)，撰寫一個程式以便找出此騎士(n2-1)次移動的順序，而每個格子只拜訪過一次。
*/


// a struct make for knight's stack class
struct knightData
{
    int i;
    int j;
    int step;
};

// a stack
class stack
{
    private:
    // a struct make for knight's stack class
    knightData data;
    // pointer of next stack class
    stack * next;

    public:
    // constructer ( all of values are -1)
    stack()
    {
        data.i = -1;
        data.j = -1;
        data.step = -1;
        next = NULL;
    }
    // constructer (i,j,step given)
    stack(int i, int j , int step)
    {
        data.i = i;
        data.j = j;
        data.step = step;
        next = NULL;
    }
    
    // push (stack)
    void push(int i, int j , int step)
    {
        stack * new_stack = new stack();
        *new_stack = *this;
        data.i = i;
        data.j = j;
        data.step = step;
        next = new_stack;
    }
    
    // get KnightData
    knightData getKnight()
    {
        return data;
    }

    // get the top of the stack's data (no pop)
    stack peek()
    {
        return *this;
    }

    // get the top of the stack's data (pop)
    stack pop()
    {
        if(next == NULL)
        {
            stack new_stack(data.i,data.j,data.step);
            data.i = -1;
            data.j = -1;
            data.step = -1;
            next = NULL;
            return new_stack;
        }
        else
        {
            stack popped(data.i,data.j,data.step);
            data.i = next->data.i;
            data.j = next->data.j;
            data.step = next->data.step;
            next = next->next;
        
            return popped;
        }

    }

    // print all data of knightData
    void print()
    {
        cout << data.i << "," << data.j << "," << data.step << endl;
    }

};

// test wheather a+b is out of array or not
bool testOut(int a , int b , int n)
{
    if(a+b >= n) return false;
    else if (a+b < 0) return false;
    else return true;
}

// array[i][j] , y is i , x is j , k is step which the knight will go, n is matrix's N , arr is array
bool canWalk(int y, int x, int k , int n , int ** arr)
{
    // test: step1~8, then do testOut to know wheather knight is out of array or not
    // if knight can walk, do [if] again to know wheather the step had been walked or not
    // if ok, return true.
    if(k==1)
    {
        if( testOut(x,1,n) && testOut(y,-2,n)) if(arr[y-2][x+1] == 0) return true;
        return false;
    }
    else if(k==2)
    {
        if( testOut(x,2,n) && testOut(y,-1,n)) if(arr[y-1][x+2] == 0) return true;
        return false;
    }
    else if(k==3)
    {
        if( testOut(x,2,n) && testOut(y,1,n)) if(arr[y+1][x+2] == 0) return true;
        return false;
    }
    else if(k==4)
    {
        if( testOut(x,1,n) && testOut(y,2,n)) if(arr[y+2][x+1] == 0) return true;
        return false;
    }
    else if(k==5)
    {
        if( testOut(x,-1,n) && testOut(y,2,n)) if(arr[y+2][x-1] == 0) return true;
        return false;
    }
    else if(k==6)
    {
        if( testOut(x,-2,n) && testOut(y,1,n)) if(arr[y+1][x-2] == 0) return true;
        return false;
    }
    else if(k==7)
    {
        if( testOut(x,-2,n) && testOut(y,-1,n)) if(arr[y-1][x-2] == 0) return true;
        return false;
    }
    else if(k==8)
    {
        if( testOut(x,-1,n) && testOut(y,-2,n)) if(arr[y-2][x-1] == 0) return true;
        return false;
    }
    return false;
}

// only make for adding i,j by inputting k(step)
void add(int &y , int &x , int k)
{
    if(k==1)
    {
        x+=1;
        y-=2;
    }
    else if(k==2)
    {
        x+=2;
        y-=1;
    }
    else if(k==3)
    {
        x+=2;
        y+=1;
    }
    else if(k==4)
    {
        x+=1;
        y+=2;
    }
    else if(k==5)
    {
        x-=1;
        y+=2;
    }
    else if(k==6)
    {
        x-=2;
        y+=1;
    }
    else if(k==7)
    {
        x-=2;
        y-=1;
    }
    else if(k==8)
    {
        x-=1;
        y-=2;
    }
}

int main()
{
    int ** arr;
    bool flag = true;

    // create a stack named "knight"
    stack knight;
    // didnt walk, init 0
    int now_step=0;
    // first (x,y) is (0,0)
    // "now" is make for counting how many times the knight walks
    int now = 1 , now_i = 1 , now_j = 1;
    int n;

    for(n=1 ; n<=6 ; n++) // n is matrix's n
    {
        flag = true;
        arr = new int*[n]; 
        // dynamic array's size can change if n changed.
        for(int i=0 ; i<n ; i++)
        {
            arr[i] = new int[n];
            for(int j=0 ; j<n ; j++)
            {
                // all is 0 at first
                arr[i][j] = 0;
            }
        }

        now_step=0;
        // first (x,y) is (0,0)
        // "now" is make for counting how many times the knight walks
        now = 1 ; now_i = 1 ; now_j = 1;

        while(true)
        {
            // try K1~K8
            now_step++;

            // if now_step >= 9, means knight tried all method, if i,j are 1 too, means no solution
            if(now_step>=9 && now_i == 1 && now_j == 1)
            {
                cout << "no solution" << endl;
                flag = false;
                break;
            }
            // if now_step >= 9 but i,j not (1,1), means knight tried all method, but it still can try last move
            else if(now_step>=9)
            {
                arr[now_i-1][now_j-1] = 0;
                now_i = knight.peek().getKnight().i;
                now_j = knight.peek().getKnight().j;
                // change the step to last move
                now_step = knight.peek().getKnight().step;
                // pop off the last answer (bad walk)
                knight.pop();
                // count -1
                now--;
            }
            // walk sucessfully
            else
            {
                if(canWalk(now_i-1,now_j-1,now_step,n,arr))
                {
                    // push it to stack(answer)
                    knight.push(now_i,now_j,now_step);
                    arr[now_i-1][now_j-1] = now;
                    add(now_i,now_j,now_step);
                    // count +1
                    now++;
                    // restart the method from K1
                    now_step = 0;
                }
            }

            // if finish, break.
            if(now == n*n) break;

        }

        if(flag)
        {
            arr[now_i-1][now_j-1] = n*n;
            
            // print answer
            for(int i= 0 ; i<n ; i++)
            {
                for(int j=0 ; j<n ; j++)
                {
                    printf("\t%d",arr[i][j]);
                }
                cout << endl;
            }
        }

        for(int i=0 ; i<n ; i++)
        {
            delete arr[i];
        }
        while(knight.pop().getKnight().i != -1)
        {
            // do nothing
        }
        cout << endl;

    }
    return 0;

}