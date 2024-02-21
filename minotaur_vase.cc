/*
COP4520-24Spring 0V01: Concept of Parallel and Distributed Processing
Programming Assignment 2 Problem 2
Instructor: Juan Parra
Due date: Jan 26 at 12am - Feb 23 at 11:59pm
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

// Global variables for synchronization
condition_variable cv;
queue<int> guestQueue;
bool showroomAvailable = true;
int numGuests;

// Mutex for thread synchronization
mutex mtx;

void viewVase(int guestNumber) {
    unique_lock<mutex> lock(mtx);

    // Guest joins the queue
    guestQueue.push(guestNumber);
    cout << "Guest " << guestNumber << " is waiting in line." << endl;

    // Wait until it's this guest's turn and the showroom is available
    cv.wait(lock, [guestNumber](){ return guestQueue.front() == guestNumber && showroomAvailable; });

    // Viewing the vase
    showroomAvailable = false;
    cout << "Guest " << guestNumber << " is viewing the vase." << endl;
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate viewing the vase

    // Exit the showroom
    showroomAvailable = true;
    cout << "Guest " << guestNumber << " has finished viewing the vase." << endl;
    guestQueue.pop(); // Remove the guest from the queue

    // Notify the next guest
    cv.notify_all();
}

void startSimulation(int numGuests) {
    vector<thread> guestThreads;

    for (int i = 1; i <= numGuests; ++i) {
        guestThreads.emplace_back(viewVase, i);
    }

    for (auto& t : guestThreads) {
        t.join();
    }
}

int main() {
    cout << "Enter the number of guests: ";
    cin >> numGuests;

    startSimulation(numGuests);

    return 0;
}
