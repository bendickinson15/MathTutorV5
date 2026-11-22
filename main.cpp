/********************************************************************************************************************************************
 Program....: MathTutorV5
 Programmers: Benjamin Dickinson
 Section....: 2 10:00am
 Date.......: 2026.10.30
 GitHub Repo: https://github.com/bendickinson15/MathTutorV5
 Description: An easy math tutor for young children. In version 3, it displays the program's intro, gets the full user's name,
              asks a simple question of + - * or /, tells them if they are correct or incorrect, asks if they want to go again,
              repeats if they do,and levels up or down if they get 3 correct or incorrect. After selecting no a summary report
              appears showing, your past question, their level, and attempts you took on them. It also does total average
              and more.
********************************************************************************************************************************************/
#include <iostream> // Used for cin and cout Plus left and right alignment
#include <string> // Allows string variables
#include <cstdlib> // Used for random number generation
#include <ctime> // Allows random to be unpredictable using the time
#include <cctype> // Used to change a string to lower
#include <vector> // Allows for us to use the vector data type
#include <iomanip> // this is needed for the set width command or setw
#include "mathtutor.h" //mathtutor functions

using namespace std;

int currentRange = 10; // Starting maximum for number range
const int MAX_ATTEMPTS = 3; // Maximum for number of attempts

int main() {
    // Initialize variables for user name and answer
    string userName = "unknown";
    string userInput = "?"; // Does the user want another math problem
    int totalIncorrect = 0; // Keeps track if user has gotten 3 correct in a row
    int totalCorrect = 0; // Keeps track if user has gotten 3 incorrect in a row
    int totalQuestions = 0; //Kept track of in the do while loop and used in the summary report
    int level = 1; // Current level the user is on

    bool isCorrect = false;
    vector<vector<int> >questions; //creates a 2D vector

    srand(time(NULL)); // Sets random seed to the time

    //display intro
    DisplayGameIntro();

    //gets and stores user's name
    userName = GetUserName();


    do {
        totalQuestions++;

        //generates a random question and puts the data into a vector
        vector<int> row = GenerateRandomQuestion(level);

        //gives 3 attempts and stores whether correct or not to add to the streak of correct/incorrect
        isCorrect = GiveThreeAttempts (userName, row,totalCorrect,totalIncorrect);
        if (isCorrect){
            totalCorrect++;
        } else {
            totalIncorrect++;
        }

        //checks correct/incorrect streak to level up or down
        CheckForLevelChange(totalCorrect, totalIncorrect, level);

        //adds finishing touches to the row
        questions.push_back(row);

        //gets user's input as to if they want to play again or not
        userInput = AskToPlayAgain();
    }while (userInput == "y" || userInput == "yes"); // Go again if the user says "y" or "yes"

    //displays summary report
    DisplaySummaryReport(questions);

    // End of program
    cout << endl;
    cout << "Thanks for playing!" << endl;
    cout << "End of program" << endl;
    return 0;
}