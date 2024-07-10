// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <bitset>

// Define a structure to hold the result of the full adder
struct FullAdderResult {
    bool sum;
    bool carryOut;
};

// Single bit full adder function
FullAdderResult fullAdder(bool a, bool b, bool carryIn) {
    bool sum = a ^ b ^ carryIn; // XOR for sum
    bool carryOut = (a & b) | (b & carryIn) | (a & carryIn); // OR for carry
    return { sum, carryOut };
}

// 8-bit full adder using the single bit full adder
void eightBitFullAdder(std::bitset<8> a, std::bitset<8> b, std::ofstream& outFile) {
    std::bitset<8> sum;
    bool carry = 0;
    FullAdderResult result;

    // Process each bit
    for (int i = 0; i < 8; ++i) {
        result = fullAdder(a[i], b[i], carry);
        sum[i] = result.sum;
        carry = result.carryOut;
    }

    // Write the results to CSV file
    outFile << a << "," << b << "," << sum << "," << carry << "\n";
}

int main() {
    std::ofstream outFile("truth_table.csv");

    // Write CSV header
    outFile << "A,B,Sum,Carry Out\n";

    // Generate the truth table for all combinations of inputs
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            eightBitFullAdder(std::bitset<8>(i), std::bitset<8>(j), outFile);
        }
    }

    outFile.close(); // Close the file after writing all data
    return 0;
}

