#include <fstream>
using namespace std;

int main()
{
    int s,sk1,sk2,sk3,sk4;
    ifstream fd("skaiciai_data.txt");
    ofstream fr("skaiciai_rez.txt");
    fd>>s;
    for(sk1=1;sk1<=s;sk1++)
    {
        for(sk2=sk1+1;sk2<=9;sk2++)
            for(sk3=sk2+1;sk3<=9;sk3++)
                for(sk4=sk3+1;sk4<=9;sk4++)
                    if(sk1+sk2+sk3+sk4==s)fr<<sk1<<" "<<sk2<<" "<<sk3<<" "<<sk4<<endl;
    }
    fd.close();
    fr.close();
    return 0;
}
