#include "nested_profiler.cpp"

void fa()
{
    TimeFunction;
    for (int i = 0; i < 1e7; i++)
        ;
    return;
}
void fb()
{
    TimeFunction;
    for (int i = 0; i < 1e7; i++)
        ;
    return;
}
void fc()
{
    TimeFunction;
    for (int i = 0; i < 1e7; i++)
        ;
    fb();
    return;
}
void fd()
{
    TimeFunction;
    for (int i = 0; i < 1e7; i++)
        ;
    return;
}

int main()
{
    BeginProfile();
    // {
    //     TimeFunction;
    //     for (int i = 0; i < 1e7; i++)
    //         ;
    // }
    fa();
    fb();
    fc();
    // fd();
    EndAndPrintProfile();
    return 0;
}