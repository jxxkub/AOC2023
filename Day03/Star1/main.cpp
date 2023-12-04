#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <numeric>

/* This code is partially not mine, the main idea came from:
https://github.com/vss2sn/advent_of_code/blob/master/2023/cpp/day_03a.cpp
*/

using namespace std;

struct Number {
    int col;
    int row;
    int number;
    int order; // number of digits in number
};

struct Gear {
    int n = 0;
    vector<int> numbers;
}

int main(int argc, char* argv[]) {

    string line;
    fstream input("input.txt");

    vector<string> map;
    vector<Number> numbers; // store numbers and their location

    // match one or more digits
    regex numberRegex(R"(\d+)");

    while (getline(input, line)) {
        map.push_back(line);

        auto numberBegin = sregex_iterator(line.begin(), line.end(), numberRegex);
        auto numberEnd = sregex_iterator();

        for (auto iter = numberBegin; iter != numberEnd; ++iter) {
            Number n;
            n.row = map.size() - 1;
            n.col = iter->position();
            n.number = stoi(iter->str());
            n.order = iter->str().size();
            numbers.push_back(n);
        }
    }

    //vector<int> parts;
    unordered_map<int, Gear> gears;
    for (const auto& n : numbers) {
        bool still_searching = true;
        for (int row = n.row - 1; (row <= n.row + 1) && still_searching; row++) {
            if (row < 0 || row >= map.size()) continue;

            const int col_increment = (row == n.row) ? n.order + 1 : 1;
            for (int col = n.col - 1; (col <= n.col + n.order) && still_searching; col += col_increment) {
                if (col < 0 || col >= map[row].size()) continue;
                if (map[row][col] != '.' && !(map[row][col] >= '0' && map[row][col] <= '9')) {
                    still_searching = false;
                    parts.push_back(n.number);
                }
            }
        }
    }

    const auto total = accumulate(begin(parts), end(parts), 0);
    cout << total << '\n';
    return 0;
}
