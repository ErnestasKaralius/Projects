#include <iostream>

using namespace std;

int main()

{
    int a, b, c;
    cin >> a >> b >> c;

    if(a>b && a>c) cout << "Didziausias skaicius yra " << a;
        else if(b>a && b>c) cout << "Didziausias skaicius yra " << b;
            else cout << "Didziausias skaicius yra " << c;

    return 0;
}
