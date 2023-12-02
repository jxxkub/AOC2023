#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int red_count = 0, green_count = 0, blue_count = 0, total = 0, totalScore = 0;

    string line;
    string game;

    while (getline(inputFile, line)) {

        int red_max = 0, green_max = 0, blue_max = 0;

        istringstream iss(line);
        string token;

        // Skip "Game X:" label
        iss >> token >> token;
        while (getline(iss, token, ',')) {
            // Process each move after comma
            istringstream moveStream(token);
            int move_count = 0;
            string color;

            while (moveStream >> move_count >> color) {
                color.erase(remove(color.begin(), color.end(), ';'), color.end());
                if (color == "red" && move_count > red_max) {
                    red_max = move_count;
                } else if (color == "green" && move_count > green_max) {
                    green_max = move_count;
                } else if (color == "blue" && move_count > blue_max) {
                    blue_max = move_count;
                }
            }
        }
        //cout << "Red: " << red_max << " ";
        //cout << "Green: " << green_max << " ";
        //cout << "Blue: " << blue_max << " ";
        total = red_max * green_max * blue_max;
        //cout << "Total: " << total << endl;
        totalScore += total;
    }

    cout << "Sum of the power: " << totalScore << endl;

    inputFile.close();

    return 0;
}
