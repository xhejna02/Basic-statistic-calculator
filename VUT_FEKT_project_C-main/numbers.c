#include <stdio.h>
double getAverage( double numbers[], int nn);
double getVazenyAverege( double numbers[], int nn);
double getRozptyl( double numbers[], int nn, double average);
double getOdchylka( double rozptyl);
double getMedian( double numbers[], int nn);
void tiskHistogram(double numbers[], int nn, double max, FILE* vystup );
double mean(double* values, int n);
double stddev(double* values, int n);
double* generate(int n);
void printGaus(double* values, int n);

