#include <iostream>

using namespace std;

int main()

{
    double a, b, c, d;
    cin >> a >> b >> c >> d;

    if(a>b && a>c && a>d)
    {
        cout << "Didziausias vidurkis " << a << endl;
        cout << a-b << ", " << a-c << ", " << a-d;
    }
    else if(b>a && b>c && b>d)
    {
        cout << "Didziausias vidurkis " << b << endl;
        cout << b-a << ", " << b-c << ", " << b-d;
    }
    else if(c>a && c>b && c>d)
    {
        cout << "Didziausias vidurkis " << c << endl;
        cout << c-a << ", " << c-b << ", " << c-d;
    }
    else
    {
        cout << "Didziausias vidurkis " << d << endl;
        cout << d-a << ", " << d-b << ", " << d-c;
    }
    return 0;
}
