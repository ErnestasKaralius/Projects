#include <iostream>
using namespace std;

int main()
{
    int n,p,m,t=1,msum=0,psum=0;
    cin>>n>>p>>m;
    while(n>0)
    {
        if(t%2==0)
            if(n>=m){n=n-m;msum=msum+m;}
                else {msum=msum+n;n=0;}
            else if(n>=p) {n=n-p;psum=psum+p;}
                else {psum=psum+n;n=0;}
        t++;
    }
    cout<<msum<<endl;
    cout<<psum;

    return 0;
}
