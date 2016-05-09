#include "conio.h"
#include "math.h"
#include "iostream"
#include <iomanip>

#include "../TridiagonalMatrixSolver/solve.h"

using namespace std;
using namespace System;

int main(array<System::String ^> ^args){
	const int TIME_LOWER_BOUND = 0;
	const int TIME_UPPER_BOUND = 1;
	const int COORD_LOWER_BOUND_X = 0;
	const int COORD_UPPER_BOUND_X = 4;
	const int COORD_LOWER_BOUND_Y = 0;
	const int COORD_UPPER_BOUND_Y = 4;

	const double mu = 0.02;

	const double tau = 0.5;
	const double delta_x = 1;
	const double delta_y = 1;

	const int coord_x_steps = (COORD_UPPER_BOUND_X - COORD_LOWER_BOUND_X) / delta_x + 1;
	const int coord_y_steps = (COORD_UPPER_BOUND_Y - COORD_LOWER_BOUND_Y) / delta_y + 1;
	const int time_steps = 4*(TIME_UPPER_BOUND - TIME_LOWER_BOUND) / tau + 1;

	const int matr_size_x = coord_x_steps - 2;
	const int matr_size_y = coord_y_steps - 2;

	//initialize phi
	double *** phi = new double**[time_steps];
	for (int t = 0; t < time_steps; t++){
		phi[t] = new double*[coord_x_steps];
		for (int x = 0; x < coord_x_steps; x++){
			phi[t][x] = new double[coord_y_steps];
		}
	}
	//set phi values according to boundary conditions
	//t = 0 => phi = 0.03
	for (int x = 0; x < coord_x_steps; x++){
		for (int y = 0; y < coord_y_steps; y++){
			phi[0][x][y] = 0.03;
		}
	}
	for (int t = 0; t < time_steps; t++){
		//x = 0, x = 4 => phi = 0.03
		for (int y = 0; y < coord_y_steps; y++){
			phi[t][0][y] = 0.03;
			phi[t][coord_x_steps-1][y] = 0.03;
		}
		//y = 0, y = 4 => phi = 0.03
		for (int x = 0; x < coord_x_steps; x++){
			phi[t][x][0] = 0.03;
			phi[t][x][coord_y_steps-1] = 0.03;
		}
	}

	int t = 1;
	while(t < time_steps){
		//BEGIN: equation 1
		//define matrix coefficients
		double * b = new double[matr_size_x]; //above main diagonal
		double * c = new double[matr_size_x];	//main diagonal					  
		double * a = new double[matr_size_x];	//below main diagonal
		double * f = new double[matr_size_x]; //free elements
		double * solutions = new double[matr_size_x];
		for (int i = 0; i < matr_size_x; i++){
			c[i] = 1 / tau + 2 * mu /(2 * delta_x * delta_x);
			if (i == 0){
				a[i] = 0;
				b[i] = -mu / (2 * delta_x * delta_x);
			}
			else if (i == matr_size_x - 1){
				b[i] = 0;
				a[i] = -mu / (2 * delta_x * delta_x);
			}
			else{
				b[i] = -mu / (2 * delta_x * delta_x);
				a[i] = -mu / (2 * delta_x * delta_x);
			}
		}	
		//solve equations systems
		for (int y = 1; y < matr_size_y; y++){
			for (int x = 1; x <= matr_size_x; x++){
				if (x == 1){
					f[x] = phi[t-1][x][y] * (1/tau - mu/(delta_x *delta_x)) + mu/(2 * delta_x * delta_x) * (phi[t][x-1][y] + phi[t-1][x+1][y] + phi[t-1][x-1][y]); 
				} else if (x == matr_size_x){
					f[x] = phi[t-1][x][y] * (1/tau - mu/(delta_x * delta_x)) +  mu/(2 * delta_x * delta_x) * (phi[t][x+1][y] + phi[t-1][x+1][y] + phi[t-1][x-1][y]);
				}
				else{
					f[x] = phi[t-1][x][y] * (1/tau - mu/(delta_x * delta_x)) +  mu/(2 * delta_x * delta_x) * (phi[t-1][x+1][y] + phi[t-1][x-1][y]);
				}
			}
			solveMatrix(matr_size_x, a, c, b, &f[1], solutions);
			for (int x = 1; x <= matr_size_x; x++){
				phi[t][x][y] = solutions[x];
			}
		}
		//END: equation 1

		//BEGIN: equation 2
		//define matrix coefficients
		b = new double[matr_size_y]; //above main diagonal
		c = new double[matr_size_y];	//main diagonal					  
		a = new double[matr_size_y];	//below main diagonal
		f = new double[matr_size_y]; //free elements
		solutions = new double[matr_size_y];
		for (int i = 0; i < matr_size_y; i++){
			c[i] = 1/tau + 2 * mu /(2 * delta_y * delta_x);
			if (i == 0){
				a[i] = 0;
				b[i] = -mu / (2 * delta_y * delta_y);
			}
			else if (i == matr_size_y -1){
				b[i] = 0;
				a[i] = -mu / (2 * delta_y * delta_y);
			}
			else{
				b[i] = -mu / (2 * delta_y * delta_y);
				a[i] = -mu / (2 * delta_y * delta_y);
			}
		}	
		//solve equations systems
		//END: equation 2
	}

	//END: equation 1

	//output the results
	Console::WriteLine(L"Problem solved");
	for (int t = 0; t < time_steps; t++){
		Console::WriteLine(L"{0,8}", "");
		Console::WriteLine(L"Time = {0,8}", ((TIME_LOWER_BOUND + t*tau)/4).ToString(L"F"));
		Console::Write(L"{0,8}", "");
		for (int y = 0; y < coord_y_steps; y++){
			Console::Write(L"{0,8}", (COORD_LOWER_BOUND_Y + y*delta_y).ToString(L"F"));
		}
		Console::WriteLine();
		for (int x = 0; x < coord_x_steps; x++){
			Console::Write(L"{0,8}", (COORD_LOWER_BOUND_X + x*delta_x).ToString(L"F"));
			for (int y = 0; y < coord_y_steps; y++){
				Console::Write(L"{0,8}", phi[t][x][y].ToString(L"F"));
			}
			Console::WriteLine();
		}
	}

	getch();
	//cleanup
	for (int t = 0; t < time_steps; t++){
		for (int x = 0; x < coord_x_steps; x++){
			delete[] phi[t][x];
		}
		delete[] phi[t];
	}
	delete [] phi;
	return 0;
}