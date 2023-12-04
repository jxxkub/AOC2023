#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

/* This code is partially not mine, the main idea came from:
https://github.com/vss2sn/advent_of_code/blob/master/2023/cpp/day_03b.cpp
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
};

int main() {

    string line;
    fstream input ("input.txt");

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

    unordered_map<int, Gear> gears;

    for (const auto& n : numbers) {
        for (int row = n.row - 1; (row <= n.row + 1); row++) {
            if (row < 0 || row >= map.size()) continue;
            const int col_increment = (row == n.row) ? n.order + 1 : 1; 
            for (int col = n.col - 1; (col <= n.col + n.order); col += col_increment) {
                if (col < 0 || col >= map[row].size()) continue;
                if (map[row][col] == '*') {
                    const int id = map[0].size() * row + col;

                    auto& gear = gears[id];
                    gear.n++;
                    gear.numbers.push_back(n.number);
                }
            }
        }
    }

    size_t ans = 0;
    for (const auto& [id, gear] : gears) {
        if (gear.n == 2) {
            ans += (gear.numbers[0] * gear.numbers[1]);
        }
    }
    cout << ans << '\n';
    return 0;
}
