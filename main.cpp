/********************************************************************************************************************************************
 Program....: MathTutorV5
 Programmers: Ben Dickinson
 Section....: 2 10:00am
 Date.......: 2026.10.30
 GitHub Repo: https://github.com/capacha1/MathTutorV4
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
#include <limits> // Used to validate user answer data type
#include <cctype> // Used to change a string to lower
#include <vector> // Allows for us to use the vector data type
#include <iomanip> // this is needed for the set width command or setw


using namespace std;

int main() {
    // Initialize variables for user name and answer
    string userName = "unknown";
    string userInput = "?"; // Does the user want another math problem

    int userAnswer; // the answer that the user provides
    int correctAnswer = 0;
    int leftNum = 0; // the left number
    int rightNum = 0; // the right number
    int temp = 0; // Used for switching left and right numbers
    enum MathType {ADD, SUB, MULT, DIV}; // helps choose the math symbol
    MathType mathType = ADD;
    char mathSymbol = '?'; // this is the math symbol displayed in the console
    int totalQuestions = 0; //Kept track of in the do while loop and used in the summary report
    int const MAX_ATTEMPTS = 3;
    int level = 1; // Current level the user is on
    int const LEVEL_RANGE_CHANGE = 5; // How much the range of numbers changes when you level up or down
    int totalIncorrect = 0; // Keeps track if user has gotten 3 correct in a row
    int totalCorrect = 0; // Keeps track if user has gotten 3 incorrect in a row
    int averageCorrect = 0; // Used for average in the summary report
    int currentRange = 10; // Starting maximum for number range
    int attempts = 0; // variable used to display number of attempts
    vector<vector<int> >questions; //creates a 2D vector

    srand(time(NULL)); // Sets random seed to the time

    // ASCII art and math fun facts
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

    // Get user name and welcome them
    cout << endl;
    cout << "What is your full name: ";
    getline(cin, userName); // Handle spaces in name
    cout << "Welcome " << userName << " to the Silly Simple Math Tutor!" << endl;
    cout << endl;

    do {
        totalQuestions++;
        mathType = static_cast<MathType>(rand() % 4); // generates random number for math symbol (+=0, -=1, *=2, /=3)

        leftNum = rand() % currentRange + 1; // generates random left number output between 1 and the currentRange
        rightNum = rand() % currentRange + 1; // generates random right number output between 1 and currentRange

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
                return -1;
        }

        //Adds all of those variables into the row
         vector<int> row = {level, leftNum, mathSymbol, rightNum, correctAnswer};

        for (int i = 1; i <= MAX_ATTEMPTS; i++) { // Gives the user three attempts

            // Get and check user answer
            cout << "[Level# " << level << "] " << userName << ", what is " << leftNum << mathSymbol << rightNum << "? ";

            // Loop until the user enters numeric data
            while (!(cin >> userAnswer)) {
                cin.clear();//clear the cin error flag
                //need to include the limit library to use numeric_limits
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tInvalid input!" << endl;
                cout << "\tPlease enter a number: ";
            }//end of the userAnswer while loop

            if (userAnswer == correctAnswer) { // Checks if user answer is correct
                cout << "\tCongrats, you got it correct!" << endl;
                totalCorrect += 1;
                totalIncorrect = 0; // Resets total incorrect streak
                row.push_back(i);
                break;
            }
            else if (i == 3) { // If the user has used their last attempt and it waa not right
                cout << "\tSorry you are out of attempts" << endl;
                cout << "\tThe correct answer was " << correctAnswer << endl;
                totalIncorrect++;
                totalCorrect = 0; // Resets total correct streak
                row.push_back(0);
            }
            else { // If the answer is incorrect and the user has attempts left
                cout << "\tBummer, that was incorrect" << endl;
                cout << "\tYou have " << MAX_ATTEMPTS-i << " attempt(s) left." << endl;
            }
        } //end of for loop

        //takes the finished row and adds items to it
        questions.push_back(row);

        getline(cin, userInput); //clear input buffer

        while (true) { // Checks if user y or n expected is valid
            cout<< "Would you like to go again yes = y | no = n? ";
            getline(cin, userInput);
            cout << endl;
            for (int i = 0; i < userInput.size(); i++) { // Changes user answer to all lowercase
                userInput.at(i) = tolower(userInput.at(i));
            }
            if ((userInput != "y" && userInput != "n") && (userInput != "no" && userInput != "yes")) {
                cout << "\tInvalid input please try again..." << endl;
                continue;
            }
            break;
        }
        if (totalCorrect >= 3) { // If the user gets 3 correct in a row
            currentRange += LEVEL_RANGE_CHANGE;
            level++;
            cout << "WooHoo - Leveling you up to level " << level << endl;
            cout << "The numbers are now between 1 and " << currentRange << endl << endl;
            totalCorrect = 0; // Resets total correct streak
        }
        else if (totalIncorrect >= 3) { // If the user gets three incorrect in a row (not including incorrect attempts)
            currentRange -= LEVEL_RANGE_CHANGE;
            level--;
            cout << "BooHoo - leveling you down to level " << level << endl;
            cout << "The numbers are now between 1 and " << currentRange << endl << endl;
            totalIncorrect = 0; // Resets total incorrect streak
        }
    }while (userInput == "y" || userInput == "yes"); // Go again if the user says "y" or "yes"

    //zeroing totals for correct and incorrect answers
    totalCorrect = 0;
    totalIncorrect = 0;

    // report heading
    cout << "======================================================" << endl;
    cout << "                   Summary Report              " << endl;
    cout << "======================================================" << endl;
    cout << "  Level               Questions              Attempts" << endl;
    cout << "  -------        -------------------        ----------" << endl;

    // loop through the 2D vector to display all questions
    for (int i = 0; i < questions.size(); i++) {
        //pull the current row's data out into more readable variables
        level = questions.at(i).at(0);
        leftNum = questions.at(i).at(1);
        mathSymbol = static_cast<char>(questions.at(i).at(2));
        rightNum = questions.at(i).at(3);
        correctAnswer = questions.at(i).at(4);
        attempts = questions.at(i).at(5);

        //displays the question
        cout << " " << setw(4) << right << level << " "
             << setw(15) << right << leftNum << " "
             << mathSymbol << " "
             << setw(1) << right << rightNum << " "
             << setw(2) << right << "="
             << setw(4) << right << correctAnswer << " ";

        //displays the attempts
        if (attempts != 0) {
            cout << "             " << attempts << endl;
            totalCorrect++;
        }
        else {
            cout << "            Incorrect" << endl;
            totalIncorrect++;
        }
    }
    //Gathers total amount of questions and outputs the result
    cout << "\nTotal Questions:    " << totalQuestions << endl;
    //Gathers total amount of correct questions and outputs the result
    cout << "Total Correct:      " << totalCorrect << endl;
    //Gathers total amount of incorrect questions and outputs the result
    cout << "Total Incorrect:    " << totalIncorrect << endl;
    //Takes the total correct questions and multiplies by 100 then divides by the total amount questions
    averageCorrect = (totalCorrect * 100) / totalQuestions;
    //Gathers average correct and outputs the result
    cout << "Average Correct:    " << averageCorrect << "%" << endl;

    // End of program
    cout << endl;
    cout << "Thanks for playing!" << endl;
    cout << "End of program" << endl;
    return 0;
}
