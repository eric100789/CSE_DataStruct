#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <string>
#include <algorithm>

/*
Author: B103040001 孫世諭
Date: November. 18,2022
Purpose: 測試五種排序(sorting)演算法的執行效率
*/

using namespace std;

void SelectionSort(int * arr, int num)
{
    int min = 999999; // big num to find min
    int min_index = 0; // record index number
    int temp;
    for(int i=0 ; i<num ; i++) 
    {
        min = 999999;
        min_index = 0;
        for(int j=i ; j<num ; j++) // find min and make it to first
        {
            if(min > arr[j])
            {
                min_index = j;
                min = arr[j];
            }
        }
        temp = arr[i];
        arr[i] = arr[min_index]; // swap
        arr[min_index] = temp;
    }
}

void InsertionSort(int * arr, int num) 
{
    int temp,now,j;
    for(int i=0 ; i<num ; i++)
    {
        now = arr[i]; // now number
        for(j=i ; j>0 ; j--)
        {
            if(arr[j-1] < now) break; // break
            temp = arr[j];
            arr[j] = arr[j-1]; // swap
            arr[j-1] = temp;
        }
    }
}

int * Merge(int *arr1, int num1, int *arr2, int num2) // Merge two array
{
    int * arr3 = new int [num1+num2]; // new array
    
    int now_i=0, now_j=0; 
    while( now_i<num1 && now_j<num2 ) // we must compare when there has number left
    {
        if(arr1[now_i] <= arr2[now_j]) // arr2[now_j] is bigger or equal
        {
            arr3[now_i+now_j] = arr1[now_i]; 
            now_i += 1;
        }
        else // arr1[now_i] is bigger or equal
        {
            arr3[now_i+now_j] = arr2[now_j];
            now_j += 1;
        }
    }
    for(int i=now_i ; i<num1 ; i++) // add left numnber to my array
    {
        arr3[now_i+now_j] = arr1[i];
        now_i++;
    }
    for(int i=now_j ; i<num2 ; i++)
    {
        arr3[now_i+now_j] = arr2[i];
        now_j++;
    }
    return arr3;
}

int * MergeSort(int *arr, int num)
{

    if(num == 1) return arr; // bad bad
    int * arr1 = new int [num/2]; // devide to two array
    int * arr2 = new int [num - num/2];

    for(int i=0; i<num/2 ; i++) arr1[i] = arr[i]; // new array1
    for(int i=num/2; i<num ; i++) arr2[i-num/2] = arr[i]; // new array2

    int * MergedList1 = MergeSort(arr1,num/2); // MergeSort
    int * MergedList2 = MergeSort(arr2,num-num/2); // MergeSort

    return Merge( MergedList1 , num/2, MergedList2, num-num/2); // Merge two array

    delete MergedList1,MergedList2; // delete bad array
}

void swap (int & a, int & b) // swap but never used
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void QuickSort(int *arr, int left, int right)
{
    if(left <0 || right<left) return; // oh no
    int pivot = arr[left];
    int temp;
    int i=left, j=right;

    while(i != j)
    {
        while(pivot >= arr[i] && i < j) i++; // from left
        while(pivot < arr[j] && i < j) j--; // from right
        if(i < j)
        {
            temp = arr[i];
            arr[i] = arr[j]; // swap, 為什麼我不用剛才的swap函式?????????????
            arr[j] = temp;
        }
    }
    if( arr[i] > pivot) i--;
    arr[left] = arr[i];
    arr[i] = pivot;

    QuickSort(arr,i+1,right); // recursive
    QuickSort(arr,left,i-1);
}

int cmpfunc (const void * a, const void * b) // used for qsort
{
   return ( *(int*)a - *(int*)b );
}

int main() // UIUIUI
{
    while(true)
    {
        int input;
        printf("(1)Create Input File (2)Create Output File (3)Exit\n>> "); // UIUIUI
        cin >> input;
        if(input == 1)
        {
            printf("Please input your data numbers...\n>> "); // UIUIUI
            cin >> input;
            srand(time(NULL)); // radom numbers
            
            ofstream output_file;
            output_file.open("input.txt");
            output_file << input << endl; // inputinputinputinputinput number how many goods
            
            for(int i=0;i<input;i++) output_file<<rand()<<endl; // inputinputinputinputinput
            output_file.close();
        }
        else if(input == 2)
        {
            printf("(1)InsertionSort (2)MergeSort (3)QuickSort (4)C:qsort (5)C++:sort()\n>> ");// UIUIUI 
            cin >> input;
            if(input>5 || input<1) cout << "WRONG NUMBER." << endl; // YOU BAD BOI
            else
            {
                ifstream input_file;
                input_file.open("input.txt"); // open file
                
                int data_num;
                input_file >> data_num;
                int * arr = new int[data_num]; // dynamic array
                for(int i=0 ; i<data_num ; i++)
                {
                   input_file >> arr[i] ;
                }

                if(input == 1)
                {
                    string opened = "outputA.txt";
                    clock_t a,b;
                    a=clock();
                    InsertionSort(arr, data_num);
                    b=clock();
                    cout << "Time Used: " << double(b-a)/CLOCKS_PER_SEC << endl; // clock
                    ofstream output_file;
                    output_file.open(opened);
                    output_file << "Insertion Sort" << endl;
                    for(int i=0 ; i<data_num ; i++) output_file << arr[i] << endl ;
                    output_file.close();
                    cout << "File Saved." << endl;
                }
                else if(input == 2)
                {
                    string opened = "outputB.txt";
                    clock_t a,b;
                    a=clock();
                    arr = MergeSort(arr, data_num);
                    b=clock();
                    cout << "Time Used: " << double(b-a)/CLOCKS_PER_SEC << endl; // clock
                    ofstream output_file;
                    output_file.open(opened);
                    output_file << "Merge Sort" << endl;
                    for(int i=0 ; i<data_num ; i++) output_file << arr[i] << endl ;
                    output_file.close();
                    cout << "File Saved." << endl;
                }
                else if(input == 3)
                {
                    string opened = "outputC.txt";
                    clock_t a,b;
                    a=clock();
                    QuickSort(arr, 0 ,data_num);
                    b=clock();
                    cout << "Time Used: " << double(b-a)/CLOCKS_PER_SEC << endl; // clock
                    ofstream output_file;
                    output_file.open(opened);
                    output_file << "Quick Sort" << endl;
                    for(int i=0 ; i<data_num ; i++) output_file << arr[i] << endl ;
                    output_file.close();
                    cout << "File Saved." << endl;
                }
                else if(input == 4)
                {
                    string opened = "outputD.txt";
                    clock_t a,b;
                    a=clock();
                    qsort(arr, data_num, sizeof(int), cmpfunc);
                    b=clock();
                    cout << "Time Used: " << double(b-a)/CLOCKS_PER_SEC << endl; // clock
                    ofstream output_file;
                    output_file.open(opened);
                    output_file << "C qsort" << endl;
                    for(int i=0 ; i<data_num ; i++) output_file << arr[i] << endl ;
                    output_file.close();
                    cout << "File Saved." << endl;
                }
                else if(input ==5)
                {
                    string opened = "outputE.txt";
                    clock_t a,b;
                    a=clock();
                    sort(arr, arr+data_num);
                    b=clock();
                    cout << "Time Used: " << double(b-a)/CLOCKS_PER_SEC << endl; // clock
                    ofstream output_file;
                    output_file.open(opened);
                    output_file << "C++ sort" << endl;
                    for(int i=0 ; i<data_num ; i++) output_file << arr[i] << endl ;
                    output_file.close();
                    cout << "File Saved." << endl;
                }
                delete arr; // delete dynamic array 我剛發現我程式莫名其妙爆炸就是因為我忘記加這行
            }
        }
        else if(input == 3) return 0;
    }
    return 0;
}