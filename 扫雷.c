#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#pragma warning(disable:4996)
#define E_NUM 4              //简单难度雷的数量
#define N_NUM 6              //普通难度雷的数量
#define H_NUM 8              //困难难度雷的数量
#define HANG 5               //一行5格
#define LIE  5               //一列5格
#define MINE -1              //地雷设为—1
int dif,i, j;                //dif为玩家选择的难度，i为行，j为列
int dif_sht[] = { 0,E_NUM,N_NUM,H_NUM };  //表驱动
char game_sq[HANG][LIE][3];     //定义游戏界面显示的表
int m_sq [HANG+2][LIE+2];       //定义7x7数组的雷表
int num_sq[HANG+2][LIE+2];      //定义7x7数组的数表
void init_sq();              //初始化数组
void set_m(int dif);     //布雷，只在2-11行，2-11列布雷，这样就可以避免数组越界
void m_8_num();          //统计m_sq[i][j]附近8格雷的数量
void enc();              //加密函数
int  ui();               //界面函数
int game_playing();      //游戏函数
int main() {
	int gt_res;          //用于判断是否goto的变量
	save:
	gt_res=ui();
	if (gt_res == 1) {
		system("cls");
		goto save;
	}
	init_sq();
	set_m(dif);
	m_8_num();
	getchar();
	enc();
	gt_res=game_playing();
	if (gt_res == 1) { 
		system("cls");
		goto save;
	}
	return 0;
}

void init_sq() {        

	for (i = 0; i < HANG+2; i++)
	{
		for (j = 0; j < LIE+2; j++)
		{
			m_sq[i][j] = 0;
			num_sq[i][j] = 0;
		}
		
	}
}

void set_m(int dif) {
	srand((unsigned)time(NULL));
	int cnt = 0;       //cnt为已经布置的地雷数
	while (cnt < dif_sht[dif]) {		
		i = rand() % HANG+1;
		j = rand() % LIE+1;
		if (m_sq[i][j] == 0) {   //布置地雷，if来避免重复在一个地方布置
			m_sq[i][j] = MINE;
			cnt++;
		}
	}
	for ( i = 1; i <= HANG; i++)
	{
		for ( j = 1; j <= LIE; j++)
		{
			//printf("%4d", m_sq[i][j]);    //输出雷表
		}
		//printf("\n\n");
	}

}

void m_8_num() {
	for (i = 1; i <=HANG ; i++)
	{
		for ( j = 1; j <=LIE; j++)     //只对布雷的区域进行雷数统计
		{
			for (int a = i-1; a <=i+1; a++)
			{
				for (int b = j-1; b <=j+1 ; b++)  //对第i行第j列的格子的周围八个格子进行遍历
				{
					if (m_sq[a][b] == MINE) {
						num_sq[i][j]++;

					}
				}
			}
			//printf("%-4d", num_sq[i][j]);    //输出数表
		}
		//printf("\n\n");
	}
}

void enc() {
	for (i  = 0;  i<HANG;i++)
	{
		for (j = 0; j <LIE; j++)
		{
			strcpy(game_sq[i][j], "■");
			printf("%-4s", game_sq[i][j]);   //输出游戏界面的表
		}
		printf("\n\n");
	}
}

int game_playing() {
	int a, b;           //a为玩家输入的行号，b为玩家输入的列号
	int cnt = 0;        //cnt为计数器
	int res_mes;        //游戏结束后玩家的选择
	printf("请输入行号和列号,中间用','隔开");
	scanf("%d,%d", &a, &b);
	while ((a < 1 || a>5) || (b < 1 || b>5)) {
		printf("请输入正确的数值\n");
		scanf("%d,%d", &a, &b);
	}
	while (m_sq[a][b] != MINE) {
		system("cls");
		for ( i = 0; i < HANG; i++)
		{
			for ( j = 0; j < LIE; j++)
			{
				if (i == a-1 && j == b-1) {
					itoa(num_sq[a][b], game_sq[a-1][b-1], 10);
					printf("%-4d", num_sq[a][b]);
					cnt++;
				}else{ 
					printf("%-4s", game_sq[i][j]); 
				}
				
			}
			printf("\n\n");
		}
		scanf("%d,%d", &a, &b);
		if (cnt == ((HANG * LIE) - dif_sht[dif])) {
			goto win;
		}
	}
win:if (cnt == ((HANG * LIE) - dif_sht[dif])) {
	res_mes = MessageBoxA(NULL, "您赢了！是否再来一次", "结果", MB_YESNO);
}
	if (cnt < ((HANG * LIE) - dif_sht[dif])) {
		for (i = 1; i <= HANG; i++)
		{
			for (j = 1; j <= LIE; j++)
			{
				if (m_sq[i][j] == MINE) {
					printf("%-4c", '#');
				}
				else {
					printf("%-4d", m_sq[i][j]);
				}

			}
			printf("\n\n");
		}
		res_mes = MessageBoxA(NULL, "您输了,是否再来一次", "结果", MB_YESNO);
	}
	if (res_mes == IDYES) {
		return 1;
	}else{ 
		return 0; 
	}
}
int ui() {
	printf("%60s", "扫雷");
	printf("\n→请选择难度");
	printf("\n   选择简单难度请输入'1'");
	printf("\n   选择普通难度请输入'2'");
	printf("\n   选择困难难度请输入'3'\n");
	printf("→查看操作说明请输入'4'\n");
	scanf("%d", &dif);
	if (dif < 1 || dif>4) {
		printf("请输入正确的数字");
	}
	if (dif == 4) {
		printf("最左边是第一列，最上面是第一行，#代表雷，■代表还未确认的区域");
		getchar();
		getchar();
		return 1;
	}
	else { return 0; }
}
