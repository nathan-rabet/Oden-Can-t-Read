#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 2;
    int *p1 = &a;
    int *p2 = p1;

    printf("%d\n",*p2);
}