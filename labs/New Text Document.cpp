#include<iostream>
#include<pthread.h>
using namespace std;
const long vectorlenth=800000;

struct product{
double *a ;
double *b;
double sum;
long veclenth;
};

void fun()
{
	double *x,*y;
	product p;
	x = p.a;
	y = p.b;
	for(int i=0;i<p.veclenth;i++)
	{
		p.sum += x[i]*y[i];
	}


}


void main()
{ 
	product p;
	p.veclenth=vectorlenth;
	p.a=new double[vectorlenth];
	p.b=new double[vectorlenth];
	for(int i=0;i<vectorlenth;i++)
	{
		p.a[i]=1;
		p.b[i]=1;
	
	}
	

	system("pause");
}