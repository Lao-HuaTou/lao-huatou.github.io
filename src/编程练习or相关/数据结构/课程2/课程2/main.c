#pragma warning(disable:4996)
#include <windows.h>
#include "his_global.h"
#include <stdio.h>
// 假设我们在 global.h 里定义了全局变量来记录当前登录者的 ID
// extern char current_user_id[20]; 

int main() {
    // 1. 系统初始化
    SetConsoleOutputCP(65001);
    // 从所有的 txt 文件中把链表建起来
    init_system_from_files();
    
    int current_role;
    char current_user_id[ID_LEN];
    // 提示：欢迎语最好放进循环里，或者 login 函数里。
    // 这样当上一个人注销登录后，下一个人面对屏幕还能看到欢迎语。
    
    while(1)
    {
        printf("\n=== 欢迎使用 HIS 医疗管理系统 ===\n");
        // login 函数不仅要返回角色，还要在内部把账号 ID 存入全局变量 current_user_id
        current_role = login(current_user_id);   // 1:患者, 2:医生, 3:管理员, 0:无效, -1:退出系统
        
        switch(current_role) 
        {
            case 1:
                patient_menu(current_user_id);
                break;
            case 2:
                doctor_menu(current_user_id);
                break;
            case 3:
                admin_menu(current_user_id);
                break;
            case 0:
                printf("\n"); //输入错误导致的重新返回登录界面
                break;
            case -1:
                // 退出前的核心操作：数据落盘！
                printf("正在将数据保存至本地文件...\n");
                save_all_data_to_files(); 
                printf("数据保存完毕。安全退出系统，再见！\n");
                return 0; // 直接结束进程
            default:
                printf("[异常] 未知状态码，请重试。\n");
                break;
        }
    }
    return 0;
}