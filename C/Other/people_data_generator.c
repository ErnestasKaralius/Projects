#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define OUTPUT_SIZE 10000

int main()
{
    srand(time(NULL));

    char male_names[][30] = {
        "Adolfas", "Alvydas", "Alfonsas", "Aurimas", "Aurelijus", "Aleksandras", "Algirdas", "Algimantas", "Algis", "Andrius", "Antanas",
        "Arturas", "Arunas", "Augustinas", "Azuolas", "Balys", "Bronislovas", "Benediktas", "Baris", "Dziugas", "Danielius",
        "Darius", "Dovydas", "Domantas", "Gediminas", "Jonas", "Juozas", "Jurgis", "Jurius", "Justas", "Kazimieras",
        "Karolis", "Kazys", "Kipras", "Konstantinas", "Kestas", "Kestutis", "Kazys", "Tadas", "Lukas", "Leonas", "Laurynas",
        "Linas", "Lingaudas", "Marijus", "Mikalojus", "Mindaugas", "Motiejus", "Mykolas", "Martynas", "Mantas", "Mantvinas", "Naglis",
        "Paulius", "Petras", "Povilas", "Pijus", "Ramunas", "Ringaudas", "Remigijus", "Rolandas", "Rytis", "Rusnius",
        "Rimas", "Simonas", "Stasys", "Steponas", "Saulius", "Sigitas", "Svajunas", "Valdas", "Vladas", "Vygantas",
        "Vytautas", "Vincas", "Zydrunas", "Zygimantas", "Zilvitis", "Edgaras", "Sarunas", "Grinvydas", "Giedrius", "Gintaras",
        "Eimantas", "Evaldas", "Ovidijus", "Osvaldas", "Ignas", "Ugnius"
    };

    char male_surnames[][30] = {
        "Adamkus", "Almenas", "Avizienis", "Baltrusaitis", "Brazauskas", "Basanavicius", "Bistras", "Birutis", "Balciunas",
        "Braziunas", "Butkus", "Ciurlionis", "Danauskas", "Dauksa", "Daukantas", "Dobkevicius", "Dubeneckis", "Girenas", "Galdikas",
        "Grinius", "Grybauskas", "Griskevicius", "Gudaitis", "Gustaitis", "Ivanauskas", "Juknevicius", "Jablonskis",
        "Jasikevicius", "Jankauskas", "Jucys", "Kairys", "Krupavicius", "Karalius", "Kacinskas", "Kazlauskas", "Karvelis",
        "Kubilius", "Landsbergis", "Lozoraitis", "Labanauskas", "Mikutavicius", "Merkys", "Paksas", "Paleckis", "Poskus",
        "Paulauskas", "Petrauskas", "Piskarskas", "Rapsys", "Radvila", "Sabaniauskas", "Simonavicius", "Sirvydas", "Slezevicius",
        "Smetona", "Snieckus", "Steponavicius", "Staugaitis", "Straizys", "Stulginkis", "Terleckas", "Urbsys", "Vagnorius", "Valeska",
        "Voldemaras", "Vileisis", "Urbonavicius", "Zuokas", "Zilinskas", "Sidlauskas"
    };

    char professions[][30] = {
        "Inzinierius", "Gydytojas", "Chirurgas", "Aktorius", "Aviatorius", "Dispeceris", "Fotografas", "Gidas", "Girininkas", "Jureivis",
        "Korepetitorius", "Karininkas", "Mesininkas", "Mokslininkas", "Pastininkas", "Pienininkas", "Policininkas", "Ugniagesys", "Redaktorius",
        "Rastvedys", "Rasytojas", "Sportininkas", "Sekretorius", "Stalius", "Tyrejas", "Ukininkas", "Vertejas", "Virejas", "Mokytojas",
        "Radiologas", "Elektrikas", "Detektyvas", "Programuotojas", "Akuseris", "Skulptorius", "Zvejys", "Sokejas", "Santechnikas", "Prodiuseris",
        "Murininkas", "Medziotojas", "Konsulas", "Kiemsargis", "Gelininkas", "Geografas", "Istorikas", "Geofizikas", "Fokusininkas", "Fizikas",
        "Energetikas", "Destytojas", "Dazytojas", "Biofizikas", "Informatikas", "Biografas", "Biochemikas", "Aukletojas", "Akrobatas"
    };

    char languages[][30] = {
        "Latvi??", "Est??", "Rus??", "Lenk??", "Ukrainie??i??", "Vokie??i??", "Pranc??z??", "Ispan??", "Angl??", "Airi??", "??ved??", "Suomi??",
        "Dan??", "Norveg??", "Island??", "??ek??", "Slovak??", "Nyderland??", "Fryz??", "Graik??", "Serb??", "Slov??n??", "Kroat??", "Alban??", "Vengr??",
        "Rumun??", "Gruzin??", "Arm??n??", "Turk??", "Katalon??", "Portugal??", "Kin??", "Japon??", "Vietnamie??i??", "Kor??jieci??", "Taj??", "Bask??",
        "Arab??", "Baltarusi??", "??emai??i??", "Lotyn??", "Oksitan??", "Rom??", "Limburgie??i??", "Liuksemburgie??i??", "Jidi??", "Bosni??", "Korsikie??i??",
        "Bulgar??", "Rus??n??", "Sard??", "Sicilie??i??", "Karaim??", "Makedon??", "Ital??", "Azerbaid??anie??i??", "??kot??", "Val??", "Urdu", "Bengal??",
        "Pand??ab??", "Tamil??", "Marath??", "Esperanto", "Hindi", "Nepal??", "Sindh??", "Udmurt??", "Komi??", "Veps??", "Karel??", "Mansi??", "Chant??",
        "Bavar??", "??e????n??", "Galis??", "??iuva????", "Ba??kir??", "Juodkalnie??i??", "Kurd??", "Somali??", "Pers??", "Uzbek??", "Kazach??", "Turkm??n??",
        "Kirgiz??", "Tad??ik??", "Tuvi??", "Karakalpak??", "Orom??", "Jorub??", "Igb??", "Ful??", "Amhar??", "Malagasi??", "Akan??", "Zul??", "Afrikan??"
    };

    FILE *output_file;
    output_file = fopen("GeneratedData.txt", "w");

    for(int i = 0; i < OUTPUT_SIZE; ++i)
    {
        char known_languages[100] = "";
        for(int j = 0; j < 1 + rand() % 5; ++j)
        {
            int language_not_inserted = 1;
            while(language_not_inserted)
            {
                char temp_language[30];
                strcpy(temp_language, languages[rand() % 98]);

                if(!strstr(known_languages, temp_language))
                {
                    strcat(known_languages, temp_language);
                    int length = strlen(known_languages);
                    known_languages[length] = ' ';
                    known_languages[length + 1] = '\0';

                    language_not_inserted = 0;
                }
            }
        }

        fprintf(output_file, "%-15s %-15s %-15s %-5d %s\n", male_names[rand() % 89], male_surnames[rand() % 70], professions[rand() % 58], 18 + rand() % 63, known_languages);
    }

    fclose(output_file);

    return 0;
}
