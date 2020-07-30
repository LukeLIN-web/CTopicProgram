#include "graphicLib.h"
#include "register.h"
#include "file.h"
#include "md5.h"
#include "myTime.h"

extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern teacher teachers;//教师用户
extern int curSataus;
extern char user_name[64]; // 用于编辑用户名
extern char password[64];  // 用于编辑密码
extern int adminNum, stuNum, teaNum, classNum;
extern bool isDisplayConsole;

administrator* checkNameAdmin(const char* name)
{
	administrator* tmp = &administrators;
	while (tmp->ID[0] != '\0') {
		if (strcmp(name, tmp->name) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

student* checkNameStu(const char* name)
{
	student* tmp = &students;
	while (tmp->ID[0] != '\0') {
		if (strcmp(name, tmp->name) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

teacher* checkNameTea(const char* name)
{
	teacher* tmp = &teachers;
	while (tmp->ID[0] != '\0') {
		if (strcmp(name, tmp->name) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void DrawMenuRegister()
{
	static char* menuListFile[] = {
	"文件",
	"重新开始  | Ctrl-R", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
	"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"学院",
		"暂停    | Ctrl-T"
	};
	static char* menuListCla[] = {
		"班级",
		"新建",
		"删除",
		"修改成绩",
		"搜索",
		"统计",
		"review"      
	};
	static char* menuListStu[] = {
		"学生",
		"登录"
	};
	static char* menuListHelp[] = {
		"帮助",
		"关于本软件"
	};

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menuListFile[0]) * 2; // 主菜单宽度
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // 缩进
	int    selection;

	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 2)
		_exit(-1); // choose to exit
	else if (selection == 1)
	{
		//to be continue
	}

	// 学院 菜单
	//menuListCol[1] = enable_move_disc ? "暂停动画   |   Ctrl-T" : "继续动画   |   Ctrl-T";
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListCol, sizeof(menuListCol) / sizeof(menuListCol[0]));
	if (selection == 1) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : press 学院 in register interface\n", curSataus);
	}

	// 班级菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	if (selection == 1) {
		//TODO：
	}
	// 学生菜单
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListStu, sizeof(menuListStu) / sizeof(menuListStu[0]));
	if (selection == 1) {
		//TODO：
	}
	// Help 菜单
	selection = menuList(GenUIID(0), x + 4 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection == 1) {
		//TODO：显示本软件信息
	}
}

void DrawTextBoxRegister()
{
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = winwidth / 3;
	double y = winheight / 3 * 2;
	double w = TextStringWidth("暂");
	double dx = w;
	double dy = h * 2;

	static int typeButtonSelected = 0;
	static char newUserName[64] = { 0 }; // 新用户名
	static char newPassword[64] = { 0 }; // 新密码
	static char userType[][7] = { "老师", "学生", "管理员" };
	static bool isUserNameExist = false, isPasswordEmpty = false, isUserNameEmpty = false;
	
	
	// 画出注册界面
	drawLabel(winwidth / 2 - TextStringWidth("注  册") / 2, winheight / 4 * 3, "注  册");
	drawLabel(x, y, "类型：");
	drawLabel(x, y - dy, "姓名：");
	drawLabel(x, y - dy * 2, "密码：");	
	if (textbox(GenUIID(0), x + w * 5, y - dy, w * 12, h, newUserName, sizeof(newUserName))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : newUserName textBox update : %s\n", curSataus, newUserName);
		isUserNameExist = false;
		isUserNameEmpty = false;
	}
	if(isUserNameExist)
		drawLabel(x + w * 18, y - dy, "该名字已存在！");
	if(isUserNameEmpty)
		drawLabel(x + w * 18, y - dy, "名字为空！");
	if (textbox(GenUIID(0), x + w * 5, y - dy * 2, w * 12, h, newPassword, sizeof(newPassword))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : newPassword textBox update : %s\n", curSataus, newPassword);
		isPasswordEmpty = false;
	}
	if(isPasswordEmpty)
		drawLabel(x + w * 18, y - dy * 2, "密码为空！");
	if (typeButtonSelected != 0) {
		if (button(GenUIID(0), x += w * 5, y, w * 3, h, "老师")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : select \"老师\" account type\n", curSataus);
			if (typeButtonSelected != 0)
				typeButtonSelected = 0;
		}
	}
	if (typeButtonSelected != 1) {
		if (button(GenUIID(0), x += w * 5, y, w * 3, h, "学生")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : select \"学生\" account type\n", curSataus);
			if (typeButtonSelected != 1)
				typeButtonSelected = 1;
		}
	}
	if (typeButtonSelected != 2) {
		if (button(GenUIID(0), x += w * 5, y, w * 4, h, "管理员")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : select \"管理员\" account type\n", curSataus);
			if (typeButtonSelected != 2)
				typeButtonSelected = 2;
		}
	}
	setButtonColors("Blue", "White", "Blue", "White", 1);
	switch (typeButtonSelected) {
		case 0:
			if (button(GenUIID(0), x += w * 5, y, w * 3, h, "老师")) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : register : select \"老师\" account type\n", curSataus);
				if (typeButtonSelected != 0)
					typeButtonSelected = 0;
			}
			break;
		case 1:
			if (button(GenUIID(0), x += w * 5, y, w * 3, h, "学生")) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : register : select \"学生\" account type\n", curSataus);
				if (typeButtonSelected != 1)
					typeButtonSelected = 1;
			}
			break;
		case 2:
			if (button(GenUIID(0), x += w * 5, y, w * 4, h, "管理员")) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : register : select \"管理员\" account type\n", curSataus);
				if (typeButtonSelected != 2)
					typeButtonSelected = 2;
			}
			break;
	}
	setButtonColors("Blue", "Blue", "Red", "Red", 0);
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("注册") / 2, y - dy * 4, w * 4, h, "注册")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : press \"注册\",name:%s,password:%s,type:%s\n", curSataus, newUserName, newPassword, userType[typeButtonSelected]);
		if (newUserName[0] != '\0')
			isUserNameExist = checkNameTea(newUserName) || checkNameStu(newUserName) || checkNameAdmin(newUserName);
		else
			isUserNameEmpty = true;
		if (newPassword[0] == '\0')
			isPasswordEmpty = true;
		if (!(isUserNameEmpty || isUserNameExist || isPasswordEmpty)) {
			switch (typeButtonSelected) {
				case 0: 
				{
					teacher* tmp = &teachers;
					while (tmp->ID[0] != '\0') tmp = tmp->next;
					getID(tmp->ID);
					strcpy(tmp->name, newUserName);
					strcpy(tmp->password, newPassword);
					tmp->next = (teacher*)malloc(sizeof(teacher));
					memset(tmp->next, 0, sizeof(teacher));
					++teaNum;
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : register : ID:%s\n", curSataus, tmp->ID);
				}
					break;
				case 1:
				{
					student* tmp = &students;
					while (tmp->ID[0] != '\0') tmp = tmp->next;
					getID(tmp->ID);
					strcpy(tmp->name, newUserName);
					strcpy(tmp->password, newPassword);
					tmp->next = (student*)malloc(sizeof(student));
					memset(tmp->next, 0, sizeof(student));
					++stuNum;
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : register : ID:%s\n", curSataus, tmp->ID);
				}
					break;
				case 2:
				{
					administrator* tmp = &administrators;
					while (tmp->ID[0] != '\0') tmp = tmp->next;
					getID(tmp->ID);
					strcpy(tmp->name, newUserName);
					strcpy(tmp->password, newPassword);
					tmp->next = (administrator*)malloc(sizeof(administrator));
					memset(tmp->next, 0, sizeof(administrator));
					++adminNum;
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : register : ID:%s\n", curSataus, tmp->ID);
				}
					break;
			}
			strcpy(user_name, newUserName);
			strcpy(password, newPassword);
			memset(newUserName, 0, sizeof(newUserName));
			memset(newPassword, 0, sizeof(newPassword));
			curSataus = 0; 
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : register,success,turn to login interface\n", curSataus);
			saveToFile();
		}
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("注册") / 2 + w * 5, y - dy * 4, w * 4, h, "取消")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : press \"取消\",turn to login interface\n", curSataus);
		curSataus = 0;
	}
}
