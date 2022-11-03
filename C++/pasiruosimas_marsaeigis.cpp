#include <fstream>
#include <iostream>
using namespace std;

struct seka {
    string priezastis;
    int kiekis;
    int K[30];
};

void koordinaciu_nustatymas(int sk, int&x, int&y);

int main()
{
    int px,py;
    int tx,ty;
    int x,y;

    int n,k;
    int sk;

    seka S[10];

    ifstream fd("marsaeigis_data.txt");
    ofstream fr("marsaeigis_rez.txt");

    fd>>px>>py;
    fd>>tx>>ty;

    fd>>n;
    for(int i=0; i<n; i++)
    {
        fd>>k;

        S[i].kiekis = 0;
        x=px, y=py;

        int j = 0;
        bool pasiektas = false;
        while(j < k && !pasiektas)
        {
            fd>>sk;
            S[i].K[j] = sk;
            S[i].kiekis++;
            koordinaciu_nustatymas(sk,x,y);
            j++;

            if(x == tx && y == ty) pasiektas = true;
        }
        if(x == tx && y == ty) S[i].priezastis = "pasiektas tikslas   ";
            else S[i].priezastis = "sekos pabaiga       ";

    }

    for(int i=0; i<n; i++)
    {
        fr<<S[i].priezastis;
        for(int j=0; j<S[i].kiekis; j++)
            fr<<S[i].K[j]<<" ";
        fr<<S[i].kiekis<<"\n";
    }

    return 0;

    fd.close();
    fr.close();

}

void koordinaciu_nustatymas(int sk, int&x, int&y)
{
    if(sk == 1) y++;
        else if(sk == 2) x++;
            else if(sk == 3) y--;
                else x--;
}

