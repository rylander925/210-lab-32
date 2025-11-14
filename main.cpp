/*
COMSC-210 | Lab 33 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iostream>
#include <deque>
#include <string>
#include <array>
#include "Car.h"

using namespace std;

enum Event {LEAVES, JOINS, SWITCHES};

bool RollProbability(int percent);

Event RollEvents(int leaves, int joins, int switches);

void PrintQueue(deque<Car> queue, string headerMessage = "Queue:");

template<size_t numLanes>
void PrintLanes(array<deque<Car>, numLanes> lanes);

int main() {
    srand(time(0));
    const int MAX_CYCLES = 20;
    const int LANES = 4;
    const int LANE_SIZE = 2;

    const int LEAVE_PROBABILITY = 46;
    const int JOIN_PROBABILITY = 39;
    const int SWITCH_PROBABILITY = 15;

    const int EMPTY_LEAVE_PROBABILITY = 50;
    const int EMPTY_JOIN_PROBABILITY = 50;


    //Create and populate queue
    array<deque<Car>, LANES> lanes;
    for(int i = 0; i < LANES; i++) lanes.at(i) = deque<Car>(LANE_SIZE);

    cout << "Initial queue: " << endl;
    PrintLanes(lanes);

    //Runs simulation based on specified number of cycles
    for(int cycles = 1; cycles <= MAX_CYCLES; cycles++) {
        cout << "Time: " << cycles << endl;

        //Rolls probabilities for each lane and outputs results
        for (int lane = 0; lane < LANES; lane++) {
            cout << "Lane: " << lane + 1 << " ";

            Event event = lanes.at(lane).empty() ? RollEvents(EMPTY_LEAVE_PROBABILITY, EMPTY_JOIN_PROBABILITY, 0) : RollEvents(LEAVE_PROBABILITY, JOIN_PROBABILITY, SWITCH_PROBABILITY);
            switch(event) {
                //Rolls simulation, assuming a car either leaves or joins
                case (LEAVES):
                    //Maintain probability of "leaving" but only actually leave if queue is not empty
                    if (!lanes.at(lane).empty()) {
                        cout << "Car paid: ";
                        lanes.at(lane).front().print();
                        lanes.at(lane).pop_front();
                    } else {
                        cout << "left enmpty." << endl;
                    }
                    break;
                case (JOINS):
                    cout << "Joined lane: ";
                    lanes.at(lane).push_back(Car());
                    lanes.at(lane).back().print();
                    break;
                case (SWITCHES):
                    int switchTo = rand() % (LANES - 1);
                    switchTo += switchTo == lane;

                    cout << "Switched to Lane " << switchTo + 1 << ": ";

                    lanes.at(switchTo).push_back(lanes.at(lane).back());
                    lanes.at(lane).pop_back();
                    lanes.at(switchTo).back().print();
                    break;
            }
        }

        //Displays queue at the end of each cycle
        PrintLanes(lanes);
        cout << endl;
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
 * Given weights of leaving, joining, or switching lanes, rolls an event
 * @param leaves Chance of a car leaving queue
 * @param joins Chance of a car joining queue
 * @param switches Chance of
 */
Event RollEvents(int leaves, int joins, int switches) {
    int num = rand() % (leaves + joins + switches); //rolls number between 0 and the total weight of all probabilities
    return (num < (leaves + joins)) ? (num < leaves ? LEAVES : JOINS) : SWITCHES;  //determines result, from number, treating each weight as a range
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
}

/**
 * Outputs an array of car queues
 * @param lanes Array of car queues to output
 */
template<size_t numLanes>
void PrintLanes(array<deque<Car>, numLanes> lanes) {
    int lane = 0;
    for (deque<Car> queue : lanes) {
        cout << "Lane " << ++lane << " ";
        PrintQueue(queue);
    }
}