#include <fstream>
#include <iostream>
#include <vector>

namespace day4 {
struct Coordinates {
  int y;
  int x;
};

bool operator==(const Coordinates& c1, const Coordinates& c2) {
  return c1.y == c2.y && c1.x == c2.x;
}

bool contains(std::vector<Coordinates>& coords, const Coordinates& c) {
  return std::count(coords.begin(), coords.end(), c) > 0;
}

bool isAccessible(const std::vector<std::string>& grid, const Coordinates coords) {
  int count = 0;
  if (coords.y - 1 >= 0) {
    if (coords.x - 1 >= 0 && grid[coords.y - 1][coords.x - 1] == '@') {
      count++;
    }
    if (grid[coords.y - 1][coords.x] == '@') { count++; }
    if (coords.x + 1 < grid[coords.y - 1].size() && grid[coords.y - 1][
          coords.x + 1] == '@') { count++; }
  }

  if (coords.x - 1 >= 0 && grid[coords.y][coords.x - 1] == '@') { count++; }
  if (coords.x + 1 < grid[coords.y].size() && grid[coords.y][coords.x + 1] ==
      '@') { count++; }

  if (coords.y + 1 < grid.size()) {
    if (coords.x - 1 >= 0 && grid[coords.y + 1][coords.x - 1] == '@') {
      count++;
    }
    if (grid[coords.y + 1][coords.x] == '@') { count++; }
    if (coords.x + 1 < grid[coords.y + 1].size() && grid[coords.y + 1][
          coords.x + 1] == '@') { count++; }
  }

  return count < 4;
}

void removeRec(
    std::vector<std::string>& grid,
    std::vector<Coordinates>& alreadyRemoved,
    const Coordinates coords
    ) {
  if (grid[coords.y][coords.x] != '@' || !isAccessible(grid, coords)) {
    return;
  }

  grid[coords.y][coords.x] = '.';
  alreadyRemoved.push_back(coords);

  if (coords.y - 1 >= 0) {
    if (coords.x - 1 >= 0 &&
        !contains(alreadyRemoved, {coords.y - 1, coords.x - 1})) {
      removeRec(grid, alreadyRemoved, {coords.y - 1, coords.x - 1});
    }
    if (!contains(alreadyRemoved, {coords.y - 1, coords.x})) {
      removeRec(grid, alreadyRemoved, {coords.y - 1, coords.x});
    }
    if (coords.x + 1 < grid[coords.y - 1].size() &&
        !contains(alreadyRemoved, {coords.y - 1, coords.x + 1})) {
      removeRec(grid, alreadyRemoved, {coords.y - 1, coords.x + 1});
    }
  }

  if (!contains(alreadyRemoved, {coords.y, coords.x - 1})) {
    removeRec(grid, alreadyRemoved, {coords.y, coords.x - 1});
  }
  if (!contains(alreadyRemoved, {coords.y, coords.x + 1})) {
    removeRec(grid, alreadyRemoved, {coords.y, coords.x + 1});
  }

  if (coords.y + 1 < grid.size()) {
    if (coords.x - 1 >= 0 &&
        !contains(alreadyRemoved, {coords.y + 1, coords.x - 1})) {
      removeRec(grid, alreadyRemoved, {coords.y + 1, coords.x - 1});
    }
    if (!contains(alreadyRemoved, {coords.y + 1, coords.x})) {
      removeRec(grid, alreadyRemoved, {coords.y + 1, coords.x});
    }
    if (coords.x + 1 < grid[coords.y + 1].size() &&
        !contains(alreadyRemoved, {coords.y + 1, coords.x + 1})) {
      removeRec(grid, alreadyRemoved, {coords.y + 1, coords.x + 1});
    }
  }
}

void run() {
  std::vector<std::string> grid;

  std::ifstream infile("../data/day4.txt");
  for (std::string line; getline(infile, line);) {
    grid.push_back(line);
  }

  int part1Result = 0;
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      if (grid[y][x] == '@' && isAccessible(grid, {y, x})) { part1Result++; }
    }
  }

  std::vector<Coordinates> removed = {};

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      if (grid[y][x] == '@' && isAccessible(grid, {y, x})) {
        removeRec(grid, removed, {y, x});
      }
    }
  }

  std::cout << "----------- DAY 4 -----------\n";
  std::cout << "The solution for Part 1 is: " << part1Result << "\n";
  std::cout << "The solution for Part 2 is: " << removed.size() << "\n";
}
}