#include "his_global .h"
#include <stdio.h>
#include <string.h> 

//-------------------------------------查找--------------------------------------------------------------------
Doctor* find_doctor_by_id(const char* input_id) {

//    if (Hos == NULL || Hos->dept_head == NULL) return NULL;

    Department* dept_cur = g_dept_list->dummy_head;

    while (dept_cur != NULL) {
        Doctor* doc_cur = dept_cur->dummy_doc_head;
        Doctor* doc_last = NULL;
        while (doc_cur != NULL) {

            if (strcmp(doc_cur->id, input_id) == 0) {

                return doc_last;
            }
            doc_last = doc_cur;
            doc_cur = doc_cur->nxt;
        }
        
        dept_cur = dept_cur->nxt;
    }

    printf("未找到该医生信息，请重新检查工号输入是否正确。\n");
    return NULL;
}

Patient* find_patient_by_id(const char* input_id) {
    Patient* pat_cur = g_patient_list->dummy_head;
    while (pat_cur != NULL) {
        if (strcmp(pat_cur->id, input_id) == 0) {
            
            return pat_cur;
        }
        pat_cur = pat_cur->nxt;
    }

    printf("未找到该患者信息，请重新检查患者信息输入是否正确。\n");
    return NULL;
}

DrugNode* find_drug_by_id(const char* input_id) {
    DrugNode* drug_cur = g_pharmacy->dummy_head;
    while (drug_cur != NULL) {
        if (strcmp(drug_cur->drug_id, input_id) == 0 || strcmp(drug_cur->trade_name, input_id) == 0 || strcmp(drug_cur->generic_name, input_id) == 0 ||
            strcmp(drug_cur->alias, input_id) == 0)
            return drug_cur;
        drug_cur = drug_cur->nxt;
    }
    printf("未找到该药品信息，请重新检查药品信息输入是否正确。\n");
    return NULL;
}

Department* find_dept_by_id(const char* input_id) {
 //   if (Hos == NULL || Hos->dept_head == NULL) return NULL;

    Department* dept_cur = g_dept_list->dummy_head;
 //   Department* dept_last =NULL;
    while (dept_cur != NULL) {
    if (strcmp(dept_cur->dept_name, input_id) == 0) {

                return dept_cur;
    }

        dept_cur = dept_cur->nxt;
    }

    printf("未找到该医生信息，请重新检查工号输入是否正确。\n");
    return NULL;
}
//------------------------------------------找------------------------------------------------------------
void delete_doctor_by_id(const char* input_id) {
//    if (Hos == NULL || Hos->dept_head == NULL) return NULL;


    Doctor* doc_last = find_doctor_by_id(input_id);
    g_dept_list->count--;
    Doctor* doc_cur = doc_last->nxt;
    doc_last->nxt = doc_cur->nxt;
    free(doc_cur);
}


void delete_patient_by_id(const char* input_id) {
  //  if (Hos == NULL || Hos->dept_head == NULL) return NULL;

    Patient* pat_last = find_patient_by_id(input_id);
    g_patient_list->count--;
    Patient* pat_cur = pat_last->nxt;
    if (pat_cur == g_patient_list->tail) {
        g_patient_list->tail = pat_last;
    }
    else pat_last->nxt = pat_cur->nxt;
    free(pat_cur);
}

//----------------------------------------增---------------------------------------------------------------
void add_patient(const char* input_id) {
    Patient* n_pat = (Patient*)malloc(sizeof(Patient));
    Patient* a = find_patient_by_id(input_id);
    if (a != NULL) {
        printf("你加个沟把\n");
        return;
    }
    strcpy(n_pat->id,input_id);
    n_pat->nxt = NULL;
    g_patient_list->tail->nxt = n_pat;
    g_patient_list->tail = n_pat;
    g_patient_list->count++;
}

void insert_doctor_to_dept(const char* input_id,const char* dpt_id) {
    Doctor* n_doc = (Doctor*)malloc(sizeof(Doctor));
    Doctor* a = find_doctor_by_id(input_id);
    if (a != NULL) {
        printf("你加个沟把\n");
        return;
    }
    Department* dpt = find_dept_by_id(dpt_id);
    strcpy(n_doc->id, input_id);
    n_doc->nxt = NULL;
    dpt->tail->nxt = n_doc;
    dpt->tail = n_doc;
}

void add_department(const char* input_id) {
    Department* n_dpt = (Department*)malloc(sizeof(Department));
    Department* a = find_dept_by_id(input_id);
    if (a != NULL) {
        printf("你加个沟把\n");
        return;
    }
    strcpy(n_dpt->dept_name, input_id);
    g_dept_list->tail->nxt = n_dpt;
    g_dept_list->tail = n_dpt;
    g_dept_list->count++;
}
//----------------------------------------更新----------------------------------------------------------------------
void update_patient(char* id, char* n_name, int type) {
    Patient* t_pat = find_patient_by_id(id);
    strcpy(t_pat->name , n_name);
    t_pat->type = type;
}

void update_doctor(char* id, char* n_name, int type) {
    Doctor* t_doc = find_doctor_by_id(id);
    strcpy(t_doc->name, n_name);

}

void trans_patient(const char* patient_id, const char* o_dpt, const char* t_dpt) {
    Patient* pat = find_patient_by_id(patient_id);

}
