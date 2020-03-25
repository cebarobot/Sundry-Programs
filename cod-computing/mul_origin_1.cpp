#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const char dot_char = '.';

void print_binary(unsigned int x, int len, bool print_dot, int print_plus, bool underline) {
    if (len == 0) {
        printf("$\\quad$");
        return;
    }
    printf("$");
    if (print_plus == 1) {
        printf("+");
    } else if (print_plus == 2) {
        printf("\\phantom{+}");
    }
    char str[100];
    for (int i = 0; i < len; i++) {
        str[i] = (x & 1) + '0';
        // printf("--%d\n", str[i]);
        x >>= 1;
    }
    for (int i = 0; i < len; i++) {
        if (underline && i == len - 1) {
            printf("\\underline{");
        }
        putchar(str[len - i - 1]);
        if (underline && i == len - 1) {
            printf("}");
        }
        if (print_dot && i == 0) {
            putchar(dot_char);
        }
    }
    printf("$");
}

unsigned b_link(unsigned x, unsigned y, int len_y) {
    return (x << len_y) | y;
}

unsigned b_high(unsigned x, int len_low) {
    return x >> len_low;
}

unsigned b_low(unsigned x, int len_low) {
    // printf("%X\n", (~((unsigned(~0) >> len_low) << len_low)));
    return x & (~((unsigned(~0) >> len_low) << len_low));
}

const char str_orgin[] =    "开始部分积为 $0$<br>";
const char str_add0[] =     "乘数为 $0$，加上 $0$";
const char str_add1[] =     "乘数为 $1$，加上 $x^*$";
const char str_shr[] =      "部分积、乘数 $\\to 1$ 位<br>";
const char str_empty[] =    "$\\quad$";

int main() {
    int nnn = 5;
    unsigned xxx = 27;
    unsigned yyy = 29;
    unsigned acc = 0;
    unsigned mq = yyy;
    printf("|部分积|乘数|说明|\n");
    printf("|:-|:-|:-|\n");
    
    bool add_flg = mq & 1;
    int add_next;
    unsigned accmq = b_link(acc, mq, nnn);

    // line 0
    printf("|");
    print_binary(0, nnn + 1, 1, 2, 0);
    printf("<br>");
    add_next = add_flg? xxx : 0;
    print_binary(add_next, nnn + 1, 1, 1, 0);
    printf("|");
    print_binary(mq, nnn, 0, 0, 1);
    printf("<br>");
    printf(str_empty);
    printf("|");
    printf(str_orgin);
    printf(add_flg ? str_add1 : str_add0);
    printf("|\n");

    for (int i = 1; i <= nnn; i++) {

        acc += add_next;

        unsigned accmq_old = b_link(acc, mq, nnn);
        unsigned acc_old = acc;
        unsigned mq_old = b_high(mq, nnn - i + 1);
        accmq = (accmq_old >> 1);
        acc = b_high(accmq, nnn);
        mq = b_low(accmq, nnn);
        add_flg = mq & 1;
        add_next = add_flg? xxx : 0;

        // col 1
        printf("|");
        print_binary(acc_old, nnn + 1, 1, 2, 0);
        printf("<br>");
        print_binary(acc, nnn + 1, 1, 2, 0);
        if (i != nnn) {
            printf("<br>");
            print_binary(add_next, nnn + 1, 1, 1, 0);
        }

        // col 2
        printf("|");
        print_binary(mq_old, i - 1, 0, 0, 0);
        printf("<br>");
        print_binary(mq, nnn, 0, 0, i != nnn);
        if (i != nnn) {
            printf("<br>$\\quad$");
        }
        // col 3
        printf("|<br>");
        printf(str_shr);
        if (i != nnn) {
            printf(add_flg ? str_add1 : str_add0);
        }
        printf("|\n");
    }

    return 0;
}