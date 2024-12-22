#include <iostream>
#include <vector>
#include <cstdint> // For fixed-width integer types like uint32_t

using namespace std;

// Function to simulate the secret number evolution
uint32_t evolveSecretNumber(uint32_t secretNumber) {
    // Step 1: Multiply by 64, mix, and prune
    secretNumber ^= (secretNumber * 64);
    secretNumber %= 16777216;

    // Step 2: Divide by 32, mix, and prune
    secretNumber ^= (secretNumber / 32);
    secretNumber %= 16777216;

    // Step 3: Multiply by 2048, mix, and prune
    secretNumber ^= (secretNumber * 2048);
    secretNumber %= 16777216;
    cout<<secretNumber%10<<endl;
    return secretNumber;
}

int main() {
    // Input: initial secret numbers for each buyer
    int n=1;
    vector<uint32_t> initialSecrets(n);
    for(int i=0;i<n;i++) cin>>initialSecrets[i];

    // Number of new secret numbers to generate per buyer
    const int iterations = 2000;

    // Variable to store the sum of the 2000th secret numbers
    uint64_t sumOf2000thSecrets = 0;

    // Process each buyer's secret number
    for (uint32_t secretNumber : initialSecrets) {
        for (int i = 0; i < iterations; ++i) {
            secretNumber = evolveSecretNumber(secretNumber);
        }
        sumOf2000thSecrets += secretNumber;
    }

    // Output the result
    cout << "Sum of 2000th secret numbers: " << sumOf2000thSecrets << endl;

    return 0;
}
