#include <iostream>
#include <string>
using namespace std;

bool recievers_end(string& data)
{
    int n = stoi(data);
    int c = 0;
    while(n != 0)
    {
        int r = n%10;
        if(r == 1)
            c++;
        n = n/10;
    }
    
    if(c%2 == 0)    return true;
    return false;
}

int main() {
    //n = 1100001
    int n, count = 0;string s;
    cin >> n;
    
    int num = n;
    while(num != 0)
    {
        int r = num%10;
        if(r == 1)
        {
            count++;
        }
        num = num/10;
    }
    s = to_string(n);

    
    if(count%2 == 0)
    {
        //even
        cout << n << " has even parity\n";
        s.push_back('0');
    }else
    {
        //odd
        cout << n << " has odd parity\n";
        s.push_back('1');
    }
    cout << s << endl;
    
    if((recievers_end(s)) == true)
        cout << "No error detected\n";
    else
        cout << "Error detected\n";
    return 0;
}