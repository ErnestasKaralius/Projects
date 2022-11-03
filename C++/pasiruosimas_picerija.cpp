#include <fstream>
#include <cmath>
using namespace std;

void skaitymas(int&n, int&m, int&nepristatyta, int&suma);
void rasymas(int nepristatyta, int suma);
int atstumas(int x, int y);

int main()
{
    int n, m;
    int nepristatyta, suma;

    skaitymas(n,m,nepristatyta,suma);
    rasymas(nepristatyta, suma);

    return 0;
}

void skaitymas(int&n, int&m, int&nepristatyta, int&suma)
{
    int i=0;
    int x,y;
    ifstream fd("picerija_data.txt");

    fd>>n>>m;
    suma=0;
    while(i < n && suma <= m)
    {
        fd>>x>>y;
        suma += atstumas(x,y);
        i++;
    }

    nepristatyta = n - i;

    fd.close();
}

int atstumas(int x, int y)
{
    return (abs(x) + abs(y)) * 2;
}

void rasymas(int nepristatyta, int suma)
{
    ofstream fr("picerija_rez.txt");

    fr<<nepristatyta<<" "<<suma;

    fr.close();
}
