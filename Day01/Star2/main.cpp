#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int concatenateDigits(int first, int last) {
    return first * 10 + last;
}

int firstDigit(int n) {
    while (n >= 10) 
        n /= 10;
    return n;
}

int lastDigit(int n) {
    return (n % 10);
}

int main() {
    ifstream input("input.txt");
    string line;
    int sum = 0;

    unordered_map<string, string> umap;

    umap["one"] = "1";
    umap["two"] = "2";
    umap["three"] = "3";
    umap["four"] = "4";
    umap["five"] = "5";
    umap["six"] = "6";
    umap["seven"] = "7";
    umap["eight"] = "8";
    umap["nine"] = "9";

    if (input.is_open()) {
        while (getline(input, line)) {
            string result;
            for (size_t i = 0; i < line.length(); ++i) {
                // Check if a substring from the current position matches any key
                for (const auto& entry : umap) {
                    const string& key = entry.first;
                    const string& value = entry.second;
                    if (line.compare(i, key.length(), key) == 0) {
                        result += value;
                        i += 1;  // Move to the next character
                        break;
                    }
                }
                // If the current character is a digit, append it to the result
                if (isdigit(line[i])) {
                    result += line[i];
                }
            }
            //cout << result << '\n';
            sum += concatenateDigits(firstDigit(stoi(result)), lastDigit(stoi(result)));
        }
        input.close();
    }
    cout << "Sum: " << sum << endl;

    return 0;
}
