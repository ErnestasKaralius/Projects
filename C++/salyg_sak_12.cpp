#include <iostream>

int main()

{
    int a, sk1, sk2, sk3;
    std::cin >> a;

    sk1 = a/100;
    sk2 = a%100/10;
    sk3 = a%10;
    if (sk1>5 || sk2>5 || sk3>5) std::cout << "Turi skaitmenu, didesniu uz 5";
        else std::cout << "Neturi skaitmenu, didesniu uz 5";

    return 0;
}
