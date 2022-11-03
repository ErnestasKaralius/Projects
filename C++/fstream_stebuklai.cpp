#include <fstream>
using namespace std;

int main()
{
    int s,s1,s2,st1,st2,i;
    ifstream fd ("stebuklai_data.txt");
    ofstream fr ("stebuklai_rez.txt");
    fd>>s>>s1>>s2;
    for(st1=0;st1<=s;st1++)
        for(st2=0;st2<=s;st2++)
            if(st1*s1+st2*s2==s)fr<<st1<<" "<<st2<<endl;

    fd.close();
    fr.close();
    return 0;
}
