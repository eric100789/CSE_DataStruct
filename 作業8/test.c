#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int num)
{
    int i=1;
    for(i=2 ; i<=num/2+1 ; i++)
    {
        if(num%i == 0) return 0;
    } 
    return 1;
}

int main()
{
    int input;
    printf("Please input target number: ");
    scanf("%d",&input);

    int i,num=0;
    int array_num = ((int)sqrt(input));
    int * P = (int*) malloc(sizeof(int)*array_num);
    for(i=1 ; i<=array_num; i++)
    {
        if( isPrime(i) )
        {
            num++;
            P[num] = i;
        }
    }

    for(i=1 ; i<=num ; i++) 
    {
        printf("%d ",P[i]);
    }

    return 0;
}