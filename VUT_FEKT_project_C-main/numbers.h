#include "numbers.c"
#include <math.h>
#include  <ctype.h>
#include <stdlib.h>
#include <time.h>

double getAverage( double numbers[], int nn)
{
    int i;
    double sum = 0;
    double average;
    for (i = 0; i < nn; i++){
        sum = sum + numbers[i];
    }
    average = sum / (double)nn;

    return average;
};

double getVazenyAverage(double numbers[], int nn)
{
    int i;
    double devider = 0;
    double sum = 0;
    double average;
    double koef[nn];
    for ( i = 0; i < nn; ++i){
        printf("Zadejte vahu %d cisla\n", i + 1);
        scanf("%lf", &koef[i]);
    }

    for (i = 0; i < nn; i++){
        sum = sum + (koef[i] * numbers[i]);

        devider = devider + koef[i];
    }
    average = sum / devider;
    return average;
}

double getRozptyl(double numbers[], int nn, double average)
{
    int i;
    double   x;
    double sum = 0;
    double result;
    for (i = 0; i < nn; i++){
        x = numbers[i] - average;
        sum = sum + pow(x,2);
    }
    result = sum / (double)nn;
    return result;

}

double getOdchylka(double rozptyl)
{
    double result = 0;
    if (rozptyl >= 0)
    result = sqrt(rozptyl);
    return result;
}

double getMedian( double numbers[], int nn)
{
    int i, j;
    double median, result;


    int average;
    average = (nn - 1)/2;
    if ( nn % 2 == 0 ) {    //kontrola sudost/lichost počtu prvku
        median = numbers[average] + numbers[average + 1];
        result = median / 2;
    } else {
        result = numbers[average];      //prumer dvou cisel, kt jsou uprostred
    }

    return result;
}

void tiskHistogram(double numbers[], int nn, double max , FILE* vystup)
{
    int i;
    int vyska = max ;
    printf("    Histogram zadanych hodnot\n");
    fprintf(vystup,"    Histogram zadanych hodnot\n");
    for (i = 0; i < nn + 4; i++) {
        fprintf(vystup, "####");
        printf("####");
    }
    printf("\n");
    fprintf(vystup,"\n");
    for (vyska; vyska > 0; vyska--)
    {
        printf("|$| %5d - ", vyska);
        fprintf(vystup,"|$| %5d - ", vyska);
        for (i = 0; i < nn; i++ )
        {
            if (numbers[i] < vyska) {
                printf("    ");
                fprintf(vystup, "    ");
            }
            else {
                fprintf(vystup, "[*] ");
                printf("[*] ");
            }
        }
        printf(" |$|\n");
        fprintf(vystup," |$|\n");
    }
    printf("|$|  Prvek: ");
    fprintf(vystup,"|$|  Prvek: ");
    for (i = 0; i < nn; i++) {
        printf("[%d] ", i + 1);
        fprintf(vystup, "[%d] ", i + 1);
    }
    printf(" |$|\n");
    fprintf(vystup," |$|\n");


    for (i = 0; i < nn + 4; i++) {
        printf("####");
        fprintf(vystup, "####");
    }
    fprintf(vystup,"\n");
    printf("\n");
}


double mean(double* values, int n)  //prumer pro gauss
{
    int i;
    double s = 0;

    for ( i = 0; i < n; i++ )
        s += values[i];
    return s / n;
}


double stddev(double* values, int n)        //rozptyl pro gauss
{
    int i;
    double average = mean(values,n);
    double s = 0;

    for ( i = 0; i < n; i++ )
        s += (values[i] - average) * (values[i] - average);
    return sqrt(s / (n - 1));
}


double* generate(int n)         //generace cisel pro gauss
{
    int i;
    int m = n + n % 2;
    double* values = (double*)calloc(m,sizeof(double));
    double average, deviation;

    if ( values )
    {
        for ( i = 0; i < m; i += 2 )
        {
            double x,y,rsq,f;
            do {
                x = 2.0 * rand() / (double)RAND_MAX - 1.0;
                y = 2.0 * rand() / (double)RAND_MAX - 1.0;
                rsq = x * x + y * y;
            }while( rsq >= 1. || rsq == 0. );
            f = sqrt( -2.0 * log(rsq) / rsq );
            values[i]   = x * f;
            values[i+1] = y * f;
        }
    }
    return values;
}


void printGaus(double* values, int n)          //tisk gauss
{
    const int width = 50;
    int max = 0;

    const double low   = -3.05;
    const double high  =  3.05;
    const double delta =  0.1;

    int i,j,k;
    int nbins = (int)((high - low) / delta);
    int* bins = (int*)calloc(nbins,sizeof(int));
    if ( bins != NULL )
    {
        for ( i = 0; i < n; i++ )
        {
            int j = (int)( (values[i] - low) / delta );
            if ( 0 <= j  &&  j < nbins )
                bins[j]++;
        }

        for ( j = 0; j < nbins; j++ )
            if ( max < bins[j] )
                max = bins[j];

        for ( j = 0; j < nbins; j++ )
        {
            printf("(%5.2f, %5.2f) |", low + j * delta, low + (j + 1) * delta );
            k = (int)( (double)width * (double)bins[j] / (double)max );
            while(k-- > 0) putchar('*');
            printf("  %-.1f%%", bins[j] * 100.0 / (double)n);
            putchar('\n');
        }

        free(bins);
    }
}