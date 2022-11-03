#include <fstream>
using namespace std;

int didziausia_mase();
int lengvesniu_kupriniu_kiekis();

int main()
{
    ofstream fr("kuprines_rez.txt");

    fr<<didziausia_mase()<<" "<<lengvesniu_kupriniu_kiekis();

    fr.close();

    return 0;
}

int didziausia_mase()
{
    ifstream fd("kuprines_data.txt");

    int n,did,sk;

    fd>>n;
    fd>>did;

    for(int i=1; i<n; i++)
    {
        fd>>sk;
        if(sk > did)
            did = sk;
    }

    fd.close();

    return did;
}

int lengvesniu_kupriniu_kiekis()
{
    ifstream fd("kuprines_data.txt");

    int kiekis=0;
    int n,sk,did = didziausia_mase();

    fd>>n;
    for(int i=0; i<n; i++)
    {
        fd>>sk;
        if(did - 2 * sk >= 0) kiekis++;
    }

    fd.close();

    return kiekis;
}
