#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>


namespace day6 {
long part1(std::vector<std::string> problems) {
  std::vector<std::vector<std::string>> splitBySpace;

  // Lazy structuring of data strings...
  boost::trim(problems[0]);
  boost::trim(problems[1]);
  boost::trim(problems[2]);
  boost::trim(problems[3]);
  boost::trim(problems[4]);

  std::vector<std::string> tokens;
  boost::split(tokens, problems[0], boost::is_any_of(" "), boost::token_compress_on);
  splitBySpace.push_back(tokens);
  boost::split(tokens, problems[1], boost::is_any_of(" "), boost::token_compress_on);
  splitBySpace.push_back(tokens);
  boost::split(tokens, problems[2], boost::is_any_of(" "), boost::token_compress_on);
  splitBySpace.push_back(tokens);
  boost::split(tokens, problems[3], boost::is_any_of(" "), boost::token_compress_on);
  splitBySpace.push_back(tokens);
  boost::split(tokens, problems[4], boost::is_any_of(" "), boost::token_compress_on);
  splitBySpace.push_back(tokens);

  // solving of the problem
  long part1Result = 0;
  for (int i = 0; i < splitBySpace[0].size(); i++) {
    if (splitBySpace[4][i] == "+") {
      part1Result += stol(splitBySpace[0][i]) + stol(splitBySpace[1][i]) + stol(splitBySpace[2][i]) + stol(
          splitBySpace[3][i]);
    } else {
      part1Result += stol(splitBySpace[0][i]) * stol(splitBySpace[1][i]) * stol(splitBySpace[2][i]) * stol(
          splitBySpace[3][i]);
    }
  }

  return part1Result;
}

long part2(std::vector<std::string> problems) {
  using namespace std::string_literals;

  long result = 0;

  auto it0 = problems[0].rbegin() - 1;
  auto it1 = problems[1].rbegin() - 1;
  auto it2 = problems[2].rbegin() - 1;
  auto it3 = problems[3].rbegin() - 1;
  auto it4 = problems[4].rbegin() - 1;

  std::vector<long> numbers;
  while (it0 != problems[0].rend()) {
    ++it0;
    ++it1;
    ++it2;
    ++it3;
    ++it4;

    std::string s = ""s + *it0 + *it1 + *it2 + *it3;
    boost::trim(s);
    numbers.push_back(std::stol(s));

    if (*it4 != ' ') {
      long subResult = *it4 == '+' ? 0 : 1;

      for (const long n : numbers) {
        if (*it4 == '+') {
          subResult += n;
        } else {
          subResult *= n;
        }
      }

      result += subResult;

      numbers.clear();
      ++it0;
      ++it1;
      ++it2;
      ++it3;
      ++it4;
    }
  }

  return result;
}

void run() {
  std::ifstream infile("../data/day6.txt");

  std::vector<std::string> problems;
  for (std::string line; getline(infile, line);) {
    problems.push_back(line);
  }

  std::cout << "----------- DAY 6 -----------\n";
  std::cout << "The solution for Part 1 is: " << part1(problems) << "\n";
  std::cout << "The solution for Part 2 is: " << part2(problems) << "\n";
}
}