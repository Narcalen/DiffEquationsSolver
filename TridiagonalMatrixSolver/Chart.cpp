#include "stdafx.h"
#include "Chart.h"
#include <limits>

Chart::Chart(void){
	InitializeComponent();
}

Chart::Chart(double** phi,int TIME_LOWER_BOUND, int time_steps, double tau, int COORD_LOWER_BOUND, int coord_steps, double h){
	InitializeComponent();
	this -> TIME_LOWER_BOUND = TIME_LOWER_BOUND;
	this -> time_steps = time_steps;
	this -> tau = tau;
	this -> COORD_LOWER_BOUND = COORD_LOWER_BOUND;
	this -> coord_steps = coord_steps;
	this -> h = h;
	this -> phi = new double*[time_steps];
	for (int t = 0; t < time_steps; t++){
		this -> phi[t] = new double[coord_steps];
		for (int x = 0; x < coord_steps; x++){
			this -> phi[t][x] = phi[t][x];
		}
	}
}

//System::Void Chart::Function_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e){
Void Chart::OnPaint(PaintEventArgs^ pe ){
	int width = this -> pictureBox1 -> Width;
	int height = this -> pictureBox1 -> Height;
	int xoffset = 5;
	int yoffset = height - 5;

	double phi_max = -std::numeric_limits<double>::infinity();
	for (int x = 0; x < coord_steps-1; x++){
		if (phi[0][x] > phi_max){
			phi_max = phi[0][x];
		}
		if (phi[time_steps-1][x] > phi_max){
			phi_max = phi[time_steps-1][x];
		}
	}

	int xfactor = width / (COORD_LOWER_BOUND + coord_steps*h);
	int yfactor = height / phi_max - 10;

	pictureBox1 -> Image = gcnew Bitmap(width, height);
	Graphics^ g = Graphics::FromImage(pictureBox1 -> Image);

	//create axes
	g -> DrawLine(Pens::Black, 0, yoffset, width, yoffset);
	g -> DrawLine(Pens::Black, xoffset, 0, xoffset, height);

	Pen^ pen1 = gcnew Pen(Color::Green);
	Pen^ pen2 = gcnew Pen(Color::OrangeRed);
	//draw chart
	for (int x = 0; x < coord_steps-1; x++){
		//t = 0
		g -> DrawLine(pen1, xoffset + xfactor * (COORD_LOWER_BOUND + x*h), (float)(yoffset - yfactor * phi[0][x]), 
			xoffset + xfactor * (COORD_LOWER_BOUND + (x+1)*h), (float)(yoffset - yfactor * phi[0][x+1]));
		//t = 1
		g -> DrawLine(pen2, xoffset + xfactor * (COORD_LOWER_BOUND + x*h), (float)(yoffset - yfactor * phi[time_steps-1][x]), 
			xoffset + xfactor * (COORD_LOWER_BOUND + (x+1)*h), (float)(yoffset - yfactor * phi[time_steps-1][x+1]));
	}
}