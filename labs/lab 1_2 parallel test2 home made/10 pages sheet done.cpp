#include<iostream>
#include<ctime>
#include<omp.h>
#include<iomanip>
using namespace std;

const int n = 10000;


void main()
{

	clock_t t1, t2;
	double wt1, wt2;
	int *a, sum = 0, mysum;
	a = new int[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = 1;
	}

	int threadsNo = 4;
	double len;


	t1 = clock();
	wt1 = omp_get_wtime();

	//mmoken 25tser kol aly katabto ta7t dah 
#pragma omp parallel for num_threads(threadsNo) reduction(+:sum)
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}

		/*
#pragma omp parallel num_threads(threadsNo) 
	{
#pragma omp single
		{
			cout << "using  " << threadsNo << "  htread : " << endl;
			//len = (double)n / threadsNo;
		}

		int id = omp_get_thread_num();//return the thread ID
		//int from = len * id;
		//int to = from + len;

		mysum = 0;
#pragma omp for reduction(+:sum)
		for (int i = 0; i < n; i++) 
		{ 
			sum += a[i];
		}
//#pragma omp critical
//			sum += mysum;
	}
		*/

	/*
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	*/

	t2 = clock();
	wt2 = omp_get_wtime();

	cout << setprecision(10);
	cout << "sum = " << sum << endl;
	cout << "cpu time :" << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "wtime :" << wt2 - wt1 << endl;

	system("pause");
}