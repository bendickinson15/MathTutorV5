/***************************************************************
Program    : MathTutorV5
Programmer : Benjamin Dickinson
Date       : 2026.11.21
Github Repo: https://github.com/bendickinson15/MathTutorV5
Description: Contains all function calls for main in MathTutorV5
****************************************************************/
#include "mathtutor.h"
#include <cctype> // for tolower
#include <cstdlib> // for srand and rand
#include <string> // Allows string variables
#include <iostream> // Used for cin and cout Plus left and right alignment
#include <limits> // Used to validate user answer data type
#include <vector> // Allows for us to use the vector data type
#include <iomanip> // this is needed for the set width command or setw

using namespace std;

//Function displays ASCII art and math fun facts. Doesn't do anything major.
void DisplayGameIntro() {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << R"(|   _       __     __                             __           __  ___      __  __       ______      __              |
|  | |     / /__  / /________  ____ ___  ___     / /_____     /  |/  /___ _/ /_/ /_     /_  __/_  __/ /_____  _____  |
|  | | /| / / _ \/ / ___/ __ \/ __ `__ \/ _ \   / __/ __ \   / /|_/ / __ `/ __/ __ \     / / / / / / __/ __ \/ ___/  |
|  | |/ |/ /  __/ / /__/ /_/ / / / / / /  __/  / /_/ /_/ /  / /  / / /_/ / /_/ / / /    / / / /_/ / /_/ /_/ / /      |
|  |__/|__/\___/_/\___/\____/_/ /_/ /_/\___/   \__/\____/  /_/  /_/\__,_/\__/_/ /_/    /_/  \__,_/\__/\____/_/       |)" << endl;

    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "|                                  Welcome to the Silly Simple Math Tutor version 1!                                 |" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << endl;
    cout << "Here are some cool math jokes:" << endl;
    cout << "    * There's no limit to what math can do." << endl;
    cout << "    * Some people have some polar opinions about math." << endl;
    cout << "    * Are monsters good at math? Not unless you Count Dracula." << endl;
    cout << "    * Why should you never argue with a 90-degree angle? Because it's always right." << endl;
}

//Function gets the user's name for storage in a string. Also welcomes them to the program.
string GetUserName() {
    string name = "?";
    cout << endl;
    cout << "What is your full name: ";
    getline(cin, name); // Handles spaces in name
    cout << "Welcome " << name << " to the Silly Simple Math Tutor!" << endl;
    return name;
}

//Function gets the user's answer and verifies their response is a numeric value.
int GetNumericValue() {
    int input = 0;
    // Loop until the user enters numeric data
    while (!(cin >> input)) {
        cin.clear();//clear the cin error flag
        //need to include the limit library to use numeric_limits
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tInvalid input!" << endl;
        cout << "\tPlease enter a number: ";
    }//end of the userAnswer while loop
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

//Function gets user's input as to if they want to do another question or not.
string AskToPlayAgain() {
    string input = "?";
    while (true) { // Checks if user y or n expected is valid
        cout<< "Would you like to go again? yes / y | no / n ";
        getline(cin, input);
        cout << endl;
        for (int i = 0; i < input.size(); i++) {
            input.at(i) = tolower(input.at(i)); // Changes user answer to all lowercase
        }
        if ((input != "y" && input != "n") && (input != "no" && input != "yes")) {
            cout << "\tInvalid input please try again..." << endl;
            continue;
        }
        break;
    }
    return input;
}

//Function generates a random question, checks its validity, and stores data from the question.
vector<int> GenerateRandomQuestion(int mathLevel) {
    enum MathType {ADD, SUB, MULT, DIV}; // helps choose the math symbol
    MathType mathType = ADD;
    char mathSymbol = '?'; // this is the math symbol displayed in the console
    int leftNum = 0; // the left number
    int rightNum = 0; // the right number
    int temp = 0; // Used for switching left and right numbers
    int const LEVEL_RANGE_CHANGE = 5; // How much the range of numbers changes when you level up or down
    int correctAnswer = 0;
    mathType = static_cast<MathType>(rand() % 4); // generates random number for math symbol (+=0, -=1, *=2, /=3)

    leftNum = rand() % (currentRange + ((mathLevel-1) * LEVEL_RANGE_CHANGE)) + 1; // generates random left number output between 1 and the currentRange
    rightNum = rand() % (currentRange + ((mathLevel-1) * LEVEL_RANGE_CHANGE)) + 1; // generates random right number output between 1 and the currentRange

    //mathType = 5; //-used for testing switch default

    switch (mathType) {
        case ADD: //Addition
            mathSymbol = '+';
            correctAnswer = leftNum + rightNum;
            break;
        case SUB: //Subtraction
            mathSymbol = '-';
            if (leftNum < rightNum) { // Switch left and right num if right num is greater
                temp = leftNum;
                leftNum = rightNum;
                rightNum = temp;
            }
            correctAnswer = leftNum - rightNum;
            break;
        case MULT: //Multiplication
            mathSymbol = '*';
            correctAnswer = leftNum * rightNum;
            break;
        case DIV: //Division
            mathSymbol = '/';
            // Avoids fractions while keeping logic simple
            correctAnswer = leftNum;
            leftNum *= rightNum;
            break;
        default: // Error handling if mathType is not between 1 and 4. This should not happen
            cout << "Invalid question type: " << mathType << endl;
            cout << "Program ended with error " << endl;
            cout << "Please report this error to Derek or Cameron." << endl;
            return {};
    }
    return {mathLevel, leftNum, mathSymbol, rightNum, correctAnswer};
}

//Function gives the user three attempts per question to get it correct. Stores their attempts for report later on.
bool GiveThreeAttempts(const string& name, vector<int>& question, int& streakCorrect, int& streakIncorrect) {
    int level = question.at(0);
    int left = question.at(1);
    char symbol = static_cast<char>(question.at(2));
    int right = question.at(3);
    int answer = question.at(4);

    for (int i = 1; i <= MAX_ATTEMPTS; i++) {
        cout << "[Level# " << level << "] " << name << ", what is " << left << symbol << right << "? ";
        int userAnswer = GetNumericValue();

        if (userAnswer == answer) {
            cout << "\tCongrats, you got it correct!" << endl;
            streakIncorrect = 0; // Resets consecutive wrong streak
            question.push_back(i);
            return true;
        }
        else if (i == MAX_ATTEMPTS) {
            cout << "\tSorry you are out of attempts" << endl;
            cout << "\tThe correct answer was " << answer << endl;
            streakCorrect = 0; // Resets consecutive right streak
            question.push_back(0);
            return false;
        }
        else {
            cout << "\tBummer, that was incorrect" << endl;
            cout << "\tYou have " << (MAX_ATTEMPTS - i) << " attempt(s) left." << endl;
        }
    }

    return false;
}

//Function checks if the user increased or decreased in level based on the user's correct/incorrect streak.
void CheckForLevelChange(int& numCorrect, int& numIncorrect, int& level) {
    int maxRange = 0;
    if (numCorrect >= 3) { // If the user gets 3 correct in a row
        level++;
        cout << "WooHoo - Leveling you up to level " << level << endl;
        maxRange = currentRange + ((level - 1) * 5);
        cout << "The numbers are now between 1 and " << maxRange << endl << endl;
        numCorrect = 0; // Resets total correct streak
    }
    else if (numIncorrect >= 3) { // If the user gets three incorrect in a row (not including incorrect attempts)
        level--;
        cout << "BooHoo - leveling you down to level " << level << endl;
        if (level < 1) {
            level = 1;
        }
        maxRange = currentRange + ((level - 1) * 5);
        cout << "The numbers are now between 1 and " << maxRange << endl << endl;
        numIncorrect = 0; // Resets total incorrect streak
    }
}

//Function displays the summary report to the questions answered by the user.
void DisplaySummaryReport(const vector<vector<int> > &allQuestions)
{
    //zeroing totals for totalling correct and incorrect answers
    int numCorrect = 0;
    int numIncorrect = 0;

    // report heading
    cout << "======================================================" << endl;
    cout << "                   Summary Report              " << endl;
    cout << "======================================================" << endl;
    cout << "  Level               Questions              Attempts" << endl;
    cout << "  -------        -------------------        ----------" << endl;

    // loop through the 2D vector to display all questions
    for (int i = 0; i < allQuestions.size(); i++) {
        //pull the current row's data out into more readable variables
        int level = allQuestions.at(i).at(0);
        int leftNum = allQuestions.at(i).at(1);
        char mathSymbol = static_cast<char>(allQuestions.at(i).at(2));
        int rightNum = allQuestions.at(i).at(3);
        int answer = allQuestions.at(i).at(4);
        int attempts = allQuestions.at(i).at(5);

        //displays the question
        cout << " " << setw(4) << right << level << " "
             << setw(15) << right << leftNum << " "
             << mathSymbol << " "
             << setw(1) << right << rightNum << " "
             << setw(2) << right << "="
             << setw(4) << right << answer << " ";

        //displays the attempts
        if (attempts != 0) {
            cout << "             " << attempts << endl;
            numCorrect++;
        }
        else {
            cout << "            Incorrect" << endl;
            numIncorrect++;
        }
    }
    //Gathers total amount of questions and outputs the result
    cout << "\nTotal Questions:    " << allQuestions.size() << endl;
    //Gathers total amount of correct questions and outputs the result
    cout << "Total Correct:      " << numCorrect << endl;
    //Gathers total amount of incorrect questions and outputs the result
    cout << "Total Incorrect:    " << numIncorrect << endl;
    //Takes the total correct questions and multiplies by 100 then divides by the total amount questions
    int averageCorrect = (numCorrect * 100) / allQuestions.size();
    //Gathers average correct and outputs the result
    cout << "Average Correct:    " << averageCorrect << "%" << endl;
}