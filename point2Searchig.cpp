#include <stdio.h>
#include <stdlib.h>

int data[] = {10, 14, 15, 17, 20, 24, 30, 40, 45};

int elm;

int binsearch(int low, int high)
{
    int i, middle;

   
    if(low>high)
    {
        return -1;
    }
    middle = (low + high)/2;
   
    if(elm == data[middle])
    {
       
        return middle;
    }
    else
    {
        if(elm < data[middle])
        {
            high = middle-1;
            return binsearch(low, high);
        }
        else
        {
            low = middle+1;
            return binsearch(low, high);
        }
    }
}

int linearSearch(int n)
{
    for(int i = 0; i < n; i++)
    {
        if(data[i] == elm)
            return i;
    }
    return -1;
}

int interpolationSearch(int lo, int hi)
{
    int pos;

    if (lo <= hi && elm >= data[lo] && elm <= data[hi]) {

        pos = lo + (((double)(hi - lo) / (data[hi] - data[lo])) * (elm - data[lo]));
 
        
        if (data[pos] == elm)
            return pos;
 
        
        if (data[pos] < elm)
            return interpolationSearch(pos + 1, hi);
 
        
        if (data[pos] > elm)
            return interpolationSearch(lo, pos - 1);
    }
    return -1;
}

int main()
{

    int numdata, low, high;
    int status = 0 ;
    numdata = sizeof(data) / sizeof(int);
    low = 0 ;
    high = numdata-1 ;
    printf("There are %d elements in the array\n", numdata);
    printf(" The array is as follows :- ");
    for(int i = 0; i < numdata; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("Please enter the element to be searched: \n");
    scanf("%d",&elm);
    status = binsearch(low,high);
    if(status == -1)
    {
        printf("Element %d is not found in the array by Binary Search",elm);
    }
    else
    {
        printf("Element %d is found in the array by Binary Search at index %d\n", elm, status);
    }

    status = linearSearch(numdata);
    if(status == -1)
    {
        printf("Element %d is not found in the array by Linear Search",elm);
    }
    else
    {
        printf("Element %d is found in the array by Linear Search at index %d\n", elm, status);
    }

    status = interpolationSearch(0, numdata - 1);
    if(status == -1)
    {
        printf("Element %d is not found in the array by Interpolation Search",elm);
    }
    else
    {
        printf("Element %d is found in the array by Interpolation Search at index %d\n", elm, status);
    }
    return 0;
}

