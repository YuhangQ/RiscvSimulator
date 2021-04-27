#include <stdio.h>
int main() {
    /*
    int sum = 0;
    for(int i=1; i<=100; i++) {
        sum += i;
    }
    */
    int ans = 0;
    for(int i=1; i<=10; i++) {
        ans += i * i;
    }
    printf("%d\n", ans);
    return 0;
}