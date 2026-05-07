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
    if(scanf("%d",&role_choice)!=1)
    {
        while(getchar()!='\n');
        printf("读入命令失败，请重试\n");
        return 0;
    }
    if(role_choice==-1)
    {
        return -1;
    }
    char id_keyin[ID_LEN];

    switch (role_choice)
    {
    case 1:
        printf("【患者端】\n");
        printf("请输入身份证id:\n");
        if(scanf("%19s",id_keyin)!=1)
        {
            printf("输入失败请重试\n");
            while(getchar()!='\n');
            return 0;
        }
        Patient*p=find_patient_by_id(id_keyin);
        if(p==NULL)
        {
            printf("未能查询到此账号，请重试\n");
            printf("提示：初次就诊请先前往窗口或自助机【建档】！\n");
            return 0;
        }
        else
        {
            printf("登录成功。欢迎您,%s！",p->name);
            strcpy(current_user_id,id_keyin);
            return 1;
        }
        
        break;
    
    case 2:
        printf("【医生端】\n");
        printf("请输入工号id:\n");
        if(scanf("%19s",id_keyin)!=1)
        {
            printf("输入失败请重试\n");
            while(getchar()!='\n');
            return 0;
        }
        Doctor*d=find_doctor_by_id(id_keyin);
        if(d==NULL)
        {
            printf("未能查询到此工号，请重试\n");
            return 0;
        }
        else
        {
            printf("登录成功。欢迎您,%s医生！",d->name);
            strcpy(current_user_id,id_keyin);
            return 2;
        }
    
    case 3:
        
        break;//TODO:need to finish
    default:
        break;
    }
    
    

}



patient_menu(current_user_id);
{

        printf("【患者自助终端】");
        printf("请进行下一步操作");
        printf("1.历史记录");
        printf("2.挂号");
        printf("3.取药");
        printf("4.药品公示查询")
        printf("-1.返回");

        int operate_step;   //操作
 
    while (1)
    {
       if (scanf("%d", &operate_step) != 1)
       {
        while (getchar() != '\n');
        printf("读入命令失败，请重试\n");
        return 0;
       }
       if (operate_step == -1)
       {
          return -1;
       }

  
        switch (operate_step)
        {
        case 1:
            view_histroy(current_user_id);

        case 2:
            prescription_register(current_user_id);

        case 3:
            check_selfmedicine(current_user_id);
        
        case 4:
            check_publicmedicine(current_user_id);

        default:
            return 0;
        }
   }
}

doctor_menu(current_user_id)
{
    printf("【医生自助终端】");
    printf("请进行下一步操作");
    printf("1.查看候诊名单");
    printf("2.叫号接诊");
    printf("3.办理出院");
    printf("-1.退出");


        int operate_step;   //操作

    while (1) 
    {
        if (scanf("%d", &operate_step) != 1)
        {
            while (getchar() != '\n');
            printf("读入命令失败，请重试\n");
            return 0;
        }
        if (operate_step == -1)
        {
            return -1;
        }


        switch (operate_step)
        {
        case 1:
          check_waiting(current_user_id);

        case 2:
           call_quene(current_user_id);

        case 3:
            handle_dischrage(current_user_id);
       
        default:
            return 0;
        }
    }

}

admin_menu(current_user_id)
{

    printf("【管理员自助终端】");
    printf("请进行下一步操作");
    printf("1.基础数据维护");
    printf("2.病房监控");
    printf("3.药物管理");
    printf("4.人事管理");
    printf("-1.退出")；

        int operate_step;   //操作

    while (1) {
        if (scanf("%d", &operate_step) != 1)
        {
            while (getchar() != '\n');
            printf("读入命令失败，请重试\n");
            return 0;
        }
        if (operate_step == -1)
        {
            return -1;
        }


        switch (operate_step)
        {
        case 1:
            manage_system(current_user_id);

        case 2:
            bed_manage(current_user_id);

        case 3:
            medicine_manage(current_user_id);

        case 4:
            doctor_manage(current_user_id);

        default:
            return 0;
        }
    }










}