#include <stdio.h>
#include <limits.h>

long int F(int n, int m);

int main() {
    int n, m;
    
    scanf("%d %d", &n, &m);
    
    long int result = F(n, m);
    
    if (result == LONG_MAX) {
        printf("overflow\n");
    }
    else {
        printf("%ld\n", result);
    }
    return 0;
}

long int F(int n, int m) {
    if (n % 2 == 0) {
        return n/2;
    }
    else if (n == 1) {
        return m;
    }
    else {
        long long result = F(((n + 1)/2), m+1);
        if (result - LONG_MAX > 0 ) {
            return LONG_MAX;
        }
        else {
            return result;
        }
    }
}