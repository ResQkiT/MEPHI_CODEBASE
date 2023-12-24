#include <stdio.h>
#include <stdbool.h>
#define DAYS_IN_YEAR = 365

bool isVesocosniy(int year){
    if(year % 400 == 0){
        return true;
    }else if(year%100 == 0){
        return false;
    }else if(year % 4 == 0){
        return true;
    }else{
        return false;
    }
    return;
}

int getDays(int year, int month, int day){
    int k , k2;
    if (isVesocosniy(year))
    {
        k2 = 60;
    }else{
        k2 = 59;
    }
    
    switch (month)
    {
    case 1:
        k = day;
        break;
    case 2:
        k = 31 + day;
    case 3:
        k = k2 + day;
        break;
    case 4:
        k = k2 + 31 + day;
        break;    
    case 5:
        k = k2 + 61 + day;
        break;
    case 6:
        k = k2 + 92 + day;
        break;
    case 7:
        k = k2 + 122 + day;
        break;
    case 8:
        k = k2 + 153 + day;
        break;
    case 9:
        k = k2 + 184 + day;
        break;
    case 10:
        k = k2 + 214 + day;
        break;
    case 11:
        k = k2 + 245 + day;
        break;
    case 12:
        k = k2 + 275 + day;
        break;
    }
    return k;
}

int main(void) {
    int d1 , m1, y1;
    int d2, m2, y2;
    scanf("%i %i %i", &d1, &m1,&y1);
    scanf("%i %i %i", &d2, &m2,&y2);
    int k;
    if(y1 == y2){
        k = getDays(y2, m2, d2) - getDays(y1, m1, d1) - 1;
    }else if(y2 - y1 == 1){
        if(isVesocosniy(y1)){
            k = 366 - getDays(y1, m1, d1) + getDays(y2, m2 , d2);

        }else{
            k = 365 - getDays(y1, m1, d1) + getDays(y2, m2 , d2) - 1;
        }
    }else{
        if(isVesocosniy(y1) ){
            k = 366 - getDays(y1, m1, d1) + getDays(y2, m2 , d2) - 1;

        }else{
            k = 365 - getDays(y1, m1, d1) + getDays(y2, m2 , d2) - 1;
        }
    }
    for(int i = y1 + 1; i < y2; i++){
        if(isVesocosniy(i)){
            k += 366;
        }else{
            k += 365;
        }
    }
    printf("%i", k);

}