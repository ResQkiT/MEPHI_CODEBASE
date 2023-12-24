#include <stdio.h>
int getLast(int a){
    int last = 0;
    for(int k = 2 ; k<a; k++){
        if(a%k == 0){
            last = k;
        }       
    }
    return last;
}
int main(void) {
    int maxC = 0;
    int maxCount = 0;
    for(int i = 440; i<=470; i++){
        printf("%i  ", i);
        int z = 0;
        for(int k = 2 ; k<i; k++){
            if(i%k == 0){
                if (k != getLast(i))
                {
                    printf("%3i," , k);
                }else{
                    printf("%3i" , k);
                }
                z++;
            }else{
                continue;
            }        
            if(z % 4 == 0  && getLast(i) != k){
                printf("\n");
                printf("     ");
            }
        }
        if(z >= maxCount){
            maxC = i;
            maxCount = z;
        }
        int ost = z % 4;
        if (z == 0)
        {
            ost = 0;
        }else if (ost == 0)
        {
            ost = 4;
        }
        int online = 5 + 3 * ost + ost - 1 + (ost == 0 );
        for(int r = online; r <=20; r++ ){
            printf(" ");
        }
        printf("%5i\n",z);

    }
    printf("\n");
    printf("%i\n", maxC);
}