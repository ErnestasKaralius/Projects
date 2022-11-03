#include <fstream>

using namespace std;

struct staciakampis {
    int x, y;
    int dx, dy;
    int r, g, b;
};

struct lentele {
    int r, g, b;
};

void skaitymas(int&n, staciakampis S[], lentele L[][100]);
void staciakampiu_uzdejimas(int n, staciakampis S[], lentele L[][100]);
void piesinio_matmenys(int&a, int&b, int&mazx, int&mazy, lentele L[][100]);
void rasymas(lentele L[][100], int a, int b, int mazx, int mazy);

int main()
{
    int n;
    int a, b; // Ilgis ir plotis
    int mazx, mazy; // Mažiausia X ir Y koordinatė
    staciakampis S[100];
    lentele L[100][100];

    skaitymas(n,S,L);
    staciakampiu_uzdejimas(n,S,L);
    piesinio_matmenys(a,b,mazx,mazy,L);
    rasymas(L,a,b,mazx,mazy);

    return 0;
}

void skaitymas(int&n, staciakampis S[], lentele L[][100])
{
    ifstream fd("piesinys_data.txt");

    fd>>n;
    for(int i=0; i<n; i++)
    {
        fd>>S[i].x>>S[i].y;
        fd>>S[i].dx>>S[i].dy;
        fd>>S[i].r>>S[i].g>>S[i].b;
    }

    // Langelių nuspalvinimas balta spalva
    for(int x=0; x<100; x++)
        for(int y=0; y<100; y++)
        {
            L[x][y].r = 255;
            L[x][y].g = 255;
            L[x][y].b = 255;
        }

    fd.close();
}

void staciakampiu_uzdejimas(int n, staciakampis S[], lentele L[][100])
{
    for(int i=0; i<n; i++)
        for(int x=S[i].x; x<S[i].x + S[i].dx; x++)
            for(int y=S[i].y; y<S[i].y + S[i].dy; y++)
            {
                L[x][y].r = S[i].r;
                L[x][y].g = S[i].g;
                L[x][y].b = S[i].b;
            }
}

void piesinio_matmenys(int&a, int&b, int&mazx, int&mazy, lentele L[][100])
{
    int didx=0, didy=0;
    mazx=99,mazy=99;

    for(int x=0; x<100; x++)
        for(int y=0; y<100; y++)
        {
            if(L[x][y].r != 255 || L[x][y].g != 255 || L[x][y].b != 255)
            {
                // Didžiausios Y koordinatės radimas
                if(y > didy)
                    didy = y;

                // Mažiausios Y koordinatės radimas
                if(y < mazy)
                    mazy = y;
            }

            if(L[y][x].r != 255 || L[y][x].g != 255 || L[y][x].b != 255)
            {
                // Didžiausios X koordinatės radimas
                if(y > didx)
                    didx = y;

                // Mažiausios X koordinatės radimas
                if(y < mazx)
                    mazx = y;
            }
        }
    // Ilgis ir plotis
    a = didy - mazy + 1;
    b = didx - mazx + 1;
}

void rasymas(lentele L[][100], int a, int b, int mazx, int mazy)
{
    ofstream fr("piesinys_rez.txt");

    fr<<a<<" "<<b<<"\n";
    for(int y=mazy; y<a + mazy; y++)
        for(int x=mazx; x<b + mazx; x++)
            fr<<L[x][y].r<<" "<<L[x][y].g<<" "<<L[x][y].b<<"\n";

    fr.close();
}
