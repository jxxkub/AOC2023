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

    int red_count = 12;
    int green_count = 13;
    int blue_count = 14;

    string line;
    int game = 1;  // games start from 1.
    int totalScore = 0;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string token;

        // Skip "Game X:" label
        iss >> token >> token;

        bool gameValid = true; // Assume the game is valid

        while (getline(iss, token, ',')) {
            // Process each move after comma
            istringstream moveStream(token);
            int move_count;
            string color;

            while (moveStream >> move_count >> color) {
                color.erase(remove(color.begin(), color.end(), ';'), color.end());
                if ((red_count < move_count && color == "red") ||
                    (green_count < move_count && color == "green") ||
                    (blue_count < move_count && color == "blue")) {
                    cout << "Impossible\n";
                    gameValid = false;
                }
            }
        }

        if (gameValid) {
            totalScore += game;
        }
        
        game++;
    }

    cout << "Total score of valid games: " << totalScore << endl;

    inputFile.close();

    return 0;
}
