#include <stdio.h>

int main() {
    int x = 100 ;
    printf("%d\n", x); // print x value
    printf("%p\n", &x); // print x address
    printf("%d\n", *(&x)); 
    return 0;
}