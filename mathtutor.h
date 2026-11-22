/************************************************************
Program    : MathTutorV5
Programmer : Benjamin Dickinson
Date       : 2026.11.21
Github Repo: https://github.com/bendickinson15/MathTutorV5
Description: Contains all prototypes for functions main calls
*************************************************************/
#ifndef MATHTUTORV5_MATHTUTOR_H
#define MATHTUTORV5_MATHTUTOR_H

#include <string> //for string data
#include <vector> //for vector/2d vector data

using namespace std;

extern int currentRange;
extern const int MAX_ATTEMPTS;

//Bridge between function file and main file
void DisplayGameIntro();
string GetUserName();
vector<int> GenerateRandomQuestion(int mathLevel);
string AskToPlayAgain();
int GetNumericValue();
bool GiveThreeAttempts(const string& name, vector<int>& question, int& streakCorrect, int& streakIncorrect);
void CheckForLevelChange(int& numCorrect, int& numIncorrect, int& level);
void DisplaySummaryReport(const vector<vector<int> > &allQuestions);

#endif