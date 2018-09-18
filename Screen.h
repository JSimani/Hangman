#ifndef SCREEN_H_
#define SCREEN_H_
#include "Object.h"

class Screen {

    private:

        // Dynamic array of objects, which store the ASCII pictures
        Object *object;

        // Keeps track of the number of objects there are in the dynamic array
        int objectCount;

    public:

        // Initializes all member variables in the Screen object
        Screen();

        // Frees all heap-allocated memory in the object
        ~Screen();

        // Counts the number of objects being read-in
        void countObjects(std::string filename);

        // Reads in the objects into the dynamic array of objects
        void readIn(std::string filename);

        // Prints all of the necessary objects onto the screen
        void print(int wrongCount);

};

#endif