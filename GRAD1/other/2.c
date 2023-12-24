#include <math.h>
#include <stdio.h>
#include <limits.h>
int main()
{
    int k;
    scanf("%d",&k);
    long sum=0;
    int n=0;
    int flag=0;
    int znak=2;
    long rez;
    while (1){
        n+=1;
        for(int i=1;i<2*k;i+=2){
            //printf("%d", i);
            if (sum<=LONG_MAX-pow(i,k)){
                sum+=pow(i,n);
            }
            else if (0>LONG_MAX-pow(i,k)){
                znak=1;
                flag=1;
                break;
            }
            else if(sum>LONG_MAX-pow(i,k)){
                znak=0;
                flag=1;
                break;
            }
        }
        if (flag!=1){
            rez=sum;
            sum=0;
        }
        else{
            printf("%ld\n",rez);
            printf("%d\n",n-1);
            if (znak==1){
                printf("*\n");
            }
            else{
                printf("+\n");
            }
            break;
        }
        
    }
    return 0;
}
