#include <stdio.h>
int main(void) {
    float a, b;
    scanf("%f %f", &a, &b);
    float c = a * b;
    printf("%.3f", c);
}