#include <iostream>

using namespace std;

void SelectionSort(int * arr, int num)
{
    int min = 999999;
    int min_index = 0;
    int temp;
    for(int i=0 ; i<num ; i++)
    {
        min = 999999;
        min_index = 0;
        for(int j=i ; j<num ; j++)
        {
            if(min > arr[j])
            {
                min_index = j;
                min = arr[j];
            }
        }
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

void InsertionSort(int * arr, int num)
{
    int temp,now,j;
    for(int i=0 ; i<num ; i++)
    {
        now = arr[i];
        for(j=i ; j>0 ; j--)
        {
            if(arr[j-1] < now) break;
            temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
        }
    }
}

int * Merge(int *arr1, int num1, int *arr2, int num2)
{
    int * arr3 = new int [num1+num2];
    
    int now_i=0, now_j=0;
    while( now_i<num1 && now_j<num2 )
    {
        if(arr1[now_i] <= arr2[now_j])
        {
            arr3[now_i+now_j] = arr1[now_i];
            now_i += 1;
        }
        else
        {
            arr3[now_i+now_j] = arr2[now_j];
            now_j += 1;
        }
    }
    for(int i=now_i ; i<num1 ; i++)
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

    if(num == 1) return arr;
    int * arr1 = new int [num/2];
    int * arr2 = new int [num - num/2];

    for(int i=0; i<num/2 ; i++) arr1[i] = arr[i];
    for(int i=num/2; i<num ; i++) arr2[i-num/2] = arr[i];

    return Merge( MergeSort(arr1,num/2), num/2, MergeSort(arr2,num-num/2), num-num/2 );
}

int main()
{
    int a[] = {1,2,4,7,9,32,121};
    int b[] = {2,3,4,5};
    int d[] = {1,3,8,2,7,44,354,4,24,6};
    
    int * c = Merge(a,7,b,4);
    int * e = MergeSort(d,10);

    for(int i=0 ; i<10 ; i++) cout << e[i] << " " ;

    return 0;
}