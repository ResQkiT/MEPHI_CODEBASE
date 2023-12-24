#include <stdio.h>
#include <math.h>
void zapolnit(int m1[],int n,int a1, int b1){
    int i;
    for (i=0;i<n;i++){
        m1[i]=a1*(i-b1);
    }
}
void vivod(int m1[],int n){
    int i;
    for (i=0; i<n;i++){
        printf("%5d",i+1);
    }
    printf("\n");
    for (i=0;i<n;i++){
        printf("%5d",m1[i]); 
    }
    printf("\n");
}
void peremeshka(int m1[],int n, int m2[], int j, int k){
    int i,p;
    for (i=0;i<=k;i++){
        p = m1[i];
        m1[i] = m2[j - i -1];
        m2[j - i -1] = p;
    } 
}
int main()
{
    int m1[14], m2[10],a1,b1,a2,b2,k;
    scanf("%d%d",&a1,&b1);
    scanf("%d%d",&a2,&b2);
    scanf("%d",&k);
    zapolnit(m1,14,a1,b1);
    vivod(m1,14);
    printf("\n");
    zapolnit(m2,10,a2,b2);
    vivod(m2,10);
    printf("\n");
    peremeshka(m1,14,m2,10,k);
    vivod(m1,14);
    printf("\n");
    vivod(m2,10);
    printf("\n");
    peremeshka(m2,10,m1,14,k);
    vivod(m1,14);
    printf("\n");
    vivod(m2,10);
    return 0;
}