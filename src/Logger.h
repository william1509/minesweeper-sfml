#include <iostream>
#include <vector>

namespace Logger {
    template <class T>
    void Log(T param)
    {
        std::cout << param << std::endl;
    }

    // void LogBoard(std::vector<Cell*> cells) {
    //     for(size_t i = 0; i < cells.size(); i++) {
    //         std::cout << cells[i]->_isClicked;
    //         if(i % MINE_WIDTH == 0) {
    //             std::cout << std::endl;
    //         }
    //     }
    // }
}
