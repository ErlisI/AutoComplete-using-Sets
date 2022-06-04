//
//  main.cpp
//  Lab #1
//
//  Created on 1.2.22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

int const MAX_SIZE = 100;

class List {

private:
    string name;
    string itemsArray[MAX_SIZE];
    int numberOfItems = 0; //Counts all the list
    int keepCount = 0; //Keeps count of the current item on the list

public:
    void appendList(string);
    void displayAll();
    void getInput();
    void userInput(char[]);
    bool searchAll(char[]);
    bool searchDuplicates(string);
    bool notFound = false;
};

void readData(ifstream&, List&);

int main() {

    List bags;

    ifstream inFile;

    readData(inFile, bags);

    cout << "----------------------" << endl;
    cout << "Search: ";

    bags.getInput();

    cout << endl;

    return 0;
}

//Sets the name and also copies the list names to the string array
void List::appendList(string bName) {

    this->name = bName;
    if(!searchDuplicates(bName))
        this->itemsArray[this->numberOfItems++] = bName;
}

//Just a function to display all the list
void List::displayAll() {

    for (int i = 0; i < this->numberOfItems; i++)
        cout << this->itemsArray[i] << endl;

}

//Function to read the data from a file
void readData(ifstream& inFile, List& bags) {

    string name;

    inFile.open("Text.txt"); // Open file

    if (!inFile) { //check if file was opened correctly

        cout << "File can't be opened" << endl;
        exit(1);

    }

    //Getting the data
    while (!inFile.eof()) {

        getline(inFile, name);
        bags.appendList(name);
    }

    inFile.close();

}

//This function is the logic
bool List::searchAll(char ch[]) {

    for (int j = 0; j < strlen(ch); j++) {

        //This branching just checks each input entered and compares it to each char of the string array of the current name
        if (((tolower(ch[j]) == tolower(this->itemsArray[this->keepCount][j])))) {
            this->keepCount;
            continue;
        }
        else {
            this->keepCount += 1;
            return false;
        }
    }
    return true;
}

//This function searches for duplicates in the array and its used to implement sets
bool List::searchDuplicates(string name) {

    for(int i = 0; i < this->numberOfItems; i++)
        if (this->itemsArray[i] == name)
            return true;

    return false;
}

//This function basically just gets the input from the user and passes it to the function searchAll()
void List::getInput() {

    char ch[MAX_SIZE]{};

    int i = 0;

    while (ch[i] != 'q') {
        if (_kbhit()) {
            system("cls");
            cout << "----------------------" << endl;
            cout << "Search: ";

            ch[i++] = _getch();
            cout << ch;

            //Checking for backspace before anything is typed
            if (ch[i - 1] == '\b' && i == 1) {
                cout << " ";
                ch[i - 1] = '\0';
                i -= 1;

            }
            else if (ch[i - 1] == 'q') {
                cout << ch;
                cout << "\n\n";
                cout << "Thanks for searching with us!" << endl;
                break;

                //Checking for backspace after something is typed
            }
            else if (ch[i - 1] == '\b') {
                cout << " ";
                cout << "\b \b";
                ch[i - 1] = '\0';
                ch[i - 2] = '\0';
                i -= 2;
            }

            //This calls the function with the logic
            if (i >= 3) {
                int countFalse;//I just set this counter to check how many times there is no match in the array, and after i check if the name is nowhere i ask if the user wants to add it
                countFalse = 0;
                cout << endl;
                while (this->keepCount < this->numberOfItems)
                    if (searchAll(ch)) {
                        cout << this->itemsArray[this->keepCount++] << endl;
                    }
                    else {
                        countFalse++;
                    }
                if (countFalse == this->numberOfItems) {
                    userInput(ch);
                    memset(ch, 0, sizeof(ch));
                    i = 0;
                    system("cls");
                }
                this->keepCount = 0;
            }
            else if (i < 3) {
                cout << "\n \n";
                displayAll();
            }
        }
    }
    _getch();
    cout << endl;
}

//This just asks if they want to add the name that is not in the array
void List::userInput(char ch[]) {

    char res;
    string name;
    cout << "The word you are searching isn't in the list! Would you like to add a name to the list? (Y/N): ";
    cin >> res;
    if (tolower(res) == 'y') {
        system("cls");
        cout << "Enter the new item: ";
        cin >> name;
        if (!searchDuplicates(name))
            appendList(name);

        else {
            cout << "This Anime Is Already In the List" << endl;

            //This part is not needed but its a nice feature to have for a better user experience
            cout << "Would you like to add another? (Y/N): ";
            cin >> res;
            if (tolower(res) == 'y') {
                system("cls");
                cout << "Enter the new item: ";
                cin >> name;
                if (!searchDuplicates(name))
                    appendList(name);
                else {
                    cout << "This Anime Is Already In the List (*Press Anything To Go Back*)" << endl;
                    _getch();
                }
            }
        }
    }
}
