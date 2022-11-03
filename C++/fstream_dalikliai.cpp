#include <fstream>
using namespace std;

int main()
{
    int a,i,b,j,suma,gsuma,did;
    ifstream fd("dalikliai_data.txt");
    ofstream fr("dalikliai_rez.txt");
    fd>>a>>b;
    for(i=a;i<=b;i++)
    {
       suma=0;
       for(j=1;j<=i;j++) if(i%j==0)suma++;
       if(i==a){did=i;gsuma=suma;}
       if(suma>gsuma){did=i;gsuma=suma;}
    }
    fr<<did<<" "<<gsuma<<endl;
    for(i=did;i==did;i++)
        for(j=1;j<=i;j++) if(i%j==0)fr<<j<<" ";

    fd.close();
    fr.close();
    return 0;
}
