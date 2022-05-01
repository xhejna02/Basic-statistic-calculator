#include <stdio.h>
#include  <ctype.h>
#include <string.h>
#include <stdlib.h>

int getTextLenght(char* text)
{

    int result = 0;
    char* znak;
    znak = text;

    for (znak ; *znak != NULL; znak++)
    {
            result++;
    }


    return result;

}

int getWords(char* text)
{

    int result = 0;
    char *pch;
    pch = strtok(text, " ,.");
    while (pch != NULL)
    {
        result++;
        pch = strtok(NULL, " ,.");
    }



    return result;
}

int getPocetPismen(char* text, int pocetSlov, FILE* vystup)
{




    int i = 0;
    int vyska = 0;
    int pocetPismen[pocetSlov];
    char *pch;
    pch = strtok(text, " ,.");

    int pocetPismenSlova[pocetSlov];

    while (pch != NULL)
    {
        pocetPismen[i] = strlen(pch);
        if (i < pocetSlov - 1)
            pocetPismenSlova[i] = pocetPismen[i];
        else
            pocetPismenSlova[i] = pocetPismen[i] - 1;
        if (pocetPismenSlova[i] > vyska)
            vyska = pocetPismenSlova[i];
        pch = strtok(NULL, " ,.");
        i++;
    }
    fprintf(vystup, "       Histogram delek slov\n");

    for (vyska; vyska > 0; vyska--)
    {
        fprintf(vystup,"%4d - ", vyska);
        for (i = 0; i < pocetSlov; i++ )
        {
            if (pocetPismenSlova[i] < vyska)
                fprintf(vystup,"    ");
            else
                fprintf(vystup,"[*] ");
        }
        fprintf(vystup,"\n");
    }
    fprintf(vystup,"Slovo: ");
    for (i = 0; i < pocetSlov; i++)
        fprintf(vystup,"[%d] ", i + 1);



    return 0;
}

