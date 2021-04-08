#include<iostream>
#include<ctime>
#include<omp.h>
using namespace std;


void main()
{

	clock_t t1, t2;
	double wt1, wt2;

	int threadsNo, id;

	t1 = clock();
	//to get time for the omp only
	wt1 = omp_get_wtime();

#pragma omp parallel num_threads(6) default(shared) private(id)
	{
		//the index of the thread
		id = omp_get_thread_num();

		//for(int i = 0; i < 100000; i++);

		//to get the no of threads defult 4 for my pc
#pragma omp single
		//if (id == 0)// 3ashan msh kol thread t7sb al 3adad
		threadsNo = omp_get_num_threads();
#pragma omp critical
		cout << "hello from thread -> " << id << " <-total no of threads is : " << threadsNo << endl;

	}


	t2 = clock();
	wt2 = omp_get_wtime();

	cout << "cpu time in sec : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "w time in sec : " << wt2 - wt1 << endl;


	system("pause");
}