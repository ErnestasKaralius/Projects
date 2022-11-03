#include <iostream>

using namespace std;

int main()

{
    int variantas, a, b, x;
    cin >> variantas >> a >> b;
    if(variantas==1)
    {
        x=a*b+3;
        cout << "x = " << x;
    }
    else if(variantas==2)
    {
        x=2*a+b;
        cout << "x = " << x;
    }
    else if(variantas==3)
    {
        x=a-3*b;
        cout << "x = " << x;
    }
    else cout << "Tokio varianto nera!";

    return 0;
}
