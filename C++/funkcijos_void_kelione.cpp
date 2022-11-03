#include <fstream>
using namespace std;
void kada_atvyks(int s,int v,int&val,int&min);

int main()
{
    int n; // Aplankytų miestų skaičius
    int val,min; // Išvykimo laikas valandomis ir minutėmis
    int s,v; // Atstumas tarp miestų ir turisto greitis
    ifstream fd("kelione_miestais_data.txt");
    ofstream fr("kelione_miestais_rez.txt");
    fd>>val>>min;
    fd>>n;
    for(int i=0;i<n;i++)
    {
        fd>>s>>v;
        kada_atvyks(s,v,val,min);
        fr<<i+1<<" "<<val<<" "<<min<<endl;
    }
    fd.close();
    fr.close();
    return 0;
}

void kada_atvyks(int s,int v,int&val,int&min)
{
    min+=(double)s/v*60;
    val=(val+min/60)%24;
    min%=60;
}


