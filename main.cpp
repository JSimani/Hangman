#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Hangman.h"
#include "termfuncs.h"

using namespace std;

static const string BODYPARTS = "/User/JSimani/Desktop/Projects/Hangman/data.dat";
static const string DICTIONARY = "/User/JSimani/Desktop/Projects/Hangman/dictionary.txt";

void first_game();
void second_game();
string random_word(string filename);

int main()
{
    first_game();
    while(!cin.eof()) {
        second_game();
    }

    return 0;
}

void first_game()
{
    char response = 'A';
    string word = "";
    srand(time(NULL));

    cout << "(C)hoose a word\n"
         << "(R)andom word\n"
         << "(Q)uit\n";

    response = toupper(getachar());
    while ((response != 'C') && (response != 'R') && (response != 'Q')) {
        cout << "Invalid Response " << endl;
        response = toupper(getachar());
    }

    if (response == 'C') {
        cout << "Word: ";
        getline(cin, word);
        screen_clear();
    } else if (response == 'R') {
        word = random_word(DICTIONARY);
    } else if (response == 'Q') {
        screen_clear();
        exit(0);
    } 

    Hangman h(word, BODYPARTS);
    h.run();
}

string random_word(string filename)
{
    int word_count = 0, random_index;
    string current_word;
    ifstream infile(filename.c_str());
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    while (infile >> current_word) {
        word_count++;
    }
    infile.close();

    cout << "Word Count: " << word_count << endl;

    infile.open(filename);
    random_index = rand() % word_count;

    for (int i = 0; i < random_index; i++) {
        infile >> current_word;
    }

    infile.close();

    return current_word;
}

void second_game()
{
    char response = 'A';
    string word = "";

    place_cursor(11, 30);
    cout << "(C)hoose a word";
    place_cursor(12, 30);
    cout << "(R)andom word";
    place_cursor(13, 30);
    cout << "(Q)uit";
    place_cursor(14, 30);

    response = toupper(getachar());
    while ((response != 'C') && (response != 'R') && (response != 'Q')) {
        place_cursor(14, 30);
        cout << "                 ";
        place_cursor(14, 30);
        cout << "Invalid Response ";
        response = toupper(getachar());
    }
    
    place_cursor(14, 30);
    if (response == 'C') {
        cout << "Word: ";
        getline(cin, word);
        screen_clear();
    } else if (response == 'R') {
        word = random_word(DICTIONARY);
    } else if (response == 'Q') {
        screen_clear();
        exit(0);
    } 
    
    Hangman h(word, BODYPARTS);
    h.run();
}