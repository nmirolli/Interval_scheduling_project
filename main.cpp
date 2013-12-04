/*#############################################################################
#
#  Class:      	Algorithms
#  Project:   	Interval_Scheduling
#  File:        main.cpp
#  Authors:     Nicholas Mirolli, Morgan Willis
#  Emails:      ndm28@zips.uakron.edu, mtw16@zips.uakron.edu
#
#############################################################################*/

#include <cstdlib>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Event.h"
#include "Time.h"

using namespace std;

void swapEvent(Event* array, int a, int b);
void greedySort(Event* greedy, int numEvents);
void optimalSort(Event* optimal, int numEvents);
void removeConflicts(Event* array, int numEvents);
void printOutFile(Event* array, Event* greedy, Event* optimal, int numEvents, string outFilename);

int main(int argc, char** argv) {
    
    //get file
    string filename;
    cout << "Name of file: ";
    getline(cin, filename);
    string outputFilename = filename.substr(0, filename.size()-4);
    ifstream infile(filename.c_str());
    stringstream ss;
    string inputLine = "";
    
    // First line : Filename
    getline(infile,inputLine);
    cout << "filename: " << inputLine << endl;
    // Second line : comment
    getline(infile,inputLine);
    cout << "Comment : " << inputLine << endl;
    
    // Continue with a stringstream
    ss << infile.rdbuf();
    int numEvents;
    // Third line : Events
    ss >> numEvents;
    cout << numEvents << " Events" << endl;
    
    Event* array = new Event[numEvents];
    //Populate array of Events with events
    cout << "\nOriginal File: \n";
    for(int i=0; i<numEvents; i++) {
        string name = "";
        short startTimeH, startTimeM, endTimeH, endTimeM;
        ss >> name;
        ss >> startTimeH >> startTimeM >> endTimeH >> endTimeM;
        array[i].setName(name);
        array[i].setStartTime(startTimeH,startTimeM);
        array[i].setEndTime(endTimeH,endTimeM);
        array[i].print();
    }
    // close file
    infile.close();
    
    //Greedy Algorithm
    //Create array of Events for greedy sorting
    Event* greedy = new Event[numEvents];
    for(int i=0; i<numEvents; i++) {
        greedy[i] = array[i];
    }
    //Sort Events by starting times using insertion sort because datasets will be small
    greedySort(greedy, numEvents);
    //remove start time/end time conflicts
    removeConflicts(greedy, numEvents);
    //print greedy
    int greedyCount = 0;
    cout << "\nGreedy: \n";
    for(int j=0; j<numEvents; j++) {
        if(greedy[j].getName() != "Conflict") {
            greedyCount++;
            greedy[j].print();
        }
    }
    //print number of events
    cout << "Number of Events: " << greedyCount << endl;
            
    //Optimal Algorithm
    //Create array of Events for optimal sorting
    Event* optimal = new Event[numEvents];
    for(int i=0; i<numEvents; i++) {
        optimal[i] = array[i];
    }
    //Sort Events by ending times using insertion sort because datasets will be small
    optimalSort(optimal, numEvents);
    //remove start time/end time conflicts
    removeConflicts(optimal, numEvents);
    //print optimal
    int optimalCount = 0;
    cout << "\nOptimal: \n";
    for(int j=0; j<numEvents; j++) {
        if(optimal[j].getName() != "Conflict") {
            optimalCount++;
            optimal[j].print();
        }
    }
    //print number of events
    cout << "Number of Events: " << optimalCount << endl;
    
    //writes results to a file
    printOutFile(array, greedy, optimal, numEvents, outputFilename);
    
    //Delete greedy array of Events
    delete[] greedy;
    //delete optimal array of Events
    delete[] optimal;
    
    return 0;
}

//swaps the positions of two events within an array
void swapEvent(Event* array, int a, int b) {
    Event temp;
    temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

//sorting Events by start time using insertion sort
void greedySort(Event* greedy, int numEvents) {
    int iMin;
    //advance the position through the entire array
    for(int i=0; i<numEvents; i++) {
        //find the min element in the unsorted, assume the min is the first element
        iMin = i;
        //test against elements after i to find the smallest
        for (int j=(i+1); j<numEvents; j++) {
            //if this element is less, then it is the new minimum
            if (greedy[j].getStartTime().getHour() < greedy[iMin].getStartTime().getHour()) {
                //found new minimum, remember its index
                iMin = j;
            }
            else if(greedy[j].getStartTime().getHour() == greedy[iMin].getStartTime().getHour()) {
                if(greedy[j].getStartTime().getMinute() < greedy[iMin].getStartTime().getMinute()) {
                    iMin = j;
                } 
            }
        }
        //iMin is the index of the minimum element. Swap it with the current position
        if ( iMin != i ) {
            swapEvent(greedy, i, iMin);
        }
    }
}

//sorting Events by end time using insertion sort
void optimalSort(Event* optimal, int numEvents) {
    int iMin;
    //advance the position through the entire array
    for(int i=0; i<numEvents; i++) {
        //find the min element in the unsorted, assume the min is the first element
        iMin = i;
        //test against elements after i to find the smallest
        for (int j=(i+1); j<numEvents; j++) {
            //if this element is less, then it is the new minimum
            if (optimal[j].getEndTime().getHour() < optimal[iMin].getEndTime().getHour()) {
                //found new minimum, remember its index
                iMin = j;
            }
            else if(optimal[j].getEndTime().getHour() == optimal[iMin].getEndTime().getHour()) {
                if(optimal[j].getEndTime().getMinute() < optimal[iMin].getEndTime().getMinute()) {
                    iMin = j;
                } 
            }
        }
        //iMin is the index of the minimum element. Swap it with the current position
        if ( iMin != i ) {
            swapEvent(optimal, i, iMin);
        }
    }
}

//removes all start time/end time conflicts for the array
void removeConflicts(Event* array, int numEvents) {
    for(int i=0; i<numEvents; i++) {
        if(array[i].getName() != "Conflict") {
            for(int j=0; j<(numEvents); j++) {
                if((array[j].getName() != "Conflict") && (array[i] != array[j]) && (j>i)) {
                    if(array[j].getStartTime() < array[i].getEndTime()) {
                        array[j].setName("Conflict");
                    }
                    else if(array[j].getStartTime().getHour() == array[i].getEndTime().getHour()) {
                        if(array[j].getStartTime().getMinute() < array[i].getEndTime().getMinute()) {
                            array[j].setName("Conflict");
                        }
                    }
                }
            }
        }
    }
}

//writes results to a file
void printOutFile(Event* array, Event* greedy, Event* optimal, int numEvents, string outFileName) {
    ofstream outFile;
    outFileName.append("_results.txt");
    outFile.open(outFileName.c_str());
    if (!outFile.is_open()) {
        cout << "Can't open output file"  << outFileName << endl;
        return;
    }
 
    // write the header of the file 
    outFile << outFileName << endl << "Output file for " << outFileName << endl << endl;
    
    //writes the results to a .txt file for viewing
    //loops through array
    outFile << "Original File: \n";
    for(int i=0; i<numEvents; i++) {
        outFile << array[i].getName() << " " 
                << array[i].getStartTime().getHour() 
                << ":" << setw(2) << setfill('0') 
                << array[i].getStartTime().getMinute() << " " 
                << array[i].getEndTime().getHour() 
                << ":" << setw(2) << setfill('0') 
                << array[i].getEndTime().getMinute() << "\n";
    }
    int greedyCount = 0;
    outFile << "\nGreedy: \n";
    for(int j=0; j<numEvents; j++) {
        if(greedy[j].getName() != "Conflict") {
            outFile << greedy[j].getName() << " " 
                << greedy[j].getStartTime().getHour() 
                << ":" << setw(2) << setfill('0') 
                << greedy[j].getStartTime().getMinute() << " " 
                << greedy[j].getEndTime().getHour() 
                << ":" << setw(2) << setfill('0') 
                << greedy[j].getEndTime().getMinute() << "\n";
            greedyCount++;
        }
    }
    outFile << "Number of Events: " << greedyCount << endl;
    int optimalCount = 0;
    outFile << "\nOptimal: \n";
    for(int k=0; k<numEvents; k++) {
        if(optimal[k].getName() != "Conflict") {
            outFile << optimal[k].getName() << " " 
                << optimal[k].getStartTime().getHour() 
                << ":" << setw(2) << setfill('0') 
                << optimal[k].getStartTime().getMinute() << " " 
                << optimal[k].getEndTime().getHour() 
                << ":" << setw(2) << setfill('0') 
                << optimal[k].getEndTime().getMinute() << "\n";
            optimalCount++;
        }
    }
    outFile << "Number of Events: " << optimalCount << endl;
    outFile.close();
}