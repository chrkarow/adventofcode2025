#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Coordinates {
  int y;
  int x;
};

bool operator==(const Coordinates& c1, const Coordinates& c2) {
  return c1.y == c2.y && c1.x == c2.x;
}

bool contains(vector<Coordinates> coords, Coordinates c) {
  return count(coords.begin(), coords.end(), c) > 0;
}

bool isAccessible(const vector<string>& grid, const Coordinates coords) {
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
    vector<string>& grid,
    vector<Coordinates>& alreadyRemoved,
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

void day4() {
  std::vector<string> grid;

  ifstream infile("../data/day4.txt");
  for (string line; getline(infile, line);) {
    grid.push_back(line);
  }

  int part1Result = 0;
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      if (grid[y][x] == '@' && isAccessible(grid, {y, x})) { part1Result++; }
    }
  }

  vector<Coordinates> removed = {};

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      if (grid[y][x] == '@' && isAccessible(grid, {y, x})) {
        removeRec(grid, removed, {y, x});
      }
    }
  }

  cout << "----------- DAY 4 -----------\n";
  cout << "The solution for Part 1 is: " << part1Result << "\n";
  cout << "The solution for Part 2 is: " << removed.size() << "\n";
}