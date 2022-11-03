#include <iostream>

using namespace std;

int main()

{
    int p1, p2, p3, p4, p5;
    cin >> p1 >> p2 >> p3 >> p4 >> p5;

    double vidurkis = (double)(p1+p2+p3+p4+p5)/5;
    if (vidurkis>9) cout << "Gaus tris saldainius";
        else if(vidurkis<=9 && vidurkis>=7) cout << "Gaus du saldainius";
            else cout << "Gaus viena saldaini";

    return 0;
}
