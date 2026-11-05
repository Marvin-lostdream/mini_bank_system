#pragma once

#include <cstdlib>
#include <ctime>

namespace myMathLib
{

  long long powerToM(int number, int pw)
  {
    if (pw < 0)
      return 0;

    long long result = 1;

    for (int i = 1; i <= pw; i++)
    {
      result *= number;
    }
    return result;
  }

  void swapNum(int &num1, int &num2)
  {
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }

  int randomNumber(int from, int to)
  {
    return rand() % (to - from + 1) + from;
  }

  void swap(int &num1, int &num2)
  {
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }

}