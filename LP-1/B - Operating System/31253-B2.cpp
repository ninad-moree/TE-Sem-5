#include <iostream>
#include <algorithm>
using namespace std;

class Job
{
    string name;
    int execution_time;
    int waiting_time;
    int time_left;

public:
    Job()
    {
        name = "";
        execution_time = 0;
        waiting_time = 0;
        time_left = 0;
    }
    void input()
    {
        cout << "Enter name:";
        cin >> name;
        cout << "Enter execution time:";
        cin >> execution_time;
        time_left = execution_time;
    }

    void output()
    {
        cout << "Job:" << name << endl;
        cout << "Execution Time :" << execution_time << endl;
        cout << "Waiting Time :" << waiting_time << endl;
    }

    friend class JobScheduler;
};

class JobScheduler
{
    Job *arr;
    int noOfProcesses;

public:
    JobScheduler(int n)
    {
        noOfProcesses = n;
        arr = new Job[noOfProcesses];

        for (int i = 0; i < noOfProcesses; i++)
        {
            arr[i].input();
            cout << endl;
        }
    }

    void FCFS()
    {
        int waiting = 0;
        for (int i = 1; i < noOfProcesses; i++)
        {
            waiting = waiting + arr[i - 1].execution_time;
            arr[i].waiting_time = waiting;
        }
        for (int i = 0; i < noOfProcesses; i++)
        {
            arr[i].output();
            cout << endl;
        }
    }

    void SJF()
    {
        Job *temp = new Job[noOfProcesses];
        for (int i = 0; i < noOfProcesses; i++)
        {
            temp[i].name = arr[i].name;
            temp[i].execution_time = arr[i].execution_time;
            temp[i].waiting_time = 0;
        }

        int waiting2 = 0;

        for (int i = 0; i < noOfProcesses; i++)
        {
            for (int j = i + 1; j < noOfProcesses; j++)
            {
                if (temp[i].execution_time > temp[j].execution_time)
                {
                    Job job;
                    job = temp[i];
                    temp[i] = temp[j];
                    temp[j] = job;
                }
            }
        }
        for (int i = 1; i < noOfProcesses; i++)
        {
            waiting2 = waiting2 + temp[i - 1].execution_time;
            temp[i].waiting_time = waiting2;
        }
        for (int i = 0; i < noOfProcesses; i++)
        {
            temp[i].output();
            cout << endl;
        }
    }

    void roundRobin()
    {
        int timeQuantum;
        cout << "Enter time quantum: ";
        cin >> timeQuantum;

        for (int i = 0; i < noOfProcesses; i++)
        {
            if (arr[i].execution_time > timeQuantum)
            {
                arr[i].output();
                cout << "Will not be executed lagging by " << arr[i].execution_time - timeQuantum << endl;
            }
            else
            {
                arr[i].output();
                cout << "Will be executed.\n";
            }
            cout << endl;
        }
    }
};

int main()
{
    int n1;
    cout << "Enter no of processes:";
    cin >> n1;
    JobScheduler js(n1);

    int choice;

    while (choice != 4)
    {
        cout << "What do you want to do" << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF" << endl;
        cout << "3. Round Robin" << endl;
        cout << "4. Exit" << endl;
        cout << endl;
        cout << "Enter choice:";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            js.FCFS();
            cout << endl;
            break;

        case 2:
            js.SJF();
            cout << endl;
            break;

        case 3:
            js.roundRobin();
            cout << endl;
            break;

        case 4:
            cout << "Exiting program...";
            break;

        default:
            cout << "Wrong input!\n";
            break;
        }
    }

    return 0;
}