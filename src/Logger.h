#include <iostream>

namespace Logger {
    template <class T>
    void Log(T proper)
    {
        std::cout << proper << std::endl;
    }
}
