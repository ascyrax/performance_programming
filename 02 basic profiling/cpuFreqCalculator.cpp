#include <cstdint>
#include <iostream>
#include <mach/mach_time.h>

uint64_t asm_read_cpu_counter()
{
    uint64_t val;
    __asm__(
        "mrs %0, cntvct_el0"
        : "=r"(val));
    return val;
}

int main()
{
    uint64_t start = asm_read_cpu_counter();
    uint64_t a = mach_absolute_time();
    for (int i = 0; i < 1000000; i++)
        ;

    uint64_t end = asm_read_cpu_counter();
    uint64_t b = mach_absolute_time();
    std::cout << start << std::endl
              << a << std::endl
              << end << std::endl
              << b << std::endl
              << end - start << std::endl
              << b - a << std::endl;

    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    uint64_t duration = (b - a) * info.numer / info.denom;

    std::cout << info.numer << " " << info.denom << std::endl;

    std::cout << "Duration: " << duration << " nanoseconds" << std::endl;
    return 0;
}