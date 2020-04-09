#include <unistd.h>
#include <stdio.h>
#define MIN -5
#define MAX 100
int sum(int a, int b) {return a + b;}
int main() {
int a = 5;for (int i = 0; i < 3; i++) {printf("Hello");}printf("sum: %d\n", sum(MAX, MIN));
}