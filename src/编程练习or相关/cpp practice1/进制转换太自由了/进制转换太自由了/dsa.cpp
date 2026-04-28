#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

string decimalToK(int decimal, int k) {
    if (decimal == 0) return "0";

    string result = "";
    int num = decimal;

    while (num > 0) {
        int remainder = num % k;
        result += '0' + remainder;  // 将数字转换为字符
        num /= k;
    }

    reverse(result.begin(), result.end());
    return result;
}

// K进制转十进制
int kToDecimal(const string& kNumber, int k) {
    int decimal = 0;
    int power = 1;

    for (int i = kNumber.length() - 1; i >= 0; i--) {
        int digit = kNumber[i] - '0';
        decimal += digit * power;
        power *= k;
    }

    return decimal;
}





#include <stdio.h>
#include <string.h>
#include <math.h>

// 十进制转K进制
void decimalToK(int decimal, int k, char* result) {
    if (decimal == 0) {
        strcpy(result, "0");
        return;
    }

    char temp[100];
    int index = 0;
    int num = decimal;

    while (num > 0) {
        int remainder = num % k;
        temp[index++] = '0' + remainder;
        num /= k;
    }

    // 反转字符串
    int resultIndex = 0;
    for (int i = index - 1; i >= 0; i--) {
        result[resultIndex++] = temp[i];
    }
    result[resultIndex] = '\0';
}

// K进制转十进制
int kToDecimal(char* kNumber, int k) {
    int decimal = 0;
    int length = strlen(kNumber);
    int power = 1;

    for (int i = length - 1; i >= 0; i--) {
        int digit = kNumber[i] - '0';
        decimal += digit * power;
        power *= k;
    }

    return decimal;
}