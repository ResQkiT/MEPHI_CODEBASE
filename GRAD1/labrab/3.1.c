#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double function(double n){
    return sqrt(( 7 + cos(n)*cos(n) + sqrt(n) + 3*n*n*n)/ (5 + sqrt(n)+n*n*n));
}

int main()
{
    long int startInt = 20000000;
    long int endInt = 200000000;
    double prefSum = 0.0;
    double prefSumCorrect = 0.0;
    for(long int N = startInt; N<= endInt; N+= 20000000){
        double sum = prefSum;
        double S = prefSumCorrect, cor = 0.0, Scor = 0.0, fcor;

        for(int n = N-20000000 + 1; n <= N; n++){
            double temp = function(n);
            sum += temp;

            fcor = temp - cor;
            Scor = S + fcor;
            cor = (Scor - S) - fcor;
            S = Scor;
        }
        prefSum = sum;
        prefSumCorrect = S;

        printf("%9i%18.4f%18.4f%10.4f\n", N, prefSum, prefSumCorrect, sum - S);

    }
}
