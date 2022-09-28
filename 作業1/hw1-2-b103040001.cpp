#include <iostream>
#include <vector>
using namespace std;
/*
Author: B103040001 孫世諭
Date: Sept. 8,2022
Purpose: 題目：印出1到N之間所有整數之階乘 (factorial)，N<=50。
*/

// print the vector (reversed)
void print_vector(vector<int> target)
{
    // for loop to print the target vector
    for(int i=target.size()-1 ; i>=0 ; i--)
    {
        cout << target[i] ;
    }
    cout << endl;
}

// make my target number(vector) be multiplied by int num
vector<int> multiply(vector<int> target , int num)
{
    for(int i=0 ; i<target.size() ; i++)
    {
        //multiply all number of target(vector)
        target[i] *= num;
    }

    //because of while loop, variable of index is needed.
    int now_index = 0; 
    do
    {
        // if the target[now_index] is the last number and >10 , new storage is needed.
        if(target[now_index] >= 10 && target.size()-1 == now_index)
        {
            target.push_back(target[now_index]/10);
            target[now_index] = target[now_index]%10;
        }
        // if the target[now_index] is not the last number but >10 , next storage += target[now_index]/10
        // then , make itself %10
        else if(target[now_index] >= 10)
        {
            target[now_index+1] += target[now_index]/10;
            target[now_index] = target[now_index]%10;
        }
        // add 1 such as for loop
        now_index++;
    // the size will change if we have pushed number.
    } while(now_index < target.size());
    return target;
}

// the function of Factorial
void fact(int n)
{
    // first number to make it be multiplied
    vector<int> ans = {1};
    
    for(int i=1 ; i<=n ; i++)
    {
        // store the multiply answer
        ans = multiply(ans , i);
        cout << i << "!=";
        print_vector(ans);
    }
}

int main()
{
    // make the input stored
    int input;
    do
    {
        cin >> input;
        // do fact
        fact(input);
        cout << endl;
    // if we write 0 , stopped exe
    }while(input!=0);

    return 0;
}
