#include <iostream>
#include <iomanip>

using namespace std;

int main()

{
    int x, r, h;
    double const pi = 3.14;
    cin >> x >> r >> h;

    double turis =(pi*(r*r)*h)/1000;
    cout << fixed << setprecision(2) << "Indo turis: " << turis << " l." << endl;
    if(turis>x)
    {
        cout << "Skystis inde telpa" << endl;
        cout << "Laisvos vietos liko: " << turis - x << " l.";
    }
    else
    {
        cout << "Skystis inde netelpa" << endl;
        cout << "Liko nesupilta: " << x - turis << " l.";
    }


    return 0;
}
