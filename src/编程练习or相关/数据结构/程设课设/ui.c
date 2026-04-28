#include "his_global.h"
#include <stdio.h>
#include <string.h>

int login(char* current_user_id)
{
    printf("\n====================================\n");
    printf("        【HIS 系统登录中心】        \n");
    printf("  1. 患者端 (刷身份证)\n");
    printf("  2. 医生端 (刷工号)\n");
    printf("  3. 管理员端 (系统维护)\n");
    printf("  -1. 退出系统并保存数据\n");
    printf("====================================\n");
    printf("请选择登录身份: ");
    
    int role_choice;
    if(scanf("%d", &role_choice) != 1)
    {
        while(getchar() != '\n');
        printf("读入命令失败，请重试\n");
        return 0;
    }
    
    if(role_choice == -1)
    {
        return -1;
    }
    
    char id_keyin[ID_LEN];

    switch (role_choice)
    {
    case 1:
        { // 使用大括号划定作用域，避免声明变量报错
            printf("【患者端】\n");
            printf("请输入身份证id:\n");
            if(scanf("%19s", id_keyin) != 1)
            {
                printf("输入失败请重试\n");
                while(getchar() != '\n');
                return 0;
            }
            Patient* p = find_patient_by_id(id_keyin);
            if(p == NULL)
            {
                printf("未能查询到此账号，请重试\n");
                printf("提示：初次就诊请先前往窗口或自助机【建档】！\n");
                return 0;
            }
            else
            {
                printf("登录成功。欢迎您, %s！\n", p->name);
                strcpy(current_user_id, id_keyin);
                return 1;
            }
        }
        break;
    
    case 2:
        {
            printf("【医生端】\n");
            printf("请输入工号id:\n");
            if(scanf("%19s", id_keyin) != 1)
            {
                printf("输入失败请重试\n");
                while(getchar() != '\n');
                return 0;
            }
            Doctor* d = find_doctor_by_id(id_keyin);
            if(d == NULL)
            {
                printf("未能查询到此工号，请重试\n");
                return 0;
            }
            else
            {
                printf("登录成功。欢迎您, %s医生！\n", d->name);
                strcpy(current_user_id, id_keyin);
                return 2;
            }
        }
        break;
    
    case 3:
        printf("【管理员端】\n");
        // TODO: need to finish
        break;
        
    default:
        printf("无效的选项，请重试\n");
        break;
    }
    
    return 0; // 补充默认返回值
}


void patient_menu(char* current_user_id) // 去掉了原有的分号
{
    int operate_step;   //操作
 
    while (1)
    {
        printf("\n【患者自助终端】\n");
        printf("请进行下一步操作\n");
        printf("1.历史记录\n");
        printf("2.挂号\n");
        printf("3.取药\n");
        printf("4.药品公示查询\n"); // 加上了原有的分号
        printf("-1.返回\n");
        printf("请输入指令: ");

        if (scanf("%d", &operate_step) != 1)
        {
            while (getchar() != '\n');
            printf(">>> 读入命令失败，请输入有效的数字\n");
            continue; // 跳回循环开头
        }

        while (getchar() != '\n'); // 清除回车符
       
        if (operate_step == -1)
        {
            printf("已退出患者终端\n");
            return;
        }

        switch (operate_step)
        {
        case 1:
            view_histroy(current_user_id);
            break;
        case 2:
            prescription_register(current_user_id);
            break;
        case 3:
            check_selfmedicine(current_user_id);
            break;
        case 4:
            check_publicmedicine(current_user_id);
            break;
        default:
            printf(">>> 报错：无此选项\n");
        }
   }
}


void doctor_menu(char* current_user_id)
{
    int operate_step;   //操作

    while (1) 
    {
        printf("\n【医生自助终端】\n");
        printf("请进行下一步操作\n");
        printf("1.查看候诊名单\n");
        printf("2.叫号接诊\n");
        printf("3.办理出院\n");
        printf("-1.退出\n");
        printf("请输入指令: ");

        if (scanf("%d", &operate_step) != 1)
        {
            while (getchar() != '\n');
            printf(">>> 读入命令失败，请输入有效的数字\n");
            continue;
        }
        
        while (getchar() != '\n');

        if (operate_step == -1)
        {
            printf("已退出医生终端\n");
            return;
        }

        switch (operate_step)
        {
        case 1:
            check_waiting(current_user_id);
            break;
        case 2:
            call_quene(current_user_id);
            break;
        case 3:
            handle_dischrage(current_user_id);
            break;
        default:
            printf(">>> 报错：无此选项\n");
        }
    }
}


void admin_menu(char* current_user_id)
{
    int operate_step;   //操作

    while (1) 
    {
        printf("\n【管理员自助终端】\n");
        printf("请进行下一步操作\n");
        printf("1.基础数据维护\n");
        printf("2.病房监控\n");
        printf("3.药物管理\n");
        printf("4.人事管理\n");
        printf("-1.退出\n"); // 修复了全角分号
        printf("请输入指令: ");

        if (scanf("%d", &operate_step) != 1)
        {
            while (getchar() != '\n');
            printf(">>> 读入命令失败，请输入有效的数字\n");
            continue;
        }
        
        while (getchar() != '\n');

        if (operate_step == -1)
        {
            printf("已退出管理员终端\n");
            return;
        }

        switch (operate_step)
        {
        case 1:
            manage_system(current_user_id);
            break;
        case 2:
            bed_manage(current_user_id);
            break;
        case 3:
            medicine_manage(current_user_id);
            break;
        case 4:
            doctor_manage(current_user_id);
            break;
        default:
            printf(">>> 报错：无此选项\n");
        }
    }
} // 删除了末尾多余的右大括号

//注册


void prescription_register(char* current_patient_id) {
    char target_dept_name[NAME_LEN];
    char target_doc_name[NAME_LEN];
    
    printf("\n=== 门诊挂号向导 ===\n");
    
    // 【第 1 环节：选科室】
    printf("请输入您要挂号的科室名称 (如 内科, 外科): ");
    scanf("%49s", target_dept_name);
    
    Department* target_dept = find_dept_by_id(target_dept_name);
    if (target_dept == NULL) {
        printf("[系统] 抱歉，未找到 '%s'，请检查输入是否正确。\n", target_dept_name);
        return; // 提前结束
    }//TODO:ROB
    
    // 【第 2 环节：展示该科室的医生列表】
    printf("\n[%s] 今日坐诊医生列表:\n", target_dept->dept_name);
    Doctor* doc_curr = target_dept->dummy_doc_head->nxt;
    if (doc_curr == NULL) {
        printf("  (当前科室暂无医生排班)\n");
        return;
    }
    
    while (doc_curr != NULL) {
        // 这里偷偷把医生的工号也打出来，方便同名情况，但主要还是看名字
        printf("  - 姓名: %s (专家号: %s)\n", doc_curr->name, doc_curr->id);
        doc_curr = doc_curr->nxt;
    }
    
    // 【第 3 环节：选医生】
    printf("\n请输入您想预约的医生: ");
    scanf("%49s", target_doc_name);
    
    Doctor* target_doc = find_doctor_by_name_in_dept(target_dept, target_doc_name);
    if (target_doc == NULL) {
        printf("[系统] 抱歉，%s 里没有叫 '%s' 的医生。\n", target_dept->dept_name, target_doc_name);
        return;
    }
    
    // 【第 4 环节：所有信息确认无误，生成病历单】
    // 这里调用我们之前讨论过的业务代码 (传入确定的科室名和医生名，或者直接传工号)
    int result = create_registration_record(current_patient_id, target_dept->dept_name, target_doc->name, target_doc->id);
    
    if (result == 1) {
        printf("[系统] 挂号成功！您已成功预约 %s 的 %s 医生。\n", target_dept->dept_name, target_doc->name);
    } else {
        printf("[系统] 系统繁忙，挂号失败！\n");
    }
}

