#include <iostream>

using namespace std;

int main()

{
    int a, b, c;
    cin >> a >> b >> c;

    if(a%3==0) cout << "Atsakymas: " << a;
        else if(b%3==0) cout << "Atsakymas: " << b;
            else if(c%3==0) cout << "Atsakymas: " << c;
                else cout << "Atsakymas: nera";

    return 0;
}
