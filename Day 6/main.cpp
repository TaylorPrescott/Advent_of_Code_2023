#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// For each ms you spend holding down the button, the boat's speed increases by 1 mm/ms. 
// Example: race lasts 7 ms, record distance is 9mm. Could hold button for 2ms, giving it a speed of 2mm/ms. It will have 5ms to travel, reaching a total distance of 10mm. Could also hold button for 5ms causing it to go 10mm.

// Goal: Determine number of ways you could beat the record in each race. What do you get if you multiply these numbers together?

// Stop throwing everything in main() and repeating

int main(int argc, char *argv[]) {

    ifstream raceResults (argv[1]);
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

    return 0;
}