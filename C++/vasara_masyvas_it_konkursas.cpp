#include <fstream>
using namespace std;

int main()
{
    int n; // Mokinių skaičius
    int B[100]; // Balų masyvas
    int vid=0; // Vidurkis
    int i;
    ifstream fd("it_konkursas_data.txt");
    ofstream fr("it_konkursas_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>B[i];

    // Vidurkio radimas
    for(i=0;i<n;i++) vid=vid+B[i];
    vid=vid/n;

    for(i=0;i<n;i++)
        if(B[i]<vid)
        {
            B[i]=B[n-1];
            n--;
            i--;
        }
    fr<<"II etape dalyvaus mokinių: "<<n;
    fr<<"\nJie surinko balų: ";
        for(i=0;i<n;i++) fr<<B[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
