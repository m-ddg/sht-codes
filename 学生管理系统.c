#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#pragma warning(disable:4996)
//定义学生信息的结构体↓
typedef struct stu {
	char name[20];				 //姓名
	char gender[5];				 //性别
	int age;					 //年龄
	long long ID;		         //学号
	float score;				 //成绩
	struct stu* next;
}stu, *stt;

stt ID_node[10];           //按学号末位来划分信息要存入的链表

//初始化结点指针数组↓
void init_ID_node();

//菜单函数↓
void menu();

//退出函数↓
int quit();
int qu_res;			//quit函数的返回值

//录入信息↓
void reg_info();

//搜索信息↓
void sr_info();

//删除信息↓
void de_info();

//改动信息↓
void mod_info();

//打印信息↓
void print_info();

//保存信息↓
void save_info();

//初始化结点指针数组↓
void init_ID_node();

//创建结点↓
stt create_node();

int main() {
	int branch;
	init_ID_node();
	jump_1:
	branch = 100;          //防止下次运行到switch直接进入分支
	menu();
	scanf("%d", &branch);
	switch (branch) {
	case 0:
		qu_res = quit();
		if (qu_res == 0) {   //若选择不退出则回到菜单界面
			system("cls");
			goto jump_1;
		}
		break;
	case 1:
		reg_info();
		system("cls");
		goto jump_1;
		break;
	case 2:
		sr_info();
		system("cls");
		goto jump_1;
		break;
	case 3:
		de_info();
		system("cls");
		goto jump_1;
		break;
	case 4:
		mod_info();
		system("cls");
		goto jump_1;
		break;
	case 5:
		print_info();
		system("cls");
		goto jump_1;
		break;
	case 6:
		save_info();
		system("cls");
		goto jump_1;
		break;
	default:
		break;
	}
	return 0;
}

void menu() {
	printf("\t\t\t\t\t\t欢迎使用学生管理系统\n");
	printf("请输入数字选择功能\n");
	printf("0:退出\n");
	printf("1:录入信息\n");
	printf("2:查找信息(仅支持学号查找)\n");
	printf("3:删除信息\n");
	printf("4:改动信息\n");
	printf("5:打印信息\n");
	printf("6:保存信息\n");
}

int quit() {
	int res;
	res = MessageBoxA(NULL, "是否退出程序？", "退出程序", MB_YESNO);
		if (res == IDYES) {
			return 1;         //退出返回1
		}else{return 0; }     //不退出返回0
}

void reg_info() {
	stu temp;			   //temp用于临时保存输入的信息
	int res;
	stt pn = create_node();
	jump_2:
	printf("----------------");
	printf("\n请输入姓名\n");
	scanf("%s",temp.name);
	printf("请输入性别\n");
	scanf("%s", temp.gender);
	printf("请输入年龄\n");
	scanf("%d", &temp.age);
	printf("请输入学号\n");
	scanf("%lld", &temp.ID);
	printf("请输入成绩\n");
	scanf("%f", &temp.score);
	res = MessageBoxA(NULL, "确认录入？", "确认", MB_YESNO);
	if (res == IDNO) {
		goto jump_2;
	}
	int ID_L = temp.ID % 10;    //ID_L为学号的末位
	*pn = temp;
	pn->next = ID_node[ID_L]->next;
	ID_node[ID_L]->next = pn;
}

void sr_info() {
	long long temp_ID;           //temp_ID用以接收输入的学号
	int ID_L;                    //ID_L用来表示学号的末位数
	printf("-------------\n");
	printf("请输入学号来查找信息\n");
	scanf("%lld", &temp_ID);
	ID_L = temp_ID % 10;
	stt pn=ID_node[ID_L];
	while (pn->ID != temp_ID && pn != NULL) {
		pn = pn->next;
	}
	if (pn == NULL) {
		printf("系统尚未录入该学生信息\n");
		system("pause");
	}
	else {
		printf("姓名:%s\n",pn->name);
		printf("性别:%s\n",pn->gender);
		printf("年龄:%d\n",pn->age);
		printf("学号:%lld\n",pn->ID);
		printf("成绩:%f\n",pn->score);
		system("pause");
	}
}

void de_info() {
	long long temp_ID;           //temp_ID用以接收输入的学号
	int ID_L;                    //ID_L用来表示学号的末位数
	printf("-------------\n");
	printf("请输入想要删除信息的学号\n");
	scanf("%lld", &temp_ID);
	ID_L = temp_ID % 10;
	stt pn = ID_node[ID_L];      //pn快指针
	stt qn = NULL;               //qn慢指针
	while (pn->ID != temp_ID && pn != NULL) {
		qn = pn;
		pn = pn->next;
	}
	if (pn == NULL) {
		printf("系统尚未录入该学生信息\n");
		system("pause");
	}
	else {
		int res = MessageBoxA(NULL, "确定删除该学生的信息？", "删除信息", MB_YESNO);
		if (res == IDYES) {
			qn->next = pn->next;
		}
	}
}

void mod_info() {
	long long temp_ID;           //temp_ID用以接收输入的学号
	int ID_L;                    //ID_L用来表示学号的末位数
	printf("-------------\n");
	printf("请输入学号来改动信息\n");
	scanf("%lld", &temp_ID);
	ID_L = temp_ID % 10;
	stt pn = ID_node[ID_L];
	while (pn->ID != temp_ID && pn != NULL) {
		pn = pn->next;
	}
	if (pn == NULL) {
		printf("系统尚未录入该学生信息\n");
		system("pause");
	}
	else {
		int samp;
		printf("请输入对应数字来选择要改变的信息\n");
		printf("1.名字\n");
		printf("2.性别\n");
		printf("3.年龄\n");
		printf("4.学号\n");
		printf("5.成绩\n");
		scanf("%d", &samp);
		printf("请输入新的信息\n");
		switch (samp) {
		case 1: {
			char temp_name[20];
			scanf("%s", temp_name);
			strcpy(pn->name, temp_name);
		}
			  break;
		case 2: {
			char temp_gender[5];
			scanf("%s", temp_gender);
			strcpy(pn->gender, temp_gender);
		}
			  break;
		case 3: {
			int temp_age;
			scanf("%d", &temp_age);
			pn->age = temp_age;
		}
			  break;
		case 4: {
			long long temp_ID;
			scanf("%lld", &temp_ID);
			pn->ID = temp_ID;
		}
			  break;
		case 5: {
			float temp_score;
			scanf("%f", &temp_score);
			pn->score = temp_score;
		}
			  break;
		default:
			break;
		}
	}
	printf("修改成功\n");
	system("pause");
}

void print_info() {
	int cnt=0;				
	stt pn = NULL;
	printf("-------------\n");
	for (int i = 0; i < 10; i++)
	{
		pn = ID_node[i]->next;
		if (pn == NULL) { cnt++; }
		while (pn) {
			printf("姓名：%s\n",pn->name);
			printf("性别：%s\n",pn->gender);
			printf("年龄：%d\n",pn->age);
			printf("学号：%lld\n",pn->ID);
			printf("成绩：%f\n",pn->score);
			pn = pn->next;
			system("pause");
		}
	}
	if (cnt == 10) {
		printf("尚未录入任何学生的信息\n");
		system("pause");
	}
}

void save_info() {
	FILE* fp = fopen("D://stu_info.data", "a+");
	if (fp == NULL) {
		printf("保存失败\n");
		system("pause");
		goto jump_3;
	}
	for (int i = 0; i < 10; i++)
	{
		stt p = malloc(sizeof(stu));
		p = ID_node[i]->next;
		while (p) {
			fwrite(p, sizeof(stu), 1, fp);
			p = p->next;
		}
		free(p);
	}
	fclose(fp);
	MessageBoxA(NULL, "成功保存", "保存成功", MB_OK);
	jump_3:;
}

void init_ID_node() {
	for (int i = 0; i < 10; i++) {
		ID_node[i] = create_node();
		ID_node[i]->next = NULL;
	}
}

stt create_node() {
	stt node = (stt)malloc(sizeof(stu));
	return node;
}
