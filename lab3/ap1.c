#include <stdio.h>
#include <stdlib.h>
void main()
{
    int list[5];
    int *plist[5] = {
        NULL,
    };
    plist[0] = (int *)malloc(sizeof(int));
    list[0] = 1;
    list[1] = 100;
    *plist[0] = 200;
    printf("list[0] = %d\n", list[0]);
    printf("&list[0] = %p\n", &list[0]);
    printf("list = %p\n", list);
    printf("&list = %p\n", &list);
    printf("----------------------------------------\n\n");
    printf("list[1] = %d\n", list[1]);
    printf("&list[1] = %p\n", &list[1]);
    printf("*(list+1) = %d\n", *(list + 1));
    printf("list+1 = %p\n", list + 1);
    printf("----------------------------------------\n\n");
    printf("*plist[0] = %d\n", *plist[0]);
    printf("&plist[0] = %p\n", &plist[0]);
    printf("&plist = %p\n", &plist);
    printf("plist = %p\n", plist);
    printf("plist[0] = %p\n", plist[0]);
    printf("plist[1] = %p\n", plist[1]);
    printf("plist[2] = %p\n", plist[2]);
    printf("plist[3] = %p\n", plist[3]);
    printf("plist[4] = %p\n", plist[4]);
    free(plist[0]);
}
