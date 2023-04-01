#pragma once

void test1()
{
    std::cout << "\n\nTest 1:\n";

    Array<Dummy> arr( 3, Dummy() );
    std::cout << arr;
}

void test2()
{
    std::cout << "\n\nTest 2:\n";
    
    Array<Dummy> arr1( 4, Dummy() );
    std::cout << arr1 << std::endl;

    Array<Dummy> arr2(1);
    arr1 = arr2;

    std::cout << arr1;
}

void test3()
{
    std::cout << "\n\nTest 3:\n";

    Array<Dummy> arr( 3, Dummy() );

    try
    {
        std::cout << arr[150];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}