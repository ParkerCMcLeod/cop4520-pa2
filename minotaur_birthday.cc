/*
COP4520-24Spring 0V01: Concept of Parallel and Distributed Processing
Programming Assignment 2 Problem 1
Instructor: Juan Parra
Due date: Jan 26 at 12am - Feb 23 at 11:59pm
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <atomic>
#include <condition_variable>

using namespace std;

// Global variables for thread synchronization
atomic<int> numGuestsAtom(0);
atomic<int> currentGuestAtom(0);
atomic<int> countingGuestReplacementsAtom(0);
atomic<bool> cupcakePresentAtom(true);
atomic<bool> countingGuestAlreadyEatenAtom(false);
atomic<int> completedTurnsAtom(0);
atomic<bool> simulationDone(false);
condition_variable cv;

// Mutex for thread synchronization
mutex mtx;

// Seed for random number generator
random_device rd;

void enterLabyrinth(int guestNumber) {
    cout << "Guest " << guestNumber << " enters the labyrinth." << endl;
    this_thread::sleep_for(chrono::milliseconds(100)); // Guest is navigating the maze
}

void exitLabyrinth(int guestNumber) {
    cout << "Guest " << guestNumber << " exits the labyrinth." << endl;
}

void guestFunction(int guestNumber) {
    while (true) {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [guestNumber]() { 
            return simulationDone.load() || guestNumber == (currentGuestAtom.load() % numGuestsAtom) + 1; 
        });

        if (simulationDone) {
            break; // Exit if simulation is done
        }

        if (countingGuestReplacementsAtom >= numGuestsAtom) {
            simulationDone = true; // Set the simulation as done
            cv.notify_all(); // Ensure all threads can exit
            break; // All guests have completed their turns
        }

        enterLabyrinth(guestNumber);

        if (cupcakePresentAtom) {
            if (guestNumber == 1) {
                if (!countingGuestAlreadyEatenAtom) {
                    cout << "Guest " << guestNumber << " eats the cupcake." << endl;
                    countingGuestAlreadyEatenAtom = true;
                    cupcakePresentAtom = false;
                }
            } else {
                cout << "Guest " << guestNumber << " eats the cupcake." << endl;
                cupcakePresentAtom = false;
            }
        } else {
            if (guestNumber == 1 && countingGuestAlreadyEatenAtom) {
                cout << "Guest " << guestNumber << " replaces the cupcake." << endl;
                countingGuestReplacementsAtom++;
                cupcakePresentAtom = true;
            }
        }

        completedTurnsAtom++;

        uniform_int_distribution<int> dist(1, numGuestsAtom);
        currentGuestAtom = dist(rd); // Select next guest

        cv.notify_all(); // Notify minotuar that the current guest has exited the maze

        exitLabyrinth(guestNumber);
    }
}

void startSimulation(int numGuests) {
    numGuestsAtom = numGuests;
    vector<thread> guestThreads;

    for (int i = 0; i < numGuests; ++i) {
        guestThreads.emplace_back(guestFunction, i + 1);
    }

    for (auto& t : guestThreads) {
        t.join();
    }

    cout << "Guest one replaced the cupcake " << countingGuestReplacementsAtom << " times." << endl; // Guest who counts answers
    cout << "We can guarantee all guests have visited the labyrinth! It took " << completedTurnsAtom << " turns to make this guarantee." << endl; // Guest who counts answers
}

int main() {
    cout << "Enter the number of guests: ";
    int numGuests;
    cin >> numGuests;

    startSimulation(numGuests);

    return 0;
}