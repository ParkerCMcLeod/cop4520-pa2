#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <atomic>

using namespace std;

// Global atomic variables for thread synchronization
atomic<int> numGuestsAtom(0);
atomic<int> currentGuestAtom(0);
atomic<int> guestOneReplacementsAtom(0);
atomic<bool> cupcakePresentAtom(true);
atomic<bool> guestOneAlreadyEatenAtom(false);
atomic<int> completedTurnsAtom(0);

// Mutex for thread synchronization
mutex mtx;

// Seed for random number generator
random_device rd;

void enterLabyrinth(int guestNumber) {
    cout << "Guest " << guestNumber << " enters the labyrinth." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
}

void exitLabyrinth(int guestNumber) {
    cout << "Guest " << guestNumber << " exits the labyrinth." << endl;
}

void guestFunction(int guestNumber) {
    while (true) {
        unique_lock<mutex> lock(mtx); 


        lock.unlock();
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

    cout << "Guest one replaced the cupcake " << guestOneReplacementsAtom << " times." << endl;
    cout << "We can guarantee all guests have visited the labyrinth! It took " << completedTurnsAtom << " turns to make this guarantee." << endl;
}

int main() {
    cout << "Enter the number of guests: ";
    int numGuests;
    cin >> numGuests;

    startSimulation(numGuests);

    return 0;
}