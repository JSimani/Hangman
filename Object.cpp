#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Object.h"
#include "termfuncs.h"
using namespace std;

/* Constructor
 * Purpose: Initializes all member variables in the object
 * Parameters: None
 * Return Type: None
 * Errors Thrown: None */
Object::Object()
{
    image = NULL;

    name = "";

    yDimension = 0;
    xDimension = 0;

    yPosition = 0;
    xPosition = 0;
}

/* Destructor
 * Purpose: Frees all heap-allocated memory in the object
 * Parameters: None
 * Return Type: None
 * Errors Thrown: None */
Object::~Object()
{
    if (image) {
        delete []image;
        image = NULL;
    }
}

/* findObject()
 * Purpose: Navigates to the position in the ifstream from which the object 
 * should be read in
 * Parameters: Reference to an ifstream (ifstream that will be updated when 
 * items are read-in), int (which object should be read-in)
 * Return Type: void
 * Errors Thrown: runtime_error if objects could not be read in correctly */
void Object::findObject(ifstream &infile, int objectNumber)
{
    int count = 0;
    string check;
    while (count != objectNumber) {
        // If it reaches end-of-file before finishing reading in
        if (!(infile >> check))
            throw runtime_error("Error reading in objects");
        
        if (check == "object")
            count++;
    }
}

/* readIn()
 * Purpose: Reads in a specific object from the file
 * Parameters: string (file from which the object is read-in), int (which 
 * object to read in)
 * Return Type: void
 * Errors Thrown: runtime_error if the file could not be opened */
void Object::readIn(std::string filename, int objectNumber)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (!(infile.is_open())) { 
        string errorMessage = "Error opening file " + filename;
        throw runtime_error(errorMessage);
    }

    findObject(infile, objectNumber);
    infile >> yDimension >> xDimension >> yPosition >> xPosition >> name;
    image = new string[yDimension];

    /* getline() has to read in a throwaway string at the beginning because 
     * the newline character has not been reached yet */
    string throwaway;
    for (int i = 0; i < yDimension + 1; i++) {
        if (i == 0)
            getline(infile, throwaway);
        else 
            getline(infile, image[i - 1]);
    }

    infile.close(); 
}

/* print()
 * Purpose: Prints the object to the screen
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Object::print()
{
    screen_home();
    for (int i = 0; i < yDimension; i++) {
        for (int j = 0; j < xDimension; j++) {
            place_cursor(yPosition + i, xPosition + j);
            // Does not print whitespace
            if (image[i][j] != ' ')
                cout << image[i][j];
        }
    }
}