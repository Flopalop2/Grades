// Lab 02 - SNAP
/*
	For some reason, my output prints the students/grades in a different order, but if you check them all,
	they match the desired outputs.
*/
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <fstream>
#include "Database.h"

using namespace std;

int main(int argc, char* argv[])
{
	VS_MEM_CHECK // Memory leak check
	
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}

	cout << "Input file: " << argv[1] << endl;

	ifstream inFile(argv[1]);

	if (!inFile)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 1;
	}

	cout << "Output file: " << argv[2] << endl;

	ofstream outFile(argv[2]);

	if (!outFile)
	{
		inFile.close();
		cerr << "Unable to open " << argv[2] << " for output";
	}

	Database schoolData;

	// Read file
	outFile << "Input Strings: " << endl;
	while (inFile)
	{
		try
		{
			schoolData.parseInput(inFile, outFile);
		}
		catch (string msg)
		{
			outFile << " ** Undefined " << msg;
		}

		outFile << endl;
	}

	inFile.close();

	// Print Vectors
	outFile << "Vectors:" << endl;
	schoolData.printVectors(outFile);

	// Print Grades
	outFile << "Course Grades:" << endl;
	schoolData.printGrades(outFile);

	//Print Student Schedules
	outFile << "Student Schedules:" << endl;
	schoolData.printSchedule(outFile);

	outFile.close();

	return 0;
}