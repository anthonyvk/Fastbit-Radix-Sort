#include <stdio.h>
#include <iostream>
#define ull unsigned long long int
using namespace std;
ull _swap = 0;	//Assignments or shifts here
ull comp = 0;
ull fcall = 0;
ull loop = 0;

void Merge(ull d[],ull lb,ull m,ull ub)	{
	fcall++;

	if(ub-lb == 0)	return;
	ull t[ub-lb+1];
	ull ia = lb, ib = m;
	ull it = 0;

	while(ia<=m-1 && ib<=ub)	{
		loop++;
		if(d[ia]<=d[ib])	{
			_swap++;
			t[it++] = d[ia];
			ia++;
		}
		else	{
			_swap++;
			t[it++] = d[ib];
			ib++;
		}
	}
	while(ia<=m-1)	{	loop++;_swap++;		t[it++] = d[ia++];	}
	while(ib<=ub)	{	loop++;_swap++;		t[it++] = d[ib++];	}

	for(ull i=0;i<it;i++)	{
		loop++;
		d[lb+i] = t[i];
	}

}
void MergeSort(ull d[],ull lb,ull ub)	{
	if(lb<ub)	{
		//fcall++;
		ull m = lb + (ub-lb)/2;
		MergeSort(d,lb,m);
		MergeSort(d,m+1,ub);
		Merge(d,lb,m+1,ub);
	}
}

int main()	{
	ios_base::sync_with_stdio(false);
	ull d[899999];
	ull n;
	
	cout<<"Enter N : ";
	cin>>n;
	cout<<"Enter the elements :\n";
	for(ull i=0;i<n;i++)
		cin>>d[i];

	MergeSort(d,0,n-1);

	fflush(stdin);
	cout<<"After Sorting :\n";
	for(ull i=0;i<n;i++)
		cout<<d[i]<<" ";
	cout<<"\n";
	cout<<"\nAnalysis => LOOP : "<<loop<<endl;
	cout<<"\nAnalysis => SWAP : "<<_swap<<endl;
	return 0;
}