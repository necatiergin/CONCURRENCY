#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <queue>
#include <mutex>

const int queue_capacity    = 5;
const int total_items       = 15;

// Semaphores to manage flow control
std::counting_semaphore<queue_capacity> slots_available(queue_capacity);
std::counting_semaphore<queue_capacity> items_available(0);

// Mutex to protect the shared queue container
std::mutex queue_mutex;
std::queue<int> buffer;

void producer()
{
    for (int i = 0; i < total_items; ++i) {
        slots_available.acquire();

        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            buffer.push(i);
            std::cout << "[Producer] Produced: " << i << '\n';
        }

        items_available.release();
    }
}

void consumer() 
{
    for (int i = 0; i < total_items; ++i) {
        
        items_available.acquire();

        int data;
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            data = buffer.front();
            buffer.pop();
            std::cout << "[Consumer] Consumed: " << data << '\n';
        }

        // Signal that a slot has become free
        slots_available.release();
    }
}

int main() 
{
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();
}
