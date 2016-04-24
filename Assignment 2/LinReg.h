/*****************************************************************************************************************
	Filename: LinReg.h
	Version: 1.00
	Author: Kieran Gillibrand
	Student Number: 040-756-866
	Course Name: Numerical Computing, CST8233
	Lab Section: 300
	Assignment Name: Linear Regression; Least Squares Fit to Data
	Assignment Number: 2
	Due Date: Nov 9th 2015
	Submission Date: Nov 6th 2015
	Professor's Name: Andrew Tyler
	Purpose: Declare the LinReg class and it's methods for performing linear regression
*****************************************************************************************************************/

using namespace std; //Standard namespace

//Header guard
#ifndef LINREG_H
#define LINREG_H

#define YEAR_OFFSET 1960.0 //Amount subtracted from all years in the input file
#define CO2_OFFSET 316.5 //Amount subtracted from all co2 values in the input value

#include <vector> //Vector container

//Linreg class
class LinReg
{
	public:
		string load (); //Load from file

		//Get functions
		double getM (void);
		double getC (void);

		//Calculation functions
		void linear (void);
		void power (void);
		void exponential (void);

		double extrapolate (char input, double year); //Extrapolation function

	private:
		//Private variables
		double m = 0.0;
		double c = 0.0;
		
		//Vectors for years and co2 values
		vector <double> years;
		vector <double> co2;
};
#endif
