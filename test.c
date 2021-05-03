#include <stdio.h>

int hello() {
    return 1;
}
int main() {
    int ans = 0;
    for(int i=1; i<=10; i++) {
        ans += i * i;
    }

    ans += hello();
    return 0;
}