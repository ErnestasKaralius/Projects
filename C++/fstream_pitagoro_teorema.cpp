#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    int m1,m2,sk,mn,d;
    ifstream fd("pitagoras_data.txt");
    ofstream fr("pitagoras_rez.txt");
    fd>>m1>>m2;
    for(m1;m1<=m2;m1++)
        for(mn=1;mn<=12;mn++)
            for(d=1;d<=31;d++)
            {
                sk=m1%100;
                if(d*d+mn*mn==sk*sk||mn*mn+sk*sk==d*d||sk*sk+d*d==mn*mn)fr<<m1<<" "<<mn<<" "<<d<<endl;
            }

    fd.close();
    fr.close();
    return 0;
}
