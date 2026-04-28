#ifndef HIS_GLOBE
#define HIS_GLOBE

#define ID_LEN 20      
#define NAME_LEN 50    
#define DESC_LEN 256   
#define TIME_LEN 30    

// ==========================================
// 0. 前向声明区 (防止嵌套引用报错)
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
//四大链表
typedef struct DeptList DeptList;
typedef struct WardList WardList;
typedef struct Pharmacy Pharmacy;
typedef struct PatientList PatientList;
// ==========================================
// 模块 1：行政科室管理 (二级嵌套)
// ==========================================

struct Doctor {
    // [基础数据]
    char name[NAME_LEN];
    char id[ID_LEN];
    char dept[ID_LEN];    // 所属科室名称
    // [横向连结]
    Doctor* nxt;          // 指向本科室的下一个医生


};

struct Department {
    // [基础数据]
    char dept_name[NAME_LEN]; 
    // [纵向挂载]
    Doctor* dummy_doc_head;     // 打开科室门，里面是一串医生 (医生链表头)
    // [横向连结]
    Doctor* tail;
    Department* nxt;      // 指向下一个科室
};

// 【升级】全局科室链表管理器
struct DeptList {
    Department* dummy_head; // 哨兵节点
    Department* tail;       // 尾指针，O(1) 极速尾插
    int count;              // 当前科室数量
};


// ==========================================
// 模块 2：空间床位调度 (二级嵌套)
// ==========================================

struct BedNode {
    // [基础数据]
    int bed_id;               // 床号
    int is_occupied;          // 状态：0空闲, 1占用
    char patient_id[ID_LEN];  // 谁在睡这张床？(空闲时为空串)
    // [横向连结]
    BedNode* nxt;             // 指向本病房的下一张床
};

struct WardNode {
    // [基础数据]
    char type[ID_LEN];        // 病房类型 (如: "普通双人间")
    char dept_id[ID_LEN];     // 归属科室 (有些病房是全院通用，可为空)
    int total_beds;           // 总床数
    int available_beds;       // 剩余空床数 (核心调控指标)
    // [纵向挂载]
    BedNode* bed_head;        // 打开病房门，里面是一串床位 (床位链表头)
    // [横向连结]
    WardNode* nxt;
                // 指向下一个病房
};

// 【升级】全局病房链表管理器
struct WardList {
    WardNode* dummy_head;
    WardNode* tail;
    int count;
};
// ==========================================
// 模块 3：药房与物资库 (二级嵌套)
// ==========================================

struct DrugHistory {
    // [基础数据]：一条出入库流水
    char time[TIME_LEN];        // 变动时间
    int change_amount;          // 变动量 (+100 进货，-2 发药)
    char action_type[DESC_LEN]; // 动作 ("采购入库", "门诊发药")
    // [横向连结]
    DrugHistory* nxt;           // 指向该药品的上一条流水
};

struct DrugNode {
    // [基础数据]
    char drug_id[ID_LEN];
    char generic_name[NAME_LEN];// 通用名
    char trade_name[NAME_LEN];  // 商品名
    char alias[NAME_LEN];       // 别名
    char dept_id[ID_LEN];       // 专属科室ID (通用药为空)
    int stock;                  // 当前库存
    double price;               // 单价
    // [纵向挂载]
    DrugHistory* history_head;  // 翻开账本，查看该药的历史流水
    // [横向连结]
    DrugNode* nxt;              // 指向药房库里的下一种药
};

// 【升级】全局药房本体 (作为药品链表管理器)
struct Pharmacy {
    DrugNode* dummy_head;
    DrugNode* tail;
    int count;              // 药品种类总数
    double total_value;     // 动态维护全院药品总价值
};


// ==========================================
// 模块 4：核心业务层 - 患者与病历 (最复杂的组装体)
// ==========================================

// --- 病历的三个附属子单据 ---
struct ExamNode {
    char type[ID_LEN];          // 检查类型 ("血常规")
    char result[DESC_LEN];      // 检查结果
    ExamNode* nxt;              // 多个检查连成串
};

struct PrescriptionNode {
    DrugNode* drug;             // 【重点】这里不存药名，直接存药房里那个真实药品的指针！
    int quantity;               // 开药数量
    PrescriptionNode* nxt;      // 多种药连成一个处方单
};

struct InpatientInfo {
    char admission_date[TIME_LEN]; // 入院时间
    char discharge_date[TIME_LEN]; // 出院时间 (未出院则为空串)
    char ward_type[ID_LEN];        // 住在什么类型的病房
    int bed_id;                    // 住在几号床
    InpatientInfo* nxt;            // 【追踪调动】指向下一次换床记录，连成住院轨迹
};

// --- 病历本体 ---
struct MedicalRecord {
    // [基础信息：本次看诊的抬头]
    int serial_num;             // 挂号流水号
    char time[TIME_LEN];        // 就诊时间
    char dept_name[NAME_LEN];   // 就诊科室
    char doc_name[NAME_LEN];    // 负责医生
    char doc_id[ID_LEN];        // 医生工号
    char diagnosis[DESC_LEN];   // 医生写的医嘱/诊断

    // [纵向挂载：看诊产生的三项具体业务] (如果没有，则指针为 NULL)
    ExamNode* exam_head;                 // 开了什么检查？
    PrescriptionNode* prescription_head; // 开了什么药？
    InpatientInfo* inpatient_inf;        // 办理住院了吗？

    // [横向连结]
    MedicalRecord* nxt;         // 指向该患者的下一次历史看诊记录
};

// --- 患者本体 ---
struct Patient {
    // [基础数据]
    char name[NAME_LEN];
    char id[ID_LEN];            // 身份证
    int type;                   // 当前状态：0 门诊, 1 住院
    // [纵向挂载]
    MedicalRecord* record_dummy_head; 
    MedicalRecord* record_tail;
    int record_count;      
    // [横向连结]
    Patient* nxt;               // 指向医院里的下一个建档患者
};

// 【升级】全局患者链表管理器
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

// ==========================================
// 6. 核心接口函数声明
// ==========================================
void init_list_managers();
void init_system_from_files();
void save_all_data_to_files();
int login(char* current_user_id);
Doctor* find_doctor_by_id(const char* input_id);
Patient* find_patient_by_id(const char* input_id);

#endif