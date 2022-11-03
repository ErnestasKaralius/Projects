#include <iostream>

using namespace std;

int main()

{
    int n1, n2, n3;
    double a, b, k;
    cin >> a >> b >> n1 >> n2 >> n3 >> k;

    if(k<=a)
    {
        k = k*n1;
        cout << "Uz bandeles sumoketa " << k << " euru";

    }
    else if(k>a && k<b)
    {
        k = k*n2;
        cout << "Uz bandeles sumoketa " << k << " euru";
    }
    else
    {
        k = k*n3;
        cout << "Uz bandeles sumoketa " << k << " euru";
    }
    return 0;
}
