#include "solve.h"
#include "stdafx.h"
#include <math.h>

void solveMatrix (int n, double *a, double *c, double *b, double *f, double *x)
{
	/*double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i]/c[i-1];
		c[i] = c[i] - m*b[i-1];
		f[i] = f[i] - m*f[i-1];
	}

	x[n-1] = f[n-1]/c[n-1];

	for (int i = n - 2; i >= 0; i--)
		x[i]=(f[i]-b[i]*x[i+1])/c[i];*/

	double * alpha = new double[n];
	double * beta = new double[n];
	double z;

	alpha[0] = - b[0] /c[0];
	beta[0] = f[0] / c[0];

	for (int i = 0; i < n-1; i++){
		z = -c[i] - a[i] * alpha[i];
		alpha[i+1] = b[i] / z;
		beta[i+1] = (a[i]*beta[i] - f[i]) / z;		
	}

	x[n-1] = (a[n-1]*beta[n-1] - f[n-1]) / (-c[n-1] - a[n-1] * alpha[n-1]);
	
	for (int i = n-2; i >= 0; i--){
		x[i] = alpha[i+1] * x[i+1] + beta[i+1];
	}
}

double source(double coord){
	double result = exp(-(coord - 2) / 8);
	return result;
}

double source2D(double x, double y){
	double result = exp(-(x + y - 4) / 8);
	return result;
}
