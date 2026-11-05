#pragma once

#include <iostream>
#include <limits>
#include "myMathLib.h"
using namespace std;

namespace inputsLib
{
  // ====================== For Read Numbers ====================== //

  int readNumber(string msg)
  {
    int number = 0;
    cout << msg << endl;
    cin >> number;
    while (cin.fail())
    {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "Invalid Number , Enter a new One : ";
      cin >> number;
    }
    return number;
  }

  int readPositiveNumberWithMsg(string msg)
  {
    int number = 0;
    do
    {
      cout << msg << endl;
      cin >> number;
      if (number < 0)
      {
        cout << "\nThe number must be positive ! \n";
      }
    } while (number < 0);
    return number;
  }

  int readNumberInRange(int from, int to)
  {
    int number;
    do
    {
      cout << "Enter a number from " << from << " to " << to << " : ";
      cin >> number;
    } while (number < from || number > to);
    return number;
  }

  // ================== For Read String ================== //

  string readString(string msg)
  {
    string sentence = "";
    cout << msg;
    getline(cin >> ws, sentence);
    return sentence;
  }

  char readChar(string msg)
  {
    char character = ' ';
    cout << msg << endl;
    cin >> character;
    return character;
  }

}