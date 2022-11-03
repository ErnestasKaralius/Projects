#include <iostream>

using namespace std;

int main()
{
    int n, a, s=0;
    cin >> n;
    for(a=1; a<=n; a++) s = s+a;
    cout << s;

    return 0;
}
