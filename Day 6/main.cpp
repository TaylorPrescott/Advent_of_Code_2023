#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// #include <climits>
// Used with:
// unsigned long long int maxVal = ULLONG_MAX;
// cout << maxVal << endl;
// to check if number could fit. compiler was throwing stoi() index out bounds error. Used stoull() and changed return type to reflect it.

using namespace std;

// Stop repeating (No need for race times and distance records to have separate loops)


// For each ms you spend holding down the button, the boat's speed increases by 1 mm/ms. 
// Example: race lasts 7 ms, record distance is 9mm. Could hold button for 2ms, giving it a speed of 2mm/ms. It will have 5ms to travel, reaching a total distance of 10mm. Could also hold button for 5ms causing it to go 10mm.

// Goal: Determine number of ways you could beat the record in each race. What do you get if you multiply these numbers together?

void question_one(char *file) {
    ifstream raceResults (file);
    vector<int> raceTimes;
    vector<int> distanceRecords;

    // Read file and store time and distance results in respective vectors
    if ( raceResults.is_open() ) {
        while ( raceResults.good() ) {
            string currentLine;
            getline(raceResults, currentLine);

            if ( currentLine.find("Time") == 0 ) {

                // Handle race times
                string currentRaceTime = "";
                for (int i = 0; i < currentLine.length(); i++) {
                    if ( isdigit(currentLine[i]) ) {
                        currentRaceTime += currentLine[i];
                    } else if ( currentLine[i] == ' ' && currentRaceTime != "" ) {
                        raceTimes.push_back(stoi(currentRaceTime));
                        currentRaceTime = "";
                    }
                }
                raceTimes.push_back(stoi(currentRaceTime));

                // Print race times vector
                // for (const int& i : raceTimes) {
                //     cout << i << " ";
                // }
                // cout << endl;

            } else {

                // Handle distances
                string currentDistanceRecord = "";
                for (int i = 0; i < currentLine.length(); i++) {
                    if ( isdigit(currentLine[i]) ) {
                        currentDistanceRecord += currentLine[i];
                    } else if ( currentLine[i] == ' ' && currentDistanceRecord != "" ) {
                        distanceRecords.push_back(stoi(currentDistanceRecord));
                        currentDistanceRecord = "";
                    }
                }
                distanceRecords.push_back(stoi(currentDistanceRecord));

                // Print distanceRecords vector
                // for (const int& i : distanceRecords) {
                //     cout << i << " ";
                // }
                // cout << endl;
            }
        }
    }

    // Find number of ways to win each race and multiply them together.
    int waysToWin[raceTimes.size()];
    int finalProduct = 1;

    for (int i = 0; i < raceTimes.size(); i++) {
        int currentWaysToWin = 0;
        for (int j = 1; j < raceTimes[i]; j++) {
            if ( (raceTimes[i] - j) * j > distanceRecords[i]) {
                currentWaysToWin++;
            }
        }
        if ( currentWaysToWin > 0 ) {
            waysToWin[i] = currentWaysToWin;
        } else {
            // If no ways to win a race, dont multiply the others by 0.
            waysToWin[i] = 1;
        }
    }

    for (int i = 0; i < raceTimes.size(); i++) {
        finalProduct *= waysToWin[i];
    }

    cout << finalProduct << endl;
}



// Question two: The paper with race times and record distances actually had very bad kerning. There's really one race. Ignore the spaces between the numbers on each line. How many ways can you beat the record in this one much longer race?

unsigned long long int getValues(string currentLine) {
    string currentNumValues = "";
    unsigned long long int value;
    for (int i = 0; i < currentLine.length(); i++) {
        if ( isdigit(currentLine[i]) ) {
            //cout << currentLine[i];
            currentNumValues += currentLine[i];
        }
    }
    //cout << endl;
    value = stoull(currentNumValues);
    return value;
}

void question_two(char *file) {
    ifstream raceResults (file);
    unsigned long long int raceTime;
    unsigned long long int distanceRecord;
    unsigned long long int numWaysToWin = 0;

    if ( raceResults.is_open() ) {
        while ( raceResults.good() ) {
            string currentLine;
            getline(raceResults, currentLine);
            //cout << currentLine << endl;
            cout << getValues(currentLine) << endl; 
            if ( currentLine.find("Time") == 0 ) {
                raceTime = getValues(currentLine);
            } else {
                distanceRecord = getValues(currentLine);
            }
        }
    }

    for (int i = 1; i < raceTime; i++) {
        if ( (raceTime - i) * i > distanceRecord ) {
            numWaysToWin++;
        }
    }
    cout << numWaysToWin << endl;
}

int main(int argc, char *argv[]) {

    //question_one(argv[1]);
    //question_two(argv[1]);

    return 0;
}