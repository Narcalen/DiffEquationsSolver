// TridiagonalMatrixSolver.cpp : main project file.

#include "stdafx.h"
#include "conio.h"
#include "math.h"
#include "iostream"

#include "solve.h"

using namespace std;
using namespace System;


int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"Hello World");

	int i,n,k;
	const int n1 = 5; 
	double z;

	double eps[n1];
	double X[n1]; 
	double et[n1];

	double A[n1][n1] =	{{4,3,0,0,0},
						{2, 2,-1,0,0},
						{0, 1,4,1,0},
						{0, 0,1,2,-1},
						{0, 0,0,1,2}};


	double B[n1] = {4, 2, 7.5, 1, -3};

		double a[n1] = {0,2,1,1,1};
	double b[n1] = {3, -1, 1, -1, 0};
	double c[n1] = {4, 2, 4, 2, 2};
	double f[n1] = {4, 2, 7.5, 1, -3};
	double x[n1] = {0,0,0,0, 0};

	//double A[n1][n1] = {{1,0,  0,  0},
	//					{1,-2, 1,  0},
	//					{0,1,  -2, 1},
	//					{0,0,  0,  1}};
	//double B[n1] = {0,0,0,2};

	//	double a[n1] = {0,1,1,0};
	//double b[n1] = {0,1,1,0};
	//double c[n1] = {1,-2,-2,1};
	//double f[n1] = {0,0,0,2};
	//double x[n1] = {0,0,0,0};

	cout<<"Matrix A:"<<endl;
	for (i=0;i<n1;i++)
	{
		for (k=0;k<n1;k++)
			cout<<A[i][k]<<"\t ";
		cout<<endl;
	}

	cout<<"Matrix B:"<<endl;
	for (i=0;i<n1;i++)
		cout<<B[i]<<endl;

	n=n1-1;

	eps[0]=-A[0][1]/A[0][0];
	et[0]=B[0]/A[0][0];

	for(i=1;i<n;i++)
	{
		z=A[i][i]+A[i][i-1]*eps[i-1];
		eps[i]=-A[i][i+1]/z;
		et[i]=(B[i]-A[i][i-1]*et[i-1])/z;
	}

	X[n]=(B[n]-A[n][n-1]*et[n-1])/(A[n][n]+A[n][n-1]*eps[n-1]);

	for(i=n-1;i>=0;i--)
		X[i]=eps[i]*X[i+1]+et[i];

	/*eps[0] = -A[0][1] / (double)A[0][0];
	et[0] = B[0] / (double)A[0][0];

	for (i = 0; i < n; i++){
	z = A[i][i] + A[i][i-1]*eps[i-1];
	eps[i+1] = -A[i][i+1]/z;
	et[i+1] = (B[i] - A[i][i-1]*et[i-1]) / z;
	}

	X[n] = (B[n] - A[n][n-1] * et[n]) / (A[n][n] + A[n][n-1]*eps[n]);

	for (i = n-1; i >= 0; i --){
	X[i] = eps[i+1] * X[i+1] + et[i+1];
	}*/

	cout<<"Matrix X:"<<endl;
	for(i=0;i<n1;i++)
		cout<<X[i]<<endl;

	solveMatrix(n1,a,c,b,f,x);
	cout<<"Matrix x:"<<endl;
	for(i=0;i<n1;i++)
		cout<<x[i]<<endl;

	getch();
	return 0;
}
