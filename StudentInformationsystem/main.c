#include "graphicLib.h"

//自己的头文件
#include "login.h"
#include "file.h"
#include "register.h"
#include "admin.h"
#include "teacher.h"
#include "stu.h"
// 旋转计时器
#define MOVE_DISC  1

/***************************************************************
 VisualStudio 2010 用户注意：
    将Character Set设置为 Use Multibyte Character Set
	否则中文显示不正常
***************************************************************/

// 全局变量
double winwidth, winheight;   // 窗口尺寸
int    enable_move_disc = 1;  // 允许移动
int    timer_interval = 2;    // 间隔时间 (in ms)
char   time_elapse_speed[64]; // 用于编辑时间流逝速度
char user_name[64];    // 用于编辑用户名
char password[64];     // 用于编辑密码
bool isDisplayConsole = true;

/*
 * 标识目前页面的状态
 * 0 = 登录界面，1 = 学生登录，2 = 老师登录，3 = 管理员登录
 * 4 = 注册界面
 * 5 = 管理员新建班级, 6 = 管理员删除班级，7 = 管理员事项审批
 * 8 = 老师事项申请  9= 老师新建学生   10= 老师删除学生   
   11= 学生事项申请  12 =学生个人信息修改 13 = 老师事项审批
   14 = 学生查看成绩界面 
   15 = 老师修改成绩界面.  16 = 老师统计学生成绩界面.
*/
int curSataus = 0;      

void DrawMenuLogin();


// 用户的字符事件响应函数
void CharEventProcess(char ch){
	uiGetChar(ch); // GUI字符输入
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

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
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

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标

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

// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{
	if( timerID==MOVE_DISC && enable_move_disc ) 
	{
		
		// if( s )	display(); // 刷新显示
	}
	//display(); // 刷新显示
}


// 用户主程序入口
// 仅初始化执行一次
void Main()
{
	// 初始化窗口和图形系统
	SetWindowTitle("学生信息系统");
	SetWindowSize(10, 8); // 单位 - 英寸
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
	InitGraphics();

	
	//初始化数据文件
	initFromFile();

	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器

	// 开启定时器
	startTimer(MOVE_DISC, timer_interval);   //旋转计时器  =1
	DrawMenuLogin();
	DrawTextBoxLogin();
}

/* NOTE:
 * int button(int id, double x, double y, double w, double h, char *label)里的printf已注释
 * 登录界面文件菜单里的Exit调用的exit(-1)无法正常退出，换为_exit(-1)
 * 在字符事件响应函数void CharEventProcess(char ch)中调用DisplayClear()会导致输入/删除字符时屏幕闪烁，原因未知
 * void DrawDeleteClassAdmin()中循环输出要删除的班级按钮时，要注意调用的GenUIID(N)处于同一行，如果只调用GenUIID(0)就会返回同一个值，具体见GenUIID(N)函数备注
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