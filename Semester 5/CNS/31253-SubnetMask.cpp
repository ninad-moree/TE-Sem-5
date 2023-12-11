#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <cmath>

std::string calculateSubnetMask(int prefixLength) {
    std::string mask = "";
    for (int i = 0; i < 32; i++) {
        if (i < prefixLength) {
            mask += "1";
        } else {
            mask += "0";
        }
        if ((i + 1) % 8 == 0 && i < 31) {
            mask += ".";
        }
    }
    return mask;
}

std::string binaryToDecimal(const std::string& binary) {
    std::stringstream ss(binary);
    std::string decimal;
    while (ss.good()) {
        std::bitset<8> bits;
        ss >> bits;
        decimal += std::to_string(bits.to_ulong()) + ".";
    }
    decimal.pop_back();
    return decimal;
}

int main() {
    std::string ipAddress;
    int prefixLength;

    std::cout << "Enter IP address (e.g., 192.168.1.1): ";
    std::cin >> ipAddress;

    std::cout << "Enter subnet prefix length: ";
    std::cin >> prefixLength;

    std::string subnetMask = calculateSubnetMask(prefixLength);

    std::cout << "\nIP Address: " << ipAddress << std::endl;
    std::cout << "Subnet Prefix Length: " << prefixLength << std::endl;
    std::cout << "Subnet Mask: " << subnetMask << std::endl;
    std::cout << "Subnet Mask: " << binaryToDecimal(subnetMask) << std::endl;

    return 0;
}
