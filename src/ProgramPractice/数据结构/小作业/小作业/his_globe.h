#pragma once
//Doctor   Administrater  Patient Ward Bed 
#define ID_LEN 20      // 各种ID的最大长度（身份证、工号、流水号等）
#define NAME_LEN 50    // 名称最大长度
#define DESC_LEN 256   // 描述性文本最大长度（如病历、检查结果）
#define TIME_LEN 30
typedef struct Doctor {
	char Name[NAME_LEN];  //医生姓名
	char id[ID_LEN];	  //医生工号
	char type[ID_LEN];    //科室
	struct Operation*op;  //指向操作
	struct Doctor* nxt;   //相同科室的下一个医生信息
}Doctor;
typedef struct Operation {

}Operation;
typedef struct Department {
	char deptName[ID_LEN];//科室类型

	Doctor* Dochead;//科室医生链表
	Department* nxt;//下一个科室
};
typedef struct Patient {
	char name[NAME_LEN];  //患者姓名
	char id[ID_LEN];	  //患者id
	int type;			  //0 门诊  1  住院
	MedicalRecord* record;//医疗记录
	Patient* nxt;		  //下一个患者
}Patient;
typedef struct MedicalRecord {
//-----------------挂号信息----------------
	int serialNum;			//流水号
	char time[30];			//就诊时间
	char deptName[NAME_LEN];//门诊名称
	char docName[20];		//对应医生姓名
	char docId[20];			//医生id
	char diagnosis[DESC_LEN];//医嘱
//-----------------检查信息---------------
	ExamNode* examhead;
//-----------------住院信息---------------
	InpatientInfo* inpatientinf;//住院信息，无需链表
//-----------------处方信息---------------
	PrescriptionNode* Prescriptionhead;
	
	MedicalRecord* nxt;		//下次诊疗信息


}MedicalRecord;
//prescription exam inpatient
typedef struct PrescriptionNode {
	DrugNode*drug;			//当前药品
	int quantity;			//当前药品数量
	PrescriptionNode* nxt;  //下一药品
}PrescriptionNode;
// 药品节点
typedef struct DrugNode {
	char drug_id[ID_LEN];         // 主键：药品编号
	char generic_name[NAME_LEN];  // 通用名
	char trade_name[NAME_LEN];    // 商品名
	char alias[NAME_LEN];         // 别名
	char dept_id[ID_LEN];         // 外键：专属科室ID（如果为空字符串，则为通用药品）
	int stock;                    // 库存数量
	double price;                 // 单价
	struct DrugNode* next;
} DrugNode;
typedef struct ExamNode {
	char type[ID_LEN];
	char result[DESC_LEN];
	ExamNode* nxt;
}ExamNode;
typedef struct InpatientInfo{
	char admssionDate[TIME_LEN];
	char dischargeDate[TIME_LEN];
	char type[ID_LEN];
	int bedId;

}InpatientInfo;


typedef struct Pharmacy {//药房
	DrugNode* drughead;

}Pgarmacy;
