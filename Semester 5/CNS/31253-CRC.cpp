#include <iostream>
#include <string>

using namespace std;

string crc_remainder(const string& input, const string& polynomial) {
    int input_length = input.length();
    int polynomial_length = polynomial.length();
    
    string padded_input = input + string(polynomial_length - 1, '0');
    string remainder = padded_input;

    for (int i = 0; i < input_length; ++i) {
        if (remainder[i] == '1') {
            for (int j = 0; j < polynomial_length; ++j) {
                remainder[i + j] = (remainder[i + j] == polynomial[j]) ? '0' : '1';
            }
        }
    }

    return remainder.substr(input_length);
}

int main() {
    string data;
    string polynomial = "1101"; 

    cout << "Enter the data bits: ";
    cin >> data;

    string crc = crc_remainder(data, polynomial);

    cout << "CRC: " << crc << endl;

    string transmitted_data = data + crc;

    string received_data;
    cout << "Enter the received data bits: ";
    cin >> received_data;

    string received_crc = crc_remainder(received_data, polynomial);
    cout << "Received CRC: " << received_crc << endl;

    if (received_crc == "000") {
        cout << "No error detected. Data is correct." << endl;
    } else {
        cout << "Error detected in received data!" << endl;
    }

    return 0;
}
