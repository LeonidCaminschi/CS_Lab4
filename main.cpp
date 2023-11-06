#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;

int main() {
    int permutatedKey2[8][6] = {
            {14, 17, 11, 24, 1,  5},
            {3,  28, 15, 6,  21, 10},
            {23, 19, 12, 4,  26, 8},
            {16, 7,  27, 20, 13, 2},
            {41, 52, 31, 37, 47, 55},
            {30, 40, 51, 45, 33, 48},
            {44, 49, 39, 56, 34, 53},
            {46, 42, 50, 36, 29, 32}
    };

    int bitsToIgnore[] = {9, 18, 22, 25, 35, 38, 43, 54};

    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<uint64_t> distribution(0, pow(2,57)-1);
    uint64_t key = distribution(generator);

    cout << hex << key << endl;

    for(int i=0; i<16; i++) {

        uint64_t first_28_bits = (key >> 28);
        uint64_t last_28_bits = ((key << 36) >> 36);

        cout << hex << first_28_bits << " " << last_28_bits << endl;

        first_28_bits = (first_28_bits << 1);
        last_28_bits = (last_28_bits << 1);

        if (first_28_bits & 0x20000000) {
            first_28_bits = first_28_bits & 0x1FFFFFFF;
            first_28_bits = first_28_bits + 1;
        }

        if (last_28_bits & 0x20000000) {
            last_28_bits = last_28_bits & 0x1FFFFFFF;
            last_28_bits = last_28_bits + 1;
        }

        uint64_t intermediary = (first_28_bits << 28) + last_28_bits;
        cout << hex << intermediary << endl;
        int reorderedInt = 0;

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 6; col++) {
                int bitIndex = permutatedKey2[row][col] - 1;
                uint64_t bitValue = (intermediary >> (56 - bitIndex)) & 0x1;
                reorderedInt = (reorderedInt << 1) | bitValue;
            }
        }

        cout << hex << reorderedInt << endl;
        key = intermediary;
    }
}