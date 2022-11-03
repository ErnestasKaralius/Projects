#include <iostream>

using namespace std;

int main()

{
    int sk1, sk2, sk3;
    cin >> sk1 >> sk2 >> sk3;

    if(sk1>sk2 && sk2>sk3 && sk1>sk3)
    {
        cout << sk1 << " " << sk2 << " " << sk3 << endl;
        cout << "Skirtumas = " << sk1 - sk3;
    }

    else if(sk1>sk2 && sk2<sk3 && sk1>sk3)
    {
        cout << sk1 << " " << sk3 << " " << sk2 << endl;
        cout << "Skirtumas = " << sk1 - sk2;
    }

    else if(sk1<sk2 && sk2<sk3 && sk1<sk3)
    {
        cout << sk3 << " " << sk2 << " " << sk1 << endl;
        cout << "Skirtumas = " << sk3 - sk1;
    }

    else if(sk1>sk2 && sk2<sk3 && sk1<sk3)
    {
        cout << sk3 << " " << sk1 << " " << sk2 << endl;
        cout << "Skirtumas = " << sk3 - sk2;
    }

    else if(sk1<sk2 && sk2>sk3 && sk1<sk3)
    {
        cout << sk2 << " " << sk3 << " " << sk1 << endl;
        cout << "Skirtumas = " << sk2 - sk1;
    }

    else
    {
        cout << sk2 << " " << sk1 << " " << sk3 << endl;
        cout << "Skirtumas = " << sk2 - sk3;
    }
    return 0;
}
