#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


std::vector<std::string> readFileToList(const std::string& filePath) {
    std::vector<std::string> lines;
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }

    return lines;
}

vector<string> numSpelled = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int getNum(string line){
    int lastDigit = 0, digit = 0;
    bool firstFound = false;

    for (int i = 0; i < line.size(); ++i) {
        if(line[i] - '0' <= 9 && line[i] - '0' >= 0){
            lastDigit = line[i] - '0';
            if (!firstFound){
                firstFound = true;
                digit = lastDigit * 10;
            }
        }
        for (int j = 0; j < numSpelled.size(); ++j) {
            if (line[i] == numSpelled[j][0]){
                bool same = true;
                for (int k = 0; k < numSpelled[j].size(); ++k) {
                    if (line[i + k] == numSpelled[j][k]){

                    }
                    else{
                        same = false;
                        break;
                    }
                }
                if (same){
                    lastDigit = j;
                    if (!firstFound){
                        firstFound = true;
                        digit = j * 10;
                    }
                }
            }
        }
    }
    digit += lastDigit;
    return digit;
}

int main() {
    vector<string> lines = readFileToList("input.txt");
    int numSum = 0, numLine = 0;

    for (int i = 0; i < lines.size(); ++i) {
        numLine = getNum(lines[i]);
        numSum += numLine;
        cout<<"\nLine: " + to_string(numLine);
    }

    cout<<"\n\nSum: " + to_string(numSum);

}


