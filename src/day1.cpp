#include <fstream>
#include <iostream>
#include <list>
using namespace std;

void day1() {
    list<tuple<string, int> > instructions;

    ifstream infile("../data/day1.txt");
    for (string line; getline(infile, line);) {
        instructions.emplace_back(line.substr(0, 1), stoi(line.substr(1)));
    }

    int part1Result = 0;
    int part2Result = 0;

    int currentNo = 50;

    for (tuple currentInstruction: instructions) {
        // cout << get<0>(currentInstruction) << " " << get<1>(currentInstruction) << "\n";

        if (get<0>(currentInstruction) == "R") {
            currentNo = currentNo + get<1>(currentInstruction);
            if (currentNo >= 100) {
                part2Result += currentNo / 100;
            }
        } else {
            currentNo = currentNo - get<1>(currentInstruction);
            if (currentNo <= 0) {
                part2Result += (currentNo / 100) * -1 +
                    (currentNo * -1 != get<1>(currentInstruction) ? 1 : 0); // set offset to zero if started turning the dial from zero
            }
        }

        currentNo = currentNo % 100 < 0 ? 100 + (currentNo % 100) : currentNo % 100;

        // cout << currentNo << "\n";

        if (currentNo == 0) { part1Result++; }
    }

    cout << "----------- DAY 1 -----------\n";
    cout << "The solution for Part 1 is: " << part1Result << "\n";
    cout << "The solution for Part 2 is: " << part2Result << "\n";
}
