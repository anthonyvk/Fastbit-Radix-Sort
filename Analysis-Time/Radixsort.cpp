// C++ implementation of Radix Sort
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
using namespace std;

#define ull long long int

//For timing information
struct timeval tv;
double dstart,dend;

ull d[100000000] = {0};

// A utility function to get maximum value in arr[]
ull getMax(ull arr[], ull n)
{
    ull mx = arr[0];
    for (ull i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(ull arr[], ull n, ull exp)
{
    ull output[n]; // output array
    ull i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using 
// Radix Sort
void radixsort(ull arr[], ull n)
{
    // Find the maximum number to know number of digits
    ull m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (ull exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
 
// Driver program to test above functions
int main()
{
    ios_base::sync_with_stdio(false);
    //ull d[999999];
    ull n;
    ull compMask = 0;

    cout<<"Enter N : ";
    cin>>n;
    cout<<"Enter the elements :\n";
    for(ull i=0;i<n;i++)
        cin>>d[i];

    //compMask = ComputeMask(d,n);
    gettimeofday(&tv,NULL);
    dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
    radixsort(d, n);
    gettimeofday(&tv,NULL);
    dend = tv.tv_sec + (tv.tv_usec/1000000.0);

    fflush(stdin);
    cout<<"After Sorting :\n";
    for(ull i=0;i<n;i++)
        cout<<d[i]<<" ";
    cout<<"\n";
    cout<<"\nAnalysis => TIME : "<<(dend-dstart)<<endl;
    return 0;
}