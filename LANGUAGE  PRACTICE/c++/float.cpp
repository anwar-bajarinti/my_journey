#include<iostream>
#include<iomanip>
int  main()
{
    float a=1.1234567;
    double b=1.1234567890123456789;
    long double c=1.1234567890;
    std::cout<<std::fixed<<std::setprecision(10);
    std::cout<<a<<std::endl;
    std::cout<<b<<std::endl;
    std::cout<<c<<std::endl;
    return 0;
}