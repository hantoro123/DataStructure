#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5];
    int *plist[5] = {NULL,};

    plist[0] = (int *)malloc(sizeof(int));

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;

    // list[0]은 list의 0번 인덱스에 들어있는 값 1이고
    // &list[0], list, &list 모두 list의 시작 주소로 같은 주소값을 출력한다.
    printf("list[0]           =%d\n", list[0]);
    printf("&list[0]          =%p\n", &list[0]);
    printf("list              =%p\n", list);
    printf("&list             =%p\n", &list);

    printf("------------------------------------\n\n");

    // list[1]과 *(list + 1)은 list의 1번 인덱스에 들어있는 값 100이고
    // &list[1], list+1 모두 list의 1번 인덱스 주소로 같은 주소값을 출력한다.
    printf("list[1]           =%d\n", list[1]);
    printf("&list[1]          =%p\n", &list[1]);
    printf("*(list+1)         =%d\n", *(list + 1));
    printf("list+1            =%p\n", list+1);

    printf("------------------------------------\n\n");
    
    // *plist의 0번 인덱스에 담긴 주소에 존재하는 값 200을 출력하고
    // &plist, &plist, plist 모두 plist의 시작 주소로 같은 주소값을 출력한다.
    // plist[0], plist[1], plist[2], plist[3], plist[4]은 각 인덱스에 들어있는 주소값이 출력되면
    // plist[0]만 값이 존재하여 츌력하고 나머지는 NULL값을 가져 0을 출력한다. 
    printf("plist[0]           =%d\n", *plist[0]);
    printf("&plist[0]          =%p\n", &plist[0]);
    printf("&plist             =%p\n", &plist);
    printf("plist              =%p\n", plist);
    printf("plist[0]           =%p\n", plist[0]);
    printf("plist[1]           =%p\n", plist[1]);
    printf("plist[2]           =%p\n", plist[2]);
    printf("plist[3]           =%p\n", plist[3]);
    printf("plist[4]           =%p\n", plist[4]);

    free(plist[0]); //malloc을 free 해준다.
}