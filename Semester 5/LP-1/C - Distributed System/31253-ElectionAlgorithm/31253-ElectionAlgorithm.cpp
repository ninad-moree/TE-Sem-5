#include <iostream>
#include <cstdlib>

#define MAX 20

int pStatus[MAX], n, cordinator;
using namespace std;

class ElectionAlgorithm
{
public:
    void bully()
    {
        int schoice, crash, activate, i, gid, flag, subcoordinator;
        do
        {
            cout << "-------------------------------------------------" << endl;
            cout << "1. Crash a process" << endl;
            cout << "2. Activate a process" << endl;
            cout << "3. Display" << endl;
            cout << "4. Exit bully algorithm" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "Enter your choice: ";
            cin >> schoice;
            cout << endl;

            switch (schoice)
            {
            case 1:
                cout << "Enter process to crash: ";
                cin >> crash;
                if (pStatus[crash])
                    pStatus[crash] = 0;
                else
                    cout << "Process " << crash << " is already dead!" << endl;

                do
                {
                    cout << "Enter election generator id: ";
                    cin >> gid;
                    if (gid == cordinator || pStatus[gid] == 0)
                        cout << "Please, enter a valid generator id.." << endl;
                } while (gid == cordinator || pStatus[gid] == 0);

                flag = 0;
                if (crash == cordinator)
                {
                    for (i = gid + 1; i <= n; i++)
                    {
                        cout << "Message  is sent from " << gid << " to " << i << endl;
                        if (pStatus[i])
                        { 
                            subcoordinator = i;
                            cout << "Response is sent from " << i << " to " << gid << endl;
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                        cordinator = subcoordinator;
                    else
                        cordinator = gid;
                }
                break;

            case 2:
                cout << "Enter Process ID to be activated: ";
                cin >> activate;
                if (!pStatus[activate])
                {
                    pStatus[activate] = 1;
                }
                else
                {
                    cout << "Process " << activate << " is already alive!" << endl;
                    break;
                }
                if (activate == n)
                {
                    cordinator = n;
                    break;
                }
                flag = 0;
                for (i = activate + 1; i <= n; i++)
                {
                    cout << "Message is sent from " << activate << " to " << i << endl;
                    if (pStatus[i])
                    {
                        subcoordinator = i;
                        cout << "Response is sent from " << i << " to " << activate << endl;
                        flag = 1;
                    }
                }
                if (flag == 1)
                    cordinator = subcoordinator;
                else
                    cordinator = activate;
                break;

            case 3:
                display();
                break;

            case 4:
                break;
            }
        } while (schoice != 4);
    };

    void ring()
    {
        int tchoice, crash, activate, gid, subcoordinator, i;
        do
        {
            cout << "-------------------------------------------------" << endl;
            cout << "MENU" << endl;
            cout << "1. Crash a process" << endl;
            cout << "2. Activate a process" << endl;
            cout << "3. Display" << endl;
            cout << "4. Exit ring algorithm" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "Enter your choice: ";
            cin >> tchoice;
            cout << endl;
            switch (tchoice)
            {
            case 1:
                cout << "Enter Process ID to crash : ";
                cin >> crash;

                if (pStatus[crash])
                    pStatus[crash] = 0;
                else
                    cout << "Process " << crash << " is already dead!" << endl;
                do
                {
                    cout << "Enter election generator id: ";
                    cin >> gid;
                    if (gid == cordinator)
                        cout << "Please, enter a valid generator id.." << endl;
                } while (gid == cordinator);

                if (crash == cordinator)
                {
                    subcoordinator = 1;
                    for (i = 0; i < (n + 1); i++)
                    {
                        int pid = (i + gid) % (n + 1);
                        if (pid != 0)
                        {
                            if (pStatus[pid] && subcoordinator < pid)
                            {
                                subcoordinator = pid;
                            }
                            cout << "Election message sent from " << pid << ": #Msg" << subcoordinator << endl;
                        }
                    }

                    cordinator = subcoordinator;
                }
                break;

            case 2:
                cout << "Enter Process ID to be activated: ";
                cin >> activate;
                if (!pStatus[activate])
                    pStatus[activate] = 1;
                else
                {
                    cout << "Process " << activate << " is already alive!" << endl;
                    break;
                }

                subcoordinator = activate;
                for (i = 0; i < n + 1; i++)
                {
                    int pid = (i + activate) % (n + 1);

                    if (pid != 0)
                    {
                        if (pStatus[pid] && subcoordinator < pid)
                        {
                            subcoordinator = pid;
                        }
                        cout << "Election message passed from " << pid << ": #Msg" << subcoordinator << endl;
                    }
                }

                cordinator = subcoordinator;
                break;

            case 3:
                display();
                break;

            default:
                break;
            }
        } while (tchoice != 4);
    };

    void display()
    {
        int i;
        cout << endl;
        cout << "-------------------------------------------------\n";
        cout << "Processes:  ";
        for (i = 1; i <= n; i++)
            cout << i << "\t";
        cout << endl << "Alive:      ";
        for (i = 1; i <= n; i++)
            cout << pStatus[i] << "\t";
        cout << "\n-------------------------------------------------\n";
        cout << "COORDINATOR IS " << cordinator << endl;
        cout << endl;
    };
};

int main()
{
    ElectionAlgorithm e;
    int i, j, fchoice;

    cout << "Enter number of processes: ";
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        cout << "Enter Process " << i << " is alive or not(0/1): ";
        cin >> pStatus[i];
        if (pStatus[i])
            cordinator = i;
    }

    e.display();
    cout << endl;
    do
    {
        cout << "-------------------------------------------------" << endl;
        cout << " ### MENU ###" << endl;
        cout << "1. Bully Algo" << endl;
        cout << "2. Ring Algo" << endl;
        cout << "3. Dsiplay" << endl;
        cout << "4. Exit the code" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> fchoice;
        cout << endl;

        switch (fchoice)
        {
        case 1:
            e.bully();
            break;
        case 2:
            e.ring();
            break;
        case 3:
            e.display();
            break;
        case 4:
            exit(1);
            break;
        }
    } while (fchoice != 4);
    return 0;
}