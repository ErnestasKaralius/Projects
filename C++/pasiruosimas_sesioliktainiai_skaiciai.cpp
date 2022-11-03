#include <fstream>
using namespace std;

string konvertavimas(int sk, string koduote[]);

int main()
{
    int a,b; // Ilgis ir plotis
    int sk;
    string koduote[16] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

    ifstream fd("sesioliktainiai_data.txt");
    ofstream fr("sesioliktainiai_rez.txt");

    fd>>a>>b;
    for(int i=1; i<=a*b; i++)
    {
        for(int j=1;j<=b; j++)
        {
            fd>>sk;
            fr<<konvertavimas(sk,koduote);
        }
        if(i % b == 0) fr<<'\n'; // Kas b nauja eilutė
            else fr<<';';
    }

    fd.close();
    fr.close();

    return 0;
}


string konvertavimas(int sk, string koduote[])
{
    return koduote[sk / 16] + koduote[sk % 16];
}
