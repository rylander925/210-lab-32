/*
COMSC-210 | Lab 32 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iostream>
#include <deque>
#include "Car.h"

using namespace std;

bool RollProbability(int percent);

void PrintQueue(deque<Car> queue);

int main() {
    const int SIZE = 2;
    deque<Car> queue(SIZE);
    for (Car car : queue) { car.print(); cout << endl; }
}