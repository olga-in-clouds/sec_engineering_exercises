#include <stdio.h>
static void show(int i, int *ptr);
int main(){
   int x = 5;
   char y = 'S';
   int *xptr = &x;
   char *yptr = &y;

   printf("------ MAIN ------\n");
   printf("Value of x is: %d and it is stored at %p.  \n", x, &x);
   printf("Xptr points to %p which holds %d.\n", xptr, *xptr);
   show(x, xptr);
   printf("Value of y is: %c \n", y);
   printf("The address y is %p\n", &y);

   return 1;
}

void show(int z, int *zptr){
        printf("--> I am now in the function shod:\n");
        printf("The value of z is %d and it is stored at %p\n", z, &z);
        printf("zptr points to %p which holds value %d.\n", zptr, *zptr);
}