#include "matrix.h"
typedef struct 
{
    double re;
    double im;
}Complex;

void setComplex(void* , int , int , void *);
void getComplex(void* , int  , int );
extern FieldInfo INTEGER_IMPL  = {setComplex, getComplex , sizeof(int)};