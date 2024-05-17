#include <iostream>
#include <glad/glad.h>


int main(int argc, char** argv) {
    if (gladLoadGL()) {
        std::cerr << "Fail\n";
        return 1;
    }

    std::cout << "Ok\n";
    return 0;
}