#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int sk,i;
    ifstream fd("fstream1.txt");
    for(i=1;i<=5;i++)
    {
        fd>>sk;
        cout<<sk<<endl;
    }
    fd.close();

    return 0;
}
