#include<iostream>
using namespace std;

struct dotProductData {
	double* a; //first vector
	double* b; //second vector
	double sum = 0; //sum of the multiplied corresponding numbers of the two vectors
	int vecLength; //vector length
}dotStr;

int VecLen = 100000;

void dotProduct() {
	double *x, *y;
	x = dotStr.a;
	y = dotStr.b;

	for (int i = 0; i < dotStr.vecLength; i++) {
		dotStr.sum += x[i] * y[i];
	}
}


void main() {

	dotStr.vecLength = VecLen;

	dotStr.a = new double[VecLen];
	dotStr.b = new double[VecLen];

	for (int i = 0; i < VecLen; i++) {
		dotStr.a[i] = 1;
		dotStr.b[i] = 1;
	}

	dotProduct();

	cout << "The product is: " << dotStr.sum << endl;

	system("pause");
}