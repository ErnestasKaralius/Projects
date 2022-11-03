#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,i; // Pyragų receptų skaičius
    int O[29],K[29]; // Obuolių ir kiaušinių skaičių masyvas
    double M[29],C[29],L[29],T[29]; // Miltai, cukraus kiekis, kepimo laikas, kepimo t;
    double v,t; //  Valandos, temperatūra

    int osum=0,ksum=0; // Obuolių ir kiaušinių suma
    double msum=0,csum=0; // Miltų ir cukraus suma
    int pvsum=0, ptsum=0; // Pyragų sumos
    ifstream fd("pyragai_data.txt");
    ofstream fr("pyragai_rez.txt");
    cin>>v>>t;
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>O[i]>>K[i]>>M[i]>>C[i]>>L[i]>>T[i];

    for(i=0;i<n;i++)
    {
        // Obuolių ir kiaušinių sumos skaičiavimas
        osum=osum+O[i];
        ksum=ksum+K[i];

        // Miltų ir cukraus sumos skaičiavimas
        msum=msum+M[i];
        csum=csum+C[i];

        // Pyragų, kurie kepa ne mažiau v valandų, kiekio radimas
        if(L[i]>=v) pvsum++;

        // Pyragų, kurie kepa ne mažesnėje t temperatūroje, kiekio radimas
        if(T[i]>=t) ptsum++;
    }

    fr<<osum<<" "<<ksum<<endl;
    fr<<fixed<<setprecision(1)<<msum/n<<" "<<csum/n<<endl;
    fr<<pvsum<<"\n"<<ptsum<<endl;

    // Pyragų, kuriuos kepama aukštesnėje nei 200 laipsnių t, šalinimas
    for(i=0;i<n;i++)
        if(T[i]>=200)
        {
            O[i]=O[n-1];
            K[i]=K[n-1];
            M[i]=M[n-1];
            C[i]=C[n-1];
            L[i]=L[n-1];
            T[i]=T[n-1];
            n--;
            i--;
        }
    // Pyragų eilių išspausdinimas
    for(i=0;i<n;i++) fr<<O[i]<<" "<<K[i]<<" "<<M[i]<<" "<<C[i]<<" "<<L[i]<<" "<<T[i]<<endl;

    fd.close();
    fr.close();
    return 0;
}
