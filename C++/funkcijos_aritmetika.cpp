#include <fstream>
using namespace std;
bool ar_teisinga(int sk1,int sk2,int r);

int main()
{
    int n; // Operacijų skaičius
    int sk1,sk2,r; // Pirmas, antras skaičius ir rezultatas
    ifstream fd("aritmetika_data.txt");
    ofstream fr("aritmetika_rez.txt");
    fd>>n;
    for(int i=0;i<n;i++)
    {
      fd>>sk1>>sk2>>r;
      if(ar_teisinga(sk1,sk2,r))
      {
          if(sk1+sk2==r) fr<<sk1<<"+"<<sk2<<"="<<r<<endl;
          if(sk1-sk2==r) fr<<sk1<<"-"<<sk2<<"="<<r<<endl;
          if(sk1*sk2==r) fr<<sk1<<"*"<<sk2<<"="<<r<<endl;
          if((double)sk1/sk2==r) fr<<sk1<<"/"<<sk2<<"="<<r<<endl;
      }
      else fr<<sk1<<" "<<sk2<<" "<<r<<" KLAIDINGA"<<endl;
    }

    fd.close();
    fr.close();
    return 0;
}

bool ar_teisinga(int sk1,int sk2,int r)
{
    if(sk1+sk2==r||sk1-sk2==r||sk1*sk2==r||(double)sk1/sk2==r) return 1;
        else return 0;
}

