/*
* 
*  title：电脑报价系统
*  author：Master
*  Date：2020/2
*
*/



#include<stdio.h>
#include <conio.h> //getch函数/ 
#include<windows.h> 
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

//#define gets gets_s

int User_Interface_flag_position = 1;					//在第一级菜单的状态
int User_Interface_admin_flag_position = 1;				//在第一级管理员菜单的状态
int User_Interface_admin_flag_position_one = 1;			//在第二级管理员菜单第一个（信息添加）的状态
int User_Interface_admin_flag_position_one_fir = 1;		//在第二级管理员菜单第一个（信息添加里的CPU）的状态
int User_Interface_admin_flag_position_one_for = 1;		//在第二级管理员菜单第一个（信息添加里的显卡）的状态
int infoemation_input_recognition = 1;					//信息添加界面信息录入时识别的
int all_position = 0;									//switch 里对应哪一个菜单选取的变量---注意可以改成枚举 enmb
int Add_delet_modification = 1;							//在管理员界面公用一个交互界面 用此数字来区分进入那个系统
//下面是顾客系统的函数声明
int Costumer_Interface_flag_position=1;					//选顾客服务界面的变量
int User_Interface_costomer_flag_position_one=1;		//在第二级选硬件那一栏的
int User_Interface_costomer_flag_position_one_sss=1;	//在第二级选CPU那一栏的的子菜单
int User_Interface_costomer_flag_position_one_fov=1;	//在第二级选CPU那一栏的的子菜单
int costomer_information_search=1;						//信息查询用于识别打开文件的


struct costomer_select_information *head=NULL;
struct costomer_select_information *data_temp=NULL;
struct costomer_select_information *mp=NULL;
struct costomer_select_information *pm=NULL;
struct costomer_select_information *plo=NULL;			//购物车链表用的变量
int flag=0;												//确定链表是否已有了 有为1 没有为0

//硬件信息结构体
struct information
{
	char Temp_Model[128];		//型号
	char Temp_Date[12];			//发布日期
	char Temp[128];				//详情
	char Temp_Price[128];		//价格
};
struct costomer_select_information		//双向链表 链表 链表 链表 用于保存用户购物车信息
{
	struct costomer_select_information *prior;
	char Temp_Model[128];				//硬件数据-型号
	char Temp_Date[12];					//硬件数据-日期
	char Temp[128];						//硬件数据-备注
	char Temp_Price[128];				//硬件数据-价格
	int num;							//购物车数据-数量
	int recognize;						//购物车数据-识别符 1~12 和菜单同一个定义
	struct costomer_select_information *next;
};

void User_Interface_main(void);			//all_position--->0
void User_Interface_case_1(void);
void User_Interface_case_2(void);
void User_Interface_admin_first(void);	//all_position--->1
void User_Interface_customer_first_head(void);//all_position--->2
void User_Interface_admin_second(void);
void User_Interface_admin_second_UI_A(void);
void User_Interface_admin_second_UI_B(void);
void User_Interface_admin_second_UI_C(void);
void User_Interface_admin_third_one(void);
void User_Interface_admin_third_one_caseA(void);
void User_Interface_admin_third_one_caseB(void);
void User_Interface_admin_third_one_caseC(void);
void User_Interface_admin_third_one_caseD(void);
void User_Interface_admin_third_one_caseE(void);
void User_Interface_admin_third_one_caseF(void);
void User_Interface_admin_third_one_caseG(void);
void User_Interface_admin_third_one_caseH(void);
void User_Interface_admin_third_one_caseI(void);
void User_Interface_admin_third_one_caseJ(void);
void User_Interface_admin_third_one_caseA_Index(void);
void User_Interface_admin_third_one_caseA1(void);
void User_Interface_admin_third_one_caseA2(void);
void User_Interface_admin_third_one_caseD_Index(void);
void User_Interface_admin_third_one_caseD1(void);
void User_Interface_admin_third_one_caseD2(void);
void User_Interface_admin_third_two(void);
void User_Interface_admin_third_three(void);
void User_Interface_admin_information_input(void);
void User_Interface_admin_information_delet(void);
void User_Interface_admin_information_modification(void);

//下面是顾客系统的函数声明
void Costumer_Interface_caseA(void);
void Costumer_Interface_caseB(void);
void Costumer_Interface_caseC(void);
void User_Interface_customer_first(void);
void User_Interface_customer_second(void);
void User_Interface_customer_third(void);
void User_Interface_customer_third_one_caseA(void);
void User_Interface_customer_third_one_caseB(void);
void User_Interface_customer_third_one_caseC(void);
void User_Interface_customer_third_one_caseD(void);
void User_Interface_customer_third_one_caseE(void);
void User_Interface_customer_third_one_caseF(void);
void User_Interface_customer_third_one_caseG(void);
void User_Interface_customer_third_one_caseH(void);
void User_Interface_customer_third_one_caseI(void);
void User_Interface_customer_third_one_caseJ(void);
void User_Interface_customer_third_one_caseA_Index(void);
void User_Interface_customer_third_one_caseA1(void);
void User_Interface_customer_third_one_caseA2(void);
void User_Interface_customer_third_one_caseD_Index(void);
void User_Interface_customer_third_one_caseD1(void);
void User_Interface_customer_third_one_caseD2(void); 

void customer_Hardware_all(void);
void Text_sorting(char p[30]);
void color_egg();
void recursur();
void first_examine();

//下面是函数声明
void gotoxy(int x, int y);//用于调整光标指向 使用方法 调用 gotoxy(a,b) 把光标指向a b位置


int main()
{
	first_examine();
//获取系统时间-----------------------
	time_t tmpcal_ptr;
	struct tm *tmp_ptr = NULL;
	time(&tmpcal_ptr);
	tmp_ptr = gmtime(&tmpcal_ptr);
	tmp_ptr = localtime(&tmpcal_ptr);
	if(tmp_ptr->tm_hour>=19||tmp_ptr->tm_hour<=6)//夜间模式
	{
		system("color 07");
	}
	else//白天模式
	{
		system("color F3");
	}
	
//获取系统时间-----------------------
//设定标题----------------------------
	SetConsoleTitle("电脑报价系统");
//设定标题----------------------------
	while (1)
	{
		switch (all_position)
		{
		case 0:User_Interface_main(); break;
		case 1:User_Interface_admin_first(); break;
		case 2:User_Interface_customer_first_head(); break;
		}
	}
	return 0;
}
void User_Interface_main(void)
{

	time_t tmpcal_ptr;
	struct tm *tmp_ptr = NULL;
	int time_temp=0;
	char temp = '\0';
	if (User_Interface_flag_position == 1)
		User_Interface_case_1();
	else if (User_Interface_flag_position == 2)
		User_Interface_case_2();
	else
	{
		printf("参数错误 请关闭程序重试");
		User_Interface_case_1();
	}
	time(&tmpcal_ptr);
	tmp_ptr = gmtime(&tmpcal_ptr);
	tmp_ptr = localtime(&tmpcal_ptr);
	time_temp=tmp_ptr->tm_sec;
	printf ("欢迎使用本系统 \n当前时间为 ：%d.%02d.%02d ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
	printf("%02d:%02d:%02d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
	while (1)
	{
		fflush(stdin);
		time(&tmpcal_ptr);
		tmp_ptr = gmtime(&tmpcal_ptr);
		tmp_ptr = localtime(&tmpcal_ptr);
		if(kbhit())
		{
			temp = getch();
			if (temp == 'W' || temp == 'S') //优化建议：此处使用键盘小箭头操作需要其他函数
			{
				if (User_Interface_flag_position == 1)
				{
					User_Interface_case_2();
					User_Interface_flag_position = 2;
					printf ("欢迎使用本系统 \n当前时间为 ：%d.%02d.%02d ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
					printf("%02d:%02d:%02d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
				}
				else
				{
					User_Interface_case_1();
					User_Interface_flag_position = 1;
					printf ("欢迎使用本系统 \n当前时间为 ：%d.%02d.%02d ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
					printf("%02d:%02d:%02d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
				}
			}
			else if (temp == 'E')
			{
				if (User_Interface_flag_position == 1)//进入顾客系统
				{
					User_Interface_customer_first_head();
					all_position = 2;
					User_Interface_case_1();
				}
				else if (User_Interface_flag_position == 2)//进入管理员系统
				{
					User_Interface_admin_first();
					all_position = 1;
					User_Interface_case_2();
				}
			}
			else
				continue;
			temp = '\0';	
		}	
		else if(tmp_ptr->tm_sec!=time_temp)
		{
			time(&tmpcal_ptr);
			tmp_ptr = gmtime(&tmpcal_ptr);
			tmp_ptr = localtime(&tmpcal_ptr);
			time_temp=tmp_ptr->tm_sec;

			gotoxy(0,8);
			printf ("欢迎使用本系统 \n当前时间为 ：%d.%02d.%02d ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
			printf("%02d:%02d:%02d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
		}
	}
	return;
}
void User_Interface_admin_first(void)
{
	FILE* Ac = NULL;
	int i;
	char account[33], password[64];
	char account_file[7], password_file[7];
reinput://--------------------------------------------------------------------------------------------------GOTO语句01 终止点
	system("cls");
	puts("      *电脑报价系统*");
	puts("         (管理员)");
	puts("|------------------------|");
	puts("|账号:");
	puts("|------------------------|");
	puts("|密码:");
	puts("|------------------------|");
	puts("|在账号栏输入Exit退出输入|");
	puts("|------------------------|");
	gotoxy(6, 3);
	gets(account);
	if (!strcmp(("Exit"), account))
		return;
	gotoxy(6, 5);
//密码输入界面
	i=0;
	do
    {
        password[i]=getch();
        if(password[i]=='\r')
            break;
        if(password[i]=='\b')
        {
            if(i==0)
            {
                printf("\a");
                continue;
            }
            i=i-1;
            printf("\b \b");
        }
        else
        {
            i=i+1;
            printf("*");
        }
    }while(password[i]!='\n' && i<20);

	password[i] = '\0';


	Ac = fopen("data\\Accont.Ac", "r");
	if (Ac == NULL)
	{
		printf("\n\n\n\n密匙文件打开失败 返回上一级界面");
		Sleep(1000);
		all_position = 0;
		return;
	}
	fseek(Ac, 0L, SEEK_SET);//定位到文件头 读取用户名
	fgets(account_file, 6, Ac);
	fseek(Ac, 395520L, SEEK_SET);//定位到395520字节处 读取密码
	fgets(password_file, 7, Ac);
	//if(!strcmp(account, "Bad Apple"))
	//{
	//	color_egg();
	//	return ;
	//}
	if (strcmp(account, account_file))
	{
		MessageBox(NULL,"账号输入错误","Tips",MB_OK|MB_DEFBUTTON1);
		goto reinput;//--------------------------------------------------------------------------------------------------GOTO语句01 起始点
	}
	if (strcmp(password, password_file))
	{
		MessageBox(NULL,"密码输入错误","Tips",MB_OK|MB_DEFBUTTON1);
		goto reinput;//--------------------------------------------------------------------------------------------------GOTO语句01 起始点
	}
	if (!strcmp(password, password_file) && !strcmp(account, account_file))
	{
		printf("\n\n\n\n输入正确");
		fclose(Ac);
		User_Interface_admin_second();
	}
	fclose(Ac);
	return;
}
void User_Interface_customer_first_head(void)
{
	char temp='\0';
	if(Costumer_Interface_flag_position==1)
		Costumer_Interface_caseA();
	else if(Costumer_Interface_flag_position==2)
		Costumer_Interface_caseB();
	else if(Costumer_Interface_flag_position==3)
		Costumer_Interface_caseC();
	while(1)
	{
		if(temp=getch())
		{
			if(temp=='Q')
			{
				User_Interface_case_1();
				return ;
			}
				
			if(temp=='S')
				Costumer_Interface_flag_position++;
			if(temp=='W')
				Costumer_Interface_flag_position--;
			if(temp=='E')
			{
				if(Costumer_Interface_flag_position==1)
       	        	User_Interface_customer_first();
				else if(Costumer_Interface_flag_position==2)
					User_Interface_customer_second();
				else if(Costumer_Interface_flag_position==3)
					User_Interface_customer_third();
			}

			if(Costumer_Interface_flag_position==4)
				Costumer_Interface_flag_position=1;
			if(Costumer_Interface_flag_position==0)
				Costumer_Interface_flag_position=3;
			if(Costumer_Interface_flag_position==1)
			{ 
				Costumer_Interface_caseA();
					}
			else if(Costumer_Interface_flag_position==2)
			{
				Costumer_Interface_caseB();
			}
			else if(Costumer_Interface_flag_position==3)
			{
				Costumer_Interface_caseC();
			}
		}
	}
	return;
}
void User_Interface_admin_second(void)//-------------------------------------
{
	char temp = '\0';
	if (User_Interface_admin_flag_position == 1)
		User_Interface_admin_second_UI_A();
	else if (User_Interface_admin_flag_position == 2)
		User_Interface_admin_second_UI_B();
	else if (User_Interface_admin_flag_position == 3)
		User_Interface_admin_second_UI_C();
	else;
	while (1)
	{
		if (temp = getch())
		{
			if (temp == 'E')
			{
				if (User_Interface_admin_flag_position == 1)
				{
					Add_delet_modification = 1;
					User_Interface_admin_third_one();

				}
				else if (User_Interface_admin_flag_position == 2)
				{
					Add_delet_modification = 2;
					User_Interface_admin_third_two();

				}
				else if (User_Interface_admin_flag_position == 3)
				{
					Add_delet_modification = 3;
					User_Interface_admin_third_three();

				}
				else;
			}
			if (temp == 'Q')
			{
				User_Interface_case_2();
				return;
			}
			if (temp == 'W')
				User_Interface_admin_flag_position--;
			if (temp == 'S')
				User_Interface_admin_flag_position++;
			if (User_Interface_admin_flag_position == 0)
				User_Interface_admin_flag_position = 3;
			if (User_Interface_admin_flag_position == 4)
				User_Interface_admin_flag_position = 1;
			if (User_Interface_admin_flag_position == 1)
			{
				User_Interface_admin_second_UI_A();
			}
			else if (User_Interface_admin_flag_position == 2)
			{
				User_Interface_admin_second_UI_B();
			}
			else if (User_Interface_admin_flag_position == 3)
			{
				User_Interface_admin_second_UI_C();
			}


		}
	}
	return;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
//------------------------------------------UI界面索引函数
void User_Interface_admin_information_input(void)
{
	struct information temp;
	FILE* fp = NULL;
	system("cls");
	puts("   信息录入系统");
	puts("*输入Exit离开此界面*");
	switch (infoemation_input_recognition)
	{
	case 1:
		puts("   AMD CPU录入");
		fp = fopen("data\\#Info_Amd.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 2:puts("   Intel CPU录入");
		fp = fopen("data\\#Info_Intel.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 3:puts("   主板 信息录入");
		fp = fopen("data\\#Info_Motherboard.Ac", "r+");
		if (fp == NULL)
		{
			puts("   文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 4:puts("   内存 信息录入");
		fp = fopen("data\\#Info_Memory.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 5:puts("   AMD 显卡录入");
		fp = fopen("data\\#Info_ATI.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 6:puts("   英伟达 显卡录入");
		fp = fopen("data\\#Info_NVIDIA.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 7:puts("   硬盘 信息录入");
		fp = fopen("data\\#Info_Disk.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 8:puts("   机箱 信息录入");
		fp = fopen("data\\#Info_Computer_Case.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 9:puts("   电源 信息录入");
		fp = fopen("data\\#Info_Power_Supply.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 10:puts("   显示器 信息录入");
		fp = fopen("data\\#Info_Monitor.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 11:puts("   鼠标 信息录入");
		fp = fopen("data\\#Info_Mouse.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 12:puts("   键盘 信息录入");
		fp = fopen("data\\#Info_Keyboard.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	default:return;
	}
	puts("|-------------------------------|");
	puts("|输入型号:                      |");
	puts("|-------------------------------|");
	puts("|输入发布日期:                  |");
	puts("|-------------------------------|");
	puts("|输入价格:                      |");
	puts("|-------------------------------|");
	puts("|输入其他备注:                  |");
	puts("|-------------------------------|");
	gotoxy(10, 4);
	gets(temp.Temp_Model);
	if (!strcmp(("Exit"), temp.Temp_Model))
		return;
	gotoxy(14, 6);
	gets(temp.Temp_Date);
	if (!strcmp(("Exit"), temp.Temp_Date))
		return;
	gotoxy(10, 8);
	scanf("%s", temp.Temp_Price);
	fflush(stdin);
	gotoxy(14, 10);
	gets(temp.Temp);
	if (!strcmp(("Exit"), temp.Temp))
		return;
	fseek(fp, 0L, SEEK_END);
	fprintf(fp, "#%s/%s/%s/%s&", temp.Temp_Model, temp.Temp_Date, temp.Temp_Price, temp.Temp);
	fputc('\n', fp);
	printf("\n");
	puts("文件写入成功");
	Sleep(1000);
	fclose(fp);
	return;
}

void User_Interface_admin_third_one(void)
{
	char temp = '\0';
	if (User_Interface_admin_flag_position_one == 1)
	{
		User_Interface_admin_third_one_caseA();
	}
	else if (User_Interface_admin_flag_position_one == 2)
		User_Interface_admin_third_one_caseB();
	else if (User_Interface_admin_flag_position_one == 3)
		User_Interface_admin_third_one_caseC();
	else if (User_Interface_admin_flag_position_one == 4)
		User_Interface_admin_third_one_caseD();
	else if (User_Interface_admin_flag_position_one == 5)
		User_Interface_admin_third_one_caseE();
	else if (User_Interface_admin_flag_position_one == 6)
		User_Interface_admin_third_one_caseF();
	else if (User_Interface_admin_flag_position_one == 7)
		User_Interface_admin_third_one_caseG();
	else if (User_Interface_admin_flag_position_one == 8)
		User_Interface_admin_third_one_caseH();
	else if (User_Interface_admin_flag_position_one == 9)
		User_Interface_admin_third_one_caseI();
	else if (User_Interface_admin_flag_position_one == 10)
		User_Interface_admin_third_one_caseJ();
	while (1)
	{
		if (temp = getch())
		{
			if (temp == 'Q')
			{
				User_Interface_admin_second_UI_A();
				return;
			}
			if (temp == 'W')
				User_Interface_admin_flag_position_one--;
			if (temp == 'S')
				User_Interface_admin_flag_position_one++;
			if (User_Interface_admin_flag_position_one == 0)
				User_Interface_admin_flag_position_one = 10;
			if (User_Interface_admin_flag_position_one == 11)
				User_Interface_admin_flag_position_one = 1;

			if (User_Interface_admin_flag_position_one == 1)
				User_Interface_admin_third_one_caseA();
			if (User_Interface_admin_flag_position_one == 2)
				User_Interface_admin_third_one_caseB();
			if (User_Interface_admin_flag_position_one == 3)
				User_Interface_admin_third_one_caseC();
			if (User_Interface_admin_flag_position_one == 4)
				User_Interface_admin_third_one_caseD();
			if (User_Interface_admin_flag_position_one == 5)
				User_Interface_admin_third_one_caseE();
			if (User_Interface_admin_flag_position_one == 6)
				User_Interface_admin_third_one_caseF();
			if (User_Interface_admin_flag_position_one == 7)
				User_Interface_admin_third_one_caseG();
			if (User_Interface_admin_flag_position_one == 8)
				User_Interface_admin_third_one_caseH();
			if (User_Interface_admin_flag_position_one == 9)
				User_Interface_admin_third_one_caseI();
			if (User_Interface_admin_flag_position_one == 10)
				User_Interface_admin_third_one_caseJ();
			if (temp == 'E')
			{
				if (User_Interface_admin_flag_position_one == 1)
				{
					User_Interface_admin_third_one_caseA_Index();
				}
				else if (User_Interface_admin_flag_position_one == 2)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}

					else;
					User_Interface_admin_third_one_caseB();
				}
				else if (User_Interface_admin_flag_position_one == 3)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseC();
				}
				else if (User_Interface_admin_flag_position_one == 4)
				{
					User_Interface_admin_third_one_caseD_Index();
				}
				else if (User_Interface_admin_flag_position_one == 5)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseE();
				}
				else if (User_Interface_admin_flag_position_one == 6)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseF();
				}
				else if (User_Interface_admin_flag_position_one == 7)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseG();
				}
				else if (User_Interface_admin_flag_position_one == 8)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseH();
				}
				else if (User_Interface_admin_flag_position_one == 9)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseI();

				}
				else if (User_Interface_admin_flag_position_one == 10)
				{
					if (Add_delet_modification == 1)
						User_Interface_admin_information_input();
					else if (Add_delet_modification == 2)
					{
						User_Interface_admin_information_delet();
					}

					else if (Add_delet_modification == 3)
					{
						User_Interface_admin_information_modification();
					}
					else;
					User_Interface_admin_third_one_caseJ();
				}
			}
		}
	}
}
void User_Interface_admin_third_two(void)//信息删除
{
	system("cls");
	User_Interface_admin_third_one();
	system("cls");
	return;
}
void User_Interface_admin_third_three(void)
{
	system("cls");
	User_Interface_admin_third_one();
	system("cls");
	return;
}

void User_Interface_admin_third_one_caseA_Index(void)
{
	char temp = '\0';
	if (User_Interface_admin_flag_position_one_fir == 1)
		User_Interface_admin_third_one_caseA1();
	else if (User_Interface_admin_flag_position_one_fir == 2)
		User_Interface_admin_third_one_caseA2();
	while (1)
	{
		if (temp = getch())//无回显输入  
		{
			if (temp == 'Q')
			{
				User_Interface_admin_third_one_caseA();
				return;
			}
			if (temp == 'W')
				User_Interface_admin_flag_position_one_fir--;
			if (temp == 'S')
				User_Interface_admin_flag_position_one_fir++;
			if (User_Interface_admin_flag_position_one_fir == 3)
				User_Interface_admin_flag_position_one_fir = 1;
			if (User_Interface_admin_flag_position_one_fir == 0)
				User_Interface_admin_flag_position_one_fir = 2;

			if (temp == 'E')
				if (Add_delet_modification == 1)
					User_Interface_admin_information_input();
				else if (Add_delet_modification == 2)
				{
					User_Interface_admin_information_delet();
				}

				else if (Add_delet_modification == 3)
				{
					User_Interface_admin_information_modification();
				}
				else;

			if (User_Interface_admin_flag_position_one_fir == 1)
			{
				User_Interface_admin_third_one_caseA1();
			}
			if (User_Interface_admin_flag_position_one_fir == 2)
			{
				User_Interface_admin_third_one_caseA2();
			}



		}
	}
	return;
}
void User_Interface_admin_third_one_caseD_Index(void)
{
	char temp = '\0';
	if (User_Interface_admin_flag_position_one_for == 1)
		User_Interface_admin_third_one_caseD1();
	else if (User_Interface_admin_flag_position_one_for == 2)
		User_Interface_admin_third_one_caseD2();
	while (1)
	{
		if (temp = getch())//无回显输入  
		{
			if (temp == 'Q')
			{
				User_Interface_admin_third_one_caseD();
				return;
			}
			if (temp == 'W')
				User_Interface_admin_flag_position_one_for--;
			if (temp == 'S')
				User_Interface_admin_flag_position_one_for++;
			if (User_Interface_admin_flag_position_one_for == 3)
				User_Interface_admin_flag_position_one_for = 1;
			if (User_Interface_admin_flag_position_one_for == 0)
				User_Interface_admin_flag_position_one_for = 2;

			if (temp == 'E')
				if (Add_delet_modification == 1)
					User_Interface_admin_information_input();
				else if (Add_delet_modification == 2)
				{
					User_Interface_admin_information_delet();
				}

				else if (Add_delet_modification == 3)
				{
					User_Interface_admin_information_modification();
				}
				else;

			if (User_Interface_admin_flag_position_one_for == 1)
			{
				User_Interface_admin_third_one_caseD1();
			}
			if (User_Interface_admin_flag_position_one_for == 2)
			{
				User_Interface_admin_third_one_caseD2();
			}

		}
	}
	return;
}
void User_Interface_admin_information_delet()
{
	int i, n, M, flag = 0,resault=0;
	long int temp_address_A, temp_address_B, delet_start = -1, delet_end = -1, temp;
	char search[128], ch;
	FILE* fp = NULL;
search://-------------------------------------------------------------------goto语句终点
	system("cls");
	puts("    *信息删除操作*");

	switch (infoemation_input_recognition)
	{
	case 1:
		puts("     AMD CPU删除");
		fp = fopen("data\\#Info_Amd.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 2:puts("     Intel CPU删除");
		fp = fopen("data\\#Info_Intel.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 3:puts("     主板 信息删除");
		fp = fopen("data\\#Info_Motherboard.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 4:puts("     内存 信息删除");
		fp = fopen("data\\#Info_Memory.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 5:puts("     AMD 显卡删除");
		fp = fopen("data\\#Info_ATI.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 6:puts("     英伟达 显卡删除");
		fp = fopen("data\\#Info_NVIDIA.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 7:puts("     硬盘 信息删除");
		fp = fopen("data\\#Info_Disk.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 8:puts("     机箱 信息删除");
		fp = fopen("data\\#Info_Computer_Case.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 9:puts("     电源 信息删除");
		fp = fopen("data\\#Info_Power_Supply.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 10:puts("     显示器 信息删除");
		fp = fopen("data\\#Info_Monitor.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 11:puts("     鼠标 信息删除");
		fp = fopen("data\\#Info_Mouse.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 12:puts("     键盘 信息删除");
		fp = fopen("data\\#Info_Keyboard.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	default:return;
	}
	puts("输入Exit退出");
	puts("输入要查询的内容");
	puts("-----------------------------------");
	printf("\n");
	puts("-----------------------------------");
	gotoxy(0, 5);
	gets(search);
	gotoxy(0, 7);
	if (!strcmp(search, ("Exit")))
		return;
	//退出条件1
	fseek(fp, 0L, SEEK_SET);//文件指针归零
	printf("\n");





//文件内容查询模块-----------------------------------------------------------




	temp_address_A = ftell(fp); temp_address_B = ftell(fp); temp = ftell(fp);
	resault=0;
	while (!feof(fp))//以文件是否结束为判断条件
	{
		ch = fgetc(fp);//取出一个字符
		if (ch != search[0])//如果这个字符连第一个都不匹配 则进入下一次循环
			continue;
		else//验证后续字符
		{
			temp_address_A = ftell(fp);//储存当前fp的位置 暂存 如果相同可以直接调用 不相同可以恢复
			for (i = 1; search[i]; i++)//进行后续验证
			{
				ch = fgetc(fp);//取字符
				if (ch != search[i])//如果此处不相等，一下进行归位 B为恢复指针时用的临时变量
				{
					temp_address_B = ftell(fp);//不相等位置的下一个字节
					n = temp_address_B - temp_address_A;
					for (M = 1; M < n; M++)
						fseek(fp, -1L, SEEK_CUR);//返回原位置的下一个字节 检验
					temp_address_B = temp_address_A;
					break;
				}
			}
		}/*
		此处出来有两种情况 
		1 检测完成,符合查找条件 search[i]=='\0'  temp_address_A在第一个结果的信息段内
		2 不符合查找条件 search[i]!='\0'   fp指针归位 其他变量无关
		*/
	if (search[i] == '\0')//检测完成判断
		{	
			resault++;
			ch = fgetc(fp);//-----------------------------反向查询 直到碰到标识符
			fseek(fp, -1L, SEEK_CUR);
			while (ch != '#')
			{
				fseek(fp, -2L, SEEK_CUR);
				ch = fgetc(fp);

			}//此方法出循环恰好从#下一位输出
			if(delet_start==-1)
				delet_start = ftell(fp) - 1;
			ch = fgetc(fp);
			while (ch != '&')
			{
				if (ch != '#')
					printf("%c", ch);
				ch = fgetc(fp);
			}
			if (delet_end == -1)
				delet_end = ftell(fp) - 1;
			printf("\n");//输出搜索的文字-------------------------------------
			/* 此时已经记录了该被删除的文字段*/
		}
	}
	if(resault==0)
	{
		puts("查询不到此内容 请重试");
		Sleep(1000);
		fclose(fp);
		goto search;
		return;
	}


	//printf("程序测试 %d %d\n",delet_start,delet_end);

//----------------文件查询模块 2020 2 8修改---------------------------------------



	//此时fp的位置在要搜索内容串的第一位结束可以以 &判断
	if (delet_end != -1)
	{
		printf("*共有%d个查询结果*\n",resault);
		puts("|---------------------|");
		puts("|1:输入NO    重新搜索  |");
		puts("|---------------------|");
		puts("|2:输入YES   删除      |");
		puts("|---------------------|");
		puts("|3:输入Exit  退出      |");
		puts("|---------------------|");
		puts("  确定要删除第一个吗  ");
	}
	else
	{
	    puts("|---------------------|");
		puts("|1:输入NO    重新搜索  |");
		puts("|---------------------|");
		puts("|2:输入Exit  退出      |");
		puts("|---------------------|");
		puts("|    选择您的操作      |");
		puts("|---------------------|");
	}
	gets(search);
	if (!strcmp(search, ("NO")))
	{
		//goto语句起点-----------------------------------------------------
		goto search;
	}
	else if ((!strcmp(("YES"), search)) && delet_end != -1) //(!strcmp(("Exit"),account))
	{
		rewind(fp);
		while (delet_start != ftell(fp))
			fseek(fp, 1L, SEEK_CUR);
		puts("进入删除操作");
		fputc('\0', fp);
		ch = fgetc(fp);
		while (ftell(fp) <= delet_end)
		{
			fseek(fp, -1L, SEEK_CUR);
			fputc('\0', fp);
			ch = fgetc(fp);
		}
		fseek(fp, -1L, SEEK_CUR);
		fputc('\0', fp);
		puts("删除成功");
		Sleep(1000);
		fclose(fp);
		return;
	}
	else if (!strcmp(search, ("Exit")))
		return;
	else;
	return;
}
void User_Interface_admin_information_modification()
{
	struct information Atemp;
	int i, n, M, flag = 0,resault=0;
	long int temp_address_A, temp_address_B, delet_start = -1, delet_end = -1, temp;
	char search[128], ch;
	FILE* fp = NULL;
search2:
	system("cls");
	puts("     *信息修改操作*");
	switch (infoemation_input_recognition)
	{
	case 1:
		puts("    AMD CPU修改");
		fp = fopen("data\\#Info_Amd.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 2:puts("    Intel CPU修改");
		fp = fopen("data\\#Info_Intel.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 3:puts("    主板 信息修改");
		fp = fopen("data\\#Info_Motherboard.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 4:puts("    内存 信息修改");
		fp = fopen("data\\#Info_Memory.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 5:puts("    AMD 显卡修改");
		fp = fopen("data\\#Info_ATI.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 6:puts("    英伟达 显卡修改");
		fp = fopen("data\\#Info_NVIDIA.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 7:puts("    硬盘 信息修改");
		fp = fopen("data\\#Info_Disk.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 8:puts("    机箱 信息修改");
		fp = fopen("data\\#Info_Computer_Case.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 9:puts("    电源 信息修改");
		fp = fopen("data\\#Info_Power_Supply.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 10:puts("    显示器 信息修改");
		fp = fopen("data\\#Info_Monitor.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 11:puts("    鼠标 信息修改");
		fp = fopen("data\\#Info_Mouse.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	case 12:puts("    键盘 信息修改");
		fp = fopen("data\\#Info_Keyboard.Ac", "r+");
		if (fp == NULL)
		{
			puts("文件打开失败");
			Sleep(1000);
			return;
		}
		break;
	default:return;
	}
	puts("输入Exit退出");
	puts("输入要查询的内容");
	puts("-----------------------------------");
	printf("\n");
	puts("-----------------------------------");
	gotoxy(0, 5);
	gets(search);
	gotoxy(0, 7);
	if (!strcmp(search, ("Exit")))
		return;
	fseek(fp, 0L, SEEK_SET);

//----------------------------------------------------------------------------------
	temp_address_A = ftell(fp); temp_address_B = ftell(fp); temp = ftell(fp);
	resault=0;
	while (!feof(fp))//以文件是否结束为判断条件
	{
		ch = fgetc(fp);//取出一个字符
		if (ch != search[0])//如果这个字符连第一个都不匹配 则进入下一次循环
			continue;
		else//验证后续字符
		{
			temp_address_A = ftell(fp);//储存当前fp的位置 暂存 如果相同可以直接调用 不相同可以恢复
			for (i = 1; search[i]; i++)//进行后续验证
			{
				ch = fgetc(fp);//取字符
				if (ch != search[i])//如果此处不相等，一下进行归位 B为恢复指针时用的临时变量
				{
					temp_address_B = ftell(fp);//不相等位置的下一个字节
					n = temp_address_B - temp_address_A;
					for (M = 1; M < n; M++)
						fseek(fp, -1L, SEEK_CUR);//返回原位置的下一个字节 检验
					temp_address_B = temp_address_A;
					break;
				}
			}
		}/*
		此处出来有两种情况 
		1 检测完成,符合查找条件 search[i]=='\0'  temp_address_A在第一个结果的信息段内
		2 不符合查找条件 search[i]!='\0'   fp指针归位 其他变量无关
		*/
	if (search[i] == '\0')//检测完成判断
		{	
			resault++;
			ch = fgetc(fp);//-----------------------------反向查询 直到碰到标识符
			fseek(fp, -1L, SEEK_CUR);
			while (ch != '#')
			{
				fseek(fp, -2L, SEEK_CUR);
				ch = fgetc(fp);

			}//此方法出循环恰好从#下一位输出
			if(delet_start==-1)
				delet_start = ftell(fp) - 1;
			ch = fgetc(fp);
			while (ch != '&')
			{
				if (ch != '#')
					printf("%c", ch);
				ch = fgetc(fp);
			}
			if (delet_end == -1)
				delet_end = ftell(fp) - 1;
			printf("\n");//输出搜索的文字-------------------------------------
			/* 此时已经记录了该被删除的文字段*/
		}
	}
	if(resault==0)
	{
		puts("查询不到此内容 请重试");
		Sleep(1000);
		fclose(fp);
		goto search2;
		return;
	}


//----------------------------------------------------------------------------------

	
	if (delet_end != -1)
	{
		printf("*共有%d个搜索结果*",resault);
		puts("|--------------------|");
		puts("|1:输入NO    重新搜索|");
		puts("|--------------------|");
		puts("|2:输入YES   修改    |");
		puts("|--------------------|");
		puts("|3:输入Exit  退出    |");
		puts("|--------------------|");
		puts(" 确定要修改第一个吗");
	}
	else
	{
		puts("|--------------------|");
		puts("|1:输入NO    重新搜索|");
		puts("|--------------------|");
		puts("|2:输入Exit  退出    |");
		puts("|--------------------|");
		puts("|   选择您的操作     |");
		puts("|--------------------|");
	}
	gets(search);
	if (!strcmp(search, ("NO")))
	{

		goto search2;
	}
	else if ((!strcmp(("YES"), search)) && delet_end != -1)
	{
		rewind(fp);
		while (delet_start != ftell(fp))
			fseek(fp, 1L, SEEK_CUR);
		system("CLS");
		puts("      *进入修改操作*");
		puts("    输入您要修改的内容");
		puts("|-----------------------------|");
		puts("|输入型号:                    |");
		puts("|-----------------------------|");
		puts("|输入发布日期:                |");
		puts("|-----------------------------|");
		puts("|输入价格:                    |");
		puts("|-----------------------------|");
		puts("|输入其他备注:                |");
		puts("|-----------------------------|");
		gotoxy(10, 3);
		gets(Atemp.Temp_Model);
		if (!strcmp(("Exit"), Atemp.Temp_Model))
			return;
		gotoxy(14, 5);
		gets(Atemp.Temp_Date);
		if (!strcmp(("Exit"), Atemp.Temp_Date))
			return;
		gotoxy(10, 7);
		scanf("%s", Atemp.Temp_Price);
		fflush(stdin);
		gotoxy(14, 9);
		gets(Atemp.Temp);
		if (!strcmp(("Exit"), Atemp.Temp))
			return;
		fputc('\0', fp);
		ch = fgetc(fp);
		while (ftell(fp) <= delet_end)
		{
			fseek(fp, -1L, SEEK_CUR);
			fputc('\0', fp);
			ch = fgetc(fp);
		}
		fseek(fp, -1L, SEEK_CUR);
		fputc('\0', fp);
		puts("删除完成");
		Sleep(1000);
		while (delet_start < ftell(fp))
			fseek(fp, -1L, SEEK_CUR);
		fprintf(fp, "#%s/%s/%s/%s&", Atemp.Temp_Model, Atemp.Temp_Date, Atemp.Temp_Price, Atemp.Temp);
		fputc('\n', fp);
		fclose(fp);
		return;
	}
	else if (!strcmp(search, ("Exit")))
		return;
	else;
	return;
}

//顾客系统索引

void User_Interface_customer_first(void)
{
	char temp='\0';
	if(User_Interface_costomer_flag_position_one==1)
	{
		User_Interface_customer_third_one_caseA();
	}
	else if(User_Interface_costomer_flag_position_one==2)
		User_Interface_customer_third_one_caseB();
	else if(User_Interface_costomer_flag_position_one==3)
		User_Interface_customer_third_one_caseC();
	else if(User_Interface_costomer_flag_position_one==4)
		User_Interface_customer_third_one_caseD();
	else if(User_Interface_costomer_flag_position_one==5)	
		User_Interface_customer_third_one_caseE();
	else if(User_Interface_costomer_flag_position_one==6)
		User_Interface_customer_third_one_caseF();
	else if(User_Interface_costomer_flag_position_one==7)
		User_Interface_customer_third_one_caseG();
	else if(User_Interface_costomer_flag_position_one==8)
		User_Interface_customer_third_one_caseH();
	else if(User_Interface_costomer_flag_position_one==9)
		User_Interface_customer_third_one_caseI();
	else if(User_Interface_costomer_flag_position_one==10)
		User_Interface_customer_third_one_caseJ();
	while(1)
	{
		if(temp=getch())
		{
			if(temp=='Q')
			{
				Costumer_Interface_caseA();
				return ;
			}
			if(temp=='E')
			{
				if(User_Interface_costomer_flag_position_one==1)
				{
					User_Interface_customer_third_one_caseA_Index();
				}
				else if(User_Interface_costomer_flag_position_one==2)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseB();
				}
				else if(User_Interface_costomer_flag_position_one==3)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseC();
				}
				else if(User_Interface_costomer_flag_position_one==4)
				{
					User_Interface_customer_third_one_caseD_Index();
				}
				else if(User_Interface_costomer_flag_position_one==5)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseE();
				}
				else if(User_Interface_costomer_flag_position_one==6)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseF();
				}
				else if(User_Interface_costomer_flag_position_one==7)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseG();
				}
				else if(User_Interface_costomer_flag_position_one==8)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseH();
				}
				else if(User_Interface_costomer_flag_position_one==9)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseI();

				}
				else if(User_Interface_costomer_flag_position_one==10)
				{
					customer_Hardware_all();
					User_Interface_customer_third_one_caseJ();
				}
			}
			if(temp=='W')
				User_Interface_costomer_flag_position_one--;
			if(temp=='S')
				User_Interface_costomer_flag_position_one++;
			if(User_Interface_costomer_flag_position_one==0)
				User_Interface_costomer_flag_position_one=10;
			if(User_Interface_costomer_flag_position_one==11)
				User_Interface_costomer_flag_position_one=1;

			if(User_Interface_costomer_flag_position_one==1)
				User_Interface_customer_third_one_caseA();
			if(User_Interface_costomer_flag_position_one==2)
				User_Interface_customer_third_one_caseB();
			if(User_Interface_costomer_flag_position_one==3)
				User_Interface_customer_third_one_caseC();
			if(User_Interface_costomer_flag_position_one==4)
				User_Interface_customer_third_one_caseD();
			if(User_Interface_costomer_flag_position_one==5)
				User_Interface_customer_third_one_caseE();
			if(User_Interface_costomer_flag_position_one==6)
				User_Interface_customer_third_one_caseF();
			if(User_Interface_costomer_flag_position_one==7)
				User_Interface_customer_third_one_caseG();
			if(User_Interface_costomer_flag_position_one==8)
				User_Interface_customer_third_one_caseH();
			if(User_Interface_costomer_flag_position_one==9)
				User_Interface_customer_third_one_caseI();
			if(User_Interface_costomer_flag_position_one==10)
				User_Interface_customer_third_one_caseJ();
			
		}
	}


	return ;
}
void customer_Hardware_all(void)//硬件大全那一栏进入的函数
{
	struct information *Current=NULL;
	int all_num=0,num,i,find_y=0;// all_num为所有的数量 num i是临时用的 计数变量  find_y是用来接收键盘 让指针指到哪的
	char Temp,ch;
	double temp_num=0;//提取文件字符转化是暂存
	FILE *fp=NULL;//第一个是打开档案文件 第二个是创建购物车文件
	system("CLS");
	puts("          顾客界面");
	puts("          硬件大全");
	puts("  按下E加入购物车,Q返回上一级");
	switch(costomer_information_search)
	{
		case 1:
			puts("你当前的选择为AMD处理器,下面为查询结果↓↓");
			Text_sorting("data\\#Info_Amd.Ac");
			fp = fopen("data\\#Info_Amd.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 2:
		puts("你当前的选择为Intle处理器,下面为查询结果↓");
		Text_sorting("data\\#Info_Intel.Ac");
		fp = fopen("data\\#Info_Intel.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 3:
		puts("你当前的选择为AMD处理器,下面为查询结果↓");
		Text_sorting("data\\#Info_Motherboard.Ac");
		fp = fopen("data\\#Info_Motherboard.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 4:
		puts("你当前的选择为内存,下面为查询结果↓");
		Text_sorting("data\\#Info_Memory.Ac");
		fp = fopen("data\\#Info_Memory.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 5:
		puts("你当前的选择为AMD 显卡,下面为查询结果↓");
		Text_sorting("data\\#Info_ATI.Ac");
		fp = fopen("data\\#Info_ATI.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 6:
		puts("你当前的选择为英伟达 显卡,下面为查询结果↓");
		Text_sorting("data\\#Info_NVIDIA.Ac");
		fp = fopen("data\\#Info_NVIDIA.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 7:
		puts("你当前的选择为硬盘,下面为查询结果↓");
		Text_sorting("data\\#Info_Disk.Ac");
		fp = fopen("data\\#Info_Disk.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 8:
		puts("你当前的选择为机箱,下面为查询结果↓");
		Text_sorting("data\\#Info_Computer_Case.Ac");
		fp = fopen("data\\#Info_Computer_Case.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 9:
		puts("你当前的选择为电源,下面为查询结果↓");
		Text_sorting("data\\#Info_Power_Supply.Ac");
		fp = fopen("data\\#Info_Power_Supply.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 10:
		puts("你当前的选择为显示器,下面为查询结果↓");
		Text_sorting("data\\#Info_Monitor.Ac");
		fp = fopen("data\\#Info_Monitor.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 11:
		puts("你当前的选择为鼠标,下面为查询结果↓");
		Text_sorting("data\\#Info_Mouse.Ac");
		fp = fopen("data\\#Info_Mouse.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		case 12:
		puts("你当前的选择为键盘,下面为查询结果↓");
		Text_sorting("data\\#Info_Keyboard.Ac");
		fp = fopen("data\\#Info_Keyboard.Ac", "r");
			if (fp == NULL)
			{
				puts("文件打开失败");
				Sleep(1000);
				return;
			}
			break;
		
	}
	rewind(fp);
	Temp=fgetc(fp);
	while(!feof(fp))
	{
		if(Temp=='#')
			all_num++;
		Temp=fgetc(fp);
	}
	if(all_num==0)
	{
		fclose(fp);
		puts("暂无信息，请联系管理员添加");
		Sleep(1000);
		return ;
	}
	else
	{
		Current=(struct information *)malloc(all_num*sizeof(struct information));//依据数量定义数组
		rewind(fp);
		for(num=0;num<all_num;num++)
		{
			ch=fgetc(fp);

			while(ch!='#')
				ch=fgetc(fp);
			//出循环时fp在#下一位 ch为#

			for(i=0;ch!='/';i++)
			{
				ch=fgetc(fp);
				if(ch!='/')				
					Current[num].Temp_Model[i]=ch;
			}
			Current[num].Temp_Model[i-1]='\0';//此处 写完型号 此时指针在/下一个
			ch='\0';
//----------------------------------------------------------------------------------------------
			for(i=0;ch!='/';i++)
			{
				ch=fgetc(fp);
				if(ch!='/')	
					Current[num].Temp_Date[i]=ch;
			}
			Current[num].Temp_Date[i-1]='\0';//此处 写完日期 此时指针在/下一个
			ch='\0';
//------------------------------------价格----------------------------------------------------------
			for(i=0;ch!='/';i++)
			{
				ch=fgetc(fp);
				if(ch!='/')	
					Current[num].Temp_Price[i]=ch;
			}
			Current[num].Temp_Price[i-1]='\0';//此处 写完价格 此时指针在/下一个
			ch='\0';
//----------------------------------------------------------------------------------------------
			for(i=0;ch!='&';i++)
			{
				ch=fgetc(fp);
				if(ch!='/')	
					Current[num].Temp[i]=ch;
			}
			Current[num].Temp[i-1]='\0';//此处 写完备注 此时指针在/下一个
			ch='\0';
//----------------------------------------------------------------------------------------------			
			printf("  %d.%s\n",num+1,&Current[num].Temp_Model);
		}
		//从文件里把信息扫描进入程序 此时写入完毕 All_num为总数
		//下面是读取键盘 UI界面 打印信息
		while(1)
		{
			system("CLS");
			puts("          顾客界面");
			puts("          硬件大全");
			puts("  按下E加入购物车,Q返回上一级");
			switch(costomer_information_search)
			{
				case 1:puts("你当前的选择为AMD处理器,下面为查询结果↓");break;
				case 2:puts("你当前的选择为Intle处理器,下面为查询结果↓");break;
				case 3:puts("你当前的选择为AMD处理器,下面为查询结果↓");break;
				case 4:puts("你当前的选择为内存,下面为查询结果↓");break;
				case 5:puts("你当前的选择为AMD 显卡,下面为查询结果↓");break;
				case 6:puts("你当前的选择为英伟达 显卡,下面为查询结果↓");break;
				case 7:puts("你当前的选择为硬盘,下面为查询结果↓");break;
				case 8:puts("你当前的选择为机箱,下面为查询结果↓");break;
				case 9:puts("你当前的选择为电源,下面为查询结果↓");break;
				case 10:puts("你当前的选择为显示器,下面为查询结果↓");break;
				case 11:puts("你当前的选择为鼠标,下面为查询结果↓");break;
				case 12:puts("你当前的选择为键盘,下面为查询结果↓");break;//共计4 行
			}
			for(i=0;i<all_num;i++)
				printf("  %d.%s\n",i+1,&Current[i].Temp_Model);
			gotoxy(0,4+find_y);//find_Y的范围是 0~all_num-1----也是代表当前硬件在结构体数组内的位置
			puts("->");
			for(i=0;i<all_num+4;i++)
			{
				gotoxy(50,i);
				printf("|");
				if(i==0)
					puts("      详细信息");
				if(i==1)
					printf("产品型号:%s",Current[find_y].Temp_Model);
				if(i==2)
					printf("发布日期:%s",Current[find_y].Temp_Date);
				if(i==3)
					printf("产品价格:%s",Current[find_y].Temp_Price);
				if(i==4)
					printf("备注信息:%s",Current[find_y].Temp);
			}//框框打印完毕
			ch=getch();
			
			if(ch=='W')
			{
				find_y--;
				if(find_y<0)
					find_y=all_num-1;
			}
			else if(ch=='S')
			{
				find_y++;
				if(find_y>=all_num)
					find_y=0;
			}
			else if(ch=='E')
			{
				if(flag==0)
				{
					flag=1;
					head=(struct costomer_select_information *)malloc(sizeof(struct costomer_select_information));
					head->prior=NULL;
					head->next=NULL;
					head->num=1;
					head->recognize=costomer_information_search;
					strcpy(head->Temp,Current[find_y].Temp);
					strcpy(head->Temp_Date,Current[find_y].Temp_Date);
					strcpy(head->Temp_Model,Current[find_y].Temp_Model);
					strcpy(head->Temp_Price,Current[find_y].Temp_Price);
					plo=head;
				}//plo是上一个 data_temp是当前
				else
				{
					data_temp=(struct costomer_select_information *)malloc(sizeof(struct costomer_select_information));
					data_temp->next=NULL;
					data_temp->prior=plo;//当前节点连接上一个
					plo->next=data_temp;//上一个节点连接当前
					data_temp->num=1;
					data_temp->recognize=costomer_information_search;
					strcpy(data_temp->Temp,Current[find_y].Temp);
					strcpy(data_temp->Temp_Date,Current[find_y].Temp_Date);
					strcpy(data_temp->Temp_Model,Current[find_y].Temp_Model);
					strcpy(data_temp->Temp_Price,Current[find_y].Temp_Price);
					plo=data_temp;
					data_temp=NULL;
				}
				printf("购物车加入成功");//find_y为数组位置
			}
			//链表写入完成
			else if(ch=='Q')
			{	
				return ;
			}
		}
	}
	return ;
	
}

//第一步 合并相同的节点
void User_Interface_customer_second(void)
{
	char temp;
	int sum=0;
	int flag=0;
	system("CLS");
	puts("数据加载");
//截止----------------------------------------------------  此处准备加入链表查重 调整购物车 
//	if(head->next)//如果它是含有两个及以上节点
//	{
//		mp=head;//初始化指针
//		while(mp->next)//慢循环到倒数第二个
	//	{
	//		pm=mp->next;
	//		while(pm)//快循环到最后一个
	///		{
	//			if( (!strcmp(mp->Temp_Model,pm->Temp_Model)) && (!strcmp(mp->Temp_Date,pm->Temp_Date)) && (!strcmp(pm->Temp,mp->Temp)) && (!strcmp(pm->Temp_Price,mp->Temp_Price)) &&(mp->num==pm->num))
	//			{
	//				mp->num=mp->num+1;
	//				pm->prior->next=pm->next;
	//				pm->next->prior=pm->prior;
	//				data_temp=pm-prior;
	//				free(pm);
	//				pm=data_temp;
	//				data_temp=NULL;
	///			}
	//			pm=pm->next;
	//		}
	//		mp=mp->next;
	//	}
//	}
//在此处链表查重
//截止----------------------------------------------------
	puts("数据加载完毕");
	system("CLS");
	puts("    购物车");
	if(head==NULL)
	{
		puts("购物车为空");
		Sleep(1000);
		return ;
	}
	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==1)
		{	
			if(flag==0)
			{
				puts("AMD处理器");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==2)
		{	
			if(flag==0)
			{
				puts("Intel处理器");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==3)
		{	
			if(flag==0)
			{
				puts("主板");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==4)
		{
			if(flag==0)
			{
				puts("内存");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==5)
		{
			if(flag==0)
			{
				puts("AMD显卡");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==6)
		{
			if(flag==0)
			{
				puts("英伟达显卡");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==7)
		{
			if(flag==0)
			{
				puts("硬盘");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==8)
		{
			if(flag==0)
			{
				puts("机箱");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==9)
		{
			if(flag==0)
			{
				puts("电源");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==10)
		{
			if(flag==0)
			{
				puts("显示器");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==11)
		{
			if(flag==0)
			{
				puts("鼠标");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;

	
	mp=head;
	while(mp!=NULL)
	{
		if(mp->recognize==12)
		{
			if(flag==0)
			{
				puts("键盘");
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
				flag=1;
			}
			else
			{
				printf("型号：%s ；数目 %d ；价格%s\n",mp->Temp_Model,mp->num,mp->Temp_Price);
			}
		}
		mp=mp->next;
	}
	flag=0;


	mp=head;
	while(mp!=NULL)
	{
		sum=sum+atoi(mp->Temp_Price);
		mp=mp->next;
	}
	printf("\n\n总价：%d\n",sum);
	puts("输入Q返回 输入E清空");
	while(1)
	{
		temp=getch();
		{
			if(temp=='E')
			{
				mp=head;
				while(mp)
				{
					pm=mp->next;
					free(mp);
					mp=pm;
				}
				head=NULL;
				return ;
				
			}
			else if(temp=='Q')
			{
				return ;
			}
		}
	}
	return ;
}
void User_Interface_customer_third(void)
{
	int i,Rerurn_a;
	double sum=0;
	char temp_one[15]={"电脑硬件报价单"};
	FILE *input;
	time_t tmpcal_ptr;
	struct tm *tmp_ptr = NULL;
	system("CLS");
	puts("购物单打印系统");
	if(head==NULL)
	{
		puts("暂无内容");
		Sleep(1000);
		return ;
	}
	else
	{

		input=fopen("information_print.doc","w");
		if(input==NULL)
		{
			MessageBox(NULL,"文件打开错误,请检查上一次生成的文档文件是否已关闭。","Tips",MB_OK|MB_ICONWARNING);
			return ;
		}

		for(i=0;i<35;i++)
			fputc(32,input);
		fputs(temp_one,input);
		fputc('\n',input);
		time(&tmpcal_ptr);
		tmp_ptr = gmtime(&tmpcal_ptr);
		tmp_ptr = localtime(&tmpcal_ptr);
		fprintf(input,"生成日期:%d.%02d.%02d\n",(1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
		fputs("顾客姓名:_______________",input);fputc('\n',input);
		fputs("联系电话:_______________",input);fputc('\n',input);
		for(i=0;i<41;i++)
			fputs("一",input);
		fputc('\n',input);
		data_temp=head;
		while(data_temp)
		{
			sum=sum+atoi(data_temp->Temp_Price);
			fprintf(input,"型号:%-54s价格:￥%-10s\n",data_temp->Temp_Model,data_temp->Temp_Price);
			data_temp=data_temp->next;
		}
		fprintf(input,"合计：%.2f",sum);
		putc('\n',input);
		fputs("备注信息：\n\n\n\n\n\n",input);
		for(i=0;i<82;i++)
			fputc('_',input);
		fputc('\n',input);
		fputs("报价单生成完毕，祝您购物愉快。",input);
	}
	fclose(input);
	Rerurn_a=MessageBox(NULL,"报价单已生成在程序所在目录，是否打开","Tips",MB_YESNO);
	if(Rerurn_a==6)
		system("information_print.doc");
	else
		puts("打印完成，请到程序所在目录处查找,3s后退出");	
	Sleep(3000);
	return ;
	

}
//顾客系统里小索引
void User_Interface_customer_third_one_caseA_Index()
{
	char temp='\0';
	if(User_Interface_costomer_flag_position_one_sss==1)
		User_Interface_customer_third_one_caseA1();
	else if(User_Interface_costomer_flag_position_one_sss==2)
		User_Interface_customer_third_one_caseA2();
	while(1)
	{
		if(temp=getch())//无回显输入  
		{
			if(temp=='Q')
			{
				User_Interface_customer_third_one_caseA();
				return ;
			}
			if(temp=='W')
				User_Interface_costomer_flag_position_one_sss--;
			if(temp=='S')
				User_Interface_costomer_flag_position_one_sss++;
			if(temp=='E')
				customer_Hardware_all();
			if(User_Interface_costomer_flag_position_one_sss==3)
				User_Interface_costomer_flag_position_one_sss=1;
			if(User_Interface_costomer_flag_position_one_sss==0)
				User_Interface_costomer_flag_position_one_sss=2;
		

			if(User_Interface_costomer_flag_position_one_sss==1)
			{
				User_Interface_customer_third_one_caseA1();
			}
			if(User_Interface_costomer_flag_position_one_sss==2)
			{
				User_Interface_customer_third_one_caseA2();
			}


		}
	}
	return ;
}
void User_Interface_customer_third_one_caseD_Index()
{
	char temp='\0';
	if(User_Interface_costomer_flag_position_one_fov==1)
		User_Interface_customer_third_one_caseD1();
	else if(User_Interface_costomer_flag_position_one_fov==2)
		User_Interface_customer_third_one_caseD2();
	while(1)
	{
		if(temp=getch())//无回显输入  
		{
			

			if(temp=='Q')
			{
				User_Interface_customer_third_one_caseD();
				return ;
			}
			if(temp=='W')
				User_Interface_costomer_flag_position_one_fov--;
			if(temp=='S')
				User_Interface_costomer_flag_position_one_fov++;
			if(temp=='E')
				customer_Hardware_all();		


			if(User_Interface_costomer_flag_position_one_fov==3)
				User_Interface_costomer_flag_position_one_fov=1;
			if(User_Interface_costomer_flag_position_one_fov==0)
				User_Interface_costomer_flag_position_one_fov=2;
			if(User_Interface_costomer_flag_position_one_fov==1)
			{
				User_Interface_customer_third_one_caseD1();
			}
			if(User_Interface_costomer_flag_position_one_fov==2)
			{
				User_Interface_customer_third_one_caseD2();
			}
		}
	}
	return ;
}

void color_egg()
{
	void recursur();
	int i = 0, caf = 33;
	FILE *fp ;
	clock_t stime = 0, ftime = 0;
	char buf[1920], seat[]="data\\Img\\BA (0000).ACG", ai[5],ch;
	system("CLS");	
	printf("-----Bad Apple ASCII art player-----\nPress Enter To Play.\nPress Space To Exit\n");
	fflush(stdin);
	ch=getchar();
	if(ch==32)
		return ;
	system("cls");
	PlaySound("data\\Img\\BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);
	stime = clock();
	while(i <= 6570)
	{
		if(kbhit())
		{
			ch=getch();
			if(ch==32)
			{
				PlaySound("data\\Img\\BadApple.wav",0,SND_PURGE);
				return ;
			}
		}
		if(i % 30 == 0)
		{
			caf = 43;
		}
		else
		{
			caf = 33;
		}
		strcpy(seat, "data\\Img\\BA (");
		sprintf(ai, "%d", i);
		strcat(seat, ai);
		strcat(seat, ").ACG");
		ftime = clock();	
		if((ftime - stime) >= caf)
		{
			i++;
			fp = fopen(seat, "r");
			fread(buf, sizeof(buf), 1, fp);
			buf[1920] = '\0';
			fclose(fp);
			fprintf(stdout, "%s", buf);
			fprintf(stdout, "Frame:%d", i);
			stime += caf;
			recursur();	
		}
	}
	system("cls");
	printf("-----Bad Apple ASCII art player-----\nThanks for watching!\n2020.2.8\n");
	printf("Press Enter to Exit.\n");
	getchar();
	return ;
}
void recursur()
{
	HANDLE hout;	
	COORD coord;	
	coord.X = 0;	
	coord.Y = 0;	
	hout = GetStdHandle(STD_OUTPUT_HANDLE);	
	SetConsoleCursorPosition(hout,coord);
}


//------------------------------------------UI界面
void User_Interface_case_1(void)
{
	system("cls");
	puts("        电脑报价系统");
	puts("         身份选择");
	puts("---------------------------");
	puts("- >        顾客         < -");
	puts("---------------------------");
	printf("\n");
	puts("           管理员");
	printf("\n");
	return;
}
void User_Interface_case_2(void)
{
	system("cls");
	puts("        电脑报价系统");
	puts("         身份选择");
	printf("\n");
	puts("           顾客");
	printf("\n");
	puts("---------------------------");
	puts("- >      管理员         < -");
	puts("---------------------------");
	return;
}
void User_Interface_admin_second_UI_A(void)
{
	system("cls");
	puts("        电脑报价系统");
	puts("          管理系统");
	puts("----------------------------");
	puts("- >        信息增加      < -");
	puts("----------------------------");
	puts("           信息删除");
	printf("\n");
	puts("           信息修改");
	printf("\n");

}
void User_Interface_admin_second_UI_B(void)
{
	system("cls");
	puts("        电脑报价系统");
	puts("          管理系统");
	printf("\n");
	puts("           信息增加");
	puts("----------------------------");
	puts("- >        信息删除      < -");
	puts("----------------------------");
	puts("           信息修改");
	printf("\n");
}
void User_Interface_admin_second_UI_C(void)
{
	system("cls");
	puts("        电脑报价系统");
	puts("          管理系统");
	printf("\n");
	puts("           信息增加");
	printf("\n");
	puts("           信息删除");
	puts("----------------------------");
	puts("- >        信息修改      < -");
	puts("----------------------------");
	printf("\n");
}
void User_Interface_admin_third_one_caseA(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	puts("---------------------------|---------|");
	puts("- >         CPU         < -|   AMD   |");
	puts("---------------------------| --------|");
	puts("            主板           |  Intel  |");
	printf("                           |---------|\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
}
void User_Interface_admin_third_one_caseB(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	puts("---------------------------");
	puts("- >         主板        < -");
	puts("---------------------------");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 3;
}
void User_Interface_admin_third_one_caseC(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	puts("---------------------------");
	puts("- >         内存        < -");
	puts("---------------------------");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 4;
}
void User_Interface_admin_third_one_caseD(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存           |----------|");
	puts("---------------------------|   AMD    |");
	puts("- >         显卡        < -| ---------|");
	puts("---------------------------|  英伟达  |");
	puts("            硬盘           |----------|");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
}
void User_Interface_admin_third_one_caseE(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	puts("---------------------------");
	puts("- >         硬盘        < -");
	puts("---------------------------");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 7;
}
void User_Interface_admin_third_one_caseF(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	puts("---------------------------");
	puts("- >         机箱        < -");
	puts("---------------------------");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 8;
}
void User_Interface_admin_third_one_caseG(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	puts("---------------------------");
	puts("- >         电源        < -");
	puts("---------------------------");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 9;
}
void User_Interface_admin_third_one_caseH(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	puts("---------------------------");
	puts("- >        显示器       < -");
	puts("---------------------------");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 10;
}
void User_Interface_admin_third_one_caseI(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	puts("---------------------------");
	puts("- >         鼠标        < -");
	puts("---------------------------");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 11;
}
void User_Interface_admin_third_one_caseJ(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	puts("---------------------------");
	puts("- >         键盘        < -");
	puts("---------------------------");
	infoemation_input_recognition = 12;
}
void User_Interface_admin_third_one_caseA1(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	puts("---------------------------|---------|");
	puts("             CPU        -> |-> AMD <-|");
	puts("---------------------------| --------|");
	puts("            主板           |  Intel  |");
	printf("                           |---------|\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 1;
}
void User_Interface_admin_third_one_caseA2(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	puts("---------------------------|---------|");
	puts("             CPU        -> |   AMD   |");
	puts("---------------------------| --------|");
	puts("            主板           |->Intel<-|");
	printf("                           |---------|\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 2;
}
void User_Interface_admin_third_one_caseD1(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存           |----------|");
	puts("---------------------------|  >AMD<   |");
	puts("            显卡        -> | ---------|");
	puts("---------------------------|  英伟达  |");
	puts("            硬盘           |----------|");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 5;
}
void User_Interface_admin_third_one_caseD2(void)
{
	system("cls");
	puts("        电脑报价系统");
	if (Add_delet_modification == 1)
		puts("     管理系统--信息添加");
	else if (Add_delet_modification == 2)
		puts("     管理系统--信息删除");
	else if (Add_delet_modification == 3)
		puts("     管理系统--信息修改");
	else;
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存           |----------|");
	puts("---------------------------|   AMD    |");
	puts("            显卡        -> | ---------|");
	puts("---------------------------| >英伟达< |");
	puts("            硬盘           |----------|");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	infoemation_input_recognition = 6;
}

//顾客系统UI界面
void Costumer_Interface_caseA(void)  
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	puts("--------------------------- ");
	puts("- >  1: 硬件大全        < - ");
	puts("--------------------------- ");
	puts("     2: 我的购物车           ");
	printf("\n");
	puts("     3: 生成报价表        ");
	printf("\n");


}

void Costumer_Interface_caseB(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("     1: 硬件大全            ");
	puts("--------------------------- ");
	puts("- >  2: 我的购物车      < - ");
    puts("--------------------------- ");
	puts("     3: 生成报价表        ");
	printf("\n");


}

void Costumer_Interface_caseC(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("     1: 硬件大全             ");
	printf("\n");
	puts("     2: 我的购物车           ");
    puts("---------------------------  ");
	puts("- >  3: 生成报价表      < -  ");
    puts("--------------------------- ");
	printf("\n");


}
void User_Interface_customer_third_one_caseA(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	puts("---------------------------|---------|");
	puts("- >          CPU        < -|   AMD   |");
	puts("---------------------------| --------|");
	puts("            主板           |  Intel  |");
	printf("                           |---------|\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
}
void User_Interface_customer_third_one_caseB(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	puts("---------------------------");
	puts("- >         主板        < -");
	puts("---------------------------");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=3;
}
void User_Interface_customer_third_one_caseC(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	puts("---------------------------");
	puts("- >         内存        < -");
	puts("---------------------------");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=4;
}
void User_Interface_customer_third_one_caseD(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存           |----------|");
	puts("---------------------------|   AMD    |");
	puts("- >         显卡        < -| ---------|");
	puts("---------------------------|  英伟达  |");
	puts("            硬盘           |----------|");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
}
void User_Interface_customer_third_one_caseE(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	puts("---------------------------");
	puts("- >         硬盘        < -");
	puts("---------------------------");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=7;
}
void User_Interface_customer_third_one_caseF(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	puts("---------------------------");
	puts("- >         机箱        < -");
	puts("---------------------------");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=8;
}
void User_Interface_customer_third_one_caseG(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	puts("---------------------------");
	puts("- >         电源        < -");
	puts("---------------------------");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=9;
}
void User_Interface_customer_third_one_caseH(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	puts("---------------------------");
	puts("- >        显示器       < -");
	puts("---------------------------");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=10;
}
void User_Interface_customer_third_one_caseI(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	puts("---------------------------");
	puts("- >         鼠标        < -");
	puts("---------------------------");
	puts("            键盘");
	printf("\n");
	costomer_information_search=11;
}
void User_Interface_customer_third_one_caseJ(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	puts("---------------------------");
	puts("- >         键盘        < -");
	puts("---------------------------");
	costomer_information_search=12;
}
void User_Interface_customer_third_one_caseA1(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	puts("---------------------------|---------|");
	puts("             CPU        -> |-> AMD <-|");
	puts("---------------------------| --------|");
	puts("            主板           |  Intel  |");
	printf("                           |---------|\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=1;
}
void User_Interface_customer_third_one_caseA2(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	puts("---------------------------|---------|");
	puts("             CPU        -> |   AMD   |");
	puts("---------------------------| --------|");
	puts("            主板           |->Intel<-|");
  printf("                           |---------|\n");
	puts("            内存");
	printf("\n");
	puts("            显卡");
	printf("\n");
	puts("            硬盘");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=2;
}
void User_Interface_customer_third_one_caseD1(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存           |----------|");
	puts("---------------------------|  >AMD<   |");
	puts("            显卡        -> | ---------|");
	puts("---------------------------|  英伟达  |");
	puts("            硬盘           |----------|");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=5;
}
void User_Interface_customer_third_one_caseD2(void)
{
	system("cls");
	puts("        电脑报价系统"); 
	puts("           顾客菜单");
	printf("\n");
	puts("            CPU");
	printf("\n");
	puts("            主板");
	printf("\n");
	puts("            内存           |----------|");
	puts("---------------------------|   AMD    |");
	puts("            显卡        -> | ---------|");
	puts("---------------------------| >英伟达< |");
	puts("            硬盘           |----------|");
	printf("\n");
	puts("            机箱");
	printf("\n");
	puts("            电源");
	printf("\n");
	puts("           显示器");
	printf("\n");
	puts("            鼠标");
	printf("\n");
	puts("            键盘");
	printf("\n");
	costomer_information_search=6;
}
//----------------应用性函数--------------------
void Text_sorting(char p[30])//程序作用删除文本文档里的null和两个连续换行 对文本文档进行整理 防止长时间使用搜索程序出现搜索缓慢 
{
	char ch,next_temp;
	FILE *temp_data;
	FILE *search_file;
	search_file=fopen(p,"r");
	temp_data=fopen("data\\temp.AC","w");
	ch=fgetc(search_file);
	while(!feof(search_file))
	{
		next_temp=fgetc(search_file);
		if(ch==NULL)
			continue;
		else if(ch=='\n'&&next_temp=='\n')
		{
			continue;
		}
		else if(ch=='\n'&&next_temp==NULL)
		{
			continue;
		}
		else
		{
			fputc(ch,temp_data);
		}
		ch=next_temp;
	}
	fclose(temp_data);
	fclose(search_file);
	remove(p);
	rename("data\\temp.AC",p);
	return ;
}
void first_examine()
{
	char ch;
	FILE *fp;
	puts("数据检查中...");
	fp=fopen("data\\#Info_Amd.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Amd.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Amd.Ac文档打开成功");
	fclose(fp);

	fp=fopen("data\\#Info_ATI.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_ATI.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
	//puts("#Info_ATI.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Computer_Case.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Computer_Case.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Computer_Case.Ac文档打开成功");
	fclose(fp);
		
	fp=fopen("data\\#Info_Disk.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Disk.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Disk.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Intel.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Intel.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Intel.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Keyboard.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Keyboard.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Keyboard.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Memory.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Memory.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
	//puts("#Info_Memory.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Monitor.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Monitor.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Monitor.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Motherboard.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Motherboard.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Motherboard.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Mouse.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Mouse.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Mouse.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_NVIDIA.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_NVIDIA.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
	//puts("#Info_NVIDIA.Ac文档打开成功");
	fclose(fp);
	
	fp=fopen("data\\#Info_Power_Supply.Ac", "r");
	if(fp==NULL)
	{
		puts("#Info_Power_Supply.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("#Info_Power_Supply.Ac文档打开成功");
	fclose(fp);

	fp=fopen("data\\Accont.Ac", "r");
	if(fp==NULL)
	{
		puts("Accont.Ac文档错误,请检查文件");
		Sleep(2000);
		exit(0);
	}
//	puts("Accont.Ac文档打开成功");
	fclose(fp);
	Sleep(60);
		system("CLS");
	fp=fp=fopen("data\\first.Ac", "r");
	if(fp==NULL)
		return ;
	while(!feof(fp))
	{
		ch=getc(fp);
		printf("%c",ch);
		Sleep(3);
	}
	return ;
}
