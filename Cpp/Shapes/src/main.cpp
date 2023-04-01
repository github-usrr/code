#include "controller.h"
#include <iostream>

int main()
{
    Controller controller;
    controller.printHelp();

    std::cout << "\nEnter name of the shape: ";
    std::string name;
    std::cin >> name;

    controller.handleInput(name);

    return 0;
}
