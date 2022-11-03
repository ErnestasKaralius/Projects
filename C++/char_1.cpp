#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    char sk;
    int kiekis=0;
    ifstream fd("char_1_data.txt");

    fd>>sk;
    while(!fd.eof())
    {
        if(sk=='a') kiekis++;
        fd>>sk;
    }
    cout<<kiekis;


    fd.close();
    return 0;
}
