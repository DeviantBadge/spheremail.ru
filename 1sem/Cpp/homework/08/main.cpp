#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

constexpr size_t ping_amount = 500000;
atomic <size_t> pinged;
mutex m;

void ping() {
    for (; pinged < ping_amount;) {
        if (pinged % 2 == 0) {
            cout << "ping" << endl;
            pinged++;
        }
    }
}

void pong() {
    for (; pinged < ping_amount;) {
        if (pinged % 2 == 1) {
            cout << "pong" << endl;
            pinged++;
        }
    }
}

int main() {
    pinged = 0;
    thread t1(ping);
    thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}