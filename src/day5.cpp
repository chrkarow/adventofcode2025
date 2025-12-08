#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace day5 {
/**
 * A range of ingredient IDs. Both bounds are inclusive.
 */
struct IngredientIdRange {
  unsigned long lower;
  unsigned long upper;

  /**
   * Checks if the given number is within this range (both bounds inclusive).
   * @param n The number to check.
   * @return \c true if the number is within this range, \c false otherwise.
   */
  [[nodiscard]] bool contains(const long n) const {
    return n >= lower && n <= upper;
  }

  /**
   * @return The size of this range (both bounds inclusive)
   */
  [[nodiscard]] unsigned long size() const {
    return upper - lower + 1;
  }
};

/**
 * Checks if the given idToCheck is in at least one of the freshRanges.
 * @param freshRanges The ranges of ingredient IDs which are considered to be fresh
 * @param idToCheck The id to check
 * @return \c true if the given id is in at least one range, \c false otherwise.
 */
bool isFresh(const std::vector<IngredientIdRange>& freshRanges, const long& idToCheck) {
  return std::ranges::any_of(freshRanges, [idToCheck](const IngredientIdRange r) { return r.contains(idToCheck); });
}

/**
 * Merges bridged ingredient ID ranges in the given vector. The vector will be sorted
 * @param rangeVector The vector to work on.
 */
void mergeBridgedRanges(std::vector<IngredientIdRange>& rangeVector) {
  std::ranges::sort(rangeVector, [](const IngredientIdRange& r1, const IngredientIdRange& r2) {
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

/**
 * Recombines the given ranges so that the result only contains distinct ranges which are not overlapping.
 * @param freshIngredients the ingredient range vector to recombine
 * @return The recombined result.
 */
std::vector<IngredientIdRange> recombineRanges(std::vector<IngredientIdRange> freshIngredients) {
  std::vector<IngredientIdRange> returnVector;

  std::ranges::sort(freshIngredients, [](const IngredientIdRange& r1, const IngredientIdRange& r2) {
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
        mergeBridgedRanges(returnVector);
        break;
      }

      // extend upper bound of existing range
      if (it->lower >= lower && it->lower <= upper && it->upper > upper) {
        upper = it->upper;
        add = false;
        mergeBridgedRanges(returnVector);
        break;
      }
    }

    // range not overlapping in any case
    if (add) { returnVector.push_back(*it); }
  }

  return returnVector;
}


void run() {
  std::vector<IngredientIdRange> freshIngredients;

  int part1Result = 0;

  std::ifstream infile("../data/day5.txt");

  bool readRanges = true;
  for (std::string line; getline(infile, line);) {
    if (line.empty()) {
      readRanges = false;
      continue;
    }

    if (readRanges) {
      std::vector<std::string> rawIdRange;
      boost::split(rawIdRange, line, boost::is_any_of("-"), boost::token_compress_on);
      freshIngredients.push_back({stoul(rawIdRange.at(0)), stoul(rawIdRange.at(1))});
    } else {
      part1Result += isFresh(freshIngredients, stol(line));
    }
  }

  constexpr unsigned long startValue = 0;
  const unsigned long part2Result = std::ranges::fold_left(
      recombineRanges(freshIngredients),
      startValue,
      [](const unsigned long acc, const IngredientIdRange r) {
        return acc + r.size();
      });

  std::cout << "----------- DAY 5 -----------\n";
  std::cout << "The solution for Part 1 is: " << part1Result << "\n";
  std::cout << "The solution for Part 2 is: " << part2Result << "\n";
}
}