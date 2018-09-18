#ifndef HANGMAN_H_
#define HANGMAN_H_
#include "Screen.h"

class Hangman {

    private:

        // Stores the word to be guessed
        std::string word;

        // Stores what characters should be revealed/stay hidden on the board
        std::string correct;

        // Stores a list of correct/incorrect guesses
        std::string correctGuesses, incorrectGuesses;

        /* Each boolean represents a letter in the alphabet, indicating if the 
         * user has guessed that letter yet */
        bool guessed[26];

        // Stores the hangman board
        Screen screen;

        // Counts the user's number of incorrect guesses
        int wrongCount;

        // Counts the number of incorrect guesses allowed before game over
        int wrongLimit;

        // Currect guess by the user
        char guess;

        /* Prints the hangman board, correct/incorrect guesses, and the 
         * word being guessed */
        void printScreen();

        // Print all of the user's correct guesses so far
        void printCorrect();

        // Print all of the user's incorrect guesses so far
        void printIncorrect();

        // Prints the revealed letters in the word that is being guessed
        void printWord();

        /* Prompts the user for a guess and stores it in the object's member 
         * char: "guess" */
        void getGuess();

        // Checks to see if the word contains the guessed character
        void checkGuess();

        // Checks to see if the game is over. If it is, it prints a message.
        bool gameOver();

    public:

        // Create the game of hangman, given one string as a parameter
        Hangman(std::string element, std::string filename);

        // Frees all heap-allocated memory in the object
        ~Hangman();

        // Runs the hangman game until it is over
        void run();

};

#endif