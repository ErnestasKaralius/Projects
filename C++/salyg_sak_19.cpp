#include <iostream>

using namespace std;

int main()

{
    int t, liekana;
    cin >> t;

    liekana = t%5;
    if(liekana==1 || liekana==2) cout << "Dega zalia sviesa";
        else if(liekana==3) cout << "Dega zalia sviesa, tuoj uzsidegs raudona";
            else if(liekana==4) cout << "Dega raudona sviesa";
                else cout << "Dega raudona sviesa, tuoj uzsidegs zalia";

    return 0;
}
