#include <fstream>
using namespace std;
bool ar_atvyks_laiku(int L[],int sd,int sv,int sm);

int main()
{
    int L[3]; // Laikas: diena, valanda, minutė
    int val,min; // Kiek užtrunka valandų ir minučių
    ifstream fd("funkcijos_susitikimas_data.txt");
    ofstream fr("funkcijos_susitikimas_rez.txt");
    for(int i=0;i<3;i++) fd>>L[i]; // Laiko įdėjimas į masyvą
    fd>>val>>min;
    L[1]=L[1]+val;
    L[2]=L[2]+min;

    L[1]=L[1]+L[2]/60; // Kiek valandų
    L[2]=L[2]%60; // Minučių likutis

    L[0]=L[0]+L[1]/24; // Kiek dienų
    L[1]=L[1]%24; // Valandų likutis
    for(int i=0;i<3;i++) fr<<L[i]<<" ";

    int sd,sv,sm; // Susitikimo diena, valanda, minutė
    fd>>sd>>sv>>sm;
    if(ar_atvyks_laiku(L,sd,sv,sm)) fr<<"\nTAIP";
        else fr<<"\nNE";

    fd.close();
    fr.close();
    return 0;
}

bool ar_atvyks_laiku(int L[],int sd,int sv,int sm)
{
    if(L[0]<sd||L[0]==sd&&L[1]<sv||L[0]==sd&&L[1]==sv&&L[2]<=sm) return 1;
        else return 0;
}
