#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include "Hangman.h"
#include "termfuncs.h"
using namespace std;

#define NORMAL "\033[0m"
#define BOLD "\033[1m"

#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define BLUE_TEXT "\033[34m"
#define MAGENTA_TEXT "\033[35m"
#define CYAN_TEXT "\033[36m"
#define WHITE_TEXT "\033[37m"

static const string DICTIONARY = "dictionary.txt";

/* Parameterized Constructor
 * Purpose: Create the game of hangman, given two strings as parameters
 * Parameters: string (the word to be guessed), string (data file containing 
 * pictures to be read-in)
 * Return Type: None 
 * Errors Thrown: None */
Hangman::Hangman(string element, string filename)
{
    screen.readIn(filename);
    wrongCount = 0;

    /* Based on the number of items in the data file, there can be 8 
     * incorrect guesses */
    wrongLimit = 8;
    guess = ' ';

    // All 26 letters have not been guessed yet
    for (int i = 0; i < 26; i++)
        guessed[i] = false;


    for (size_t i = 0; i < element.size(); i++) {
        // Stores the word in a vector
        word.push_back(toupper(element[i]));

        // Stores the word that the user sees in a separate vector
        // Non-alphanumeric characters are already revealed
        if (element[i] == ' ')
            correct.push_back(element[i]);

        else if (!isalpha(element[i]))
            correct.push_back(element[i]);

        // The '~' represents a letter that has not been revealed yet
        else
            correct.push_back('~');
    }
}

/* Destructor
 * Purpose: Frees all heap-allocated memory in the object
 * Parameters: None
 * Return Type: None
 * Errors Thrown: None */
Hangman::~Hangman()
{
    // Nothing to be done
}

/* run()
 * Purpose: Runs the hangman game until it is over
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::run()
{
    printScreen();

    while (!gameOver()) {
        getGuess();
        checkGuess();
        printScreen();
    }
    
}

/* printScreen()
 * Purpose: Prints the hangman board, correct/incorrect guesses, and the 
 * word being guessed
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::printScreen()
{
    // Prints the hangman body based on how many incorrect guesses there are
    cout << YELLOW_TEXT;
    screen.print(wrongCount);
    cout << NORMAL;

    printCorrect();
    printIncorrect();
    printWord();
}

/* printCorrect()
 * Purpose: Print all of the user's correct guesses so far
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::printCorrect()
{
    place_cursor(3, 30);
    cout << BLUE_TEXT << "Correct Guesses: " << NORMAL;
    place_cursor(4, 30);
    for (size_t i = 0; i < correctGuesses.size(); i++) {
        cout << GREEN_TEXT << correctGuesses[i] << NORMAL;
        // Only print the comma if it isn't printing the last item
        if (i < correctGuesses.size() - 1)
            cout << BLUE_TEXT << ", " << NORMAL;
    }
}

/* printIncorrect()
 * Purpose: Print all of the user's incorrect guesses so far
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::printIncorrect()
{
    place_cursor(6, 30);
    cout << BLUE_TEXT << "Incorrect Guesses: " << NORMAL;
    place_cursor(7, 30);
    for (size_t i = 0; i < incorrectGuesses.size(); i++) {
        cout << RED_TEXT << incorrectGuesses[i] << NORMAL;
        if (i < incorrectGuesses.size() - 1)
            cout << BLUE_TEXT << ", " << NORMAL;
    }
    screen_home();
}

/* printWord()
 * Purpose: Prints the revealed letters in the word that is being guessed
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::printWord()
{
    // Print the lines representing individual letters
    place_cursor(19, 5);
    cout << BLUE_TEXT;
    for (size_t i = 0; i < word.size(); i++) {
        if (isalpha(word[i]))
            cout << "___ ";
        else
            cout << "  ";
    }

    // Print the letters that have been guessed correctly so far
    place_cursor(18, 5);
    for (size_t i = 0; i < word.size(); i++) {
        if (correct[i] == '~')
            cout << "    ";
        else if (correct[i] == ' ')
            cout << "  ";
        else if (!isalpha((correct[i]))) 
            cout << correct[i] << ' ';
        else
            cout << ' ' << correct[i] << "  ";
    }
    cout << NORMAL;
    screen_home();
}

/* getGuess()
 * Purpose: Prompts the user for a guess and stores it in the object's member 
 * char: "guess"
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::getGuess()
{
    place_cursor(10, 30);
    cout << BLUE_TEXT << "Guess? " << NORMAL;
    guess = getachar();
    guess = tolower(guess);
    // If the user enters an invalid guess, prompt for another guess
    while (!isalpha(guess) || guessed[guess - 'a'] == true) {
        place_cursor(10, 30);
        cout << MAGENTA_TEXT << "Invalid choice. " << BLUE_TEXT << "Guess? " 
             << NORMAL;
        guess = getachar();
        guess = tolower(guess);
    }
    guess = toupper(guess);
    screen_home();
}

/* checkGuess()
 * Purpose: Checks to see if the word contains the guessed character
 * Parameters: None
 * Return Type: void
 * Errors Thrown: None */
void Hangman::checkGuess()
{
    bool characterFound = false;
    for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == guess) {
            characterFound = true;
            correct[i] = guess;
        }
    }

    // Adds the character to the displayed list of correct/incorrect guesses
    if (characterFound)
        correctGuesses.push_back(guess);

    else {
        incorrectGuesses.push_back(guess);
        wrongCount++;
    }

    // Marks the character as guessed so that it cannot be guessed again
    guessed[tolower(guess) - 'a'] = true;
}

/* gameOver()
 * Purpose: Checks to see if the game is over. If it is, it prints a message.
 * Parameters: None
 * Return Type: bool (if the game is over)
 * Errors Thrown: None */
bool Hangman::gameOver()
{
    place_cursor(10, 30);
    // Case 1: User exceeded limit of incorrect guesses
    if (wrongCount >= wrongLimit) {
        cout << MAGENTA_TEXT << "Game Over! The correct phrase was \"";
        for (size_t i = 0; i < word.size(); i++) 
            cout << word[i];
        cout << "\"" << endl << NORMAL;
        screen_home();
        return true;
    }

    // Case 2: User solved the puzzle and guessed all correct letters
    bool solved = true;
    for (size_t i = 0; i < correct.size(); i++) {
        if (correct[i] == '~')
            solved = false;
    }

    if (solved)
        cout << GREEN_TEXT << "You win!\n" << NORMAL;
        
    screen_home();
    // Case 3: Game isn't done yet
    return solved;
}

#undef NORMAL 
#undef BOLD 

#undef RED_TEXT 
#undef GREEN_TEXT 
#undef YELLOW_TEXT 
#undef BLUE_TEXT 
#undef MAGENTA_TEXT 
#undef CYAN_TEXT 
#undef WHITE_TEXT
