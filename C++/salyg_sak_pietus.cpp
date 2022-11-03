#include <iostream>

using namespace std;

int main()

{
    int v, m, p, vv, vm;
    cin >> v >> m >> p >> vv >> vm;

    m = (v*60)+m;
    vm = (vv*60)+vm;
    if(m+p>vm) cout << "Mama pietus pagaminti nespes";
        else cout << "Mama pietus pagaminti spes";


    return 0;
}
