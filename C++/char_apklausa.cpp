#include <fstream>
using namespace std;

int main()
{
    char A[100][31]; // Adresas
    int KS[100],PG[100],N[100];
    int n; // Gyventojų skaièius
    int g; // Apklaustieji gyventojai
    char simb;
    int i,j;
    ifstream fd("char_gyventoju_apklausa_data.txt");
    ofstream fr("char_gyventoju_apklausa_rez.txt");
    fd>>n;
    fd.ignore();

    for(i=0;i<n;i++)
    {
        fd.get(A[i],30);
        fd>>g;
        KS[i]=0;PG[i]=0;N[i]=0; // Nulinimas
        for(j=0;j<g;j++)
        {
            fd>>simb;
            if(simb=='K'||simb=='S') KS[i]++;
            if(simb=='P'||simb=='G') PG[i]++;
            if(simb=='N') N[i]++;
        }
        fd.ignore();
    }
    for(i=0;i<n;i++) fr<<A[i]<<KS[i]<<" "<<PG[i]<<" "<<N[i]<<endl;



    fd.close();
    fr.close();
    return 0;
}
