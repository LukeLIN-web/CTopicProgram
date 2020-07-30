#include "graphicLib.h"
#include "register.h"
#include "file.h"
#include "md5.h"
#include "myTime.h"

extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern teacher teachers;//��ʦ�û�
extern int curSataus;
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64];  // ���ڱ༭����
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
	"�ļ�",
	"���¿�ʼ  | Ctrl-R", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
	"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"ѧԺ",
		"��ͣ    | Ctrl-T"
	};
	static char* menuListCla[] = {
		"�༶",
		"�½�",
		"ɾ��",
		"�޸ĳɼ�",
		"����",
		"ͳ��",
		"review"      
	};
	static char* menuListStu[] = {
		"ѧ��",
		"��¼"
	};
	static char* menuListHelp[] = {
		"����",
		"���ڱ����"
	};

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListFile[0]) * 2; // ���˵����
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // ����
	int    selection;

	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	// File �˵�
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 2)
		_exit(-1); // choose to exit
	else if (selection == 1)
	{
		//to be continue
	}

	// ѧԺ �˵�
	//menuListCol[1] = enable_move_disc ? "��ͣ����   |   Ctrl-T" : "��������   |   Ctrl-T";
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListCol, sizeof(menuListCol) / sizeof(menuListCol[0]));
	if (selection == 1) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : press ѧԺ in register interface\n", curSataus);
	}

	// �༶�˵�
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	if (selection == 1) {
		//TODO��
	}
	// ѧ���˵�
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListStu, sizeof(menuListStu) / sizeof(menuListStu[0]));
	if (selection == 1) {
		//TODO��
	}
	// Help �˵�
	selection = menuList(GenUIID(0), x + 4 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection == 1) {
		//TODO����ʾ�������Ϣ
	}
}

void DrawTextBoxRegister()
{
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth / 3;
	double y = winheight / 3 * 2;
	double w = TextStringWidth("��");
	double dx = w;
	double dy = h * 2;

	static int typeButtonSelected = 0;
	static char newUserName[64] = { 0 }; // ���û���
	static char newPassword[64] = { 0 }; // ������
	static char userType[][7] = { "��ʦ", "ѧ��", "����Ա" };
	static bool isUserNameExist = false, isPasswordEmpty = false, isUserNameEmpty = false;
	
	
	// ����ע�����
	drawLabel(winwidth / 2 - TextStringWidth("ע  ��") / 2, winheight / 4 * 3, "ע  ��");
	drawLabel(x, y, "���ͣ�");
	drawLabel(x, y - dy, "������");
	drawLabel(x, y - dy * 2, "���룺");	
	if (textbox(GenUIID(0), x + w * 5, y - dy, w * 12, h, newUserName, sizeof(newUserName))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : newUserName textBox update : %s\n", curSataus, newUserName);
		isUserNameExist = false;
		isUserNameEmpty = false;
	}
	if(isUserNameExist)
		drawLabel(x + w * 18, y - dy, "�������Ѵ��ڣ�");
	if(isUserNameEmpty)
		drawLabel(x + w * 18, y - dy, "����Ϊ�գ�");
	if (textbox(GenUIID(0), x + w * 5, y - dy * 2, w * 12, h, newPassword, sizeof(newPassword))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : newPassword textBox update : %s\n", curSataus, newPassword);
		isPasswordEmpty = false;
	}
	if(isPasswordEmpty)
		drawLabel(x + w * 18, y - dy * 2, "����Ϊ�գ�");
	if (typeButtonSelected != 0) {
		if (button(GenUIID(0), x += w * 5, y, w * 3, h, "��ʦ")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : select \"��ʦ\" account type\n", curSataus);
			if (typeButtonSelected != 0)
				typeButtonSelected = 0;
		}
	}
	if (typeButtonSelected != 1) {
		if (button(GenUIID(0), x += w * 5, y, w * 3, h, "ѧ��")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : select \"ѧ��\" account type\n", curSataus);
			if (typeButtonSelected != 1)
				typeButtonSelected = 1;
		}
	}
	if (typeButtonSelected != 2) {
		if (button(GenUIID(0), x += w * 5, y, w * 4, h, "����Ա")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : register : select \"����Ա\" account type\n", curSataus);
			if (typeButtonSelected != 2)
				typeButtonSelected = 2;
		}
	}
	setButtonColors("Blue", "White", "Blue", "White", 1);
	switch (typeButtonSelected) {
		case 0:
			if (button(GenUIID(0), x += w * 5, y, w * 3, h, "��ʦ")) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : register : select \"��ʦ\" account type\n", curSataus);
				if (typeButtonSelected != 0)
					typeButtonSelected = 0;
			}
			break;
		case 1:
			if (button(GenUIID(0), x += w * 5, y, w * 3, h, "ѧ��")) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : register : select \"ѧ��\" account type\n", curSataus);
				if (typeButtonSelected != 1)
					typeButtonSelected = 1;
			}
			break;
		case 2:
			if (button(GenUIID(0), x += w * 5, y, w * 4, h, "����Ա")) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : register : select \"����Ա\" account type\n", curSataus);
				if (typeButtonSelected != 2)
					typeButtonSelected = 2;
			}
			break;
	}
	setButtonColors("Blue", "Blue", "Red", "Red", 0);
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("ע��") / 2, y - dy * 4, w * 4, h, "ע��")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : press \"ע��\",name:%s,password:%s,type:%s\n", curSataus, newUserName, newPassword, userType[typeButtonSelected]);
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
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("ע��") / 2 + w * 5, y - dy * 4, w * 4, h, "ȡ��")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : register : press \"ȡ��\",turn to login interface\n", curSataus);
		curSataus = 0;
	}
}
