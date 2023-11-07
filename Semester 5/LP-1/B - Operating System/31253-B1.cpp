#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
using namespace std;

atomic<bool> mutex_flag(false);

void critical_section(int thread_id)
{
    while (mutex_flag.exchange(true))
    {
        this_thread::yield();
    }

    cout << "Thread " << thread_id << " is in the critical section." << std::endl;
    this_thread::sleep_for(std::chrono::milliseconds(500));

    mutex_flag.store(false);
}

class Semaphore
{
public:
    Semaphore(int count) : count_(count) {}

    void Wait()
    {
        unique_lock<mutex> lock(mutex_);
        while (count_ == 0)
        {
            condition_.wait(lock);
        }
        count_--;
    }

    void Signal()
    {
        unique_lock<mutex> lock(mutex_);
        count_++;
        condition_.notify_one();
    }

private:
    mutex mutex_;
    condition_variable condition_;
    int count_;
};

Semaphore semaphore(1);

void Worker(int id)
{
    cout << "Thread " << id << " is waiting." << endl;
    semaphore.Wait();
    cout << "Thread " << id << " has acquired a permit." << endl;

    this_thread::sleep_for(chrono::seconds(1));

    semaphore.Signal();
    cout << "Thread " << id << " has released a permit." << endl;
}

int main()
{

    while (true)
    {
        cout << "1.Mutex\t2.Semaphore\t3.Exit" << endl;
        int choice;
        cout << "Please enter the choice " << endl;
        cin >> choice;
        if (choice == 1)
        {
            const int num_threads = 5;
            thread threads[num_threads];

            for (int i = 0; i < num_threads; ++i)
            {
                threads[i] = thread(critical_section, i);
            }

            for (int i = 0; i < num_threads; ++i)
            {
                threads[i].join();
            }
        }
        else if (choice == 2)
        {
            const int num_threads = 3;
            thread threads[num_threads];

            for (int i = 0; i < num_threads; ++i)
            {
                threads[i] = thread(Worker, i);
            }

            for (int i = 0; i < num_threads; ++i)
            {
                threads[i].join();
            }
        }
        else if (choice == 3)
        {
            cout << "Exiting the code" << endl;
            break;
        }
        else
        {
            cout << "Enter proper choice" << endl;
            continue;
        }
    }
    return 0;
}