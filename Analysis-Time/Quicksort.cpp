#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>

#define ull long long int
using namespace std;

ull d[100000000] = {0};

//For timing information
struct timeval tv;
double dstart,dend;

inline void fnSwap(ull *a, ull *b)
{
	ull t = *a; *a = *b; *b = t;
}

ull Partition(ull a[], ull l, ull r)
{
	ull i,j,temp;
	ull p;

	p = a[l];
	i = l;
	j = r+1;

	do
	{
		do { i++;	} while (a[i] < p);
		do { j--;	} while (a[j] > p);

		fnSwap(&a[i], &a[j]);
	}
	while (i<j);

	fnSwap(&a[i], &a[j]);
	fnSwap(&a[l], &a[j]);

	return j;
}
void QuickSort(ull a[], ull l, ull r)
{
	ull s;
	if (l < r)
	{
		s = Partition(a, l, r);
		QuickSort(a, l, s-1);
		QuickSort(a, s+1, r);
	}
}

int main()	{
	ios_base::sync_with_stdio(false);
	//ull d[999999];
	ull n;

	cout<<"Enter N : ";
	cin>>n;
	cout<<"Enter the elements :\n";
	for(ull i=0;i<n;i++)
		cin>>d[i];

	//compMask = ComputeMask(d,n);
	gettimeofday(&tv,NULL);
	dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
	QuickSort(d,0,n-1);
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