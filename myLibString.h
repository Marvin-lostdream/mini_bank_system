#pragma once

#include <iostream>
#include <cctype>
#include <vector>

namespace myLibString
{
  std::string allToLowerCase(std::string sentence)
  {
    for (int i = 0; i < sentence.length(); i++)
    {

      sentence[i] = tolower(sentence[i]);
    }
    return sentence;
  }

  std::string allToUpperCase(std::string sentence)
  {
    for (int i = 0; i < sentence.length(); i++)
    {

      sentence[i] = toupper(sentence[i]);
    }
    return sentence;
  }

  char invertedLetterCase(char character)
  {
    return isupper(character) ? tolower(character) : toupper(character);
  }

  bool isVowel(char character)
  {
    character = tolower(character);
    return ((character == 'a') || (character == 'u') || (character == 'o') || (character == 'i') || (character == 'e'));
  }

  std::vector<string> mySplit(string line, string delimiter)
  {
    vector<string> vString;
    short pos = 0;
    string sWord = "";
    while ((pos = line.find(delimiter)) != std::string::npos)
    {
      sWord = line.substr(0, pos);
      if (sWord != "")
      {
        vString.push_back(sWord);
      }
      line.erase(0, pos + delimiter.length());
    }
    if (line != "")
    {
      vString.push_back(line);
    }
    return vString;
  }

}