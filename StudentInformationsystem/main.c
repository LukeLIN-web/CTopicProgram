#include "graphicLib.h"

//�Լ���ͷ�ļ�
#include "login.h"
#include "file.h"
#include "register.h"
#include "admin.h"
#include "teacher.h"
#include "stu.h"
// ��ת��ʱ��
#define MOVE_DISC  1

/***************************************************************
 VisualStudio 2010 �û�ע�⣺
    ��Character Set����Ϊ Use Multibyte Character Set
	����������ʾ������
***************************************************************/

// ȫ�ֱ���
double winwidth, winheight;   // ���ڳߴ�
int    enable_move_disc = 1;  // �����ƶ�
int    timer_interval = 2;    // ���ʱ�� (in ms)
char   time_elapse_speed[64]; // ���ڱ༭ʱ�������ٶ�
char user_name[64];    // ���ڱ༭�û���
char password[64];     // ���ڱ༭����
bool isDisplayConsole = true;

/*
 * ��ʶĿǰҳ���״̬
 * 0 = ��¼���棬1 = ѧ����¼��2 = ��ʦ��¼��3 = ����Ա��¼
 * 4 = ע�����
 * 5 = ����Ա�½��༶, 6 = ����Աɾ���༶��7 = ����Ա��������
 * 8 = ��ʦ��������  9= ��ʦ�½�ѧ��   10= ��ʦɾ��ѧ��   
   11= ѧ����������  12 =ѧ��������Ϣ�޸� 13 = ��ʦ��������
   14 = ѧ���鿴�ɼ����� 
   15 = ��ʦ�޸ĳɼ�����.  16 = ��ʦͳ��ѧ���ɼ�����.
*/
int curSataus = 0;      

void DrawMenuLogin();


// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch){
	uiGetChar(ch); // GUI�ַ�����
	switch (curSataus)	{
	case 0:
		DrawTextBoxLogin();
		break;
	case 1:
		if (isDisplayConsole) {
			fprintf(stdout, "status : %d; NOTE : TODO : char event in student interface\n", curSataus);
		}
		break;
	case 2:
		if (isDisplayConsole) {
			fprintf(stdout, "status : %d; NOTE : TODO : char event in teacher interface\n", curSataus);
		}
		break;
	case 3:
		break;
	case 4:
		DrawTextBoxRegister();
		break;
	case 5:
		DrawNewClassAdmin();
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		DrawRequestTextboxTea();
		break;
	case 9:
		DrawNewstuTea();
		break;
	case 10:
		DrawDeleteStuTea();
		break;
	case 11:
		DrawRequestTextboxStu();
	    break;
	case 12:
	    DrawInfoTextboxStu();
		break;
	case 13:
		DrawResponseTea();
		break;
	
	default:
		if (isDisplayConsole) {
			fprintf(stdout, "status : %d; WARNING : undefined char event(menu statu)\n", curSataus);
		}
		break;
	}
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	switch (curSataus) {
		case 0:
			DisplayClear();
			DrawMenuLogin();
			DrawTextBoxLogin();
			break;
		case 1:
			if (isDisplayConsole) {
				fprintf(stdout, "status : %d; NOTE : TODO : keyboard event in student interface\n", curSataus);
			}
			DrawWelcomeStu();
			DrawMenuStu();
			break;
		case 2:
			DrawMenuTea();
			DrawWellcomeTea();
			break;
		case 3:
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			break;
		case 4:
			DrawMenuRegister();
			DrawTextBoxRegister();
			break;
		case 5:
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			DrawNewClassAdmin();
			break;
		case 6:
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			DrawDeleteClassAdmin();
			break;
		case 7:
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			DrawResponseAdmin();
			break;
		case 8:
			DrawMenuTea();
			DrawWellcomeTea();
			DrawRequestTextboxTea(); 
			DrawRequestTea();
			break;
		case 11:
			DrawMenuStu();
			DrawWelcomeStu(); 
			DrawRequestTextboxStu();
			DrawRequestStu();
			break;
		case 12:
			DrawInfoTextboxStu();
			break ;
		case 13:
			DrawResponseTea();
			break;
		case 15:
			DrawSetScoreTea();
			break;
		case 16:
			DrawStuScoreStatis();
			break;
		default:
			if (isDisplayConsole) {
				fprintf(stdout, "status : %d; WARNING : undefined keyboard event(menu statu)\n", curSataus);
			}
			break;
	}
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���

	switch(curSataus) {
		case 0:
			DisplayClear();
			DrawMenuLogin();
			DrawTextBoxLogin();
			break;
		case 1:
			if (isDisplayConsole) {
				fprintf(stdout, "status : %d; NOTE : TODO : mouse event in student interface\n", curSataus);
			}
			DisplayClear();
			DrawMenuStu();    //  student choice
			DrawWelcomeStu();   
			break;
		case 2:
			DisplayClear();
			DrawMenuTea();
			DrawWellcomeTea();
			break;
		case 3:
			DisplayClear();
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			break;
		case 4:
			DisplayClear();
			DrawMenuRegister();
			DrawTextBoxRegister();
			break;
		case 5:
			DisplayClear();
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			DrawNewClassAdmin();
			break;
		case 6:
			DisplayClear();
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			DrawDeleteClassAdmin();
			break;
		case 7:
			DisplayClear();
			DrawMenuAdmin();
			DrawWellcomeAdmin();
			DrawResponseAdmin();
			break;
		case 8:
			DisplayClear();
			DrawMenuTea();
			DrawWellcomeTea();
			DrawRequestTextboxTea();
			DrawRequestTea();
			break;
		case 9:
			DisplayClear();
			DrawMenuTea();
			DrawNewstuTea();
			break;
		case 10:
			DisplayClear();
			DrawMenuTea();
			DrawDeleteStuTea();
			break;
		case 11:
			DisplayClear();
			DrawMenuStu();
			DrawWelcomeStu(); 
			DrawRequestTextboxStu();
			DrawRequestStu();
			break;
		case 12:
			DisplayClear();
			DrawInfoTextboxStu();
			break;
		case 13:
			DisplayClear();
			DrawResponseTea();
			break;
		case 14:
		   DisplayClear();
			DrawMenuStu();
			DrawWelcomeStu(); 
			break;
		case 15:
			DisplayClear();
			DrawSetScoreTea();
			break;
		case 16:
			DisplayClear();
			DrawStuScoreStatis();
			break;
		default:
			if (isDisplayConsole) {
				fprintf(stdout, "status : %d; WARNING : undefined mouse event(menu statu)\n", curSataus);
			}
			break;
	}
}

// �û��ļ�ʱ��ʱ����Ӧ����
void TimerEventProcess(int timerID)
{
	if( timerID==MOVE_DISC && enable_move_disc ) 
	{
		
		// if( s )	display(); // ˢ����ʾ
	}
	//display(); // ˢ����ʾ
}


// �û����������
// ����ʼ��ִ��һ��
void Main()
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("ѧ����Ϣϵͳ");
	SetWindowSize(10, 8); // ��λ - Ӣ��
	//SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
	InitGraphics();

	
	//��ʼ�������ļ�
	initFromFile();

	// ��ô��ڳߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��

	// ������ʱ��
	startTimer(MOVE_DISC, timer_interval);   //��ת��ʱ��  =1
	DrawMenuLogin();
	DrawTextBoxLogin();
}

/* NOTE:
 * int button(int id, double x, double y, double w, double h, char *label)���printf��ע��
 * ��¼�����ļ��˵����Exit���õ�exit(-1)�޷������˳�����Ϊ_exit(-1)
 * ���ַ��¼���Ӧ����void CharEventProcess(char ch)�е���DisplayClear()�ᵼ������/ɾ���ַ�ʱ��Ļ��˸��ԭ��δ֪
 * void DrawDeleteClassAdmin()��ѭ�����Ҫɾ���İ༶��ťʱ��Ҫע����õ�GenUIID(N)����ͬһ�У����ֻ����GenUIID(0)�ͻ᷵��ͬһ��ֵ�������GenUIID(N)������ע
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/