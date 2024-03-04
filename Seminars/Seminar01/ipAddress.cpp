#include <iostream>

union IPAddress {
    int32_t address;
    unsigned char octets[4];
};


int main() {
	IPAddress ipAddress;
	ipAddress.address = 16777343;

	std::cout << (int)ipAddress.octets[0] << "."
		<< (int)ipAddress.octets[1] << "."
		<< (int)ipAddress.octets[2] << "."
		<< (int)ipAddress.octets[3];
}