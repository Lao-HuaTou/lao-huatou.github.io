#include "his_global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// 1. 全局大管家实体化定义
// ==========================================
DeptList* g_dept_list = NULL;
WardList* g_ward_list = NULL;
Pharmacy* g_pharmacy = NULL;
PatientList* g_patient_list = NULL;

// ==========================================
// 2. 内部工具函数：根据ID找药品 (为了还原处方真实指针)
// ==========================================


// ==========================================
// 3. 内存分配：初始化四大管家与所有哨兵
// ==========================================
void init_list_managers() {
    // 1. 科室链表
    g_dept_list = (DeptList*)malloc(sizeof(DeptList));
    g_dept_list->dummy_head = (Department*)malloc(sizeof(Department));
    g_dept_list->dummy_head->nxt = NULL; 
    g_dept_list->tail = g_dept_list->dummy_head; 
    g_dept_list->count = 0;

    // 2. 病房链表
    g_ward_list = (WardList*)malloc(sizeof(WardList));
    g_ward_list->dummy_head = (WardNode*)malloc(sizeof(WardNode));
    g_ward_list->dummy_head->nxt = NULL; 
    g_ward_list->tail = g_ward_list->dummy_head; 
    g_ward_list->count = 0;

    // 3. 药房链表
    g_pharmacy = (Pharmacy*)malloc(sizeof(Pharmacy));
    g_pharmacy->dummy_head = (DrugNode*)malloc(sizeof(DrugNode));
    g_pharmacy->dummy_head->nxt = NULL; 
    g_pharmacy->tail = g_pharmacy->dummy_head; 
    g_pharmacy->count = 0; 
    g_pharmacy->total_value = 0.0;

    // 4. 患者档案链表
    g_patient_list = (PatientList*)malloc(sizeof(PatientList));
    g_patient_list->dummy_head = (Patient*)malloc(sizeof(Patient));
    g_patient_list->dummy_head->nxt = NULL; 
    g_patient_list->tail = g_patient_list->dummy_head; 
    g_patient_list->count = 0;
}

// ==========================================
// 4. Load：从文件读取构建多级链表 (包含顶级防御机制)
// ==========================================

void load_dept_doc() {
    FILE* fp = fopen("admin_dept_doc.txt", "r");
    if (!fp) { printf("[IO警告] admin_dept_doc.txt 缺失，相关数据初始化为空。\n"); return; }
    
    char type[20]; 
    Department* cur_dept = NULL;
    int line = 0;

    // %19s 防止越界，正好对应 type[20]
    while (fscanf(fp, "%19s", type) != EOF) {
        line++;
        if (strcmp(type, "DEPT") == 0) {
            Department* n = (Department*)malloc(sizeof(Department));
            if (fscanf(fp, "%49s", n->dept_name) != 1) {
                printf("[数据异常] 行 %d: 科室格式错误，跳过\n", line); free(n); continue;
            }
            // 分配子链表哨兵
            n->dummy_doc_head = (Doctor*)malloc(sizeof(Doctor)); 
            n->dummy_doc_head->nxt = NULL; 
            n->nxt = NULL;
            // 尾插法
            g_dept_list->tail->nxt = n; g_dept_list->tail = n; g_dept_list->count++;
            cur_dept = n;
        } 
        else if (strcmp(type, "DOC") == 0) {
            Doctor* d = (Doctor*)malloc(sizeof(Doctor));
            if (fscanf(fp, "%49s %19s %19s", d->name, d->id, d->dept) != 3) {
                printf("[数据异常] 行 %d: 医生格式错误，跳过\n", line); free(d); continue;
            }
            if (cur_dept) {
                d->nxt = cur_dept->dummy_doc_head->nxt; cur_dept->dummy_doc_head->nxt = d; 
            } else {
                printf("[数据异常] 行 %d: 孤立的医生节点，拦截\n", line); free(d);
            }
        }
    }
    fclose(fp);
    printf("[IO] 科室与医生数据装载完成 (%d 个科室)\n", g_dept_list->count);
}

void load_ward_bed() {
    FILE* fp = fopen("ward_bed.txt", "r");
    if (!fp) { printf("[IO警告] ward_bed.txt 缺失，跳过。\n"); return; }
    
    char type[20]; WardNode* cur_ward = NULL; int line = 0;
    
    while (fscanf(fp, "%19s", type) != EOF) {
        line++;
        if (strcmp(type, "WARD") == 0) {
            WardNode* w = (WardNode*)malloc(sizeof(WardNode));
            if (fscanf(fp, "%19s %19s %d %d", w->type, w->dept_id, &w->total_beds, &w->available_beds) != 4) {
                free(w); continue;
            }
            w->bed_head = (BedNode*)malloc(sizeof(BedNode)); w->bed_head->nxt = NULL; w->nxt = NULL;
            g_ward_list->tail->nxt = w; g_ward_list->tail = w; g_ward_list->count++;
            cur_ward = w;
        } else if (strcmp(type, "BED") == 0) {
            BedNode* b = (BedNode*)malloc(sizeof(BedNode));
            if (fscanf(fp, "%d %d %19s", &b->bed_id, &b->is_occupied, b->patient_id) != 3) {
                free(b); continue;
            }
            if (cur_ward) {
                b->nxt = cur_ward->bed_head->nxt; cur_ward->bed_head->nxt = b; 
            } else { free(b); }
        }
    }
    fclose(fp);
}

void load_pharmacy() {
    FILE* fp = fopen("pharmacy.txt", "r");
    if (!fp) { printf("[IO警告] pharmacy.txt 缺失，跳过。\n"); return; }
    
    char type[20]; DrugNode* cur_drug = NULL; int line = 0;
    
    while (fscanf(fp, "%19s", type) != EOF) {
        line++;
        if (strcmp(type, "DRUG") == 0) {
            DrugNode* d = (DrugNode*)malloc(sizeof(DrugNode));
            if (fscanf(fp, "%19s %49s %49s %49s %19s %d %lf", 
                d->drug_id, d->generic_name, d->trade_name, d->alias, d->dept_id, &d->stock, &d->price) != 7) {
                free(d); continue;
            }
            d->history_head = (DrugHistory*)malloc(sizeof(DrugHistory)); d->history_head->nxt = NULL; d->nxt = NULL;
            g_pharmacy->tail->nxt = d; g_pharmacy->tail = d; 
            g_pharmacy->count++; g_pharmacy->total_value += (d->stock * d->price);
            cur_drug = d;
        } else if (strcmp(type, "HISTORY") == 0) {
            DrugHistory* h = (DrugHistory*)malloc(sizeof(DrugHistory));
            if (fscanf(fp, "%29s %d %255s", h->time, &h->change_amount, h->action_type) != 3) {
                free(h); continue;
            }
            if (cur_drug) {
                h->nxt = cur_drug->history_head->nxt; cur_drug->history_head->nxt = h;
            } else { free(h); }
        }
    }
    fclose(fp);
}

void load_patients_records() {
    FILE* fp = fopen("patients_records.txt", "r");
    if (!fp) { printf("[IO警告] patients_records.txt 缺失，跳过。\n"); return; }
    
    char type[20]; Patient* cur_pat = NULL; MedicalRecord* cur_rec = NULL; int line = 0;
    
    while (fscanf(fp, "%19s", type) != EOF) {
        line++;
        if (strcmp(type, "PATIENT") == 0) {
            Patient* p = (Patient*)malloc(sizeof(Patient));
            if (fscanf(fp, "%49s %19s %d", p->name, p->id, &p->type) != 3) { free(p); continue; }
            
            p->record_dummy_head = (MedicalRecord*)malloc(sizeof(MedicalRecord)); p->record_dummy_head->nxt = NULL;
            p->record_tail = p->record_dummy_head; p->record_count = 0; p->nxt = NULL;
            
            g_patient_list->tail->nxt = p; g_patient_list->tail = p; g_patient_list->count++;
            cur_pat = p; cur_rec = NULL;
        } 
        else if (strcmp(type, "RECORD") == 0) {
            MedicalRecord* r = (MedicalRecord*)malloc(sizeof(MedicalRecord));
            if (fscanf(fp, "%d %29s %49s %49s %19s %255s", 
                &r->serial_num, r->time, r->dept_name, r->doc_name, r->doc_id, r->diagnosis) != 6) { free(r); continue; }
            
            // 为子单据分配哨兵
            r->exam_head = (ExamNode*)malloc(sizeof(ExamNode)); r->exam_head->nxt = NULL;
            r->prescription_head = (PrescriptionNode*)malloc(sizeof(PrescriptionNode)); r->prescription_head->nxt = NULL;
            r->inpatient_inf = (InpatientInfo*)malloc(sizeof(InpatientInfo)); r->inpatient_inf->nxt = NULL;
            r->nxt = NULL;
            
            if (cur_pat) {
                cur_pat->record_tail->nxt = r; cur_pat->record_tail = r; cur_pat->record_count++;
                cur_rec = r;
            } else { free(r); }
        } 
        else if (strcmp(type, "EXAM") == 0) {
            ExamNode* e = (ExamNode*)malloc(sizeof(ExamNode));
            if (fscanf(fp, "%19s %255s", e->type, e->result) != 2) { free(e); continue; }
            if (cur_rec) { e->nxt = cur_rec->exam_head->nxt; cur_rec->exam_head->nxt = e; } else { free(e); }
        } 
        else if (strcmp(type, "PRESC") == 0) {
            char d_id[ID_LEN]; int qty; 
            if (fscanf(fp, "%19s %d", d_id, &qty) != 2) continue;
            DrugNode* target_drug = find_drug_by_id(d_id); // 【联动】匹配真实指针
            if (target_drug && cur_rec) {
                PrescriptionNode* pr = (PrescriptionNode*)malloc(sizeof(PrescriptionNode));
                pr->drug = target_drug; pr->quantity = qty;
                pr->nxt = cur_rec->prescription_head->nxt; cur_rec->prescription_head->nxt = pr;
            } else {
                printf("[数据异常] 行 %d: 处方找不到对应药品(%s)或无病历归属\n", line, d_id);
            }
        } 
        else if (strcmp(type, "INPATIENT") == 0) {
            InpatientInfo* in = (InpatientInfo*)malloc(sizeof(InpatientInfo));
            if (fscanf(fp, "%29s %29s %19s %d", in->admission_date, in->discharge_date, in->ward_type, &in->bed_id) != 4) { free(in); continue; }
            if (cur_rec) { in->nxt = cur_rec->inpatient_inf->nxt; cur_rec->inpatient_inf->nxt = in; } else { free(in); }
        }
    }
    fclose(fp);
}

void init_system_from_files() {
    printf("[IO] 正在装载 HIS 数据总线...\n");
    init_list_managers();
    load_dept_doc();
    load_ward_bed();
    load_pharmacy();
    load_patients_records(); // 必须在 pharmacy 之后加载，因为处方依赖药房指针
    printf("[IO] 内存多级链表映射完毕！\n\n");
}


// ==========================================
// 5. Save：将内存多级链表序列化回本地文件
// ==========================================

void save_all_data_to_files() {
    FILE* fp;
    
    // 1. 保存科室与医生
    fp = fopen("admin_dept_doc.txt", "w");
    if(fp) {
        for (Department* d = g_dept_list->dummy_head->nxt; d != NULL; d = d->nxt) {
            fprintf(fp, "DEPT %s\n", d->dept_name);
            for (Doctor* doc = d->dummy_doc_head->nxt; doc != NULL; doc = doc->nxt) {
                fprintf(fp, "DOC %s %s %s\n", doc->name, doc->id, doc->dept);
            }
        }
        fclose(fp);
    }

    // 2. 保存病房与床位
    fp = fopen("ward_bed.txt", "w");
    if(fp) {
        for (WardNode* w = g_ward_list->dummy_head->nxt; w != NULL; w = w->nxt) {
            fprintf(fp, "WARD %s %s %d %d\n", w->type, w->dept_id, w->total_beds, w->available_beds);
            for (BedNode* b = w->bed_head->nxt; b != NULL; b = b->nxt) {
                fprintf(fp, "BED %d %d %s\n", b->bed_id, b->is_occupied, b->patient_id);
            }
        }
        fclose(fp);
    }

    // 3. 保存药房数据
    fp = fopen("pharmacy.txt", "w");
    if(fp) {
        for (DrugNode* dr = g_pharmacy->dummy_head->nxt; dr != NULL; dr = dr->nxt) {
            fprintf(fp, "DRUG %s %s %s %s %s %d %.2f\n", dr->drug_id, dr->generic_name, dr->trade_name, dr->alias, dr->dept_id, dr->stock, dr->price);
            for (DrugHistory* h = dr->history_head->nxt; h != NULL; h = h->nxt) {
                fprintf(fp, "HISTORY %s %d %s\n", h->time, h->change_amount, h->action_type);
            }
        }
        fclose(fp);
    }

    // 4. 保存患者档案记录
    fp = fopen("patients_records.txt", "w");
    if(fp) {
        for (Patient* p = g_patient_list->dummy_head->nxt; p != NULL; p = p->nxt) {
            fprintf(fp, "PATIENT %s %s %d\n", p->name, p->id, p->type);
            for (MedicalRecord* r = p->record_dummy_head->nxt; r != NULL; r = r->nxt) {
                fprintf(fp, "RECORD %d %s %s %s %s %s\n", r->serial_num, r->time, r->dept_name, r->doc_name, r->doc_id, r->diagnosis);
                for (ExamNode* e = r->exam_head->nxt; e != NULL; e = e->nxt) {
                    fprintf(fp, "EXAM %s %s\n", e->type, e->result);
                }
                for (PrescriptionNode* pr = r->prescription_head->nxt; pr != NULL; pr = pr->nxt) {
                    // 保存时逆向转换：将内存指针变回药品 ID 字符串存储
                    fprintf(fp, "PRESC %s %d\n", pr->drug->drug_id, pr->quantity); 
                }
                for (InpatientInfo* in = r->inpatient_inf->nxt; in != NULL; in = in->nxt) {
                    fprintf(fp, "INPATIENT %s %s %s %d\n", in->admission_date, in->discharge_date, in->ward_type, in->bed_id);
                }
            }
        }
        fclose(fp);
    }
}