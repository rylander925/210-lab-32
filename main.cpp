/*
COMSC-210 | Lab 32 | Rylan Der
IDE Used: Visual Studio Code 
*/

#include <iostream>
#include <deque>
#include <string>
#include "Car.h"

using namespace std;

bool RollProbability(int percent);

void PrintQueue(deque<Car> queue, string headerMessage = "Queue:");

int main() {
    srand(time(0));
    
    const int SIZE = 2;
    const int LEAVE_PROBABILITY = 55;

    int cycles = 0;

    //Create and populate queue
    deque<Car> queue(SIZE); //automatically calls car constructor when initializing queue
    PrintQueue(queue, "Initial queue:");

    //Runs simulation until line is empty
    while(!queue.empty()) {
        cout << "Time: " << ++cycles << " Operation: ";

        //Rolls simulation, assuming a car either leaves or joins
        if (RollProbability(LEAVE_PROBABILITY)) {
            cout << "Car paid: ";
            queue.front().print();
            queue.pop_front();
        } else {
            cout << "Joined lane: ";
            queue.push_back(Car());
            queue.back().print();
        }

        //Displays queue at the end of each cycle
        PrintQueue(queue);
    }
}

/**
 * Rolls a given probability and returns true if roll succeeds
 * @param percent Chance of success as an integer percentage (e.g. 55)
 * @return True of roll succeeds, false if roll fails
 */
bool RollProbability(int percent) {
    return (rand() % 100) < percent; //rolls number from 0-99 inclusive, succeds if less than the given integer
}

/**
 * Prints a header message followed by all cars in the dequeue
 * @param queue Dequeue of cars to print
 * @param headerMessage Message to print before printing all the cars
 */
void PrintQueue(deque<Car> queue, string headerMessage) {
    cout << headerMessage << endl; //output header messaage

    if (queue.empty()) {           //check if empty
        cout << "\tEmpty" << endl;
        return;
    }

    for (Car car : queue) {        //otherwise output all cars
        cout << "\t";
        car.print();
    }
    cout << endl;
}
