#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    char sk;
    int kiekis=0;
    ifstream fd("char_2_data.txt");
    fd>>sk;
    while(!fd.eof())
    {
        if(sk=='+'||sk=='-'||sk=='*'||sk=='/') kiekis++;
        fd>>sk;
    }
    cout<<kiekis;

    fd.close();
    return 0;
}
