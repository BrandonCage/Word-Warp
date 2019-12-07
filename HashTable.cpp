#include "HashTable.hpp"

//Given code from Hash Table project to generate hash code
unsigned int HashTable::getHash(std::string word){
    int hashValue = 0;
    for (int i=0; i<word.length();i++)
    {
        hashValue+= word[i] - 'a';
    }
    hashValue %= hashTableSize;
    return hashValue;
}

//Clears out the found LL
void HashTable::clearFound(){
    wordItem * hold;
    while (found != nullptr){
        hold = found->next;
        delete found;
        found = hold;
    }
}

string HashTable::shuffle(string word)
{
  string shuf="AAAAAAA";
  int i=0;
  int ran;
  bool used[7]={0,0,0,0,0,0,0};
  while(i<7)
  {
    ran=rand()%7;
    if(used[ran]==0)
    {
      used[ran]=1;
      shuf[i]=word[ran];
      i++;
    }
  }
  return shuf;
}

string HashTable::hint(string word)
{
  string shuf="       ";
  int ran;
  wordItem * traverse = found;
  int count = 0;
  //Count how many words there are
  while (traverse != nullptr){
      count++;
      traverse = traverse->next;
  }
  bool exit=0;
  while(exit==0)
  {
    traverse=found;
    ran=rand()%count;
    for(int j=0;j<ran;j++)
    {
      traverse = traverse->next;
    }
    if(traverse->display==0)
    {
      exit=1;
    }
  }
  ran=rand()%traverse->word.length();
  for(int k=0;k<traverse->word.length();k++)
  {
    if(k==ran)
    {
      shuf[k]=traverse->word[k];
    }
    else
    {
      shuf[k] = '*';
    }
  }
  return shuf;
}

//Adds all appropriate words at index to the found list
void HashTable::searchTable(string word){
    int index = getHash(word);
    wordItem * search = hashTable[index];
    //For every word at the index
    while (search != nullptr){
        //If it is of proper length
        if (isSameString(search->word, word)){
            bool alreadyDone = false;
            wordItem * traverse = found;
            if(traverse != nullptr){
                while (traverse != nullptr){
                    if(traverse->word == search->word){
                       alreadyDone = true;
                    }
                    traverse = traverse->next;
                }
            }
            if (!alreadyDone){
                //Create copy of structure
                wordItem * added = new wordItem;
                added->word = search->word;
                added->display = false;
                added->next = nullptr;
                //Add copy to found/display words
                traverse = found;
                if (traverse == nullptr){ //adds to head if the found list is empty
                    found = added;
                }
                //Adds to front of list if should be there alphabetically
                else if ((traverse->word.compare(added->word) > 0 && traverse-> word.length() == added->word.length()) || traverse->word.length() > added->word.length()){
                    added->next = found;
                    found = added;
                }
                //Need to find where in LL word needs to go
                else{
                    wordItem *prev = nullptr;
                    while (traverse != nullptr){
                        //If we went too far alphabetically...
                        if((traverse->word.compare(added->word) > 0 && traverse->word.length() == added->word.length()) || traverse->word.length() > added->word.length()){
                            traverse = nullptr;
                        }
                        else{
                            prev = traverse;
                            traverse = traverse->next;
                        }

                    }
                    added->next = prev->next;
                    prev->next = added;
                }
            }
            search = search -> next;
        }
        else if (search->word.length() > word.length()){
            search = nullptr;
        }
        else{
            search = search->next;
        }
    }
}

//Creates hash table of set size
HashTable::HashTable(int hashTableSize){
    srand(time(NULL));
    this->hashTableSize = hashTableSize;
    hashTable = new wordItem* [hashTableSize];
    for (int i = 0; i < hashTableSize; i++){
        hashTable[i] = nullptr;
    }
    numItems = 0;
    found = nullptr;
}

HashTable::~HashTable(){
    for (int i = 0; i < hashTableSize; i++){
        wordItem * traverse = hashTable[i];
        wordItem * hold = traverse;
        while (traverse != nullptr){
            hold = traverse->next;
            delete traverse;
            traverse = hold;
        }
    }
    wordItem * hold;
    clearFound();
}
//Adds word to the hash table
void HashTable::addWord(std::string word){
    int index = getHash(word);
    //Create word
    wordItem * newNode = new wordItem;
    newNode->word = word;
    newNode->next = nullptr;
    newNode->display = false;
    //Put at head if index is empty
    if (hashTable[index] == nullptr){
        hashTable[index] = newNode;
    }
    //Else, put at end of index
    else{
        wordItem * traverse = hashTable[index];
        while (traverse->next != nullptr){
            traverse = traverse->next;
        }
        traverse->next = newNode;
    }
    if(word.length() == 7){
        seven.push_back(sevenWordItem());
        seven[seven.size()-1].word = word;
    }
}

//Prints the found words with ---- for unknown words
void HashTable::printFound(bool cheat){
    cout << "--------------------------" << endl;
    wordItem * traverse = found;
    double count = 0;
    //Count how many words there are
    while (traverse != nullptr){
        count++;
        traverse = traverse->next;
    }
    //Set traverse to start
    traverse = found;
    wordItem * traverse1 = found;
    //Set traverse1 to start + count / 3 rounded up
    for (int i = 0; i < ceil(count / 3); i++){
        traverse1 = traverse1->next;
    }
    wordItem * traverse2 = traverse1;
    //Set traverse 2 to start + count / 3 * 2 rounded up
    for(int i = 0; i < ceil(count / 3); i++){
        traverse2 = traverse2->next;
    }
    //For count dived by 3 rounded up (number of rows)
    for (int i = 0; i < ceil(count / 3); i++){
        if (traverse != nullptr){
            if (cheat || traverse->display){
                cout << traverse->word;
            }
            else{
                for (int i = 0; i < traverse->word.length(); i++){
                    cout << "*";
                }
            }
            for (int i = 0; i < 9-traverse->word.length(); i++){
                cout << " ";
            }
            traverse = traverse->next;
        }
        if (traverse1 != nullptr){
            if (cheat || traverse1->display){
                cout << traverse1->word;
            }
            else{
                for (int i = 0; i < traverse1->word.length(); i++){
                    cout << "*";
                }
            }
            for (int i = 0; i < 9-traverse1->word.length(); i++){
                cout << " ";
            }
            traverse1 = traverse1->next;
        }
        if (traverse2 != nullptr){
            if (cheat || traverse2->display){
                cout << traverse2->word;
            }
            else{
                for (int i = 0; i < traverse2->word.length(); i++){
                    cout << "*";
                }
            }
            traverse2 = traverse2->next;
        }
        cout << endl;
    }
}

//Check for words passed, in addition to each word minus a letter
void HashTable::loadWordRecursive(string word){
    searchTable(word);
    if (word.length() > 3){
        string hold = word;
        for (int i = 0; i < word.length(); i++){
            word.erase(i, 1);
            loadWordRecursive(word);
            word = hold;
        }
    }
}

void HashTable::clearFoundHelper()
{
  clearFound();
}
//Pick random seven letter word and load possibilites into found
//Call recursive version
string HashTable::loadWord(int& sevenIndex){
    clearFound();
    sevenIndex = rand() % seven.size();
    string letters = seven[sevenIndex].word;
    loadWordRecursive(letters);
    string answer = "";
    while(letters.length() > 0){
        int next = rand() % letters.length();
        answer = answer + letters[next];
        letters.erase(next, 1);
    }
    return answer;
}

//Loads word if the index is already known
string HashTable::loadWordIndex(int index){
    clearFound();
    string letters = seven[index].word;
    loadWordRecursive(letters);
    string answer = "";
    while(letters.length() > 0){
        int next = rand() % letters.length();
        answer = answer + letters[next];
        letters.erase(next, 1);
    }
    return answer;
}

//Checks if two strings contain two characters
bool HashTable::isSameString(string one, string two){
    //Check same length
    if (one.length() != two.length()){
        return false;
    }
    else{
        //For every letter in the first
        for (int i = 0; i < one.length(); i++){
            //For every word remaining in second string
            for (int j = 0; j < two.length(); j++){
                //If lettter of index word is in temp string, remove it from temp string and go to next word
                if (two[j] == one[i]){
                    two.erase(j, 1);
                    j = one.length() + 1;
                }
                //If letter of index word was not found in temp string
                else if(j == two.length()-1){
                    i = one.length() + 1;
                    j = one.length() + 1;
                }
            }
        }
        //If all letters were removed from temp / word at index is match
        if (two.length() == 0){
            return true;
        }
        return false;
    }
}

//Checks if entree is in found
bool HashTable::isInFound(string guess, bool& done){
    bool answer = false;
    wordItem * traverse = found;
    while (traverse != nullptr){
        if (traverse->word == guess){
            done = true;
            traverse->display = true;
            answer = true;
            wordItem * traverse1 = found;
            while (traverse1 != nullptr){
                if (traverse1->display == false){
                    done = false;
                    traverse1 = nullptr;
                }
                else{
                    traverse1 = traverse1->next;
                }
            }
            traverse = nullptr;
        }
        else{
            traverse = traverse->next;
        }
    }
    return answer;
}

string HashTable::getSeven(int index){
    return seven[index].word;
}

//Returns a pointer to the vertex that holds the seven items
vector <sevenWordItem> * HashTable::getSevenVertex(){
    return &seven;
}

//Returns an int for the score in the timed game
int HashTable::timedScore(int remaining){
    int score = remaining;
    if (score < 0){
        score = 0;
    }
    wordItem * traverse = found;
    while (traverse != nullptr){
        if (traverse->display == true){
            score += traverse->word.length();
        }
        traverse = traverse->next;
    }
    return score;
}
