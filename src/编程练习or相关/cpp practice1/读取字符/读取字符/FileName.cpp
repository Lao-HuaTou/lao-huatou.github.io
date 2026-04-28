#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    string input;
    getline(cin, input);

    // 提取数值
    size_t numEnd = input.find_first_not_of("0123456789");
    double val = stod(input.substr(0, numEnd));

    // 提取原单位
    size_t unitStart = numEnd;
    size_t unitEnd = input.find(' ', unitStart);
    string from_unit = input.substr(unitStart, unitEnd - unitStart);

    // 提取目标单位（在 ? 之后）
    size_t qmarkPos = input.find('?');
    string to_unit = input.substr(qmarkPos + 1);

    // 转换到 B
    double val_B;
    if (from_unit == "GB") {
        val_B = val * pow(2, 30);
    }
    else if (from_unit == "MB") {
        val_B = val * pow(2, 20);
    }
    else if (from_unit == "KB") {
        val_B = val * pow(2, 10);
    }
    else { // "B"
        val_B = val;
    }

    // 转换到目标单位
    double result;
    if (to_unit == "GB") {
        result = val_B / pow(2, 30);
    }
    else if (to_unit == "MB") {
        result = val_B / pow(2, 20);
    }
    else if (to_unit == "KB") {
        result = val_B / pow(2, 10);
    }
    else { // "B"
        result = val_B;
    }

    // 输出，保留6位小数
    cout << fixed << setprecision(6) << result << endl;

    return 0;
}