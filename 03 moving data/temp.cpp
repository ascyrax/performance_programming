#include <iostream>
#include <cstdint> // For intptr_t
using std::cout;
using std::endl;

int main()
{
    long long a = 5;
    long long b = 6;
    long long *addr_a = &a;
    long long *addr_b = &b;

    // Cast pointers to void* for printing in decimal format
    // cout << reinterpret_cast<void*>(addr_a) << " " << reinterpret_cast<void*>(addr_b) << endl;
    cout << (long long)addr_a << endl;
    cout << (long long)addr_b << endl;
    return 0;
}
