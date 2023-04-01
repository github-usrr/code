#pragma once

#include "shapes.h"

#include <unordered_map>
#include <memory>

class Controller
{
public:
    Controller();

    void printHelp();
    void handleInput(std::string &str);

private:
    void handleCircle();
    void handleTriangle();
    void handleSquare();
    void handleRectangle();
    void handleTrapezium();
    void handleParallelogram();

    typedef void (Controller::*func)();
    std::unordered_map<std::string, func> handler;

    std::unique_ptr<Shape> shape = nullptr;
};