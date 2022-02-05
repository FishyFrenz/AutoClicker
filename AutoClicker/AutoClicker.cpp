#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

void autoclicker1() {
    std::cout << "Press U to start and stop";
    INPUT input{ 0 };
    input.type = INPUT_MOUSE;

    bool bClick = false;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1);
    int random_value = distribution(generator);

    using Clock = std::chrono::steady_clock;
    std::chrono::time_point<std::chrono::steady_clock> start, now;
    std::chrono::milliseconds duration;
    start = Clock::now();

    while (true)
    {
        //toggles it on and off with one key
        if (GetAsyncKeyState('U') & 1)
            bClick = !bClick;

        if (bClick)
        {
            now = Clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

            if (duration.count() >= random_value)
            {
                int random_value = distribution(generator);
                std::cout << random_value << std::endl;

                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                SendInput(1, &input, sizeof(INPUT));

                input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                SendInput(1, &input, sizeof(INPUT));
                start = std::chrono::steady_clock::now();
            }
        }
    }
}
int main()
{
    
    autoclicker1();
    


    return 0;
}