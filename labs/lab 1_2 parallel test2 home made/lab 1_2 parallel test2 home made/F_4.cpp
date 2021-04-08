#include<iostream>
#include<math.h>
#include<omp.h>
#include<iomanip>
#include<ctime>
#include <stdio.h>
using namespace std;

#define N 100
#define ThreadsNo 4
void main()
{
	long* A = new long[N];
	double wt1, wt2;

	for(long i = 0; i < N; i++)
	{
		A[i] = rand();
	}

	clock_t t1 = clock();
	wt1 = omp_get_wtime();
	int MinResult = A[1], MaxResult = A[1];
	/*#pragma omp parallel for num_threads(ThreadsNo) reduction(min:Min, max:Max)
	for(long i = 0; i < N; i++) {
		if(A[i]<Min)
			Min = A[i];
		if(A[i]>Max)
			Max = A[i];
	}*/
	#pragma omp parallel num_threads(ThreadsNo)
	{
		int min = A[0], max = A[0];
	#pragma omp for
		for(long i = 0; i < N; i++) {
			if(A[i] < min)
				min = A[i];
			if(A[i] > max)
				max = A[i];
		}
		#pragma omp critical
		{
			if(min < MinResult)
				MinResult = min;
			if(max > MaxResult)
				MaxResult = max;
		}
	}

	wt2 = omp_get_wtime();
	clock_t t2 = clock();

	/*for(long i = 0; i < N; i++)
		cout<<A[i]<<" ";
	cout<<"\n";*/

	cout<<"the seq   min =    "<<MinResult<<endl;
	cout<<"the seq   max =    "<<MaxResult<<endl;
	cout << "Time (in seconds) = " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "WTime (in seconds) = " << wt2 - wt1 << endl;

	system("pause");
}