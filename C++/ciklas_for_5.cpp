#include <iostream>

using namespace std;

int main()
{
    int n, lt, suma=0;
    cin >> n;
    for(lt=1; lt<=n; lt++) suma = suma + lt;
    cout << suma+5;


    return 0;
}
