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

int fibonacci(int n) {
    if(n == 0) return 0;
    else if(n == 1) return 1;

    int res = (fibonacci(n-1) + fibonacci(n-2));

    return res;
}

/**
*@brief 快速计算幂
*
*@param int a, int n    a^n
*
*@return size_t         结果
*/ 
size_t quick_pow(int a, int n) {
    int res = 1;
    if(n == 0) {
        return 1;
    }else if(n % 2 == 1) {
        res = a * quick_pow(a, n-1);
    }else {
        int temp = quick_pow(a, n/2);
        res = temp * temp;
    }

    return res;
}

int main(int argc, char const* argv[])
{
    // int sums = sum(9);
    // printf("%d \n", sums);
    // int sim_sums = stack_sim_recurson(9);
    // printf("%d \n", sim_sums);

    
    // int res_fib = fibonacci(0);
    // printf("%d", res_fib);

    size_t res_q_pow = quick_pow(2, 4);
    printf("%zu", res_q_pow);

    return 0;
}