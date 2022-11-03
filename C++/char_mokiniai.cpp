#include <fstream>
using namespace std;

int main()
{
    int V[99],M[99]; // Vaikinų ir merginų masyvai
    int vsk=0,msk=0; // Kiek vaikinų ir merginų
    int n; // Mokinių skaičius
    char lytis; // Mokinio lytis
    int amzius; // Mokinio amžius
    int amziu_suma=0; // Mokinių amžių suma
    int v_amziu_suma=0; // Vaikinų amžių suma
    int kartojasi; // Pasikartojančių amžių kiekis
    int daug_kartojasi,did_amzius; // Didžiausias amžių kiekis bei didžiausias amžius
    int i,j;
    ifstream fd ("mokiniu_klase_data.txt");
    ofstream fr ("mokiniu_klase_rez.txt");
    fd>>n;
    // Vaikinų ir merginų amžiaus idėjimas į du masyvus
    for(i=0;i<n;i++)
    {
        fd.get(lytis);
        fd>>amzius;
        amziu_suma=amziu_suma+amzius;
        if(lytis=='v')
        {
            v_amziu_suma=v_amziu_suma+amzius;
            V[vsk]=amzius;
            vsk++;
        }
        else
        {
            M[msk]=amzius;
            msk++;
        }
    }
    fr<<"Mokinių amžiaus vidurkis: "<<amziu_suma/n;

    // Vaikinai
    if(vsk>0)
    {
        fr<<"\n\nVaikinų amžiaus vidurkis: "<<v_amziu_suma/vsk;

        // Vyriausio vaikino paieška, rikiavimas mažėjimo tvarka
        for(i=0;i<vsk-1;i++)
            for(j=i+1;j<vsk;j++)
                if(V[i]<V[j]) swap(V[i],V[j]);

        fr<<"\nVyriausiam vaikinui metų: "<<V[0];

        // Koks vaikinų amžius pasikartoja daugiausia kartų
        for(i=0;i<vsk;i++)
        {
            kartojasi=1;
            for(j=i+1;j<vsk;j++) {if(V[i]==V[j]) kartojasi++; else break;} // Kiek kartų pasikartoja

            if(i==0) {daug_kartojasi=kartojasi; did_amzius=V[0];}
            if(kartojasi>daug_kartojasi) {daug_kartojasi=kartojasi; did_amzius=V[i];}
        }
        fr<<"\nDaugiausia kartų pasikartoja vaikinų amžius: "<<did_amzius;
    }
    // Merginos
    if(msk>0)
    {
        fr<<"\n\nMerginų amžiaus vidurkis: "<<(amziu_suma-v_amziu_suma)/msk;

        // Jauniausios merginos paieška, rikiavimas didėjimo tvarka
        for(i=0;i<msk-1;i++)
            for(j=i+1;j<msk;j++)
                if(V[i]>V[j]) swap(M[i],M[j]);

        fr<<"\nJauniausiai merginai metų: "<<M[0];

        // Koks merginų amžius pasikartoja daugiausia kartų
        for(i=0;i<msk;i++)
        {
            kartojasi=1;
            for(j=i+1;j<msk;j++) {if(M[i]==M[j]) kartojasi++; else break;} // Kiek kartų pasikartoja

            if(i==0) {daug_kartojasi=kartojasi; did_amzius=M[0];}
            if(kartojasi>daug_kartojasi) {daug_kartojasi=kartojasi; did_amzius=M[i];}
        }
        fr<<"\nDaugiausia kartų pasikartoja merginų amžius: "<<did_amzius;
    }

    fd.close();
    fr.close();
    return 0;
}
