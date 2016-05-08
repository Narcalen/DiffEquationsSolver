// TridiagonalMatrixSolver.cpp : main project file.

#include "stdafx.h"
#include "conio.h"
#include "math.h"
#include "iostream"
#include <iomanip>

#include "solve.h"

using namespace std;
using namespace System;


int main(array<System::String ^> ^args)
{
	const int TIME_LOWER_BOUND = 0;
	const int TIME_UPPER_BOUND = 1;
	const int COORD_LOWER_BOUND = 0;
	const int COORD_UPPER_BOUND = 4;
	const double mu = 0.02;

	const double tau = 0.1;
	const double h = 0.1;

	const int coord_steps = (COORD_UPPER_BOUND - COORD_LOWER_BOUND) / h + 1;
	const int time_steps = (TIME_UPPER_BOUND - TIME_LOWER_BOUND) / tau + 1;

	const int matr_size = coord_steps - 2;

	double ** phi = new double*[time_steps];
	for (int i = 0; i < time_steps; i++){
		phi[i] = new double[coord_steps];
	}

	//set phi values according to boundary conditions
	//t = 0 => phi = 0.03
	for (int x = 0; x < coord_steps; x++){
		phi[0][x] = 0.03;
	}
	//x = 0, x = 4 => phi = 0.03
	for (int t = 0; t < time_steps; t++){
		phi[t][0] = 0.03;
		phi[t][coord_steps-1] = 0.03;
	}

	//define matrix coefficients
	double * b = new double[matr_size]; //above main diagonal
	double * c = new double[matr_size];	//main diagonal					  
	double * a = new double[matr_size];	//below main diagonal
	double * f = new double[matr_size]; //free elements

	for (int i = 0; i < matr_size; i++){
		c[i] = 1/tau + 2*mu /(h*h);
		if (i == 0){
			a[i] = 0;
			b[i] = -mu / (h*h);
		}
		else if (i == matr_size -1){
			b[i] = 0;
			a[i] = -mu / (h*h);
		}
		else{
			b[i] = -mu / (h*h);
			a[i] = -mu / (h*h);
		}
	} 

	for (int t = 1; t < time_steps; t++){
		for (int x = 1; x <= matr_size; x++){
			if (x == 1){
				f[x] = source(COORD_LOWER_BOUND + x*h) + phi[t-1][x]/tau + (mu*phi[t][x-1])/(h*h); 
			} else if (x == matr_size){
				f[x] = source(COORD_LOWER_BOUND + x*h) + phi[t-1][x]/tau + (mu*phi[t][x+1])/(h*h); 
			}
			else{
				f[x] = source(COORD_LOWER_BOUND + x*h) + phi[t-1][x]/tau; 
			}
		} 
		solveMatrix(matr_size, a, c, b, &f[1], &phi[t][1]);
	}

	cout << fixed << setprecision(2);
	Console::WriteLine(L"Problem solved");

	//Console::Write(L"{0,6}", "");
	//for (int x = 0; x < coord_steps; x++){
	//	Console::Write(L"{0,6}", (COORD_LOWER_BOUND + x*h).ToString(L"F"));
	//}
	//Console::WriteLine();

	//for (int t = 0; t < time_steps; t++){
	//	Console::Write(L"{0,6}", (TIME_LOWER_BOUND + t*tau).ToString(L"F"));
	//	for (int x = 0; x < coord_steps; x++){
	//		Console::Write(L"{0,6}", phi[t][x].ToString(L"F"));
	//	}
	//	Console::WriteLine();
	//}

	Console::Write(L"{0,8}", "");
	for (int t = 0; t < time_steps; t++){
		Console::Write(L"{0,8}", (TIME_LOWER_BOUND + t*tau).ToString(L"F"));
	}
	Console::WriteLine();

	for (int x = 0; x < coord_steps; x++){
		Console::Write(L"{0,8}", (COORD_LOWER_BOUND + x*h).ToString(L"F"));
		for (int t = 0; t < time_steps; t++){
			Console::Write(L"{0,8}", phi[t][x].ToString(L"F"));
		}
		Console::WriteLine();
	}





	//BEGIN: TEST EXAMPLE
	/*const int n1 = 5;
	double aa[n1] = {0,2,1,1,1};
	double bb[n1] = {3, -1, 1, -1, 0};
	double cc[n1] = {4, 2, 4, 2, 2};
	double ff[n1] = {4, 2, 7.5, 1, -3};
	double xx[n1] = {0,0,0,0, 0};

	solveMatrix(n1,aa,cc,bb,ff,xx);
	cout<<"Matrix x:"<<endl;
	for(int i=0; i<n1; i++){
	cout << xx[i] << endl;
	}*/
	//END: TEST EXAMPLE

	getch();
	for (int i = 0; i < time_steps; i++){
		delete[] phi[i];
	}
	delete [] phi;
	return 0;
}
