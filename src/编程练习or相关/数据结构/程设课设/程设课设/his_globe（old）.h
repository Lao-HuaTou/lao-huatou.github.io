//#ifndef HIS_GLOBE
//#define HIS_GLOBE
//
//#include <stdio.h>
//
//// ==========================================
//// 1. 常量定义
//// ==========================================
//#define ID_LEN 20      // 各种ID的最大长度（身份证、工号、流水号等）
//#define NAME_LEN 50    // 名称/姓名最大长度
//#define DESC_LEN 256   // 描述性文本最大长度（医嘱、检查结果）
//#define TIME_LEN 30    // 时间字符串长度
//
//// ==========================================
//// 2. 类型前置声明 (告诉编译器这些名字都是结构体)
//// ==========================================
//typedef struct Doctor Doctor;
//typedef struct Department Department;
//typedef struct Patient Patient;
//typedef struct MedicalRecord MedicalRecord;
//typedef struct PrescriptionNode PrescriptionNode;
//typedef struct DrugNode DrugNode;
//typedef struct ExamNode ExamNode;
//typedef struct InpatientInfo InpatientInfo;
//typedef struct Pharmacy Pharmacy;
//typedef struct Hospital Hospital;
//
//// ==========================================
//// 3. 结构体具体定义 (注意顺序：被包含的结构体必须写在前面)
//// ==========================================
//typedef struct Bed {
//    int bed_num;
//    int is_occupied;         // 0-空，1-有人
//    Patient* resident;      // 【包含关系】指向住在这个床位的患者节点
//    struct Bed* next;
//} Bed;
//
//typedef struct Ward {
//    char ward_type[20];      // 3种类型之一
//    char belong_to_dept[20];  // 关联的科室名
//    Bed* bed_head;           // 【包含关系】该病房下的床位链表
//    struct Ward* next;
//} Ward;
//
//// --- 药品节点 ---
//struct DrugNode {
//    char drug_id[ID_LEN];    //编号
//    char generic_name[NAME_LEN];//通用名
//    char trade_name[NAME_LEN];//商用名
//    char alias[NAME_LEN];    //别名
//    char dept_id[ID_LEN];    // 专属科室ID，为空则通用
//    int stock;               // 库存
//    double price;            // 单价
//    struct DrugNode* nxt;    // 药房中的下一个药品
//};
//
//// --- 处方单中的单项药品 ---
//struct PrescriptionNode {
//    struct DrugNode* drug;        // 指向药库里的药品
//    int quantity;                 // 开药数量
//    struct PrescriptionNode* nxt; // 下一项药品
//};
//
//// --- 检查记录节点 ---
//struct ExamNode {
//    char type[ID_LEN];       // 检查类型（如：血常规、CT）
//    char result[DESC_LEN];   // 检查结果描述
//    struct ExamNode* nxt;    // 下一项检查
//};
//
//// --- 住院信息记录 ---
//struct InpatientInfo {
//    char admission_date[TIME_LEN]; // 入院日期
//    char discharge_date[TIME_LEN]; // 出院日期
//    char type[ID_LEN];             // 病房类型
//    int bed_id;                    // 床位号
//};
//
//// --- 核心：病历记录 (每次就诊产生一个记录) ---
//struct MedicalRecord {
//    int serial_num;               // 就诊流水号
//    char time[TIME_LEN];          // 就诊时间
//    char dept_name[NAME_LEN];     // 就诊科室
//    char doc_name[NAME_LEN];      // 主治医生姓名
//    char doc_id[ID_LEN];          // 主治医生ID
//    char diagnosis[DESC_LEN];     // 医嘱/诊断结论
//
//    struct ExamNode* exam_head;            // 检查项目链表
//    struct InpatientInfo* inpatient_inf;   // 住院信息（如果是门诊则为NULL）
//    struct PrescriptionNode* prescription_head; // 处方药品链表
//
//    struct MedicalRecord* nxt;    // 指向该患者的下一次就诊记录
//};
//
//// --- 患者信息 ---
//struct Patient {
//    char name[NAME_LEN];
//    char id[ID_LEN];
//    int type;                     // 0:门诊, 1:住院
//    struct MedicalRecord* record; // 该患者的所有历史病历链表头
//    struct Patient* nxt;          // 系统里的下一个患者
//};
//
//// --- 医生信息 ---
//struct Doctor {
//    char name[NAME_LEN];
//    char id[ID_LEN];
//    char dept[ID_LEN];            // 所属科室名称/ID
//    struct Doctor* nxt;           // 同科室的下一个医生
//
//};
//
//// --- 科室信息 ---
//struct Department {
//    char dept_name[ID_LEN];
//    struct Doctor* doc_head;      // 该科室的医生链表头
//    struct Department* nxt;       // 医院里的下一个科室
//};
//
//// --- 药房管理 ---
//struct Pharmacy {
//    struct DrugNode* drug_head;   // 药库药品链表头
//};
//
//// --- 医院总入口 (全局数据结构) ---
//struct Hospital {
//    struct Department* dept_head;    // 所有科室的入口
//    struct Pharmacy* global_pharmacy; // 全局药库入口
//};
//
//struct patientlist {
//
//};
//
//// ==========================================
//// 4. 函数原型声明
//// ==========================================
//Doctor* find_doctor_by_id(const char* input_id);
//Patient* find_patient_by_id(const char* input_id);
//DrugNode* find_drug_by_id(const char* input_id);
//
//#endif