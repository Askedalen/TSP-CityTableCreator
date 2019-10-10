// CityTableCreator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int cityCount; // Number of cities
std::vector<std::vector<int>> costTable; // 2 Dimensional vector containing the distances between each city. 
bool alternativeDistances = false;

void fillVector() {
	/*
	This function fills the vector costTable with randomly generated numbers in the interval [1, 99].
	The table is symmetric, so that the distance from city 1 to city 2 is the same as city 2 to city 1,
	and the distance between the same city is 0. 
	*/
	for (int i = 0; i < cityCount; i++) {
		costTable[i] = std::vector<int>(cityCount); // Create a new vector in the specified index
		for (int j = 0; j < cityCount; j++) {
			if (i == j) {
				// If i and j are the same, the value is 0. The distance from city 1 to city 1 is 0.
				costTable[i][j] = 0; 
				std::cout << "Value in " << i << ", " << j << " is " << "0" << std::endl;
			} else {
				// If i and j are different, checks whether the distance between the two cities already has been created.
				const std::vector<int>& city = costTable.at(j); // Gets the vector that is column j, rather than row j.
				int existingNumber;
				// Checks if the index i in the column has a value
				try { existingNumber = city.at(i); } catch (std::out_of_range oor) { existingNumber = 0; } 

				if (existingNumber == 0) {
					// If distance is not already created, adds a random number between and excluding 0 and 100.
					// If the random number is 0, it creates a new random number.
					// This is repeated until the number is not 0.
					if (alternativeDistances) {
						costTable[i][j] = (rand() % 50) + 50;
					} else {
						do {
							costTable[i][j] = rand() % 100; // Create random number
						} while (costTable[i][j] == 0); // While number is 0. 
					}
					std::cout << "Value in " << i << ", " << j << " is " << costTable[i][j] << std::endl;
					
				} else {
					// If distance is already created, adds that distance, so the table is symmetrical.
					costTable[i][j] = city.at(i);
					std::cout << "Value in " << i << ", " << j << " is " << costTable[i][j] << std::endl;
				}
			}
		}
	}
}

void printVectorToFile() {
	/*
	This function writes the generated table to a file.
	*/
	char filename[128]; // Uses char[] instead of string because ofstream
	std::cout << "Filename: ";
	std::cin >> filename; // User inputs filename
	std::ofstream file(filename); // Creates an output file stream.
	if (file.is_open()) { 
		for (const std::vector<int>& vec : costTable) { // For each vector in costTable
			for (const int& num : vec) { // For each number in vec
				file << num << " "; // Prints the number and a space to the file
			}
			file << std::endl; // Prints \n to the file
		}
		std::cout << "Successfully wrote to file!" << std::endl;
	} else {
		std::cout << "Could not open file!" << std::endl;
	}
}

void printVector() {
	/*
	This function prints the vector to the command line.
	*/
	std::cout << "      ";
	for (int x = 0; x < cityCount; x++) {
		std::cout << (x < 9 ? "0" : "") << x + 1 << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < cityCount; i++) {
		std::cout << (i < 9 ? "0" : "") << i + 1 << " || ";
		for (int j = 0; j < cityCount; j++) {
			int cellContent = costTable[i][j];
			std::cout << (cellContent < 10 ? "0" : "") << cellContent << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void setCityCount() {
	std::cout << "How many cities?" << std::endl;
	std::cin >> cityCount;
}

void runLoop() {
	do {
		setCityCount();
		costTable.clear();
		costTable.resize(cityCount);
		fillVector();
		if (cityCount <= 50) printVector();
		printVectorToFile();
	} while (true);
}

int main()
{
	runLoop();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
