/*********************************************************
Author : Anthony Vinay Kumar S

This optimized version prevents recusion when there is only 
two elements in one partition. It prevents by checking and 
swapping . The elements are swapped only if the lower index 
elements is greater than the high index element(low+1 a.k.a 
next element to its right).
*********************************************************/

#include <stdio.h>
#include <iostream>
#define dataType unsigned long long int
#define ull unsigned long long int

/*********************************************************
Bit Size for different datatypes
The shifting is done by number of bits in a datatype minus 1,
since already 1 exists in mask.

Because this sorting holds good for Positive Integers,
We are not considering signed bit during comparison.
Therefore , the Signed datatype shift is reduced by 1.
*********************************************************/
#define UNSIGNED_INT 31
#define INT 30
#define UNSIGNED_LONG_LONG_INT 63
#define LONG_LONG_INT 62
#define CHAR 7

using namespace std;

ull _swap = 0;
ull comp = 0;
ull fcall = 0;
ull loop = 0;

/*********************************************************
FastBitSort Method sorts the bits and returns the value S.
S indicates the 0's partition ranging from Index [0 .. S].
If S returns -1 , It indicates there are no '0's.

d[] - Array of values to be sorted.
lb  - Lowerbound indicating the starting index of the array(inclusive).
ub  - Upperbound indicating the ending index of the array(inclusive).
compMask - Additional bitmasking information to optimise sort.
bitMask - Bit-Position to perform sorting.

Argument bit indicates at which value the sorting must be done
*********************************************************/
/*ull ComputeMask(ull d[],ull n)	{		//To be Implemented
	return ~0;
}*/

void FastBitSort(ull d[],ull lb,ull ub,ull compMask=~0,ull bitMask=(1<<INT))	{		//ub is inclusive
	//Terminating Condition
	if(ub<=lb || bitMask==0 || (ub-lb)==0)	{	return;	}

	ull s = lb , e = ub;
	while(s<=e)	{
		loop++;
		if((d[s]&bitMask) < (d[e]&bitMask))	{		//change to > for descending
			s++;	e--;
		}
		else if((d[s]&bitMask) > (d[e]&bitMask))	{		//change to < for descending
			//Swap
			_swap++;
			ull temp = d[s];
			d[s] = d[e];
			d[e] = temp;
			s++;	e--;
		}
		else	{	
			//Equal Case	,	This section d[s] == d[e] . Therefore checking with one data is enough (since d[s]==d[e])
			if((d[s]&bitMask) == 0)	{		//change to '== 1' for descending
				s++;
			}
			else 	{ 
				e--;
			}
		}
	}
	//Here `(s-1)` contains the partition.
	//lb to (s-1) is the 0's partition.
	//(s-1) to ub is the 1's partition.

	//return (s-1);		//Returns Partition Location i.e Ending of 0 (including 0's position.)
	//Find the next bit set in the compMask , and proceed for computation. Not yet Implemented. (Future Enhancement)

	/*********************************************************************************************
	Optimization :- If there are two elements , perform swapping instead of calling a function.
	This is an optimization step. It is done here because to prevent calling function.*/
	
	//0's Partition
	if(((s-1)-lb)==1)	{	//If there are only two elements in 0's Partition
		if(d[lb]>d[s-1])	{	//Swap only if d[i]>d[i+1]
			ull temp = d[lb];
			d[lb] = d[s-1];
			d[s-1] = temp;
		}
	}
	else	{
		FastBitSort(d,lb,s-1,compMask,bitMask>>1);
	}
	//1's Partition
	if((ub-s)==1)	{	//If there are only two elements in one Partition
		if(d[s]>d[ub])	{	//Swap only if d[i]>d[i+1]
			ull temp = d[ub];
			d[ub] = d[s];
			d[s] = temp;
		}
	}
	else	{		//There are more elements , call the function again.
		FastBitSort(d,s,ub,compMask,bitMask>>1);
	}
	/**********************************************************************************************/
}

int main()	{
	ios_base::sync_with_stdio(false);
	ull d[999999];
	ull n;
	ull compMask = 0;

	cout<<"Enter N : ";
	cin>>n;
	cout<<"Enter the elements :\n";
	for(ull i=0;i<n;i++)
		cin>>d[i];

	//compMask = ComputeMask(d,n);
	FastBitSort(d,0,n-1,compMask);

	fflush(stdin);
	cout<<"After Sorting :\n";
	for(ull i=0;i<n;i++)
		cout<<d[i]<<" ";
	cout<<"\n";
	cout<<"\nAnalysis => LOOP : "<<loop<<endl;
	cout<<"\nAnalysis => SWAP : "<<_swap<<endl;
	return 0;
}