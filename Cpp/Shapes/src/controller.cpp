#include "controller.h"
#include <iostream>

Controller::Controller()
{
    handler["Circle"]        = &Controller::handleCircle;
    handler["Triangle"]      = &Controller::handleTriangle;
    handler["Square"]        = &Controller::handleSquare;
    handler["Rectangle"]     = &Controller::handleRectangle;
    handler["Trapezium"]     = &Controller::handleTrapezium;
    handler["Parallelogram"] = &Controller::handleParallelogram;
}

void Controller::printHelp()
{
    std::cout << "\nCalculate area and perimeter of shapes:"
                 "\nCircle, Triangle, Square, Rectangle, Trapezium, Parallelogram."
                 "\nDescription: a, b, c, d mean sides of shapes\n"
                 "\n* Trapezium edges designation:"
                 "\n                               b      "
                 "\n                             ......   "
                 "\n                        c  ......... d"
                 "\n                         ............ "
                 "\n                       ..............."
                 "\n                               a    \n";

}

void Controller::handleInput(std::string &name)
{
    std::string incorrectNameStr = "\nError! Incorrect name\n";

    // first char to uppercase
    if (!name.empty())
    {
        name[0] = std::toupper(name[0]);
    }
    else
    {
        std::cerr << incorrectNameStr;
        return;
    }

    // handle shape
    if ( handler.find(name) != handler.end() ) // shape has been found
    {
        (this->*handler[name]) (); // handle shape (call handler on name)
    }
    else // invalid shape
    {
        std::cerr << incorrectNameStr;
        return;
    }

    // result
    if (shape)
    {
        std::cout << "\nArea: "      << shape->getArea();
        std::cout << "\nPerimeter: " << shape->getPerimeter() << std::endl;
    }
}

void Controller::handleCircle()
{
    std::cout << "\nEnter radius: ";
    double r;
    std::cin >> r;

    try
    {
        shape.reset(new Circle(r));
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n' << e.what() << '\n';
    }
}

void Controller::handleTriangle()
{
    std::cout << "\nEnter a: ";
    double a;
    std::cin >> a;

    std::cout << "\nEnter b: ";
    double b;
    std::cin >> b;

    std::cout << "\nEnter c: ";
    double c;
    std::cin >> c;

    try
    {
        shape.reset(new Triangle(a, b, c));
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n' << e.what() << '\n';
    }
}

void Controller::handleSquare()
{
    std::cout << "\nEnter side: ";
    double a;
    std::cin >> a;

    try
    {
        shape.reset(new Square(a));
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n' << e.what() << '\n';
    }
}

void Controller::handleRectangle()
{
    std::cout << "\nEnter a: ";
    double a;
    std::cin >> a;

    std::cout << "\nEnter b: ";
    double b;
    std::cin >> b;

    try
    {
        shape.reset(new Rectangle(a, b));
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n' << e.what() << '\n';
    }
}

void Controller::handleTrapezium()
{
    std::cout << "\nEnter a: ";
    double a;
    std::cin >> a;

    std::cout << "\nEnter b: ";
    double b;
    std::cin >> b;

    std::cout << "\nEnter c: ";
    double c;
    std::cin >> c;

    std::cout << "\nEnter d: ";
    double d;
    std::cin >> d;

    try
    {
        shape.reset(new Trapezium(a, b, c, d));
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n' << e.what() << '\n';
    }
}

void Controller::handleParallelogram()
{
    std::cout << "\nEnter a: ";
    double a;
    std::cin >> a;

    std::cout << "\nEnter b: ";
    double b;
    std::cin >> b;

    std::cout << "\nEnter angle in degrees: ";
    double alphaDeg;
    std::cin >> alphaDeg;

    try
    {
        shape.reset(new Parallelogram(a, b, alphaDeg * M_PI / 180));
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n' << e.what() << '\n';
    }
}