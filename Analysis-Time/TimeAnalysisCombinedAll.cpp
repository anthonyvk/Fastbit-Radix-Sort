#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include <fstream>
#include <string>

#define ull unsigned long long int
using namespace std;

ull d[100000000] = {0};		//Needed 1000000000

//For timing information
struct timeval tv;
double dstart,dend;

/*_____________________________________________________________________
______________________________QUICK SORT_____________________________*/
inline void fnSwap(ull *a, ull *b)	{
	ull t = *a; *a = *b; *b = t;
}
ull Partition(ull a[], ull l, ull r)	{
	ull i,j,temp;
	ull p;

	p = a[l];
	i = l;
	j = r+1;

	do	{
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
//_____________________________________________________________________


/*_____________________________________________________________________
______________________________MERGE SORT_____________________________*/
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
//_____________________________________________________________________


/*_____________________________________________________________________
______________________________RADIX SORT_____________________________*/
ull getMax(ull arr[], ull n)
{
    ull mx = arr[0];
    for (ull i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}void countSort(ull arr[], ull n, ull exp)
{
    ull output[n]; // output array
    ull i, count[10] = {0}; 
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 	for (i = n - 1; i >= 0; i--)    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void radixsort(ull arr[], ull n)
{
    ull m = getMax(arr, n);
	for (ull exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
//_____________________________________________________________________


/*_____________________________________________________________________
______________________________RADIXBIT SORT_____________________________*/
#define UNSIGNED_INT 31
#define INT 30
#define UNSIGNED_LONG_LONG_INT 63
#define LONG_LONG_INT 62
#define CHAR 7

void FastBitSort(ull d[],ull lb,ull ub,ull compMask=~0,ull bitMask=(1<<INT))	{		//ub is inclusive
	//Terminating Condition
	if(ub<=lb || bitMask==0 || (ub-lb)==0)	{	return;	}

	ull s = lb , e = ub;
	while(s<=e)	{
		if((d[s]&bitMask) < (d[e]&bitMask))	{		//change to > for descending
			s++;	e--;
		}
		else if((d[s]&bitMask) > (d[e]&bitMask))	{		//change to < for descending
			//Swap
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
}
//_____________________________________________________________________


int main()	{
	ofstream ofile("AllTimeAnalysis.txt");
	ull n;

	cin>>n;
	for(ull i=0;i<n;i++)	{
		cin>>d[i];
	}

	ofile<<"N = "<<n<<endl;
	cout<<"N = "<<n<<endl;

	//Time Analysis - QuickSort
	gettimeofday(&tv,NULL);
	dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
	QuickSort(d,0,n-1);
	gettimeofday(&tv,NULL);
    dend = tv.tv_sec + (tv.tv_usec/1000000.0);
    ofile<<"Quicksort : TIME : "<<(dend-dstart)<<endl;
    cout<<"Quicksort : TIME : "<<(dend-dstart)<<endl;

	//Time Analysis - MergeSort
	gettimeofday(&tv,NULL);
	dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
	MergeSort(d,0,n-1);
	gettimeofday(&tv,NULL);
    dend = tv.tv_sec + (tv.tv_usec/1000000.0);
    ofile<<"Mergesort : TIME : "<<(dend-dstart)<<endl;
    cout<<"Mergesort : TIME : "<<(dend-dstart)<<endl;

	//Time Analysis - RadixSort
	gettimeofday(&tv,NULL);
	dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
	radixsort(d, n);
	gettimeofday(&tv,NULL);
    dend = tv.tv_sec + (tv.tv_usec/1000000.0);
    ofile<<"Radixsort : TIME : "<<(dend-dstart)<<endl;
    cout<<"Radixsort : TIME : "<<(dend-dstart)<<endl;

    //Time Analysis - RadixBitSort
	gettimeofday(&tv,NULL);
	dstart = tv.tv_sec + (tv.tv_usec/1000000.0);
	FastBitSort(d,0,n-1,NULL);
	gettimeofday(&tv,NULL);
    dend = tv.tv_sec + (tv.tv_usec/1000000.0);
    ofile<<"RadixBitSort : TIME : "<<(dend-dstart)<<endl;
    cout<<"RadixBitSort : TIME : "<<(dend-dstart)<<endl;

    ofile<<endl<<endl;

	return 0;
}