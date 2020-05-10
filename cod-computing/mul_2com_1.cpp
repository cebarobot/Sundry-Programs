// 乘法：补码比较法 1 位乘
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

const char dot_char = '.';
const int dot_pos = 1;

string print_binary(unsigned int x, int len, bool print_dot, int print_plus, bool underline) {
    string out_string;
    if (len == 0) {
        out_string += "$\\quad$";
        return out_string;
    }
    out_string += "$";
    if (print_plus == 1) {
        out_string += "+";
    } else if (print_plus == 2) {
        out_string += "\\phantom{+}";
    }
    char str[100];
    for (int i = 0; i < len; i++) {
        str[i] = (x & 1) + '0';
        x >>= 1;
    }
    for (int i = 0; i < len; i++) {
        if (underline && i == len - 1) {
            out_string += "\\underline{";
        }
        out_string += str[len - i - 1];
        if (underline && i == len - 1) {
            out_string += "}";
        }
        if (print_dot && i == dot_pos) {
            out_string += dot_char;
        }
    }
    out_string += "$";
    return out_string;
}

unsigned b_high(unsigned x, int len_low) {
    return x >> len_low;
}

unsigned b_low(unsigned x, int len_low) {
    // printf("%X\n", (~((unsigned(~0) >> len_low) << len_low)));
    return x & (~((unsigned(~0) >> len_low) << len_low));
}

unsigned b_link(unsigned x, unsigned y, int len_y) {
    return (x << len_y) | b_low(y, len_y);
}

void print_line(string & col_acc, string & col_mq, string & col_cc, string & col_note) {
    printf("|%s|%s|%s|%s|\n", col_acc.c_str(), col_mq.c_str(), col_cc.c_str(), col_note.c_str());
    col_acc.clear();
    col_mq.clear();
    col_cc.clear();
    col_note.clear();
}

int main() {
    string ans_1, ans_2;
    printf("\n用**补码一位乘**（**Booth 算法**）计算：\n\n");

    string col_acc;
    string col_mq;
    string col_cc;
    string col_note;

    int xxx = 27;
    int yyy = -29;
    int nnn = 5;
    
    printf("依次输入xxx, yyy, nnn: ");
    scanf("%d %d %d", &xxx, &yyy, &nnn);
    // int xxx = 13;
    // int yyy = 11;
    // int nnn = 4;
    // int xxx = -23;
    // int yyy = -21;
    // int nnn = 6;

    // printf("$[x]_{补} = $，$[y]_{补} = $。\n\n");

    // printf("补码一位乘（Booth 算法）的运算过程：\n");

    printf("|部分积|乘数 $y_n$|附加位 $y_{n+1}$|说明|\n");
    printf("|:-|:-|:-|:-|\n");
    int acc = 0;
    int mq = yyy;
    int cc = 0;
    col_acc += print_binary(acc, nnn + 2, 1, 2, 0);
    col_acc += "<br>";
    col_mq += print_binary(mq, nnn + 1, 0, 0, 1);
    col_mq += "<br>";
    col_cc += print_binary(cc, 1, 0, 0, 1);
    col_cc += "<br>";
    col_note += "初值 $[z_0]_{补} = 0$";
    col_note += "<br>";
    int yi;
    int ca;
    string str_case;
    for (int i = 1; i <= nnn + 1; i++) {
        yi = mq & 1;    // $y_{i}$
        ca = cc - yi;   // $y_{i+1} - y_{i}$
        str_case = "$y_n y_{n+1} = ";
        str_case += yi? '1' : '0';
        str_case += cc? '1' : '0';
        str_case += "$";
        // int accmqcc = b_link(b_link(acc, mq, nnn + 1), cc, 1);
        // printf("========%s\n", print_binary(accmqcc, 12, 1, 1, 1).c_str());
        // if (ca == 0) {
        //     int accmqcc = b_link(b_link(acc, mq, nnn + 1), cc, 1);
        //     printf("========%s\n", print_binary(accmqcc, 12, 1, 1, 1).c_str());
        // }

        if (ca == 1) {
            col_acc += print_binary(xxx, nnn + 2, 1, 1, 0);
            col_acc += "<br>";
            col_mq += "<br>";
            col_cc += "<br>";
            col_note += str_case;
            col_note += "，部分积加 $[x]_{补}$<br>";

            acc += xxx;
        } else if (ca == -1) {
            col_acc += print_binary(-xxx, nnn + 2, 1, 1, 0);
            col_acc += "<br>";
            col_mq += "<br>";
            col_cc += "<br>";
            col_note += str_case;
            col_note += "，部分积加 $[-x]_{补}$<br>";

            acc -= xxx;
        }

        if (ca && i != nnn + 1) {
            print_line(col_acc, col_mq, col_cc, col_note);
            ans_1 = print_binary(acc, nnn + 2, 1, 2, 0);
            col_acc += ans_1;
            col_acc += "<br>";
            ans_2 = print_binary(b_high(mq, nnn + 2 - i), i - 1, 0, 0, 0);
            col_mq += ans_2;
            col_mq += "<br>";
            col_cc += "<br>";
            col_note += "<br>";
        }

        // 右移
        if (i != nnn + 1) {
            int accmqcc = b_link(b_link(acc, mq, nnn + 1), cc, 1);
            // printf("========%s\n", print_binary(accmqcc, 12, 1, 1, 1).c_str());
            accmqcc >>= 1;
            acc = b_high(accmqcc, nnn + 2);
            mq = b_high(accmqcc, 1);
            cc = b_low(accmqcc, 1);
            col_acc += print_binary(acc, nnn + 2, 1, 2, 0);
            col_acc += "<br>";
            col_mq += print_binary(mq, nnn + 1, 0, 0, 1);
            col_mq += "<br>";
            col_cc += print_binary(cc, 1, 0, 0, 1);
            col_cc += "<br>";
            if (ca == 0) {
                col_note += str_case;
                col_note += "，部分积 $\\to 1$ 位，得 $[z_";
                col_note += to_string(i);
                col_note += "]_{补}$<br>";
            } else {
                col_note += "$\\to 1$ 位，得 $[z_";
                col_note += to_string(i);
                col_note += "]_{补}$<br>";
            }
        }
    }
    print_line(col_acc, col_mq, col_cc, col_note);

    ans_1 = print_binary(acc, nnn + 2, 1, 2, 0);
    col_acc += ans_1;
    col_acc += "<br>";
    ans_2 = print_binary(b_high(mq, 1), nnn, 0, 0, 0);
    col_mq += ans_2;
    col_mq += "<br>";
    col_cc += "<br>";
    col_note += "最后一步不位移，得 $[x \\cdot y]_{补}$<br>";
    print_line(col_acc, col_mq, col_cc, col_note);

    // printf("\n故 $[x \\cdot y]_{补} = $。\n\n");
    // printf("那么 $x \\cdot y = $。\n\n");
    return 0;
}