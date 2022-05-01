#include <stdio.h>
#include "numbers.h"
#include "numbers.c"
#include <string.h>
#include "text.h"
#include <ctype.h>

#define NMAX 10000000
#define MAX_TEXT 1000
#define MAX_PATH 100

struct counter_pair { //struktura pro histogram pismen
    int symbol_code;
    int symbol_count;
};

int compar(const void *a, const void *b) {
    struct counter_pair *p1 = (struct counter_pair *) a;
    struct counter_pair *p2 = (struct counter_pair *) b;

    if (p1->symbol_count < p2->symbol_count)
        return -1;
    else if (p1->symbol_count > p2->symbol_count)
        return 1;
    else
        return 0;
}


int main() {

    int vyber;
    printf("Zadejte:\n1 - pro zpracovani ciselnych hodnot\n2 - pro statisticke vypocty nad textem\n3 - Informace o programu\n4 - konec programu\n");
    scanf("%d", &vyber);
    while (getchar() != '\n');




    if ( vyber == 1)
    {
        char cesta[MAX_PATH];
        printf("Zadejte cestu vystupniho souboru\n");
        scanf("%s", cesta);
        while (getchar() != '\n');
        const char* VysledkySouborCesta = "vystup";       //soubor a cesta
        FILE *vystup = fopen(cesta, "w");


        int i,j;
        int nn;

        printf("Zadejte pocet prvku:\n");
        scanf("%d",&nn);
        double numbers[nn];

        for (i=0; i<nn ; i++){
            printf("Zadejte %d cislo :\n", i+1 );
            scanf("%lf", &numbers[i]);

        }

        double numbersSorted[nn];

        for (i = 0; i < nn; i++)
            numbersSorted[i] = numbers[i];

        for(i = 0 ; i < nn - 1; i++) {
            for (j = 0; j < nn - i - 1; j++) {
                if (numbersSorted[j] > numbersSorted[j + 1]) {
                    int tmp = numbersSorted[j];
                    numbersSorted[j] = numbersSorted[j + 1];
                    numbersSorted[j + 1] = tmp;
                }
            }
        }
        double maxNumber;
        maxNumber = round(numbersSorted[i]);

        double average, vazAverage, rozptyl, odchylka;
        average = getAverage(numbers, nn);
        vazAverage = getVazenyAverage(numbers, nn);
        rozptyl = getRozptyl(numbers, nn, average);
        odchylka = getOdchylka(rozptyl);
        fprintf(vystup,"Prumer %0.2lf\n", average);
        fprintf(vystup,"Vazeny prumer %0.2lf\n", vazAverage);
        fprintf(vystup,"Rozptyl se rovna %0.2lf\n", rozptyl);
        fprintf(vystup,"Odchylka se rovna %0.2lf\n", odchylka);
        fprintf(vystup,"Median se rovna : %0.2lf\n", getMedian(numbersSorted,nn));

        tiskHistogram(numbers,nn, maxNumber, vystup );

        double* seq;

        srand((unsigned int)time(NULL)); //cislo pro gaussovo rozlozeni

        if ( (seq = generate(NMAX)) != NULL ) {
            printf("    Gaussovo rozlozeni :\n");
            printGaus(seq, NMAX);
            free(seq);
            getchar();
        }

        fclose(vystup);

    } else if (vyber == 2) {

        char cesta[MAX_PATH];
        printf("Zadejte cestu vystupniho souboru\n");
        scanf("%s", cesta);
        while (getchar() != '\n');


        FILE *vystup = fopen(cesta, "w");

        if (vystup == NULL)
            printf("ERROR: CANT OPEN THAT FILE\n");



        int i,j, len, ch = 0;
        char* rc;
        struct counter_pair cp[256];        //struktura pro histogram pismen
        for (j=0; j<256; j++) {
            cp[j].symbol_code = j;
            cp[j].symbol_count = 0;
        }

        int pocetZnaku, pocetSlov;
        char text[MAX_TEXT], textCopy[MAX_TEXT];

        printf("Zadejte:\n1 - pro vstup ze souboru\n2 - pro vstup z konzoly\n");
        scanf("%d", &ch);
        while (getchar() != '\n');

        if (ch == 1)
        {
            char VstupSouborCesta[MAX_PATH];
            printf("Zadejte cestu vystupniho souboru\n");
            scanf("%s", VstupSouborCesta);
            while (getchar() != '\n');

            FILE *vstup = fopen(VstupSouborCesta, "r");
            rc = fgets(text, MAX_TEXT, vstup);
        }
        else
        {
            rc = fgets(text, MAX_TEXT, stdin);// textovy vstup
        }

        for (i = 0; i < MAX_TEXT; i++) {
            text[i] = tolower(text[i]);
            textCopy[i] = text[i];
        }
        len = strlen(text);

        for (j=0; j<len; j++)                       // zapis znaku do struktur
            cp[ text[j] ].symbol_count += 1;



        pocetZnaku = getTextLenght(text);
        pocetSlov = getWords(text);

        int symbolMax = 0;


        fprintf(vystup, "       Histogram pismen\n");
        for (j=0; j<256; j++) {                      // nachazi vysku histogramu
            if (cp[j].symbol_count != 0) {
                if (cp[j].symbol_count > symbolMax)
                    symbolMax = cp[j].symbol_count;
            }
        }

        for ( j = symbolMax; j > 0; j--)             //tiskuje histogram
        {
            fprintf(vystup,"%4d - ", j);
            for ( i = 0; i< 256; i++)
            {
                if(cp[i].symbol_count != 0) {
                    if (cp[i].symbol_count >= j && isalpha(cp[i].symbol_code) != 0)
                        fprintf(vystup," [*] ");
                    else if (isalpha(cp[i].symbol_code) != 0)
                        fprintf(vystup,"     ");
                }
            }
            fprintf(vystup,"\n");
        }

        fprintf(vystup,"pismeno");
        for ( i = 0; i < 256; i++) {
            if (cp[i].symbol_count != 0  && isalpha(cp[i].symbol_code) != 0)
                fprintf(vystup," [%c] ", cp[i].symbol_code);
        }




        fprintf(vystup,"\nPocet znaku: %d\n", pocetZnaku -1 );
        fprintf(vystup,"Pocet slov: %d\n", pocetSlov);
        getPocetPismen(textCopy,pocetSlov, vystup );

        fclose(vystup);

    } else if ( vyber == 3) {
        printf("Statisticka kalkulacka\nVytvorili Gibor & Hejna\n2019 VUT Brno");
    } else if ( vyber == 4) {
        return 0;
    } else {

        printf("Zadana spatna hodnota\n");
    }
    printf("\n\nPress Any key to exit\n");
    getchar();


}
