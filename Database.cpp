#include "Database.h"

/**
	Parses input from a given in file.
@param Stream to read from
@param Stream to write to
*/

void Database::parseInput(ifstream& inFile, ofstream& outFile)
{
	string currentLine;
	getline(inFile, currentLine);
	// If it's empty, don't parse.
	if (currentLine == "")
	{
		return;
	}
	outFile << currentLine;
	int openIndex = currentLine.find('(', 0);
	string classType = currentLine.substr(0, openIndex);
	vector<string> paramList;
	// (openIndex + 3) indicates that the ")." will be removed.
	string paramString = currentLine.substr(openIndex + 1, currentLine.size() - (openIndex + 3));
	int numParams = 0;
	// Push back into the appropriate vector based on what the command is.
	if (classType == "snap")
	{
		numParams = 4;
		storeParameters(paramString, paramList, numParams);
		snapData.push_back(Snap(paramList.at(0), paramList.at(1), paramList.at(2), paramList.at(3)));
	}
	else if (classType == "csg")
	{
		numParams = 3;
		storeParameters(paramString, paramList, numParams);
		paramList.at(2);
		gradeData.push_back(Csg(paramList.at(0), paramList.at(1), paramList.at(2)));
	}
	else if (classType == "cdh")
	{
		numParams = 3;
		storeParameters(paramString, paramList, numParams);
		Cdh currentCourse(paramList.at(0), paramList.at(1), paramList.at(2));
		bool isNew = true;
		// Check to see if the course has been declared already or not; if so,
		// Just add to the exisiting cdh object.
		for (unsigned int i = 0; i < timeData.size(); i++)
		{
			if (currentCourse == timeData.at(i))
			{
				isNew = false;
				timeData.at(i).addDay(paramList.at(1));
			}
		}
		if (isNew)
		{
			timeData.push_back(currentCourse);
		}
	}
	else if (classType == "cr")
	{
		numParams = 2;
		storeParameters(paramString, paramList, numParams);
		roomData.push_back(Cr(paramList.at(0), paramList.at(1)));
	}
	// Indicates an unexpected, undefined input.
	else
	{
		throw currentLine;
	}
	vectorList.push_back(currentLine.substr(0, currentLine.size() - 1));
	return;
}

/**
	Stores parameters into a paramlist vector to instantiate objects.
@param String containing all the parameters.
@param Vector of strings holding the parameters
@param Number of parameters being pushed into the vector
*/

void Database::storeParameters(string paramString, vector<string>& paramList, int numParams)
{
	for (int i = 0; i < numParams; i++)
	{
		// Tokenize each parameter and push into the parameter vector.
		string singleItem = paramString.substr(0, paramString.find_first_of(','));
		paramList.push_back(singleItem);
		paramString = paramString.substr(paramString.find_first_of(',') + 1);
	}
	return;
}

/**
	Prints out the vector list.
@param Stream to write to.
*/

void Database::printVectors(ofstream& outFile)
{
	// If it's already sorted, skip this code.
	if (!isListSorted)
	{
		sortVectorList();
	}

	// Print the vector.
	for (unsigned int i = 0; i < vectorList.size(); i++)
	{
		outFile << vectorList.at(i) << endl;
	}
	outFile << endl;
	return;
}

/**
		Sorts vectors into order Snap, Csg, Cdh, and Cr.
		@param Name of class that you want to 
*/
void Database::sortVectorList()
{
	vector<string> sortedVector;
	for (unsigned int i = 0; i < vectorList.size(); i++)
	{
		string classType = vectorList.at(i).substr(0, 3);
		if (classType == "sna")
		{
			sortedVector.push_back(vectorList.at(i));
		}
	}

	for (unsigned int i = 0; i < vectorList.size(); i++)
	{
		string classType = vectorList.at(i).substr(0, 3);
		if (classType == "csg")
		{
			sortedVector.push_back(vectorList.at(i));
		}
	}

	for (unsigned int i = 0; i < vectorList.size(); i++)
	{
		string classType = vectorList.at(i).substr(0, 3);
		if (classType == "cdh")
		{
			sortedVector.push_back(vectorList.at(i));
		}
	}

	for (unsigned int i = 0; i < vectorList.size(); i++)
	{
		string classType = vectorList.at(i).substr(0, 3);
		if (classType == "cr(")
		{
			sortedVector.push_back(vectorList.at(i));
		}
	}

	vectorList = sortedVector;

}

/**
	Prints out a formated list of grades.
	For each course, take each student, see if it matches a grade ID. If true, then print.
@param Stream to write to.
*/

void Database::printGrades(ofstream& outFile) const
{
	for (unsigned int i = 0; i < timeData.size(); i++)
	{
		for (unsigned int j = 0; j < snapData.size(); j++)
		{
			for (unsigned int k = 0; k < gradeData.size(); k++)
			{
				if (snapData.at(j).getStudentID() == gradeData.at(k).getStudentID() &&
					timeData.at(i) == gradeData.at(k))
				{
					outFile << timeData.at(i) << ", " << roomData.at(i) << " " << snapData.at(j).getStudentName() << " " << gradeData.at(k) << endl;
				}
			}
		}
		outFile << endl;
	}
	return;
}

/**
	Prints a formated schedule.
	For each student, take a course each student is in, print student, Course Day, Course Time, room.
@param Stream to write to.
*/

void Database::printSchedule(ofstream& outFile) const
{
	for (unsigned int i = 0; i < snapData.size(); i++)
	{
		outFile << snapData.at(i) << endl;
		for (unsigned int j = 0; j < timeData.size(); j++)
		{
			for (unsigned int k = 0; k < gradeData.size(); k++)
			{
				if (snapData.at(i).getStudentID() == gradeData.at(k).getStudentID() &&
					timeData.at(j) == gradeData.at(k))
				{
					outFile << "\t" << timeData.at(j) << " " << timeData.at(j).getCourseTime() << ", " << roomData.at(j) << endl;
				}
			}
		}
		outFile << endl;
	}
}