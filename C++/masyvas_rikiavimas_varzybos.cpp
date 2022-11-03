#include <fstream>
using namespace std;

int main()
{
    int K[128],T[128]; // Komandų ir taškų masyvas
    int k; // Komandų skaičius
    int i,j;
    ifstream fd("komandu_varzybos_data.txt");
    ofstream fr("komandu_varzybos_rez.txt");
    fd>>k;
    // Nuskaitymas į du masyvus
    for(i=0;i<k;i++) fd>>K[i]>>T[i];

    // Komandų rikiavimas pagal taškų mažėjimo tvarką
    for(i=0;i<k-1;i++)
        for(j=i+1;j<k;j++)
            if(T[i]<T[j]) {swap(K[i],K[j]);swap(T[i],T[j]);}

    fr<<k/2<<endl;
    for(i=0;i<k/2;i++) fr<<K[i]<<" "<<T[i]<<endl;
    fd.close();
    fr.close();
    return 0;
}
