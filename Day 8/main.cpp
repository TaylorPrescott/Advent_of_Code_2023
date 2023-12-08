#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int getNumberOfLocations(char *file)
{
    ifstream directionsFile (file);
    int lineCount = 0;
    if ( directionsFile.is_open() ) {
        string str;
        while ( directionsFile.good() ) {
            getline(directionsFile, str);
            lineCount++;
        }
    }
    return lineCount - 2;
}


string organizeDirections(char *file, string directions, string locations[], string locationValues[])
{
    
    ifstream directionsFile (file);
    int lineCount = 0;

    if ( directionsFile.is_open() ) {
        string line;
        while ( directionsFile.good() ) {

            getline(directionsFile, line);

            if ( lineCount == 0 ) {
                directions = line;
            }

            if ( lineCount > 1 ) {
                locations[lineCount - 2] = line.substr(0,3);
                locationValues[lineCount - 2] = line.substr(7,3);
                locationValues[lineCount - 2] += line.substr(12,3);
            }
            lineCount++; 
        }
    }

    return directions;
}

string getNextLocation(int currentLocationIndex, char lrInstruction, string locationValues[]) 
{
    //cout << lrInstruction << endl;
    if ( lrInstruction == 'L' ) {
        return locationValues[currentLocationIndex].substr(0,3);
    }

    if ( lrInstruction == 'R' ) {
        return locationValues[currentLocationIndex].substr(3,3);
    }
    return "foobar";
}

int getCurrentLocationIndex(string currentLocation, string locations[], int size)
{
    for (int i = 0; i < size; i++) {
        if ( locations[i] == currentLocation ) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) 
{
    int stepsToEscape = 0;
    int arrsSize = getNumberOfLocations(argv[1]);

    string currentLocation = "AAA";

    string directions;
    string locations[arrsSize];
    string locationValues[arrsSize];

    // Fill three vars above
    directions = organizeDirections(argv[1], directions, locations, locationValues);


    for (int i = 0; i < directions.length(); i++) {
        //cout << i << endl;
        int locationIndex = getCurrentLocationIndex(currentLocation, locations, arrsSize);
        
        currentLocation = getNextLocation(locationIndex, directions[i], locationValues);

        //cout << currentLocation << endl;
        stepsToEscape++;
        if ( currentLocation == "ZZZ" ) {
            cout << currentLocation << endl;
            break;
        }
        if ( i == 276 ) {
            i = -1;
        }
    }
    cout << directions.length() << endl;
    //1st attempt too low: 277
    //2nd attempt too high 19667


    cout << "Steps to escape the haunted wasteland = " << stepsToEscape << endl;
    return 0;
}