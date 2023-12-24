#include <stdio.h>
#include <stdlib.h>

void mas (int m[], int a, int b, int n){
    for (int i = 0; i!=n; i++){
        m[i] = a *(i - b);
    }
}

void print(int m[], int beg, int end_){
    for (int i=beg; i!=end_+1; i++){
        printf("%5d", i+1);
    }
    printf("\n");
    for (int i=beg; i!=end_+1; i++){
        printf("%5d", m[i]);
    }
    printf("\n");

}

void change(int m2[], int m1[], int k, int n2){
    int curr1, curr2;
    for (int i=0; i!=k; i++){
        curr2 = m2[n2-k+i];
        curr1 = m1[i];
        m2[n2-k+i] = curr1;
        m1[i] = curr2;
    }

}


int main()
{
    int a1,b1,a2,b2,k,n1,n2, beg1=0, beg2=0, end_1=13, end_2=9;

    n1 = 14;
    n2 = 10;
    int m1[14];
    int m2[10];
    scanf("%d%d%d%d%d", &a1, &b1 , &a2, &b2, &k);

    mas(m1, a1, b1, n1);
    mas(m2, a2, b2, n2);

    print(m1, beg1, end_1);
    printf("\n");
    print(m2, beg2, end_2);

    int mc1[14];
    for (int i = 0; i!=14; i++){
        mc1[i]=m1[i];
    }
    int mc2[10];
    for (int i = 0; i!=10; i++){
        mc2[i]=m2[i];
    }

    change(mc1, mc2, k, n1);

    //printf("1 ->\n");
    print(mc1, beg1, end_1);
    printf("\n");
    print(mc2, beg2, end_2);
    printf("\n");

    change(mc2, mc1, k, n2);
    //printf("2 ->\n");
    print(mc1, beg1, end_1);
    printf("\n");
    print(mc2, beg2, end_2);
    printf("\n");


    for (int i=0; i!=k; i++){
        int curr2, curr1;
        curr2 = mc1[14-k+i];
        curr1 = mc1[i];
        mc1[14-k+i] = curr1;
        mc1[i] = curr2;
    }
    printf("\n");
    print(mc1, beg1, end_1);
    printf("\n");
    print(mc2, beg2, end_2);
}
