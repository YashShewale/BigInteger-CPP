#include "BigInteger.cpp"

int main() {
    BigInteger a("12345678901234567890");
    BigInteger b("98765432109876543210");
    std::cout << "Add: " << a.add(b.a) << std::endl;
    std::cout << "Karatsuba: " << a.karatsubaMultiply(b.a) << std::endl;
    std::cout << "Fast Exponentiation: " << a.fastExponentiation("2") << std::endl;
    return 0;
}