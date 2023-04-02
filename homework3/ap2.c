#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5];
    int *plist[5];

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int));

    // list[0]은 list의 첫번째 인덱스에 있는 값으로 10이 출력된다.
    printf("list[0] \t= %d\n", list[0]);
    // list, &list, list+0 모두 list의 첫번째 주소값을 가리킨다.
    printf("list \t\t= %p\n", list);
    printf("&list[0] \t= %p\n", &list[0]);
    printf("list + 0 \t= %p\n", list+0);
    // list +1,+2,+3,+4는 list의 0번 인덱스에서 int값만큼 떨어져있으므로
    // list+1은 0번에서 4bytes떨어지고 list+2는 0번에서 8bytes 떨어져 주소값이 4bytes씩 차이난다.
    printf("list + 1 \t= %p\n", list+1);
    printf("list + 2 \t= %p\n", list+2);
    printf("list + 3 \t= %p\n", list+3);
    printf("list + 4 \t= %p\n", list+4);
    // &list[4]는 4번째 인덱스의 주소이므로 list+4와 같은값이다.
    printf("&list[4] \t= %p\n", &list[4]);

    free(plist[0]); // malloc을 free해준다.

    printf("[----- [한상준] [2017018024] -----]");
}