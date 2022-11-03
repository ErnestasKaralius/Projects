#include <iostream>

using namespace std;

int main()

{
    int d, k, n, talpa;
    cin >> d >> k >> n;

    talpa=d*n;
    if(talpa>=k) cout << "Knygos telpa i dezes";
    else
    {
        cout << "Knygos netelpa i dezes" << endl;
        cout << "I dezes netilpo knygu: " << k-talpa;
    }

    return 0;
}
