/*****************************************************************************************************************
	Filename: Main.cpp
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
	Purpose: Provide the user interface for performing linear regression
*****************************************************************************************************************/

using namespace std; //Standard namespace

#include <iostream> //Output and input streams 
#include <iomanip> //setprecision for cin floating point

#include "LinReg.h" //LinReg header for LinReg class

/*****************************************************************************************************************
	Function Name: main
	Purpose: main execution function
	Function Input Parameters: None (void)
	Function Output Parameters: An integer depending on execution
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
int main (void)
{
	char input = 0; //Input for main menu
	string path = string (); //Path string returned by load ()
	char subInput = 0; //Input for submenu
	double year = 0.0; //Year value for extrapolation

	//Main menu loop
	while (input != 4)
	{
		system ("CLS");
		cout << "*******************************************************" << endl;
		cout << "Linear Regression of Data: Main Menu" << endl;
		cout << "1. Linear:\ty = m*x + c" << endl;
		cout << "2. Power Law:\ty = m*x^c" << endl;
		cout << "3. Exponential:\ty = m*e^(cx)" << endl;
		cout << "4. Quit" << endl;
		cout << "*******************************************************" << endl;
		cout << "Select an option: ";
		cin >> input;

		//Exit
		if (input == '4')
			return 0;

		//Regression
		if (input == '1' || input == '2' || input == '3')
		{
			cout << endl;

			LinReg linreg = LinReg (); //Create a LinReg object
			path = linreg.load (); //Load from file
			cout << endl;

			cout << "Done loading" << endl;

			//Run the chosen linreg function and display the equation
			switch (input)
			{
				//Linear
				case '1':
					linreg.linear ();

					cout << "Done linear calculations" << endl;

					cout << "Straight line fit to " << path.c_str () << ":" << endl;
					cout << setprecision (3) << "\tCO2 Level = " << linreg.getM () << "t + " << linreg.getC () << endl;
				break;

				//Power series
				case '2':
					linreg.power ();

					cout << "Power law fit to " << path.c_str () << ":" << endl;
					cout << setprecision (3) << "\tCO2 Level = (" << linreg.getM () << ")*t^(" << linreg.getC () << ")"<< endl;
				break;

				//Exponential
				case '3':
					linreg.exponential ();

					cout << "Exponential fit to " << path.c_str () << ":" << endl;
					cout << setprecision (3) << "\tCO2 Level = (" << linreg.getM () << ")*e^" << linreg.getC () << "(x)" << endl;
				break;
			}

			cout << endl;

			subInput = 0;

			//Extrapolation menu loop
			while (subInput != '2')
			{
				cout << "*******************************************************" << endl;
				cout << "Linear Regression of Data: Extrapolation Menu" << endl;
				cout << "1. Do an interpolation/extrapolation" << endl;
				cout << "2. Return to main menu" << endl;
				cout << "*******************************************************" << endl;
				cout << "Select an option: ";
				cin >> subInput;

				cout << endl;

				//Extrapolate or exit
				switch (subInput)
				{
					//Extrapolate
					case '1':
						cout << "Input a year (ex: 2020) to interpolate or extrapolate with: ";
						cin >> year;

						if (cin.fail ())
						{
							cin.clear ();
							cin.ignore (numeric_limits <streamsize>::max (), '\n');
							cout << "Invalid input" << endl;
							break;
						}

						cout << "CO2 level in " << year << " = " << setprecision (3) << linreg.extrapolate (input, year) << endl; //Calculate the co2 value and display it
						cout << endl;
					break;

					//Exit to main menu, free the path
					case '2':
						system ("PAUSE");
					break;
				}
			}
		}

		//Invalid input
		else
		{
			cout << "Invalid input" << endl;
			cin.clear ();
			cin.ignore (numeric_limits <streamsize>::max (), '\n');
			system ("PAUSE");
			system ("CLS");
		}
	}
}
