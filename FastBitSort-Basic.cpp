#include <stdio.h>
#include <iostream>

//Bit Size for different datatypes
#define INT 31
#define LONG_LONG_INT 63
#define CHAR 7

using namespace std;

/*********************************************************
FastBitSort Method sorts the bits and returns the value s.
S indicates the range of '0' from Index [0 .. S].
If S returns -1 , It indicates there are no '0's

Argument bit indicates at which value the sorting must be done
*********************************************************/
void FastBitSort(int d[],int lb,int ub,int bitMask=(1<<INT))	{
	//Terminating Condition
	if(ub<=lb || bitMask==0)	return;

	int s = lb , e = ub;
	while(s<=e)	{
		if((d[s]&bitMask) < (d[e]&bitMask))	{
			s++;	e--;
		}
		else if((d[s]&bitMask) > (d[e]&bitMask))	{
			//Swap
			int temp = d[s];
			d[s] = d[e];
			d[e] = temp;
			s++;	e--;
		}
		else	{	
			//Equal Case	,	This section d[s] == d[e] . Therefore conparison with one data is enough
			if((d[s]&bitMask) == 0)	{	
				s++;
			}
			else 	{ 
				e--;
			}
		}
	}
	//return (s-1);
	//Calling Two segment i.e (0 and 1)
	FastBitSort(d,lb,s-1,bitMask>>1);	//0
	FastBitSort(d,s,ub,bitMask>>1);		//1
}

int main()	{
	ios_base::sync_with_stdio(false);
	int d[100];
	int n;

	cout<<"Enter N : ";
	cin>>n;
	cout<<"Enter the elements :\n";
	for(int i=0;i<n;i++)
		cin>>d[i];
	FastBitSort(d,0,n-1);
	fflush(stdin);
	cout<<"After Sorting :\n";
	for(int i=0;i<n;i++)
		cout<<d[i]<<" ";
	cout<<"\n";

	return 0;
}