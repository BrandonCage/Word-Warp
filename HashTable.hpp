#ifndef HW_7_HASH_TABLE
#define HW_7_HASH_TABLE

//Standard
#include <iostream>
//Read Files
#include <fstream>
//String Streams
#include <sstream>
//Strings
#include <string>
//Allows for cin and cout statements
#include <stdio.h>
//Vectors
#include <vector>
//Time
#include <time.h>
//Allows ceing function
#include <tgmath.h>
//Allows use of cout/cin
using namespace std;

// struct to store word + count combinations
struct wordItem
{
  //Items needed to play game
  std::string word;
  wordItem* next;
  bool display;
};
struct sevenWordItem{
  //Items needed to play game
  std::string word;
  //Items needed to track score
  int scores[5];
  string names[5];
  int timedScores[5];
  string timedNames[5];
};

// class HashTable for storing words.
class HashTable {
  public:
    HashTable(int hashTableSize);
    ~HashTable();
    //Adds word to the hash table
    void addWord(string word);
    //Adds all appropriate words at index to the found list
    void searchTable(string word);
    //Prints the found words with ---- for unknown words
    void printFound(bool cheat);
    //Pick random seven letter word and load possibilites into found
    string loadWord(int& sevenIndex);
    //Load words if we already know the index
    string loadWordIndex(int index);
    //Check for words passed, in addition to each word minus a letter
    void loadWordRecursive(string word);
    //Checks if two strings contain same letters
    bool isSameString(string one, string two);
    //Checks if entree is in found
    bool isInFound(string guess, bool& done);
    //Returns the 7-letter word at the given index
    string getSeven(int index);
    //Returns a pointer to the vertex that holds the seven items
    vector <sevenWordItem> * getSevenVertex();
    //Returns an int for the score in the timed game
    int timedScore(int remaining);
    //shuffles Letters
    string shuffle(string word);
    //gives hint
    string hint(string word);
    //calls clearFound
    void clearFoundHelper();
  private:
    /* member functions */
    //Given code from Hash Table project to generate hash code
    unsigned int getHash(std::string word);
    //Clears out the found LL
    void clearFound();
    //Dictionary of all words
    wordItem** hashTable;
    //Size of hash table
    int hashTableSize;
    //Amount of words currently in hash table
    int numItems;
    //Head of linked list for found words
    wordItem* found;
    //7-letter words
    vector <sevenWordItem> seven;
};
#endif
