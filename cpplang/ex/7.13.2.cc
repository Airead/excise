/**
 * @file 7.13.2.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 10:37:47
 */

/*
 * Write a program that asks the user to enter up to 10 golf scores,
 * which are to be stored in an array. You should provide a means for
 * the user to terminate input prior to entering 10 scores. The
 * program should display all the scores on one line and report the
 * average score. Handle input, display, and the average calculation
 * with three separate array processing functions.
 */

#include <iostream>

using namespace std;

const int scoresNumMax = 10;

int readScores(float *scores)
{
    int i;

    for (i = 0; i < scoresNumMax; i++) {
        cout << "[" << i + 1 << "] input golf scores: ";
        cin >> scores[i];
        if (cin.fail()) {
            break;
        }
    }

    return i;
}

float calcScores(float *scores, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++) {
        sum += scores[i];
    }

    return sum / n;
}

void displayScores(float *scores, int n)
{
    cout << "scores: ";
    for (int i = 0; i < n; i++) {
        cout << scores[i] << ", ";
    }
    cout << "average score: " << calcScores(scores, n) << endl;
}

int main(int argc, char *argv[])
{
    float scores[scoresNumMax];
    int n;

    n = readScores(scores);
    displayScores(scores, n);

    return 0;
}
