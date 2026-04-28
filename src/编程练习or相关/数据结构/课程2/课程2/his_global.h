#pragma once
#pragma warning(disable:4996)
#ifndef HIS_GLOBE_H
#define HIS_GLOBE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 常量定义
#define ID_LEN 20      
#define NAME_LEN 50    
#define DESC_LEN 256   
#define TIME_LEN 30    

// ==========================================
// 0. 前向声明
// ==========================================
typedef struct Doctor Doctor;
typedef struct Department Department;
typedef struct BedNode BedNode;
typedef struct WardNode WardNode;
typedef struct DrugHistory DrugHistory;
typedef struct DrugNode DrugNode;
typedef struct ExamNode ExamNode;
typedef struct PrescriptionNode PrescriptionNode;
typedef struct InpatientInfo InpatientInfo;
typedef struct MedicalRecord MedicalRecord;
typedef struct Patient Patient;

typedef struct DeptList DeptList;
typedef struct WardList WardList;
typedef struct Pharmacy Pharmacy;
typedef struct PatientList PatientList;

// ==========================================
// 模块 1：行政科室管理
// ==========================================
struct Doctor {
    char name[NAME_LEN];
    char id[ID_LEN];
    char dept[ID_LEN];
    Doctor* nxt;
};

struct Department {
    char dept_name[NAME_LEN];
    Doctor* dummy_doc_head; // 医生链表哨兵
    Doctor* tail;           // 医生链表尾指针
    struct Department* nxt;
};

struct DeptList {
    Department* dummy_head;
    Department* tail;
    int count;
};

// ==========================================
// 模块 2：空间床位调度
// ==========================================
struct BedNode {
    int bed_id;
    int is_occupied;
    char patient_id[ID_LEN];
    BedNode* nxt;
};

struct WardNode {
    char type[ID_LEN];
    char dept_id[ID_LEN];
    int total_beds;
    int available_beds;
    BedNode* bed_head;
    WardNode* nxt;
};

struct WardList {
    WardNode* dummy_head;
    WardNode* tail;
    int count;
};

// ==========================================
// 模块 3：药房与物资库
// ==========================================
struct DrugHistory {
    char time[TIME_LEN];
    int change_amount;
    char action_type[DESC_LEN];
    DrugHistory* nxt;
};

struct DrugNode {
    char drug_id[ID_LEN];
    char generic_name[NAME_LEN];
    char trade_name[NAME_LEN];
    char alias[NAME_LEN];
    char dept_id[ID_LEN];
    int stock;
    double price;
    DrugHistory* history_head;
    DrugNode* nxt;
};

struct Pharmacy {
    DrugNode* dummy_head;
    DrugNode* tail;
    int count;
    double total_value;
};

// ==========================================
// 模块 4：核心业务层 - 患者与病历
// ==========================================
struct ExamNode {
    char type[ID_LEN];
    char result[DESC_LEN];
    ExamNode* nxt;
};

struct PrescriptionNode {
    DrugNode* drug;             // 直接指向药房中的药品节点
    int quantity;
    PrescriptionNode* nxt;
};

struct InpatientInfo {
    char admission_date[TIME_LEN];
    char discharge_date[TIME_LEN];
    char ward_type[ID_LEN];
    int bed_id;
    InpatientInfo* nxt;
};

struct MedicalRecord {
    int serial_num;
    char time[TIME_LEN];
    char dept_name[NAME_LEN];
    char doc_name[NAME_LEN];
    char doc_id[ID_LEN];
    char diagnosis[DESC_LEN];

    ExamNode* exam_head;
    PrescriptionNode* prescription_head;
    InpatientInfo* inpatient_inf;

    MedicalRecord* nxt;
};

struct Patient {
    char name[NAME_LEN];
    char id[ID_LEN];
    int type;                   // 0:门诊, 1:住院
    MedicalRecord* record_dummy_head;
    MedicalRecord* record_tail;
    int record_count;
    Patient* nxt;
};

struct PatientList {
    Patient* dummy_head;
    Patient* tail;
    int count;
};

// ==========================================
// 5. 全局系统入口指针
// ==========================================
extern DeptList* g_dept_list;
extern WardList* g_ward_list;
extern Pharmacy* g_pharmacy;
extern PatientList* g_patient_list;

// --- 函数接口声明省略（保持你原来的即可） ---

// ==========================================
// 6. 核心接口函数声明
// ==========================================

//初始化
void init_list_managers();
void init_system_from_files();
void save_all_data_to_files();

/* --- crud.c 函数声明 --- */

// 查找类函数
Doctor* find_doctor_by_id(const char* input_id);
Patient* find_patient_by_id(const char* input_id);
DrugNode* find_drug_by_id(const char* input_id);
Department* find_dept_by_id(const char* input_id);

// 删除类函数
void delete_doctor_by_id(const char* input_id);
void delete_patient_by_id(const char* input_id);

// 新增类函数
void add_patient(const char* input_id);
void insert_doctor_to_dept(const char* input_id, const char* dpt_id);
void add_department(const char* input_id);

// 更新与业务类函数
void update_patient(char* id, char* n_name, int type);
void update_doctor(char* id, char* n_name, int type);
void trans_patient(const char* patient_id, const char* o_dpt, const char* t_dpt);

// ==========================================
// UI 与 业务模块函数声明 (含测试打桩)
// ==========================================
int login(char* current_user_id);

// 顶级菜单
void patient_menu(char* current_user_id);
void doctor_menu(char* current_user_id);
void admin_menu(char* current_user_id);

// 患者子功能
void view_histroy(char* current_user_id);
void prescription_register(char* current_patient_id);
void check_selfmedicine(char* current_user_id);
void check_publicmedicine(char* current_user_id);

// 医生子功能
void check_waiting(char* current_user_id);
void call_quene(char* current_user_id);
void handle_dischrage(char* current_user_id);

// 管理员子功能
void manage_system(char* current_user_id);
void bed_manage(char* current_user_id);
void medicine_manage(char* current_user_id);
void doctor_manage(char* current_user_id);

// 挂号业务支撑函数
Doctor* find_doctor_by_name_in_dept(Department* dept, const char* name);
int create_registration_record(char* pat_id, char* dept_name, char* doc_name, char* doc_id);

//ui函数 
int login(char* current_user_id);



#endif // HIS_GLOBE_H








