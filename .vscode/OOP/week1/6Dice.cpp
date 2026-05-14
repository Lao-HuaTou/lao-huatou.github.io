#include <iostream>
#include <cstdlib> // 包含 srand 和 rand
#include <ctime>   // 包含 time 用于初始化随机种子

class Dice {
private:
    // 24种合法的空间朝向状态，每种状态包含6个面的点数，顺序为：
    // { 顶面(Top), 底面(Bottom), 前面(Front), 后面(Back), 左面(Left), 右面(Right) }
    static const int states[24][6];
    
    int currentStateIndex; // 当前骰子处于24种状态中的哪一种

public:
    // 构造函数，默认让骰子停留在第一种状态（1点朝上）
    Dice() {
        currentStateIndex = 0; 
    }

    // 1) 模拟掷骰子过程（Cast），并返回掷得到的点数（即顶面点数）
    int Cast() {
        // 使用系统函数 rand() 随机决定骰子落地后的空间朝向（0 ~ 23）
        currentStateIndex = rand() % 24;
        return GetTop();
    }

    // 获取当前各个面的点数工具函数
    int GetTop() const    { return states[currentStateIndex][0]; }
    int GetBottom() const { return states[currentStateIndex][1]; }
    int GetFront() const  { return states[currentStateIndex][2]; }
    int GetBack() const   { return states[currentStateIndex][3]; }
    int GetLeft() const   { return states[currentStateIndex][4]; }
    int GetRight() const  { return states[currentStateIndex][5]; }

    // 2) 报告当前各面的点数
    void Report() const {
        std::cout << "==== 当前骰子各面状态报告 ====" << std::endl;
        std::cout << "  顶面 (Top):    " << GetTop()    << "  <-- 掷出的点数" << std::endl;
        std::cout << "  底面 (Bottom): " << GetBottom() << std::endl;
        std::cout << "  前面 (Front):  " << GetFront()  << std::endl;
        std::cout << "  后面 (Back):   " << GetBack()   << std::endl;
        std::cout << "  左面 (Left):   " << GetLeft()   << std::endl;
        std::cout << "  右面 (Right):  " << GetRight()  << std::endl;
        std::cout << "==============================" << std::endl;
    }

    // 3) 模拟一次掷两个或多个骰子，并返回得到的总点数
    // 设计为静态成员函数，内部通过创建临时骰子来模拟多枚骰子同时落地
    static int CastMultiple(int count) {
        if (count <= 0) return 0;
        int totalSum = 0;
        Dice tempDice; 
        for (int i = 0; i < count; ++i) {
            totalSum += tempDice.Cast(); // 每一枚骰子独立投掷
        }
        return totalSum;
    }
};

// 严格符合物理规律的24种骰子空间状态定义（相对位置恒定：对立面相加为7）
const int Dice::states[24][6] = {
    {1, 6, 2, 5, 3, 4}, {1, 6, 3, 4, 5, 2}, {1, 6, 4, 3, 2, 5}, {1, 6, 5, 2, 4, 3},
    {2, 5, 1, 6, 4, 3}, {2, 5, 3, 4, 1, 6}, {2, 5, 4, 3, 6, 1}, {2, 5, 6, 1, 3, 4},
    {3, 4, 1, 6, 2, 5}, {3, 4, 2, 5, 6, 1}, {3, 4, 5, 2, 1, 6}, {3, 4, 6, 1, 5, 2},
    {4, 3, 1, 6, 5, 2}, {4, 3, 2, 5, 1, 6}, {4, 3, 5, 2, 6, 1}, {4, 3, 6, 1, 2, 5},
    {5, 2, 1, 6, 3, 4}, {5, 2, 3, 4, 6, 1}, {5, 2, 4, 3, 1, 6}, {5, 2, 6, 1, 4, 3},
    {6, 1, 2, 5, 4, 3}, {6, 1, 3, 4, 2, 5}, {6, 1, 4, 3, 5, 2}, {6, 1, 5, 2, 3, 4}
};

int main() {
    // 【重要】在程序最开始，使用系统时间初始化随机数发生器种子
    srand(static_cast<unsigned int>(time(0)));

    // 创建一个骰子对象
    Dice myDice;

    // 功能 1 测试：模拟掷单枚骰子
    std::cout << "--- 测试1：掷一枚骰子 ---" << std::endl;
    int point = myDice.Cast();
    std::cout << "摇出的点数是: " << point << std::endl << std::endl;

    // 功能 2 测试：报告此时各个面的点数（绝对符合相对位置固定的物理规律）
    std::cout << "--- 测试2：报告当前各个面的点数 ---" << std::endl;
    myDice.Report();
    std::cout << std::endl;

    // 功能 3 测试：模拟一次掷多个骰子（例如掷 3 个骰子）
    std::cout << "--- 测试3：同时掷 3 枚骰子 ---" << std::endl;
    int diceCount = 3;
    int totalScore = Dice::CastMultiple(diceCount);
    std::cout << "同时掷出 " << diceCount << " 枚骰子，得到的总点数为: " << totalScore << std::endl;

    return 0;
}