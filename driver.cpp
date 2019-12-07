//Standard

/*
Github Notes:
Too keep all work up to date, make sure to pull before starting your work, and push whenever you finish
    too update github
        git add .
        git commit -m "commit name"
            replace commit name with an actual helpful name to tell group what was changed
        git push -u origin master
    too pull from github
        git pull

*/
#include "HashTable.hpp"
int HASH_TABLE_SIZE = 1000;


//Print menu to pick game mode
void printStartMenu(){
    cout << endl << endl << endl;
    cout << "           Word Warp" << endl;
    cout << "---------------------------------" << endl;
    cout << "1. Play standard" << endl;
    cout << "2. Play speed" << endl;
    cout << "3. Challenge " << endl;
    cout << "4. Create " << endl;
    cout << "5. More Info" << endl;
    cout << "6. Exit" << endl;
    cout << "Please enter the number of the option you wish to choose: " << endl;
}

//Menu to select which to learn more about
void printMoreInfoMenu(){
    cout << endl << endl;
    cout << "Which option would you like to learn more about?" << endl;
    cout << "1. Play standard" << endl;
    cout << "2. Play speed" << endl;
    cout << "3. Challenge " << endl;
    cout << "4. Create " << endl;
    cout << "5. Go back" << endl;
    cout << "Please enter the number of the option you wish to choose" << endl;
}

//Function that loads dictionary into hash table
void loadDictionary(HashTable& game){
    ifstream myFile;
    myFile.open("dictionary.txt");
    if (myFile.is_open()){
        string word;
        while (getline(myFile, word, ' ')){
            game.addWord(word);
        }
    }
    else{
        cout << "File could not be opened" << endl;
    }
}
//Function that loads high scores into the seven vector
void loadHighScore(HashTable& game){
    vector <sevenWordItem> *seven = game.getSevenVertex();
    ifstream myFile;
    myFile.open("highScore.txt");
    if (myFile.is_open()){
        string line;
        int index = 0;
        while (getline(myFile, line)){
            stringstream readLine;
            readLine << line;
            string word;

            getline(readLine, word, ' ');
            seven->at(index).scores[0] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).names[0] = word;

            getline(readLine, word, ' ');
            seven->at(index).scores[1] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).names[1] = word;

            getline(readLine, word, ' ');
            seven->at(index).scores[2] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).names[2] = word;

            getline(readLine, word, ' ');
            seven->at(index).scores[3] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).names[3] = word;

            getline(readLine, word, ' ');
            seven->at(index).scores[4] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).names[4] = word;

            getline(readLine, word, ' ');
            seven->at(index).timedScores[0] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).timedNames[0] = word;

            getline(readLine, word, ' ');
            seven->at(index).timedScores[1] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).timedNames[1] = word;

            getline(readLine, word, ' ');
            seven->at(index).timedScores[2] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).timedNames[2] = word;

            getline(readLine, word, ' ');
            seven->at(index).timedScores[3] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).timedNames[3] = word;

            getline(readLine, word, ' ');
            seven->at(index).timedScores[4] = stoi(word);
            getline(readLine, word, ' ');
            seven->at(index).timedNames[4] = word;

            index++;
        }
    }
    else{
        cout << "File could not be opened" << endl;
    }
}
//Checks if string player entered is
bool recursiveIsProperEntry(HashTable &game, string one, string two){
    bool answer = game.isSameString(one, two);
    if (answer){
        return true;
    }
    if (one.length() > 3){
        string hold = one;
        for (int i = 0; i < one.length(); i++){
            one.erase(i, 1);
            answer = recursiveIsProperEntry(game, one, two);
            if (answer){
                return true;
            }
            one = hold;
        }
    }
    return false;
}
//Plays the standard game mode with the inputted letters
void playStandard(HashTable & game, string letters, int sevenIndex){
    bool done = false;
    string input1;
    int penalty=0;
    time_t start = time(0);
    while(!done){
        game.printFound(false);
        cout << "Letters: " << endl;
        cout << letters << endl;
        cout << "What word would you like to guess?" << endl;
        getline(cin, input1);
        if (!recursiveIsProperEntry(game, letters, input1)){
            if (input1 == "i would like to cheat"){
                done = true;
            }
            else if(input1=="word warp")
            {
              letters=game.shuffle(letters);
            }
            else if(input1=="hint please")
            {
              cout << "Hint: " << game.hint(letters) << "\n";
              penalty+=5;
            }
            else
            {
              cout << "Those letters are not in those given to you" << endl;
            }
        }
        else{
            if(game.isInFound(input1, done)){
                cout << "You guessed a word!" << endl;
            }
            else{
                cout << "Not a valid guess" << endl;
            }

        }
    }
    cout << "You found all the words!" << endl;
    double seconds_since_start = difftime(time(0), start);
    int score = 5000 - seconds_since_start - penalty;
    cout << "Your score is: " << score << endl;
    vector <sevenWordItem> *scores = game.getSevenVertex();
    for (int i = 0; i < 5; i++){
        if (score > scores->at(sevenIndex).scores[i]){
            cout << "You got a new high score! What is your name?" << endl;
            getline(cin, input1);
            int hold = score;
            string holdName = input1;
            int hold1;
            string holdName1;
            for (int j = i; j < 5; j++){
                hold1 = scores->at(sevenIndex).scores[j];
                holdName1 = scores->at(sevenIndex).names[j];
                scores->at(sevenIndex).scores[j] = hold;
                scores->at(sevenIndex).names[j] = holdName;
                hold = hold1;
                holdName = holdName1;
            }
            i = 5;
        }
    }
    cout << "High scores: " << endl;
    for (int i = 0; i < 5; i++){
        cout << i + 1 << ". " << scores->at(sevenIndex).scores[i] << ": " << scores->at(sevenIndex).names[i] << endl;
    }
    cout << "Your game code is: " << "a" << sevenIndex << endl;
    cout << "Press enter to continue\n";
}

//Plays the time mode game with the inputted letters
void playTimed(HashTable & game, string letters, int sevenIndex){
    bool done = false;
    string input1;
    int penalty=0;
    time_t start = time(0);
    int seconds_since_start = difftime(time(0), start);
    while(!done && seconds_since_start + penalty < 300){
        game.printFound(false);
        cout << "Time Remaining: " << 300-seconds_since_start - penalty << "\n";
        cout << "Letters: " << endl;
        cout << letters << endl;
        cout << "What word would you like to guess?" << endl;
        getline(cin, input1);
        if (!recursiveIsProperEntry(game, letters, input1)){
            if (input1 == "i would like to cheat"){
                done = true;
            }
            else if(input1=="word warp")
            {
              letters=game.shuffle(letters);
            }
            else if(input1=="hint please")
            {
              cout << "Hint: " << game.hint(letters) << "\n";
              penalty+=5;
            }
            else
            {
              cout << "Those letters are not in those given to you" << endl;
            }
        }
        else{
            if(game.isInFound(input1, done)){
                cout << "You guessed a word!" << endl;
            }
            else{
                cout << "Not a valid guess" << endl;
            }
        }
        seconds_since_start = difftime(time(0), start);
    }
    cout << "End of the game" << endl;
    int score = game.timedScore(300 - seconds_since_start-penalty);
    cout << "Your score is: " << score << endl;
    vector <sevenWordItem> *scores = game.getSevenVertex();
    for (int i = 0; i < 5; i++){
        if (score > scores->at(sevenIndex).timedScores[i]){
            cout << "You got a new high score! What is your name?" << endl;
            getline(cin, input1);
            int hold = score;
            string holdName = input1;
            int hold1;
            string holdName1;
            for (int j = i; j < 5; j++){
                hold1 = scores->at(sevenIndex).timedScores[j];
                holdName1 = scores->at(sevenIndex).timedNames[j];
                scores->at(sevenIndex).timedScores[j] = hold;
                scores->at(sevenIndex).timedNames[j] = holdName;
                hold = hold1;
                holdName = holdName1;
            }
            i = 5;
        }
    }
    cout << "High scores: " << endl;
    for (int i = 0; i < 5; i++){
        cout << i + 1 << ". " << scores->at(sevenIndex).timedScores[i] << ": " << scores->at(sevenIndex).timedNames[i] << endl;
    }
    cout << "Your game code is: " << "b" << sevenIndex << endl;
    cout << "Press enter to continue\n";
}

void updateHighScore(HashTable& game){
    ofstream myFile;
    myFile.open("highScore.txt");
    if (myFile.is_open()){
        vector <sevenWordItem> *seven = game.getSevenVertex();
        for (int i = 0; i < seven->size(); i++){
            for (int j = 0; j < 5; j++){
                myFile << seven->at(i).scores[j] << " "<< seven->at(i).names[j] << " ";
            }
            for (int j = 0; j < 5; j++){
                myFile << seven->at(i).timedScores[j] << " " << seven->at(i).timedNames[j] << " ";
            }
            myFile << endl;
        }
    }
}

int main()
{
    string input = "1";
    string input1;
    string letters = "";
    bool check = true;
    bool correct;
    int sevenIndex;
    HashTable game(HASH_TABLE_SIZE);
    loadDictionary(game);
    loadHighScore(game);
    while (input != "6"){
        printStartMenu();
        getline(cin, input);
        while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6"){
            cout << "Invalid input. Please choose again." << endl;
            getline(cin, input);
        }
        switch (stoi(input)) {
            //Play the standard version of game
            case 1 :
                letters = game.loadWord(sevenIndex);
                playStandard(game, letters, sevenIndex);
                getline(cin, input1);

                break;
            //Play speed version of game
            case 2 :
                letters = game.loadWord(sevenIndex);
                playTimed(game, letters, sevenIndex);
                getline(cin, input1);
                break;
            //Play challenge version of game
            case 3 :
                cout << "Enter the challenge code you wish to use: " << endl;
                getline(cin, input1);
                while(input1[0] != 'a' && input1[0] != 'b'){
                    cout << "That was not a valid challenge code. Please enter another" << endl;
                    getline(cin, input1);
                }
                if (input1[0] == 'a'){
                    input1.erase(0, 1);
                    letters = game.loadWordIndex(stoi(input1));
                    playStandard(game, letters, stoi(input1));
                }
                else{
                    input1.erase(0, 1);
                    letters = game.loadWordIndex(stoi(input1));
                    playTimed(game, letters, stoi(input1));
                }
                break;
            //Allow player to cheat
            case 4 :
                check = true;
                game.clearFoundHelper();
                cout << "What is the word you want to find all sub-words of?" << endl;
                getline(cin,input1);
                for (int i = 0; i < input1.length(); i++){
                    if (input1[i] > 122 || input1[i] < 97){
                        check = false;
                    }
                }
                while (input1.length() > 7 || !check){
                    if (input1.length() > 7){
                        cout << "Sorry, we can only handle up to 7 letters:" << endl;
                    }
                    else{
                        cout << "Please enter a string of just lower case letters:" << endl;
                    }
                    getline(cin, input1);
                    check = true;
                    for (int i = 0; i < input1.length(); i++){
                        if (input1[i] > 122 || input1[i] < 97){
                            check = false;
                        }
                    }
                }
                game.loadWordRecursive(input1);
                game.printFound(true);
                game.clearFoundHelper();
                cout << "Press any key to return to previous menu" << endl;
                getline(cin, input);

                break;
            //Print more info for user
            case 5 :
                input = "1";
                while (input != "5"){
                    printMoreInfoMenu();
                    getline(cin, input);
                    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5"){
                        cout << "Invalid input. Please choose again." << endl;
                        getline(cin, input);
                    }
                    switch (stoi(input)){
                    //Play the standard version of game
                        case 1 :
                            cout << "In the standard version of the game, you are score based on how long it takes you to get all the words. If you would like to shuffle the letters, simply type \"word warp\". You can request a hint for a word by typing \"hint please\", but it will add 5 seconds to your time." << endl;
                            break;
                        //Play speed version of game
                        case 2 :
                            cout << "In the speed version of the game, you are given a set time and you are given points based on how many words you find. Each word is scored as the number of letters in the word. If you would like to shuffle the letters, simply type \"word warp\". You can request a hint for a word by typing \"hint please\", but it will subtract 5 seconds from your remaining time." << endl;
                            break;
                        //Play challenge version of game
                        case 3 :
                            cout << "Have your friend send the code for the game they just played. We'll give you the same letters and you can see if you can beat their score." << endl;
                            break;
                        //Create
                        case 4 :
                            cout << "If you simply want to know all of the words that can be made from the lettters of another word, enter the word in this mode and we will print all the options for you" << endl;
                            break;
                    }
                    if (input != "5"){
                        cout << "Enter any key to continue" << endl;
                        getline(cin, input);
                    }
                }

                break;
        }
    }
    cout << "Thanks for playing!" << endl;
    updateHighScore(game);
    return 0;
}


//5 slides
