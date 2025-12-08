#include <fstream>
#include <iostream>

namespace day3 {
int findMax(const std::string& searchString, char& maxChar) {
  int maxIndex = 0;

  for (int i = 0; i < searchString.size(); i++) {
    if (searchString[i] > maxChar) {
      maxChar = searchString[i];
      maxIndex = i;
    }
  }

  return maxIndex;
}

long findHighestJoltage(const std::string& line, const int& size) {
  std::string joltage;

  int nextStartIndex = 0;

  for (int i = size; i > 0; i--) {
    std::string searchString = line.substr(nextStartIndex, line.size() - (i - 1) - nextStartIndex);

    char maxChar = '0';
    nextStartIndex += findMax(searchString, maxChar) + 1;
    joltage += maxChar;
  }

  return std::stol(joltage);
}


void run() {
  long part1Result = 0;
  long part2Result = 0;

  std::ifstream infile("../data/day3.txt");
  for (std::string line; getline(infile, line);) {
    part1Result += findHighestJoltage(line, 2);
    part2Result += findHighestJoltage(line, 12);
  }

  std::cout << "----------- DAY 3 -----------\n";
  std::cout << "The solution for Part 1 is: " << part1Result << "\n";
  std::cout << "The solution for Part 2 is: " << part2Result << "\n";
}
}