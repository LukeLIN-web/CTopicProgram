//===========================================================================
//
// 
//  
//  ���δ�����2020��5��3�գ�����<<�������ר��>>�γ̴���ҵ
//            ��ʾ���ݣ�
//            1. ѧ����¼
//            2. 
//            3. 
//            
//
//===========================================================================
#include "graphicLib.h"
#include "login.h"
#include "file.h"
#include "md5.h"
#include "register.h"

//ȫ�ֱ��������������
static void   draw_rect(double cx, double cy, double w, double h, int fill);
static char   applitem[64]; // ���ڱ༭�û���
extern double winwidth, winheight; // ���ڳߴ�
extern bool isDisplayConsole;
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
extern int curSataus;

// draw a rectangle
//    (cx,cy) - center
//       w    - width
//       h    - height
static void draw_rect(double cx, double cy, double w, double h, int fill)
{
	drawRectangle(cx-w/2, cy-h/2, w, h, fill);
}

void SetItemEditString(double item)
{
	sprintf(applitem, "%f", item);
}

double GetEditItem()
{
	double v = 0;
	sscanf(applitem, "%lf", &v);
	return v;
}

//    data�ǽṹ�����飬filename���ļ����Ե�ַ��n�������Ľṹ������ ͳ��ѧ������ʱ���õ� 
// �ɹ�����1  ���ɹ�����0
/*int GetDataFromTxt( student* data, const char* filename, int* n)
{
	int i = 0; 
    FILE *fp = fopen(filename, "r");
    if( fp==NULL  ){
         //printf("Open file failed or no this file!\n");
        return 0;
    }  
    while( !feof(fp) )
    {     //����˸�ѧ�����ݡ�
		fscanf(fp, "%s %s %s %s  %s %s %s %s ",data[i].stuname,data[i].stuxuehao, data[i].stupsw, data[i].stugrade ,data[i].stumajor,data[i].stusex,data[i].stuborn,data[i].stuhome );
        i++;        
    }
    *n = i;    
	return 1 ; 
}
 
int stulogin()
{
    int i, n,flag;
    Student data[100];   //    ��ȡ���� 
    flag = GetDataFromTxt(data, "/stu.txt", &n);
	printf("login");
	if(flag == 0) return 0 ;
    //    ��¼ʾ�� 
    do{
        //    ����ֻ�Ǵ��Ե�д��һ��
        //    ������˺Ŵ����������������з��� 
        for(i = 0; i < n; ++i)
        {   // ����û���������ȷ
			if( strcmp(stu_name,data[i].stuxuehao)==0 && strcmp(stu_mima,data[i].stupsw)==0 ){
                //logsuccess =1;
                break; 
            }
			if( strcmp(stu_name,"123")==0 && strcmp(stu_mima,"123")==0 ){
               // logsuccess =1;
                break; 
            }
        }
        if( i == n ){
           //logfail =1 ;
        }else{
            break;
        }        
    }while(1);
    return 0;
}
*/
void DrawMenuStu( )
{
	student* curStu = checkNameStu(user_name);
	static char* menuListFile[] = {
		"�ļ�",
		"ע��  | Ctrl-R", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
		"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"ѧԺ",
		"��������"
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
		"������Ϣ",
		"�ύ����",
		"�鿴�ɼ�"
	};
	static char * menuListHelp[] = {"����",
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
	switch (selection) {
	case 1:
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : student : press ע�� in �ļ� menu\n", curSataus);
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
		MessageBox(NULL, TEXT("û��Ȩ��!"), TEXT("��ʾ"), MB_OK);
		break;
	case 2:
		MessageBox(NULL, TEXT("û��Ȩ��!"), TEXT("��ʾ"), MB_OK);
		break;
	default:
		break;
	}
	// �༶�˵�
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	// ѧ���˵�
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListStu, sizeof(menuListStu) / sizeof(menuListStu[0]));
	switch (selection) {
	case 1:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press ������Ϣ¼����޸� in  menu\n", curSataus);
		curSataus = 12;
		break; //������Ϣ
	case 2:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press �ύ���� in  menu\n", curSataus);
		curSataus = 11;
		break;  //�ύ����
	case 3:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press �鿴�ɼ� in  menu\n", curSataus);
		curSataus = 14 ;
		break;//�鿴�ɼ�
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
	

	if( button(GenUIID(0), x+xindent*1.7, y-xindent*9, 3*w, h, "�ύ����") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press �ύ���� in  menu\n", curSataus);
		curSataus = 11;
	}

	if( button(GenUIID(0), x+xindent*1.7, y-xindent*10, 3*w, h, "������Ϣ¼����޸�") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press ������Ϣ¼����޸� in  menu\n", curSataus);
		curSataus = 12;// ��ʾ������Ϣ��
	}

	if(button(GenUIID(0), x+xindent*1.7, y-xindent*11, 3*w, h, "�鿴�ɼ�") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press �鿴�ɼ� in  menu\n", curSataus);
		curSataus = 14 ;//��ʾ�ɼ�
	}
	if(curSataus == 14){
		drawLabel(x+TextStringWidth("�鿴�ɼ�")+3*w, y-xindent*11,"���ĳɼ�Ϊ:");
		drawLabel(x+TextStringWidth("�鿴�ɼ�")*3+3*w, y-xindent*11,curStu->scores);
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*12, w, h, "�˳�") ) {	
		_exit(-1); 
	}
	
}
void DrawWelcomeStu()
{
	drawLabel(winwidth * 0.1, winheight * 0.9, "��ӭͬѧ��");
	drawLabel(winwidth * 0.1 + TextStringWidth("��ӭͬѧ��"), winheight * 0.9, user_name);
}