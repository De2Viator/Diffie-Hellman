#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

long long power_mod(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base %= modulus;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }

        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

unsigned long long generate_public_key(unsigned long long P, unsigned long long g, unsigned long long private_key) {
    return power_mod(g, private_key, P);
}

unsigned long long generate_shared_secret(unsigned long long P, unsigned long long public_key,
                                          unsigned long long private_key) {
    return power_mod(public_key, private_key, P);
}

unsigned long long generate_random_number() {
    unsigned long long random_number = (rand() + 9) % 1000000;
    return random_number;
}

int main() {
    srand(time(NULL));
    unsigned long long P = generate_random_number();
    unsigned long long g = generate_random_number();
    unsigned long long alice_private = generate_random_number();
    unsigned long long alice_public = generate_public_key(P, g, alice_private);
    unsigned long long bob_private = generate_random_number();
    unsigned long long bob_public = generate_public_key(P, g, bob_private);
    unsigned long long alice_secret = generate_shared_secret(P, bob_public, alice_private);
    unsigned long long bob_secret = generate_shared_secret(P, alice_public, bob_private);

    std::cout << "Shared public (p): " << P << std::endl;
    std::cout << "generator (g): " << g << std::endl;
    std::cout << "\nAlice's private (a): " << alice_private << std::endl;
    std::cout << "Bob's private (b): " << bob_private << std::endl;
    std::cout << "\nAlice's public (A): " << alice_public << std::endl;
    std::cout << "Bob's public (B): " << bob_public << std::endl;
    std::cout << "\nAlice's secret (K): " << alice_secret << std::endl;
    std::cout << "Bob's secret (K): " << bob_secret << std::endl;

    return 0;
}
