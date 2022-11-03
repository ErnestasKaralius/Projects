#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    double M1[20]; // Pirmosios sportininkų grupės masyvas (20, nes kitos komandos reikšmės (didž.-10) bus idedamos į šį)
    double M2[10]; // Antrosios sportininkų grupės masyvas
    int n,m; // Sportinkų skaičius
    int vieta; // Vieta, kur įterpsime masyvo reikšmę
    int i,j,k;
    ifstream fd1("komanda_1_data.txt");
    ifstream fd2("komanda_2_data.txt");
    ofstream fr("komanda_rez.txt");
    fd1>>n;
    // Pirmosios sportininkų grupės nuskaitymas
    for(i=0;i<n;i++) fd1>>M1[i];

    fd2>>m;
    // Antrosios sportininkų grupės nuskaitymas
    for(i=0;i<m;i++) fd2>>M2[i];

    // Antrosios grupės masyvų idėjimas į pirmąjį
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            if(M2[i]>M1[n-1])
            {
                M1[n]=M2[i];
                n++;
            }
           else if(M2[i]>M1[j]&&M2[i]<M1[j+1])
            {
                vieta=j+1;
                for(k=n;k>vieta;k--) M1[k]=M1[k-1];
                M1[vieta]=M2[i];
                n++;
            }
            else if(M2[i]<M1[0])
            {
                for(k=n;k>0;k--) M1[k]=M1[k-1];
                M1[0]=M2[i];
                n++;
            }
        }
    if(n<10) fr<<"KOMANDA NESUSIDARĖ, TRŪKSTA "<<10-n;
    else
    {
        int s=n-10;
        for(i=0;i<n-s;i++) M1[i]=M1[i+s];
    }
    for(i=0;i<n;i++) fr<<fixed<<setprecision(2)<<M1[i]<<" ";
    fd1.close();
    fd2.close();
    fr.close();
    return 0;
}
