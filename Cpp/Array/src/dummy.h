#pragma once

struct Dummy {};

std::ostream & operator<<(std::ostream & out, const Dummy &)
{
    out << "Dummy";
    return out;
}