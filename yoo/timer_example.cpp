//https://stackoverflow.com/questions/3220477/how-to-use-clock-in-c
#include <iostream>
#include <cstdio>
#include <ctime>
#include <iomanip>

std::clock_t clock;
double duration;
clock = std::clock();

/* core code here*/
duration = ( std::clock() - clock ) / (double) CLOCKS_PER_SEC;
std::cout<<"the code took: "<< duration << std::setprecision(5)<<'\n';
