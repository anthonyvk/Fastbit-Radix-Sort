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

void Merge(ull d[],ull lb,ull m,ull ub)	{

	if(ub-lb == 0)	return;
	ull t[ub-lb+1];
	ull ia = lb, ib = m;
	ull it = 0;

	while(ia<=m-1 && ib<=ub)	{
		if(d[ia]<=d[ib])	{
			t[it++] = d[ia];
			ia++;
		}
		else	{
			t[it++] = d[ib];
			ib++;
		}
	}
	while(ia<=m-1)	{	t[it++] = d[ia++];	}
	while(ib<=ub)	{	t[it++] = d[ib++];	}

	for(ull i=0;i<it;i++)	{
		d[lb+i] = t[i];
	}

}
void MergeSort(ull d[],ull lb,ull ub)	{
	if(lb<ub)	{
		ull m = lb + (ub-lb)/2;
		MergeSort(d,lb,m);
		MergeSort(d,m+1,ub);
		Merge(d,lb,m+1,ub);
	}
}

int main()	{
	ios_base::sync_with_stdio(false);
	//ull d[899999];
	ull n;
	
	cout<<"Enter N : ";
	cin>>n;
	cout<<"Enter the elements :\n";
	for(ull i=0;i<n;i++)
		cin>>d[i];

	gettimeofday(&tv,NULL);
	dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
	MergeSort(d,0,n-1);
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