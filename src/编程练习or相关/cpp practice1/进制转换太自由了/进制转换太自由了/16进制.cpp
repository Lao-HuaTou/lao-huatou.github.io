#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// 通用进制转换：十进制转K进制 (2-36进制)
void decimalToK(int decimal, int k, char* result) {
    if (decimal == 0) {
        strcpy(result, "0");
        return;
    }

    char temp[100];
    int index = 0;
    unsigned int num = decimal;

    while (num > 0) {
        int remainder = num % k;
        if (remainder < 10) {
            temp[index++] = '0' + remainder;
        }
        else {
            temp[index++] = 'A' + (remainder - 10);
        }
        num /= k;
    }

    // 反转字符串
    int resultIndex = 0;
    for (int i = index - 1; i >= 0; i--) {
        result[resultIndex++] = temp[i];
    }
    result[resultIndex] = '\0';
}

// 通用进制转换：K进制转十进制 (2-36进制)
int kToDecimal(char* number, int k) {
    int decimal = 0;
    int length = strlen(number);
    int base = 1;

    for (int i = length - 1; i >= 0; i--) {
        char c = toupper(number[i]);
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        }
        else if (c >= 'A' && c <= 'Z') {
            digit = 10 + (c - 'A');
        }
        else {
            return -1;  // 无效字符
        }

        if (digit >= k) return -1;  // 数字超过进制范围

        decimal += digit * base;
        base *= k;
    }

    return decimal;
}











string decimalToK(int decimal, int k) {
    if (decimal == 0) return "0";
    if (k < 2 || k > 16) return "错误：进制范围2-16";

    string result = "";
    unsigned int num = decimal;

    while (num > 0) {
        int remainder = num % k;
        if (remainder < 10) {
            result += '0' + remainder;
        }
        else {
            result += 'A' + (remainder - 10);
        }
        num /= k;
    }

    reverse(result.begin(), result.end());
    return result;
}

// 通用K进制转十进制 (2-16进制)
int kToDecimal(const string& number, int k) {
    if (k < 2 || k > 16) return -1;

    int decimal = 0;
    int base = 1;

    for (int i = number.length() - 1; i >= 0; i--) {
        char c = toupper(number[i]);
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            digit = 10 + (c - 'A');
        }
        else {
            return -1;  // 无效字符
        }

        if (digit >= k) return -1;  // 数字超过进制范围

        decimal += digit * base;
        base *= k;
    }

    return decimal;
}