#include <stdio.h>
#include <iostream>
#include <math.h>
#include <algorithm>

int main(int argc, char **argv)
{

  int n, h,v; std::cin >> n >> h >> v;

  std::cout << (std::max(n-h,h)*std::max(n-v,v)*4) << std::endl;

  
}