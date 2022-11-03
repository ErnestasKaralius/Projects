#include <iostream>

using namespace std;

int main()

{
    int a, sk1, sk2, sk3;
    cin >> a;
    sk1 = a/100;
    sk2 = a%100/10;
    sk3 = a%10;

    if(sk1%2==0 && sk2%2==0 && sk3%2==0) cout << "Skaicius turi 3 lyginius skaitmenis";
        else if(sk1%2==0 && sk2%2!=0 && sk3%2!=0 || sk2%2==0 && sk1%2!=0 && sk3%2!=0 || sk3%2==0 && sk1%2!=0 && sk2%2!=0) cout << "Skaicius turi 1 lygini skaitmeni";
            else if(sk1%2!=0 && sk2%2!=0 && sk3%2!=0) cout << "Skaicius neturi lyginiu skaitmenu";
                else cout << "Skaicius turi 2 lyginius skaitmenis";
    return 0;
}
