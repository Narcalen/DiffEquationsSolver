#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for Chart
/// </summary>
public ref class Chart : public System::Windows::Forms::Form
{
public:
	Chart(void);
	Chart(double** phi,int TIME_LOWER_BOUND, int time_steps, double tau, int COORD_LOWER_BOUND, int coord_steps, double h);

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~Chart()
	{
		if (components)
		{
			delete components;
		}
	}
	virtual Void Chart::OnPaint(PaintEventArgs^ pe ) override;

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container ^components;
private: System::Windows::Forms::PictureBox^  pictureBox1;
		 double ** phi;
		 int TIME_LOWER_BOUND;
		 int time_steps;
		 double tau;
		 int COORD_LOWER_BOUND;
		 int coord_steps;
		 double h;

#pragma region Windows Form Designer generated code
		 /// <summary>
		 /// Required method for Designer support - do not modify
		 /// the contents of this method with the code editor.
		 /// </summary>
		 void InitializeComponent(void)
		 {
			 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			 this->SuspendLayout();
			 // 
			 // pictureBox1
			 // 
			 this->pictureBox1->Location = System::Drawing::Point(-1, -2);
			 this->pictureBox1->Name = L"pictureBox1";
			 this->pictureBox1->Size = System::Drawing::Size(658, 529);
			 this->pictureBox1->TabIndex = 0;
			 this->pictureBox1->TabStop = false;
			 // 
			 // Chart
			 // 
			 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 this->ClientSize = System::Drawing::Size(656, 527);
			 this->Controls->Add(this->pictureBox1);
			 this->MaximizeBox = false;
			 this->Name = L"Chart";
			 this->Text = L"Chart";
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			 this->ResumeLayout(false);

		 }
#pragma endregion
private:
	System::Void Chart_Load(System::Object^  sender, System::EventArgs^  e) {}
	//System::Void Function_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
};
