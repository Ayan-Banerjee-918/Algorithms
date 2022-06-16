/*find the only 10th digit number where the ith position from left specifies the number of occurrences of i in the number*/

#include <stdio.h>
#include <stdlib.h>

int* findNumber(int* number,int n) {
    int i = 0;
    int* cnt = (int*)calloc(10, sizeof(int));
    number[0] = n;
    cnt[0] = n;
    number[n]++;
    n = number[n];
    cnt[n]++;
    while (number[n] == 0) {
        cnt[0]--;
        number[n]++;
        cnt[n]++;
        n = number[n];
        if (number[n] != cnt[n]) {
            if (number[n] - 1 == 0) {
                cnt[0]--;
            }
            number[n] = cnt[n];
            n = number[n];
        }
    }
    number[number[0]]--;
    number[0] = cnt[0];
    number[cnt[0]] += 1;
    return number;
}

void main() {
    int* number = (int*)calloc(10, sizeof(int));
    int n = 9;
    number = findNumber(number,n);
    printf("The number is : ");
    for (n = 0; n < 10; n++) {
        printf("%d", number[n]);
    }
    printf("\n");
}