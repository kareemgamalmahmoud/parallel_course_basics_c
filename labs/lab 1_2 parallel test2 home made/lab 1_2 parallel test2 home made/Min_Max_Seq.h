#include<iostream>
#include<omp.h>
#include<iomanip>
#include<ctime>
using namespace std;

#define N 100
void main()
{
	long* A = new long[N];
	double wt1, wt2;

	//srand (time(NULL));
	for(long i = 0; i < N; i++)
	{
		A[i] = rand();
	}

	clock_t t1 = clock();
	wt1 = omp_get_wtime();

	long min=A[0];
	long max=A[0];
	for(long i = 0; i < N; i++)
	{
		if(A[i]<min)
			min=A[i];
		if(A[i]>max)
			max=A[i];
	}

	wt2 = omp_get_wtime();
	clock_t t2 = clock();

	for(long i = 0; i < N; i++)
		cout<<A[i]<<" ";
	cout<<"\n";

	cout<<"the seq   min =    "<<min<<endl;
	cout<<"the seq   max =    "<<max<<endl;
	cout << "Time (in seconds) = " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "WTime (in seconds) = " << wt2 - wt1 << endl;

	system("pause");
}