#include "graphicLib.h"
#include "teacher.h"
#include "file.h"

//ȫ�ֱ���

extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern teacher teachers;//��ʦ�û�
extern class classes;//�༶
extern int curSataus;
extern bool isDisplayConsole;

void DrawMenuTea()
{
	static char* menuListFile[] = {
		"�ļ�",
		"ע��  | Ctrl-R", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
		"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"ѧԺ",
		"�½��༶",
		"ɾ���༶",
		"��������"
	};
	static char* menuListCla[] = {
		"�༶",
		"�ύ����",
		"����ѧ��",
		"ɾ��ѧ��",
		"�޸ĳɼ�",
		"ͳ��"
	};
	static char* menuListStu[] = {
		"ѧ��",
		"��¼"
	};
	static char* menuListHelp[] = {
		"����",
		"���ڱ����"
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
	switch (selection) {
	case 1:
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : teacher : press ע�� in �ļ� menu\n", curSataus);
		curSataus = 0;
		memset(user_name, 0, sizeof(user_name));
		memset(password, 0, sizeof(password));
		break;
	case 2:
		_exit(-1);
		break;
	default:
		break;
	}

	// ѧԺ �˵�
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListCol, sizeof(menuListCol) / sizeof(menuListCol[0]));
	switch (selection) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	// �༶�˵�
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	switch (selection) {
	case 1:
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : teacher : press ���� in ѧԺ menu\n", curSataus);
		curSataus = 8;
		break;
	case 2:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press ����ѧ�� in ѧԺ menu\n", curSataus);
		curSataus = 9;
		break ;
	case 3:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press delete stu in ѧԺ menu\n", curSataus);
		curSataus = 10;
		break ;
	case 4 :
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 15;//ѡ��ѧ���б�
		break;
	case 5 :
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 16;//ѡ��ѧ���б�
		break;
	default:
		break;
	}
	// ѧ���˵�
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListStu, sizeof(menuListStu) / sizeof(menuListStu[0]));
	switch (selection) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	// Help �˵�
	selection = menuList(GenUIID(0),x+4*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==1 ) 
		//TODO����ʾ�������Ϣ
		help_about = !help_about;
		if(help_about==1) 
			drawBox (x+6.5*w,y-2.8*h,1.8*wlist,1.5*h,0,"ʵ��ѧ���������Ϣ��",'c',"Dark Gray");
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
	
	
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*7, 3*w, h, "���ѧ��") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press �������� in ѧԺ menu\n", curSataus);
		curSataus = 9;
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*8, 3*w, h, "ɾ��ѧ��") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press �������� in ѧԺ menu\n", curSataus);
		curSataus = 10;
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*10, 3*w, h, "�ύ����") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press �������� in ѧԺ menu\n", curSataus);
		curSataus = 8;
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*9, 3*w, h, "��������") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press �������� in ѧԺ menu\n", curSataus);
		curSataus = 13;
	}

	if(button(GenUIID(0), x+xindent*1.7, y-xindent*11, 3*w, h, "����ɼ�") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 15;//ѡ��ѧ���б�
	}
	
	if(button(GenUIID(0), x+xindent*1.7, y-xindent*12, 3*w, h, "ͳ�Ƴɼ�") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 16;//ѡ��ѧ���б�
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*13, w, h, "�˳�") ) {	
		_exit(-1); 
	}
}

void DrawWellcomeTea()
{
	drawLabel(winwidth * 0.1, winheight * 0.8, "��ӭ��ʦ��");
	drawLabel(winwidth * 0.1 + TextStringWidth("��ӭ��ʦ��"), winheight * 0.8, user_name);
}