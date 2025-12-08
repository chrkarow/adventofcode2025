#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <ranges>

namespace day7 {
std::vector<size_t> findMatches(const std::string& haystack, const char& needle) {
  size_t start_pos = haystack.find(needle);

  std::vector<size_t> matchIndices;
  while (start_pos != std::string::npos) {
    matchIndices.push_back(start_pos);

    start_pos = haystack.find(needle, start_pos + 1);
  }

  return matchIndices;
}

template <typename K, typename V> bool containsKey(const std::map<K, V>& searchMap, const K key) {
  auto keys = std::views::keys(searchMap);
  return std::ranges::find(keys, key) != keys.end();
}

template <typename K, typename V> void compute(std::map<K, V>& workingArea,
             const K key,
             const std::function<V(K, const V*)>& computeFn
    ) {
  if (containsKey(workingArea, key)) {
    workingArea.at(key) = computeFn(key, &workingArea.at(key));
  } else {
    workingArea.insert({key, computeFn(key, nullptr)});
  }
}

void run() {
  std::ifstream infile("../data/day7.txt");

  std::string startLine;
  getline(infile, startLine);

  std::map<unsigned long, unsigned long> beams;
  beams.insert({startLine.find('S'), 1});

  int part1Result = 0;

  for (std::string line; getline(infile, line);) {
    std::vector<size_t> indices = findMatches(line, '^');

    if (indices.empty()) {
      continue;
    }

    for (size_t index : indices) {
      if (containsKey(beams, index)) {
        unsigned long pathCount = beams.at(index);
        beams.erase(index);

        compute<unsigned long, unsigned long>(beams, index - 1, [pathCount](auto _, auto v) { return v == nullptr ? pathCount : *v + pathCount; });
        compute<unsigned long, unsigned long>(beams, index + 1, [pathCount](auto _, auto v) { return v == nullptr ? pathCount : *v + pathCount; });

        part1Result++;
      }
    }
  }

  unsigned long part2Result = std::ranges::fold_left(
      beams | std::views::values,
      0UL,
      std::plus()
      );

  std::cout << "----------- DAY 7 -----------\n";
  std::cout << "The solution for Part 1 is: " << part1Result << "\n";
  std::cout << "The solution for Part 2 is: " << part2Result << "\n";
}
}