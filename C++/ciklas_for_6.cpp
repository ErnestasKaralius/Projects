#include <iostream>

using namespace std;

int main()
{
    int n,s=1;
    cin >> n;
    for(n; n>0; n--) s=s*n;
    cout<<s;

    return 0;
}
