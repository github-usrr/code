#pragma once

#include "algo.h"
#include <cmath>
#include <stdexcept>

class Shape
{
public:
    virtual double getArea()      = 0;
    virtual double getPerimeter() = 0;

    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    Circle(double r) 
    {
        r > 0 ? this->r = r 
              : throw std::runtime_error("Incorrect Circle! Check the radius");
    }

    virtual double getArea()
    {
        return M_PI * r * r;
    }

    virtual double getPerimeter()
    {
        return 2 * M_PI * r;
    }

private:
    double r;
};

class Triangle : public Shape
{
public:
    Triangle(double a, double b, double c) 
    {
        if ( a > 0 && b > 0 && c > 0
            && a+b > c && a+c > b && b+c > a )
        {
            this->a = a;  this->b = b;  this->c = c;
        }
        else
            throw std::runtime_error("Incorrect triangle! Check the edges");
    }

    virtual double getArea()
    {
        const double p = getPerimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    virtual double getPerimeter()
    {
        return sum(a, b, c);
    }

private:
    double a, b, c;
};

class Square : public Shape
{
public:
    Square(double a)
    {
        a > 0 ? this->a = a 
              : throw std::runtime_error("Incorrect square! Check the side");
    }

    virtual double getArea()
    {
        return a * a;
    }

    virtual double getPerimeter()
    {
        return 4 * a;
    }

private:
    double a;
};

class Rectangle : public Shape
{
public:
    Rectangle(double a, double b)
    {
        if ( a > 0 && b > 0 )
        {
            this->a = a;  this->b = b;
        }
        else
            throw std::runtime_error("Incorrect rectangle! Check the sides");
    }

    virtual double getArea()
    {
        return a * b;
    }

    virtual double getPerimeter()
    {
        return 2 * a + 2 * b;
    }

private:
    double a, b;
};

class Trapezium : public Shape
{
public:
    Trapezium(double a, double b, double c, double d)
    {
        double height = sqrt(   c*c - pow( ((a-b)*(a-b)+c*c-d*d)/(2*(a-b)),  2)   );

        if ( a > 0 && b > 0 && c > 0 && d > 0
            && a+b+c > d && a+d+c > b && a+b+d > c && b+d+c > a
            && !std::isnan(height) )  // if h is nan, the order of edges may be wrong
        {
            this->a = a;  this->b = b;  this->c = c;  this->d = d;   this->h = height;
        }
        else
            throw std::runtime_error("Incorrect trapezium! Check the edges");
    }

    virtual double getArea()
    {
        return (a + b) * h / 2;
    }

    virtual double getPerimeter()
    {
        return sum(a, b, c, d);
    }

private:
    double a, b, c, d, h;
};

class Parallelogram : public Shape
{
public:
    Parallelogram(double a, double b, double alphaRad)
    {
        if ( a > 0 && b > 0  &&  alphaRad > 0 && alphaRad < M_PI/2 )
        {
            this->a = a;  this->b = b;  this->alphaRad = alphaRad;
        }
        else
            throw std::runtime_error("Incorrect parallelogram! Check the edges and angle");
    }

    virtual double getArea()
    {
        return a * b * sin(alphaRad);
    }

    virtual double getPerimeter()
    {
        return 2 * a + 2 * b;
    }

private:
    double a, b, alphaRad;
};