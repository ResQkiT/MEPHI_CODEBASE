#include "matrix.h"

void setInteger(void* , int , int , void *);
int getInteger(void* , int  , int );
FieldInfo INTEGER_IMPL  = {setInteger, getInteger , sizeof(int)};