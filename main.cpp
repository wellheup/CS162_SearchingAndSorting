
/*********************************************************************
** Author: Phillip Wellheuser							CS 162-400
** Date: 5/26/19
** Description: Reads several text tiles, searches them for a user
**		generated integer value, prints the results and saves sorted
**		versions of the files read to user generated .txt files
**    using simple, bubble, and binary search methods
*********************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "menuShell.hpp"

void loadFromFile(std::vector<int> &loadThis, std::string fileName);
std::string simpleSearch(std::vector<int> searchThis, int lookFor, std::string name);
void bubbleSort(std::vector<int> &sortThis);
void printList(std::vector<int> printThis, std::string name);
void writeOutFiles(std::vector<int> writeThis, std::string name);
void writeOutFiles(std::vector<int> writeThis, std::string name, std::string outFileName);
std::string binarySearch(std::vector<int> searchThis, int lookFor, std::string name);

std::vector<int> numVect,
	earlyVect,
	middleVect,
	endVect;

std::string numFile = "num.txt",
	earlyFile = "early.txt",
	middleFile = "middle.txt",
	endFile = "end.txt",
  numResult = "numResult.txt",
  earlyResult = "earlyResult.txt",
  middleResult = "middleResult.txt",
  endResult = "endResult.txt";

int lookFor;

int main() {
	//load files
	loadFromFile(numVect, numFile);
	loadFromFile(earlyVect, earlyFile);
	loadFromFile(middleVect, middleFile);
	loadFromFile(endVect, endFile);
	//search files
	lookFor = chooseIntInRange("Please enter an integer to search the UNSORTED files for: ", -100000, 100000);
	std::cout << simpleSearch(numVect, lookFor, numFile) << std::endl;
	std::cout << simpleSearch(earlyVect, lookFor, earlyFile) << std::endl;
	std::cout << simpleSearch(middleVect, lookFor, middleFile) << std::endl;
	std::cout << simpleSearch(endVect, lookFor, endFile) << std::endl;
	std::cout << "\n";
	//sort files
	bubbleSort(numVect);
	bubbleSort(earlyVect);
	bubbleSort(middleVect);
	bubbleSort(endVect);
	//print sorted files
	printList(numVect, numFile);
	printList(earlyVect, earlyFile);
	printList(middleVect, middleFile);
	printList(endVect, endFile);
	std::cout << "\n";
	//write sorted files to new files
	writeOutFiles(numVect, numFile, numResult);
	writeOutFiles(earlyVect, earlyFile, earlyResult);
	writeOutFiles(middleVect, middleFile, middleResult);
	writeOutFiles(endVect, endFile, endResult);	
	std::cout << "\n";

	//search sorted files
	lookFor = chooseIntInRange("Please enter an integer to search the SORTED files for: ", -100000, 100000);
	std::cout << binarySearch(numVect, lookFor, numFile) << std::endl;
	std::cout << binarySearch(earlyVect, lookFor, earlyFile) << std::endl;
	std::cout << binarySearch(middleVect, lookFor, middleFile) << std::endl;
	std::cout << binarySearch(endVect, lookFor, endFile) << std::endl;
	std::cout << "\n";
	//give user a chance to see sorted search results
	std::cout << "Press Enter to close the program...";
	std::cin.ignore();
	return 0;
}

/*********************************************************************
** Description: loadFromFile(), takes 2 parameters, a vector to save 
**		read int entries to and a string file name to read
*********************************************************************/
void loadFromFile(std::vector<int> &loadThis, std::string fileName) {
	int number;
	std::ifstream currentFile;
	currentFile.open(fileName, std::ios::in);
	if (!currentFile) {
		std::cout << "Error opening file" << std::endl;
	}
	while (currentFile >> number) {
		loadThis.push_back(number);
	}
	currentFile.close();
}

/*********************************************************************
** Description: simpleSearch(), takes 3 parameters, vector to search,
**		integer to search for, and a string to use when constructing 
**		the return string. Based on code from textbook pg 612
*********************************************************************/
std::string simpleSearch(std::vector<int> searchThis, int lookFor, std::string name) {
	unsigned int index = 0;
	bool found = false;
	std::string result;
	while (index < searchThis.size() && !found) {
		if (searchThis[index] == lookFor) {
			found = true;
			result = name + ": target value found";
			return result;
		}
		index++;
	}
	result = name + ": target value NOT found";
	return result;
}

/*********************************************************************
** Description: bubbleSort(), takes 1 parameter, a vector to sort,
**		and sorts it using basic bubble sort methods. Based on code 
**		from textbook pg 615
*********************************************************************/
void bubbleSort(std::vector<int> &sortThis) {
	int temp;
	bool madeSwap;

	do {
		madeSwap = false;
		for (unsigned int count = 0; count < (sortThis.size() - 1); count++) {
			if (sortThis[count] > sortThis[count + 1]) {
				temp = sortThis[count];
				sortThis[count] = sortThis[count + 1];
				sortThis[count + 1] = temp;
				madeSwap = true;
			}
		}
	} while (madeSwap == true);
}

/*********************************************************************
** Description: printList(), takes 2 parameters, a vector to print
**		the contents of, and a name to label it, then prints the 
**		contents as a list to the console
*********************************************************************/
void printList(std::vector<int> printThis, std::string name) {
	std::cout << "The sorted contents of " << name << " in ascending order: ";
	for (unsigned int i = 0; i < printThis.size(); i++) {
		if (i == printThis.size() - 1) {
			std::cout << printThis[i];
		}
		else {
			std::cout << printThis[i] << " ";
		}
	}
	std::cout << "\n";
}

/*********************************************************************
** Description: writeOutFiles(), takes 2 parameters, a vector to write
**		the contents of, and a name to label the file it writes to
**		then writes the contents of the vector to that file name
*********************************************************************/
void writeOutFiles(std::vector<int> writeThis, std::string name) {
	std::string prompt = "Please enter a name for the file in which to save sorted " + name;
	std::string outFileName = enterTxtFileWithinRange(prompt, 1, 30);
	std::ofstream outFile;
	outFile.open(outFileName, std::ios::out);
	for (unsigned int i = 0; i < writeThis.size(); i++) {
		if (i == writeThis.size() - 1) {
			outFile << writeThis[i];
		}
		else {
			outFile << writeThis[i] << ", ";
		}
	}
	outFile << "\n";

	outFile.close();
}

/*********************************************************************
** Description: writeOutFiles(), takes 2 parameters, a vector to write
**		the contents of, and a name to label the file it writes to
**		then writes the contents of the vector to that file name
*********************************************************************/
void writeOutFiles(std::vector<int> writeThis, std::string name, std::string outFileName) {
	std::string prompt = "Please enter a name for the file in which to save sorted " + name;
	std::ofstream outFile;
	outFile.open(outFileName, std::ios::out);
	for (unsigned int i = 0; i < writeThis.size(); i++) {
		if (i == writeThis.size() - 1) {
			outFile << writeThis[i];
		}
		else {
			outFile << writeThis[i] << ", ";
		}
	}
	outFile << "\n";

	outFile.close();
}

/*********************************************************************
** Description: binarySearch(), takes 3 parameters, vector to search,
**		integer to search for, and a string to use when constructing
**		the return string. Based on code from textbook pg 607
*********************************************************************/
std::string binarySearch(std::vector<int> searchThis, int lookFor, std::string name) {
	int first = 0,
		last = searchThis.size() - 1,
		middle;
	bool found = false;
	std::string result;
	while (!found && first<=last) {
		middle = (first + last) / 2;
		if (searchThis[middle] == lookFor) {
			found = true;
			result = name + ": target value found";
			return result;
		}
		else if (searchThis[middle] > lookFor) {
			last = middle - 1;
		}
		else {
			first = middle + 1;
		}
	}
	result = name + ": target value NOT found";
	return result;
}