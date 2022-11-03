#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()

{
    int a, b, c;
    bool t;
    cin >> a >> b >> c;

    if(a+b>c && b+c>a && a+c>b) { cout << "Trikampi sudaryti galima. "; t=true; }
        else { cout << "Trikampi sudaryti negalima. "; t=false; }

    if(t && a==b && b==c) cout << "Trikampis lygiakrastis. ";
        else if(t && a==b && a!=c || a==c && a!=b) cout << "Trikampis lygiasonis. ";
            else if(t) cout << "Trikampis ivairiakrastis. ";

    if(t) {
        double p =(double)(a+b+c)/2;
        double S =(double)(sqrt(p*(p-a)*(p-b)*(p-c)));
        cout << fixed << setprecision(0) << "Trikampio plotas yra S = " << S;
    }

    return 0;
}
