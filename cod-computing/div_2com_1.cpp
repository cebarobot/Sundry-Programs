// 除法：补码加减交替法
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

const char dot_char = '.';
const int dot_pos = 0;

string print_binary(unsigned int x, int len, bool print_dot = false, int print_plus = 0, bool underline = false, int width = 0) {
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
    if (width > 0 && width - len > 0) {
        out_string += "\\phantom{";
        for (int i = 0; i < width - len; i++) {
            out_string += "0";
        }
        out_string += "}";
    }
    for (int i = 0; i < len; i++) {
        if (underline && i == len - 1) {
            out_string += "\\phantom{";
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

unsigned b_replace(unsigned x, unsigned y, int len) {
    return b_link(b_high(x, len), b_low(y, len), len);
}

void print_line(string & col_acc, string & col_mq, string & col_note) {
    printf("|%s|%s|%s|\n", col_acc.c_str(), col_mq.c_str(), col_note.c_str());
    col_acc.clear();
    col_mq.clear();
    col_note.clear();
}

int main() {
    string col_acc;
    string col_mq;
    string col_cc;
    string col_note;

    int xxx;
    int yyy;
    int nnn;
    printf("依次输入xxx, yyy, nnn: ");
    scanf("%d %d %d", &xxx, &yyy, &nnn);

    printf("|被除数（余数）|商|说明|\n");
    printf("|:-|:-|:-|\n");
    int acc = xxx;
    int mq = 0;
    bool overflow_flag = false;

    col_acc += print_binary(acc, nnn + 1, 1, 2, 0);
    col_acc += "<br>";
    col_mq += "<br>";
    col_note += "<br>";

    bool reminder_pos = !(((acc >> nnn) & 1) ^ ((yyy >> nnn) & 1));

    for (int i = 0; i < nnn; i++) {
        if (i != 0) {
            acc <<= 1;
            mq <<= 1;
            col_acc += print_binary(acc, nnn + 1, 1, 2, 0);
            col_acc += "<br>";
            col_mq += print_binary(mq, i + 1, 0, 0, 1, nnn + 1);
            col_mq += "<br>";
            col_note += "$\\gets 1$ 位<br>";
        }
        if (reminder_pos) {
            acc -= yyy;
            col_acc += print_binary(-yyy, nnn + 1, 1, 1, 0);
            col_acc += "<br>";
            col_mq += "<br>";
            col_note += "$+[-y^*]_{补}$<br>";
        } else {
            acc += yyy;
            col_acc += print_binary(yyy, nnn + 1, 1, 1, 0);
            col_acc += "<br>";
            col_mq += "<br>";
            col_note += "$+[y^*]_{补}$<br>";
        }
        print_line(col_acc, col_mq, col_note);

        reminder_pos = !(((acc >> nnn) & 1) ^ ((yyy >> nnn) & 1));
        if (reminder_pos) {
            mq = b_replace(mq, 1, 1);
            col_acc += print_binary(acc, nnn + 1, 1, 2, 0);
            col_acc += "<br>";
            col_mq += print_binary(mq, i + 1, 0, 0, 0, nnn + 1);
            col_mq += "<br>";
            col_note += "$[R]_{补}$ 与 $[y]_{补}$ 同号，上商“$1$”<br>";
        } else {
            mq = b_replace(mq, 0, 1);
            col_acc += print_binary(acc, nnn + 1, 1, 2, 0);
            col_acc += "<br>";
            col_mq += print_binary(mq, i + 1, 0, 0, 0, nnn + 1);
            col_mq += "<br>";
            col_note += "$[R]_{补}$ 与 $[y]_{补}$ 异号，上商“$0$”<br>";
        }
    }
    acc <<= 1;
    mq <<= 1;
    col_acc += print_binary(acc, nnn + 1, 1, 2, 0);
    col_acc += "<br>";
    col_mq += print_binary(mq | 1, nnn + 1, 0, 0, 0, nnn + 1);
    col_mq += "<br>";
    col_note += "$\\gets 1$ 位，末尾商恒置“$1$”<br>";
    print_line(col_acc, col_mq, col_note);

    return 0;
}