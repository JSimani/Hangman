#ifndef OBJECT_H_
#define OBJECT_H_

class Object {

    private:

        // Stores the image in a dynamic array of lines for the image
        std::string *image;

        // Name of the object
        std::string name;

        // Dimensions of the object
        int yDimension;
        int xDimension;

        // Where the object should be printed on the screen
        int yPosition;
        int xPosition;

    public:

        // Initializes all member variables in the object
        Object();

        // Frees all heap-allocated memory in the object
        ~Object();

        /* Navigates to the position in the ifstream from which the object 
         * should be read in */
        void findObject(std::ifstream &infile, int objectNumber);

        // Reads in a specific object from the file
        void readIn(std::string filename, int objectNumber);

        // Prints the object to the screen
        void print();

};

#endif