#include <fstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace day2 {
int countSubstring(const std::string &str, const std::string &sub)
{
  if (sub.empty()) return 0;
  int count = 0;
  for (size_t offset = str.find(sub); offset != std::string::npos;
  offset = str.find(sub, offset + sub.length()))
  {
    ++count;
  }
  return count;
}


bool isInvalidIdPart1(const std::string &input) {
  // if size is odd we can't have a weird pattern
  if (input.size() % 2 == 1) {
    return false;
  }

  return input.substr(0, input.size() / 2) ==
         input.substr(input.size() / 2);
}

bool isInvalidIdPart2(const std::string &input) {
  for (int i = 1; i <= input.size() / 2; i++) {
    const std::string searchString = input.substr(0, i);

    if (const int n = countSubstring(input, searchString); n * i == input.size()) {
      return true;
    }
  }

  return false;
}

void run() {

  std::ifstream infile("../data/day2.txt");

  std::string line;
  getline(infile, line);

  std::vector<std::string> ranges;
  boost::split(ranges, line, boost::is_any_of(","), boost::token_compress_on);

  long part1Result = 0;
  long part2Result = 0;
  for (std::string r: ranges) {
    std::vector<std::string> range;
    boost::split(range, r, boost::is_any_of("-"), boost::token_compress_on);
    const long lowerBound = stol(range.at(0));
    const long upperBound = stol(range.at(1));

    for (long i = lowerBound; i <= upperBound; i++) {
      if (isInvalidIdPart1(std::to_string(i))) {
        part1Result += i;
      }

      if (isInvalidIdPart2(std::to_string(i))) {
        part2Result += i;
      }
    }
  }

  std::cout << "----------- DAY 2 -----------\n";
  std::cout << "The solution for Part 1 is: " << part1Result << "\n";
  std::cout << "The solution for Part 2 is: " << part2Result << "\n";
}
}