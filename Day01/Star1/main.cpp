#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <istream>

using namespace std;

int concatenateDigits(int first, int last) {
    return first * 10 + last;
}

int firstDigit(int n)
{
    // Remove last digit from number
    // till only one digit is left
    while (n >= 10) 
        n /= 10;
     
    // return the first digit
    return n;
}
 
// Find the last digit
int lastDigit(int n)
{
    // return the last digit
    return (n % 10);
}

int main() {
    ifstream input("input.txt"); // read the file
    string line;
    string result;

    int sum = 0;

    if (input.is_open()) {
        while (getline(input, line)) {
            result.clear(); // Clear the result for each new line

            for (char c : line) {
                if (isdigit(c)) {
                    result += c;
                }
            }
            
            sum += concatenateDigits(firstDigit(stoi(result)), lastDigit(stoi(result)));

        }
        input.close();
    }

    cout << sum;

    return 0;
}