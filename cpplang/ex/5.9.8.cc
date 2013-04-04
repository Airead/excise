/**
 * @file 5.9.8.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 21:06:26
 */

/*
  Write a program that uses **an array of char** and a loop to read one word at a time until
  the word done is entered. The program should then report the number of words entered
  (not counting done). A sample run could look like this:

  Enter words (to stop, type the word done):
  anteater birthday category dumpster
  envy finagle geometry done for sure
  You entered a total of 7 words.
  You should include the cstring header file and use the strcmp() function to make the
  comparison test.
 */

#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{
    using namespace std;

    char word[20];
    int count;

    cout << "Enter words (to stop, type the word done):" << endl;

    cin >> word;
    count = 0;
    while (strcmp(word, "done") != 0) {
        count++;
        cin >> word;
    }

    cout << "You entered a total of " << count << " words" << endl;

    return 0;
}
