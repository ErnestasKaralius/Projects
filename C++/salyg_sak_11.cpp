#include <iostream>

int main()

{
    int a, b, c;
    std::cin >> a >> b >> c;

    if(a<0 || b<0 || c<0) std::cout << "Tarp siu skaiciu yra neigiamu";
    else std::cout << "Tarp siu skaiciu nera neigiamu";

    return 0;
}
