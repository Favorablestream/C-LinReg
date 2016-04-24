/*****************************************************************************************************************
	Filename: LinReg.cpp
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
	Purpose: Provide the methods for performing linear regression
*****************************************************************************************************************/

using namespace std; //Standard namespace

#include <string> //String class
#include <fstream> //File streams
#include <iostream> //Output and input streams

#include "LinReg.h" //LinReg class

/*****************************************************************************************************************
	Function Name: LinReg
	Purpose: Function that loads an input file
	Function Input Parameters: None (void)
	Function Output Parameters: string path: The path that is used
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
string LinReg::load (void)
{
	ifstream file = ifstream (); //Stream for file input
	string path; //The path of the file to load
	double temp = 0.0; //Temporary variable for file input
	int records = 0; //Number of records (x, y pairs) read

	cin.ignore (numeric_limits <streamsize>::max (), '\n'); //Flush the newline character before using getline

	//Continue to get paths until one can be opened
	do
	{
		cout << "Please enter the filename to open: ";
		getline (cin, path); //Use getline to allow spaces in the path

		//Invalid input
		if (cin.fail ())
		{
			cin.clear ();
			cin.ignore (numeric_limits <streamsize>::max (), '\n');
			cout << "Invalid input" << endl;
		}
		
		file.open (path, ios::in); //Open file for input

		//If path is invalid or file cannot be opened
		if (!file.is_open ())
			cout << "Could not open file: " << path << endl << endl;
	}
	while (!file.is_open ());

	cout << "FILE OPENED FOR READING" << endl;

	//Read records from the file until the end is reached
	while (!file.eof ())
	{
		file >> temp;
		years.push_back (temp);

		file >> temp;
		co2.push_back (temp);

		++records;
	}
	file.close (); //Close file

	//If the capacities are not equal or are equal to 0 then the file is invalid, exit
	if ((years.size () != co2.size ()) || years.size () == 0 || co2.size () == 0)
	{
		cout << "File is invalid" << endl;
		system ("PAUSE");
		exit (1);
	}

	cout << "There are " << records << " records" << endl;
	cout << "File read into memory" << endl;

	return path;
}

/*****************************************************************************************************************
	Function Name: getM
	Purpose: Return the value of m
	Function Input Parameters: None (void)
	Function Output Parameters: M as a double
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
double LinReg::getM (void)
{
	return m;
}
		
/*****************************************************************************************************************
	Function Name: getC
	Purpose: Return the value of c
	Function Input Parameters: None (void)
	Function Output Parameters: C as a double
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
double LinReg::getC (void)
{
	return c;
}

/*****************************************************************************************************************
	Function Name: linear
	Purpose: Calculate the m and c values for a linear best fit
	Function Input Parameters: None (void)
	Function Output Parameters: None (void)
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
void LinReg::linear (void)
{
	double points = (double) years.size (); //Points (n)
	double sumYears = 0.0; //Sum of all x
	double sumYearsSquared = 0.0; //Sum of all x^2
	double sumCO2 = 0.0; //Sum of all y
	double sumYearsCO2 = 0.0; //Sum of all xy

	//Increment through the vectors once and get the sum values
	for (int sumCounter = 0; sumCounter < points; ++sumCounter)
	{
		sumYears += years.at (sumCounter);
		sumYearsSquared += pow (years.at (sumCounter), 2.0);

		sumCO2 += co2.at (sumCounter);
		sumYearsCO2 += years.at (sumCounter) * co2.at (sumCounter);
	}
	
	m = ((points * sumYearsCO2) - (sumYears * sumCO2)) / ((points * sumYearsSquared) - pow (sumYears, 2.0)); //Calculate m 

	c = ((sumYearsSquared * sumCO2) - (sumYearsCO2 * sumYears)) / ((points * sumYearsSquared) - pow (sumYears, 2.0)); //Calculate c
}

/*****************************************************************************************************************
	Function Name: power
	Purpose: Calculate the m and c values for a power series best fit
	Function Input Parameters: None (void)
	Function Output Parameters: None (void)
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
void LinReg::power (void)
{
	double points = (double) years.size (); //Points (n)
	double sumYearsLog = 0.0; //Sum of all log(x) (x = log(x)
	double sumYearsLogSquared = 0.0; //Sum of all (log(x))^2 (x^2 = (log(x))^2)
	double sumCO2Log = 0.0; //Sum of all log (y) (y = log (y))
	double sumYearsCO2Log = 0.0; //Sum of all (log (x) * (xy = log (x) * log (y))
	double temp = 0.0; //Temporary variable for calculating m and c values

	//Increment through the vectors once and get the sum values
	for (int sumCounter = 0; sumCounter < points; ++sumCounter)
	{
		sumYearsLog += log (years.at (sumCounter));
		sumYearsLogSquared += pow (log (years.at (sumCounter)), 2.0);

		sumCO2Log += log (co2.at (sumCounter));
		sumYearsCO2Log += log (years.at (sumCounter)) * log (co2.at (sumCounter));
	}

	m = ((points * sumYearsCO2Log) - (sumYearsLog * sumCO2Log)) / ((points * sumYearsLogSquared) - pow (sumYearsLog, 2.0)); //Calculate m

	c = ((sumYearsLogSquared * sumCO2Log) - (sumYearsCO2Log * sumYearsLog)) / ((points * sumYearsLogSquared) - pow (sumYearsLog, 2.0)); //Calculate c

	temp = c; //Store c
	c = m; //c = m
	m = exp (temp); //m = e^c
}

/*****************************************************************************************************************
	Function Name: linear
	Purpose: Calculate the m and c values for an exponential best fit
	Function Input Parameters: None (void)
	Function Output Parameters: None (void)
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
void LinReg::exponential (void)
{
	double points = (double) years.size (); //Points (n)
	double sumYears = 0.0; //Sum of all x
	double sumYearsLogSquared = 0.0; //Sum of all x^2
	double sumCO2Log = 0.0; //Sum of all log (y) (y = log (y))
	double sumYearsCO2Log = 0.0; //Sum of all x * log (y)
	double temp = 0.0; //Temporary variable for calculating m and c values

	//Increment through the vectors once and get the sum values
	for (int sumCounter = 0; sumCounter < points; ++sumCounter)
	{
		sumYears += years.at (sumCounter);
		sumYearsLogSquared += pow (log (years.at (sumCounter)), 2.0);

		sumCO2Log += log (co2.at (sumCounter));
		sumYearsCO2Log += years.at (sumCounter) * log (co2.at (sumCounter));
	}

	m = ((points * sumYearsCO2Log) - (sumYears * sumCO2Log)) / ((points * sumYearsLogSquared) - pow (sumYears, 2.0)); //Calculate m

	c = ((sumYearsLogSquared * sumCO2Log) - (sumYearsCO2Log * sumYears)) / ((points * sumYearsLogSquared) - pow (sumYears, 2.0)); //Calculate c

	temp = c; //Store c
	c = m; //c = m
	m = exp (temp); //m = e^c
}

/*****************************************************************************************************************
	Function Name: extrapolate
	Purpose: Calculate the co2 value for a given year
	Function Input Parameters: char input: The type of regression that was chosen by the user
	Function Output Parameters: The co2 value as a double
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
double LinReg::extrapolate (char input, double year)
{
	year -= YEAR_OFFSET; //Subtract the value that was subtracted from all the years in the input file (1960)

	//Use the appropriate formula, add the amount that was subtracted from all the co2 values in the input file
	switch (input)
	{
		//Linear regression
		case '1':
			return ((m * year) + c) + CO2_OFFSET;

		//Power law regression
		case '2':
			return (m * pow (year, c)) + CO2_OFFSET;

		//Exponential regression
		case '3':
			return (m * exp (c * year)) + CO2_OFFSET;
	}
	return 0.0; //Otherwise return 0.0;
}