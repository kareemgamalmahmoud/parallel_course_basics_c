#include<iostream>
#include<omp.h>
#include<ctime>
#include<iomanip>
using namespace std;

const long n = 1000000;
const int threadsNo = 4;




void main()
{
	clock_t t1, t2;

	double x; 
	double deltax = (double)1 / n;
	double sum = 0.0;

	t1 = clock();

#pragma omp parallel num_threads(threadsNo)
	{

		double mysum = 0.0;
//#pragma omp single
//		int threadsNO = omp_get_num_threads();
		
		int id = omp_get_thread_num();

		double len = (double)n / threadsNo;
		double start = (double)len * id;
		double end = (double)len + start;

	for (int i = start; i < end; i++)
	{
		x = deltax * i;
		mysum += (double)(4 / (1 + x * x))*deltax;
	}
	
#pragma omp critical
	{
		sum += mysum;
		cout << "mysum : " << mysum << "  gsum : " << sum << endl;
	}
	}
	t2 = clock();

	cout << "sum : " << sum << endl;
	cout << "Time (in seconds) = " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	system("pause");
}


/*
void main()
{

	long *a = new long[n];
	long mini = a[0], maxe = a[0];
	
	for (int i = 0; i < n; i++)
	{
		a[i] = rand()+1;
	}


	clock_t t1, t2;
	double wt1, wt2;

	t1 = clock();
	wt1 = omp_get_wtime();
	
#pragma omp parallel num_threads(4) //reduction(min : mini , max : maxe)
	{
		long localmax = a[0];
		long localmin = a[0];

		#pragma omp for
		for (int i = 0; i < n; i++) {
			if (a[i] >= localmax)
				localmax = a[i];
			if (a[i] <= localmin)
				localmin = a[i];
		}

#pragma omp critical
		{
			if (localmax > maxe)
				maxe = localmax ;
			if (localmin < mini)
				mini = localmin ;

			cout << "local max : " << localmax << " local min " << localmin << endl;
		}
	}
	t2 = clock();
	wt2= omp_get_wtime();

	cout << endl;
	cout << "  max : " << maxe << "  min : " << mini << endl;
	cout << "the time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "the time : " << (wt2 - wt1) << endl;


	system("pause");
}
*/


/*
	
		//pi parallel for 
	
	void main()
{

	double sum = 0;
	double deltax = (double)1 / n;
	//double x;

	

	clock_t t1, t2;
	double wt1, wt2;


	t1 = clock();
	wt1 = omp_get_wtime();

#pragma omp parallel num_threads(threadsNo) reduction(+:sum)
	{
		
		double x;
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			x = i*deltax;
			sum += (4 / (1 + x * x))*deltax;
		}
	}

	t2 = clock();
	wt2 = omp_get_wtime();

	cout << endl;
	cout << "the sum : " << sum << endl;
	cout << "time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "time w : " << (wt2 - wt1) << endl;

	system("pause");
}
*/

/*
		with for loop

		void main()
{

	double sum = 0;
	double deltax = (double)1 / n;
	//double x;



	clock_t t1, t2;
	double wt1, wt2;


	t1 = clock();
	wt1 = omp_get_wtime();

#pragma omp parallel num_threads(threadsNo)
	{
		int id = omp_get_thread_num();

		//double start = id * len;
		//double end = start + len;

		double mysum = 0.0;
		double x;
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			x = i*deltax;
			mysum += (4 / (1 + x * x))*deltax;
		}

		#pragma omp critical
		{
			sum += mysum;
			cout << "the id : " << id << "  start : " <<   "  end: " << "  mysum : " << mysum << "  global sum : " << sum << endl;
		}
	}

	t2 = clock();
	wt2 = omp_get_wtime();

	cout << endl;
	cout << "the sum : " << sum << endl;
	cout << "time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "time w : " << (wt2 - wt1) << endl;

	system("pause");
}


*/

/*

pi with out for parallel

void main()
{

	double sum = 0;
	double deltax = (double)1 / n;
	//double x;



	clock_t t1, t2;
	double wt1, wt2;


	t1 = clock();
	wt1 = omp_get_wtime();

#pragma omp parallel num_threads(threadsNo)
	{
		int id = omp_get_thread_num();

		double start = id * len;
		double end = start + len;

		double mysum = 0.0;
		double x;

		for (int i = start; i < end; i++)
		{
			x = i*deltax;
			mysum += (4 / (1 + x * x))*deltax;
		}

		#pragma omp critical
		{
			sum += mysum;
			cout << "the id : " << id << "  start : " << start << "  end: " << end << "  mysum : " << mysum << "  global sum : " << sum << endl;
		}
	}

	t2 = clock();
	wt2 = omp_get_wtime();

	cout << endl;
	cout << "the sum : " << sum << endl;
	cout << "time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "time w : " << (wt2 - wt1) << endl;

	system("pause");
}

*/
/*
omp pi serial

void main()
{

	double sum = 0;
	double deltax = (double)1 / n;
	double x;



	clock_t t1, t2;
	double wt1, wt2;


	t1 = clock();
	wt1 = omp_get_wtime();

	for (int i = 0; i < n; i++)
	{
		x = i*deltax;
		sum += (4 / (1 + x * x))*deltax;
	}

	t2 = clock();
	wt2 = omp_get_wtime();


	cout << "the sum : " << sum << endl;
	cout << "time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "time w : " << (wt2 - wt1) << endl;

	system("pause");
}

*/




