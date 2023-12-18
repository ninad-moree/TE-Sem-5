#include <iostream>
#include <vector>
using namespace std;

class PageReplacementAlgorithm
{
private:
    int n;          // Length of page reference sequence
    int nf;         // Number of frames
    vector<int> in; // Page reference sequence
    vector<int> p;  // Frames
    int pgfaultcnt = 0;

    void initialize()
    {
        pgfaultcnt = 0;
        p.assign(nf, 9999);
    }

    bool isHit(int data)
    {
        for (int j = 0; j < nf; j++)
        {
            if (p[j] == data)
                return true;
        }
        return false;
    }

    void dispPages()
    {
        for (int k = 0; k < nf; k++)
        {
            if (p[k] != 9999)
                cout << " " << p[k];
        }
    }

    void dispPgFaultCnt()
    {
        cout << "Total no of page faults: " << pgfaultcnt << endl;
    }

public:
    void getData()
    {
        cout << "Enter length of page reference sequence: ";
        cin >> n;
        cout << "Enter the page reference sequence: ";
        in.resize(n);
        for (int i = 0; i < n; i++)
            cin >> in[i];
        cout << "Enter no of frames: ";
        cin >> nf;
        p.resize(nf);
        cout << endl;
    }

    void fifo()
    {
        initialize();
        for (int i = 0; i < n; i++)
        {
            cout << "For " << in[i] << " :";
            if (!isHit(in[i]))
            {
                for (int k = 0; k < nf - 1; k++)
                    p[k] = p[k + 1];
                p[nf - 1] = in[i];
                pgfaultcnt++;
                dispPages();
            }
            else
                cout << "No page fault";
            cout << endl;
        }
        dispPgFaultCnt();
        cout << endl;
    }

    void optimal()
    {
        initialize();
        vector<int> near(nf, 0);
        for (int i = 0; i < n; i++)
        {
            cout << "For " << in[i] << " :";
            if (!isHit(in[i]))
            {
                for (int j = 0; j < nf; j++)
                {
                    int pg = p[j];
                    bool found = false;
                    for (int k = i; k < n; k++)
                    {
                        if (pg == in[k])
                        {
                            near[j] = k;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        near[j] = 9999;
                }
                int max = -9999;
                int repindex;
                for (int j = 0; j < nf; j++)
                {
                    if (near[j] > max)
                    {
                        max = near[j];
                        repindex = j;
                    }
                }
                p[repindex] = in[i];
                pgfaultcnt++;
                dispPages();
            }
            else
                cout << "No page fault";
            cout << endl;
        }
        dispPgFaultCnt();
        cout << endl;
    }

    void lru()
    {
        initialize();
        vector<int> least(nf, 0);
        for (int i = 0; i < n; i++)
        {
            cout << "For " << in[i] << " :";
            if (!isHit(in[i]))
            {
                for (int j = 0; j < nf; j++)
                {
                    int pg = p[j];
                    bool found = false;
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if (pg == in[k])
                        {
                            least[j] = k;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        least[j] = -9999;
                }
                int min = 9999;
                int repindex;
                for (int j = 0; j < nf; j++)
                {
                    if (least[j] < min)
                    {
                        min = least[j];
                        repindex = j;
                    }
                }
                p[repindex] = in[i];
                pgfaultcnt++;
                dispPages();
            }
            else
                cout << "No page fault!";
            cout << endl;
        }
        dispPgFaultCnt();
        cout << endl;
    }
};

int main()
{
    PageReplacementAlgorithm prAlgo;
    int choice;
    while (true)
    {
        cout << " ***** Page Replacement Algorithms ***** " << endl;
        cout << "1. Enter data" << endl;
        cout << "2. FIFO" << endl;
        cout << "3. Optimal" << endl;
        cout << "4. LRU" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            prAlgo.getData();
            break;
        case 2:
            cout << "#1# FIFO Algorithm" << endl;
            prAlgo.fifo();
            break;
        case 3:
            cout << "#2# Optimal Algorithm" << endl;
            prAlgo.optimal();
            break;
        case 4:
            cout << "#3# LRU Algorithm" << endl;
            prAlgo.lru();
            break;
        default:
            return 0;
            break;
        }
    }
}
