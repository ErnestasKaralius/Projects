#include <fstream>
using namespace std;

int main()
{
    int n,i,tsk,j;
    int suma=0,nsum=0,lsum=0,psum=0;
    int M[100];
    double vid;
    ifstream fd("masyvas_1_data.txt");
    ofstream fr("masyvas_1_rez.txt");
    fd>>n;
    for(i=0;i<n;i++)
    {
        fd>>M[i];
        // Skaičių suma
        suma=suma+M[i];
        // Pirminių skaičių kiekis
        tsk=0;
        for(j=2;j<M[i];j++) if(M[i]%j==0) tsk++;
        if(tsk==0)psum++;
        // Lyginių ir nelyginių skaičių kiekis
        if(M[i]%2==0)lsum++;
            else nsum++;
    }
    vid=(double)suma/i;
    fr<<"Suma: "<<suma<<endl;
    fr<<"Vidurkis: "<<vid<<endl;
    fr<<"Lyginių skaičių kiekis: "<<lsum<<endl;
    fr<<"Nelyginių skaičių kiekis: "<<nsum<<endl;
    fr<<"Pirminių skaičių kiekis: "<<psum<<endl;
    fr<<"Skaičiai, didesni už vidurkį: ";
    // Skaičiai, didesni už vidurkį
    for(i=0;i<n;i++)
    {
        fd>>M[i];
        if(M[i]>vid)fr<<M[i]<<" ";
    }
    fd.close();
    fr.close();
    return 0;
}
