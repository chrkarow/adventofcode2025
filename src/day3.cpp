#include <fstream>
#include <iostream>
using namespace std;

int findMax(const string& searchString, char& maxChar) {
  int maxIndex = 0;

  for (int i = 0; i < searchString.size(); i++) {
    if (searchString[i] > maxChar) {
      maxChar = searchString[i];
      maxIndex = i;
    }
  }

  return maxIndex;
}

long findHighestJoltage(const string& line, const int& size) {
  string joltage;

  int nextStartIndex = 0;

  for (int i = size; i > 0; i--) {
    string searchString = line.substr(nextStartIndex, line.size() - (i - 1) - nextStartIndex );

    char maxChar = '0';
    nextStartIndex += findMax(searchString, maxChar) + 1;
    joltage += maxChar;
  }

  return stol(joltage);
}


void day3() {
  long part1Result = 0;
  long part2Result = 0;

  ifstream infile("../data/day3.txt");
  for (string line; getline(infile, line);) {
    part1Result += findHighestJoltage(line,  2);
    part2Result += findHighestJoltage(line,  12);
  }

  cout << "----------- DAY 3 -----------\n";
  cout << "The solution for Part 1 is: " << part1Result << "\n";
  cout << "The solution for Part 2 is: " << part2Result << "\n";
}