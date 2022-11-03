#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int sk,i;
    ifstream fd("fstream1.txt");
    ofstream fr("failai2.txt");
    for(i=1;i<=5;i++)
    {
        fd>>sk;
        fr<<sk<<endl;
    }
    fd.close();
    fr.close();

    return 0;
}
