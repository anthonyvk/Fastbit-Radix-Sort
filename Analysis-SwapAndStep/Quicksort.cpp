#include <stdio.h>
#include <iostream>
#define ull unsigned long long int
using namespace std;

ull _swap = 0;
ull comp = 0;
ull fcall = 0;
ull loop = 0;

inline void fnSwap(ull *a, ull *b)
{
	_swap++;
	ull t = *a; *a = *b; *b = t;
}

ull Partition(ull a[], ull l, ull r)
{
	fcall++;
	ull i,j,temp;
	ull p;

	p = a[l];
	i = l;
	j = r+1;

	do
	{
		do { i++;loop++; } while (a[i] < p);
		do { j--;loop++; } while (a[j] > p);

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
	ull d[999999];
	ull n;

	cout<<"Enter N : ";
	cin>>n;
	cout<<"Enter the elements :\n";
	for(ull i=0;i<n;i++)
		cin>>d[i];

	//compMask = ComputeMask(d,n);
	QuickSort(d,0,n-1);

	fflush(stdin);
	cout<<"After Sorting :\n";
	for(ull i=0;i<n;i++)
		cout<<d[i]<<" ";
	cout<<"\n";
	cout<<"\nAnalysis => LOOP : "<<loop<<endl;
	cout<<"\nAnalysis => SWAP : "<<_swap<<endl;
	return 0;
}