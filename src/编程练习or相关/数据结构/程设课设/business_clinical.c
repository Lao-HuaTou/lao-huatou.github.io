#include "his_global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---------------------------------------------------------
// 以下为 UI 调用的业务空壳函数 (Stub)，供前期流转测试使用
// ---------------------------------------------------------

// --- 患者模块空壳 ---
void view_histroy(char* current_user_id) {
    printf("\n>>> [开发中] 正在查询患者 %s 的历史记录...\n", current_user_id);
}
void check_selfmedicine(char* current_user_id) {
    printf("\n>>> [开发中] 正在查询患者 %s 的取药信息...\n", current_user_id);
}
void check_publicmedicine(char* current_user_id) {
    printf("\n>>> [开发中] 正在进入全院药品公示系统...\n");
}

// --- 医生模块空壳 ---
void check_waiting(char* current_user_id) {
    printf("\n>>> [开发中] 正在拉取医生 %s 的候诊名单...\n", current_user_id);
}
void call_quene(char* current_user_id) {
    printf("\n>>> [开发中] 医生 %s 正在叫号接诊...\n", current_user_id);
}
void handle_dischrage(char* current_user_id) {
    printf("\n>>> [开发中] 医生 %s 正在为患者办理出院...\n", current_user_id);
}

// --- 管理员模块空壳 ---
void manage_system(char* current_user_id) {
    printf("\n>>> [开发中] 进入基础数据维护终端...\n");
}
void bed_manage(char* current_user_id) {
    printf("\n>>> [开发中] 进入病房监控视图...\n");
}
void medicine_manage(char* current_user_id) {
    printf("\n>>> [开发中] 进入药物库存管理...\n");
}
void doctor_manage(char* current_user_id) {
    printf("\n>>> [开发中] 进入人事管理系统...\n");
}

// --- 挂号业务内部支撑函数空壳 ---
Doctor* find_doctor_by_name_in_dept(Department* dept, const char* name) {
    // 临时防报错：随便返回一个非空指针或NULL。
    // 当前测试中只要没挂掉就行。
    return NULL; 
}

int create_registration_record(char* pat_id, char* dept_name, char* doc_name, char* doc_id) {
    // 临时返回失败，防止后续越界
    return 0; 
}
