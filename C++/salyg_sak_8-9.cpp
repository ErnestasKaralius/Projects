#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()

{
    double a, b, c;
    cin >> a >> b >> c;

    double D = b*b-4*a*c;
    if (D<0) cout << "Lygtis sprendiniu neturi";
    else if (D==0)
    {
        double x = -1*b/2*a;
        cout << "x = " << x;
    }
    else
    {
        double x1 = (-1*b-sqrt(D))/(2*a);
        double x2 = (-1*b+sqrt(D))/(2*a);
        cout << fixed << setprecision(1) << "x1 = " << x1 << " x2 = " << x2;
    }
    return 0;
}
