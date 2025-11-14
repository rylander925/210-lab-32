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
    const int SIZE = 2;
    deque<Car> queue(SIZE);
    for (Car car : queue) { car.print(); cout << endl; }
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
    for (Car car : queue) {        //output all cars
        cout << "\t";
        car.print();
        cout << endl;
    }
}