#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    int X[100],Y[100],P[100];
    int n,x0,y0;
    int x,y;
    int i,j;
    ifstream fd("koordinates_data.txt");
    ofstream fr ("koordinates_rez.txt");
    fd>>n>>x0>>y0;

    for(i=0;i<n;i++) fd>>X[i]>>Y[i];

    for(i=0;i<n;i++) P[i]=sqrt(pow(X[i]-x0,2)+pow(Y[i]-y0,2));


    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(P[i]>P[j]){swap(P[i],P[j]);swap(X[i],X[j]),swap(Y[i],Y[j]);}

    for(i=0;i<3;i++) fr<<X[i]<<" "<<Y[i]<<endl;

    fd.close();
    fr.close();
    return 0;
}
