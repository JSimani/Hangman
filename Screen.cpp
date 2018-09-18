#include <iostream>
#include <fstream>
#include <cstdlib>
#include "termfuncs.h"
#include "Screen.h"
using namespace std;

/* Constructor
 * Purpose: Initializes all member variables in the Screen object
 * Parameters: None
 * Return Type: None
 * Errors Thrown: None */
Screen::Screen()
{
    object = NULL;
    objectCount = 0;
}

/* Destructor
 * Purpose: Frees all heap-allocated memory in the object
 * Parameters: None
 * Return Type: None
 * Errors Thrown: None */
Screen::~Screen()
{
    if (object) {
        delete []object;
        object = NULL;
    }
}

/* countObjects()
 * Purpose: Counts the number of objects being read-in
 * Parameters: string (name of file to be opened and read)
 * Return Type: void
 * Errors Thrown: runtime_error if the file could not be opened */
void Screen::countObjects(string filename)
{
    ifstream infile(filename);
    if (!infile.is_open()) {
        string errorMessage = "Error opening file " + filename;
        throw runtime_error(errorMessage);
    }

    string check;
    int count = 0;
    while (infile >> check) {
        if (check == "object")
            count++;
    }

    infile.close();
    // Stores the object count in a member variable of the Screen object
    objectCount = count;
}

/* readIn()
 * Purpose: Reads in the objects into the dynamic array of objects
 * Parameters: string (name of file to be opened and read-in from)
 * Return Type: void
 * Errors Thrown: runtime_error if the file could not be opened or if the 
 * data file's format is incorrect */
void Screen::readIn(string filename) 
{
    ifstream infile(filename.c_str());
    if (!infile.is_open()) {
        string errorMessage = "Error opening file " + filename;
        throw runtime_error(errorMessage);
    }

    string check;
    if (!(infile >> check) || check != "object") {
        string errorMessage = "Error reading in file " + filename;
        throw runtime_error(errorMessage);
    }

    countObjects(filename);

    object = new Object[objectCount];
    for (int i = 0; i < objectCount; i++) 
        object[i].readIn(filename, i + 1);
    
    infile.close();
}

/* print()
 * Purpose: Prints all of the necessary objects onto the screen
 * Parameters: int (number of body parts that should be printed)
 * Return Type: void
 * Errors Thrown: None */
void Screen::print(int wrongCount)
{
    screen_clear();
    for (int i = 0; i < wrongCount + 1; i++)
        object[i].print();
}