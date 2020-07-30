#include "graphicLib.h"
#include "login.h"
#include "file.h"
#include "md5.h"
#include "register.h"

//ȫ�ֱ���
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern teacher teachers;//��ʦ�û�
extern int curSataus;
extern bool isDisplayConsole;

void DrawMenuLogin()
{
	static char* menuListFile[] = {
		"�ļ�",
		"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"ѧԺ",
	};
	static char* menuListCla[] = {
		"�༶",
		"�½�",
		"ɾ��",
		"�޸ĳɼ�",
		"����",
		"ͳ��",

	};
	static char* menuListStu[] = {
		"ѧ��",
		"��¼"
	};
	static char * menuListHelp[] = {
		"����",
		"���ڱ����",
	    "ʹ�÷���",
	    "��Ȩ��Ϣ"
	};

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListFile[0]) * 2; // ���˵����
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // ����
	int    selection;
	static int    help_about;
    static int    help_use;
    static int    help_copyright;

	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	// File �˵�
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 1)
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
			fprintf(stdout, "status : %d; NOTE : login : press ѧԺ in main menu\n", curSataus);
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
	selection = menuList(GenUIID(0),x+4*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==1 ) 
		//TODO����ʾ�������Ϣ
		help_about = !help_about;
		if(help_about==1) 
			drawBox (x+6.5*w,y-2.8*h,1.8*wlist,1.5*h,0,"ʵ��ѧ����Ϣ�������Ϣ��",'c',"Dark Gray");
		else;

	if(selection==2)
		//TODO����ʾʹ�÷���
		help_use = !help_use;
	    if(help_use==1)
			drawBox (x+6.5*w,y-4.5*h,1.8*wlist,1.5*h,0,"�����ť����Ӧ����",'c',"Dark Gray");

	if(selection==3)

		//TODO����ʾ��Ȩ
		help_copyright = !help_copyright;
	    if(help_copyright==1)
			drawLabel(x+8*w,y-h, "For Ctopic");
		//TODO����ʾ�������Ϣ


}

void DrawTextBoxLogin()
{
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double dy = h * 2;
	double x = winwidth / 4;
	double y = winheight / 4;
	double w = TextStringWidth("��") * 8;
	double xindent =  0.7*w + TextStringWidth("��");
	static bool isUserNameExist = false, isUserNameEmpty = false;
	static bool isPasswordEmpty = false, isPasswordRight = true, isTryLogin = false;

	// ����ѧ������
	drawLabel(x, y + xindent, "�û�����");
	drawLabel(x, y, "���룺");
	if (textbox(GenUIID(0), x + xindent * 0.7, y + xindent * 0.8, w, h, user_name, sizeof(user_name))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : userName textBox update : %s\n", curSataus, user_name);
		isUserNameEmpty = false;
		isUserNameExist = false;
		isTryLogin = false;
	}
	if (isUserNameEmpty)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("��"), y + xindent * 0.8, "����Ϊ�գ�");
	if(isUserNameExist)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("��") * 6, y + xindent * 0.8, "�û������ڣ�");
	if (textbox(GenUIID(0), x + xindent * 0.7, y, w, h, password, sizeof(password))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : userPassword textBox update : %s\n", curSataus, password);
		isPasswordEmpty = false;
		isPasswordRight = true;
		isTryLogin = false;
	}
	if (isPasswordEmpty)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("��"), y, "����Ϊ�գ�");
	if(isTryLogin && !isPasswordRight)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("��"), y, "���벻��ȷ��");

	if (button(GenUIID(0), x + xindent * 1.7, y - xindent, w, h, "��¼")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : press \"��¼\",user:%s,password:%s\n", curSataus, user_name, password);
		isTryLogin = true;
		if (user_name[0] == '\0')
			isUserNameEmpty = true;
		if (password[0] == '\0')
			isPasswordEmpty = true;
		if (!isUserNameEmpty && !isPasswordEmpty) {
			administrator* tmpAdmin;
			student* tmpStu;
			teacher* tmpTea;
			if (tmpAdmin = checkNameAdmin(user_name)) {
				if (strcmp(password, tmpAdmin->password) == 0) {
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : login : success,user:%s,ID:%s,type:administrator\n", curSataus, user_name, tmpAdmin->ID);
					MessageBox(NULL, TEXT("����Ա�ɹ���¼!"), TEXT("��ʾ"), MB_OK);
					curSataus = 3;
				}
				else
					isPasswordRight = false;
			}
			else if (tmpStu = checkNameStu(user_name)) {
				if (strcmp(password, tmpStu->password) == 0) {
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : login : success,user:%s,ID:%s,type:student\n", curSataus, user_name, tmpStu->ID);
					MessageBox(NULL, TEXT("ѧ����¼�ɹ�!"), TEXT("��ʾ"), MB_OK);
					curSataus = 1;   //ѧ��main��1״̬ .
				}
				else
					isPasswordRight = false;
			}
			else if (tmpTea = checkNameTea(user_name)) {
				if (strcmp(password, tmpTea->password) == 0) {
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : login : success,user:%s,ID:%s,type:teacher\n", curSataus, user_name, tmpTea->ID);
					MessageBox(NULL, TEXT("��ʦ��¼�ɹ�!"), TEXT("��ʾ"), MB_OK);
					curSataus = 2;
				}
				else
					isPasswordRight = false;
			}
			else
				isUserNameExist = true;
		}
	}

	if (button(GenUIID(0), x + xindent * 3, y - xindent, w, h, "ע��")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : press \"ע��\",turn to register interface\n", curSataus);
		memset(password, 0, sizeof(password));
		curSataus = 4;
	}

	      //��ʼ���滶ӭ
        drawBox(x,y+2.2*dy,6*dy,2.5*dy,0,"��ӭʹ��ѧ����Ϣ����ϵͳ",'c',"Brown");  //c Ϊ���������м䡣0 Ϊ����䡣
}