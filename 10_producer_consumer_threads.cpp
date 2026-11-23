#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv;
bool finished = false;
int producedCount = 0;
int consumedCount = 0;

void producer(int totalItems) {
    for (int i = 1; i <= totalItems; i++) {
        {
            lock_guard<mutex> lock(mtx);
            buffer.push(i);
            producedCount++;
            cout << "Produced: " << i << '\n';
        }
        cv.notify_one();
    }

    {
        lock_guard<mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all();
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] {
            return !buffer.empty() || finished;
        });

        if (buffer.empty() && finished)
            break;

        int item = buffer.front();
        buffer.pop();
        consumedCount++;
        cout << "Consumed: " << item << '\n';
    }
}

int main() {
    int totalItems;
    cout << "Enter number of items to produce: ";
    cin >> totalItems;
    if (totalItems < 0) {
        cout << "Number of items cannot be negative.\n";
        return 0;
    }

    cout << "\nProducer-Consumer System Started\n";
    thread producerThread(producer, totalItems);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    cout << "\nTotal items produced: " << producedCount << '\n';
    cout << "Total items consumed: " << consumedCount << '\n';
    cout << "Producer-Consumer System Completed\n";
    return 0;
}
