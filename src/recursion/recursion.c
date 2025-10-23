#include <stdio.h>

int sum(int n) {
    if(n == 1) return 1;
    
    int res = sum(n-1);

    return n + res;
}

int stack_sim_recurson(int n) {
    int stack[1000];
    int top = -1;
    int res = 0;
    
    // 模拟入栈 --递
    for(int i = 1; i <= n; ++i) {
        // int index = i + ++top;
        stack[1 + top++] = i;
    }
    
    // 模拟出栈 --归
    for(int i = n; i > 0; --i) {
        res += stack[i-1];
    }

    return res;
}

int main(int argc, char const* argv[])
{
    int sums = sum(9);
    printf("%d \n", sums);
    int sim_sums = stack_sim_recurson(9);
    printf("%d \n", sim_sums);

    return 0;
}