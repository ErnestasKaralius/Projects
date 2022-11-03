#include <iostream>

int main ()

{
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a>b && b>c && a>c) std::cout << c << " " << b << " " << a;
    else if (a>b && b<c && a>c) std::cout << b << " " << c << " " << a;
    else if (a<b && b<c && a<c) std::cout << a << " " << b << " " << c;
    else if (a>b && b<c && a<c) std::cout << b << " " << a << " " << c;
    else if (a<b && b>c && a<c) std::cout << a << " " << c << " " << b;
    else if (a<b && b>c && a>c) std::cout << c << " " << a << " " << b;
    else std::cout << "Visi ar keli skaiciai yra lygus";

    return 0;
}
