#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;

struct IngredientIdRange {
  unsigned long lower;
  unsigned long upper;

  [[nodiscard]] bool contains(long n) const {
    return n >= lower && n <= upper;
  }

  [[nodiscard]] unsigned long size() const {
    return upper - lower + 1;
  }
};

bool isFresh(const vector<IngredientIdRange>& freshRanges, const long& idToCheck) {
  return ranges::any_of(freshRanges, [idToCheck](const IngredientIdRange r) { return r.contains(idToCheck); });
}

/// Checks for bridged ranges in the given range vector and merges them to one
void margeBridgedRanges(vector<IngredientIdRange>& rangeVector) {
  ranges::sort(rangeVector, [](const IngredientIdRange& r1, const IngredientIdRange& r2) {
    return r1.upper > r2.upper;
  });

  for (auto it = rangeVector.begin(); it != rangeVector.end() - 1; ++it) {
    if (it->lower <= (it + 1)->upper) {
      it->lower = (it + 1)->lower;
      rangeVector.erase(it + 1);
      --it;
    }
  }
}

vector<IngredientIdRange> recombineRanges(vector<IngredientIdRange>& freshIngredients) {
  vector<IngredientIdRange> returnVector;

  ranges::sort(freshIngredients, [](const IngredientIdRange& r1, const IngredientIdRange& r2) {
    return r1.size() > r2.size();
  });

  returnVector.push_back(freshIngredients[0]);

  for (auto it = freshIngredients.begin() + 1; it != freshIngredients.end(); ++it) {
    bool add = true;
    for (auto& [lower, upper] : returnVector) {
      // range contained in existing range -> drop
      if (it->lower >= lower && it->lower <= upper && it->upper >= lower && it->upper <= upper) {
        add = false;
        break;
      }

      // extend lower bound of existing range
      if (it->lower < lower && it->upper >= lower && it->upper <= upper) {
        lower = it->lower;
        add = false;
        margeBridgedRanges(returnVector);
        break;
      }

      // extend upper bound of existing range
      if (it->lower >= lower && it->lower <= upper && it->upper > upper) {
        upper = it->upper;
        add = false;
        margeBridgedRanges(returnVector);
        break;
      }
    }

    // range not overlapping in any case
    if (add) { returnVector.push_back(*it); }
  }

  return returnVector;
}


void day5() {
  vector<IngredientIdRange> freshIngredients;

  int part1Result = 0;

  ifstream infile("../data/day5.txt");

  bool readRanges = true;
  for (string line; getline(infile, line);) {
    if (line.empty()) {
      readRanges = false;
      continue;
    }

    if (readRanges) {
      vector<string> rawIdRange;
      boost::split(rawIdRange, line, boost::is_any_of("-"), boost::token_compress_on);
      freshIngredients.push_back({stoul(rawIdRange.at(0)), stoul(rawIdRange.at(1))});
    } else {
      part1Result += isFresh(freshIngredients, stol(line));
    }
  }

  constexpr unsigned long startValue = 0;
  const unsigned long part2Result = ranges::fold_left(
      recombineRanges(freshIngredients),
      startValue,
      [](const unsigned long acc, const IngredientIdRange r) {
        return acc + r.size();
      });

  cout << "----------- DAY 5 -----------\n";
  cout << "The solution for Part 1 is: " << part1Result << "\n";
  cout << "The solution for Part 2 is: " << part2Result << "\n";
}