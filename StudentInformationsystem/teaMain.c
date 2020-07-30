#include "graphicLib.h"
#include "teacher.h"
#include "file.h"

//全局变量

extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern teacher teachers;//教师用户
extern class classes;//班级
extern int curSataus;
extern bool isDisplayConsole;

void DrawMenuTea()
{
	static char* menuListFile[] = {
		"文件",
		"注销  | Ctrl-R", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"学院",
		"新建班级",
		"删除班级",
		"事项审批"
	};
	static char* menuListCla[] = {
		"班级",
		"提交事项",
		"加入学生",
		"删除学生",
		"修改成绩",
		"统计"
	};
	static char* menuListStu[] = {
		"学生",
		"登录"
	};
	static char* menuListHelp[] = {
		"帮助",
		"关于本软件"
		"版权信息"
	};

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menuListFile[0]) * 2; // 主菜单宽度
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // 缩进
	int    selection;
	static int    help_about;
    static int    help_use;
    static int    help_copyright;

	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	switch (selection) {
	case 1:
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : teacher : press 注销 in 文件 menu\n", curSataus);
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

	// 学院 菜单
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListCol, sizeof(menuListCol) / sizeof(menuListCol[0]));
	switch (selection) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	// 班级菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	switch (selection) {
	case 1:
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : teacher : press 事项 in 学院 menu\n", curSataus);
		curSataus = 8;
		break;
	case 2:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press 加入学生 in 学院 menu\n", curSataus);
		curSataus = 9;
		break ;
	case 3:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press delete stu in 学院 menu\n", curSataus);
		curSataus = 10;
		break ;
	case 4 :
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 15;//选择学生列表
		break;
	case 5 :
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 16;//选择学生列表
		break;
	default:
		break;
	}
	// 学生菜单
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListStu, sizeof(menuListStu) / sizeof(menuListStu[0]));
	switch (selection) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	// Help 菜单
	selection = menuList(GenUIID(0),x+4*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==1 ) 
		//TODO：显示本软件信息
		help_about = !help_about;
		if(help_about==1) 
			drawBox (x+6.5*w,y-2.8*h,1.8*wlist,1.5*h,0,"实现学生管理的信息化",'c',"Dark Gray");
		else;

	if(selection==2)
		//TODO：显示使用方法
		help_use = !help_use;
	    if(help_use==1)
			drawBox (x+6.5*w,y-4.5*h,1.8*wlist,1.5*h,0,"点击按钮打开相应功能",'c',"Dark Gray");

	if(selection==3)

		//TODO：显示版权
		help_copyright = !help_copyright;
	    if(help_copyright==1)
			drawLabel(x+8*w,y-h, "For Ctopic");
		//TODO：显示本软件信息
	
	
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*7, 3*w, h, "添加学生") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press 事项审批 in 学院 menu\n", curSataus);
		curSataus = 9;
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*8, 3*w, h, "删除学生") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press 事项审批 in 学院 menu\n", curSataus);
		curSataus = 10;
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*10, 3*w, h, "提交事项") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press 事项审批 in 学院 menu\n", curSataus);
		curSataus = 8;
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*9, 3*w, h, "事项审批") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press 事项审批 in 学院 menu\n", curSataus);
		curSataus = 13;
	}

	if(button(GenUIID(0), x+xindent*1.7, y-xindent*11, 3*w, h, "输入成绩") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 15;//选择学生列表
	}
	
	if(button(GenUIID(0), x+xindent*1.7, y-xindent*12, 3*w, h, "统计成绩") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : teacher : press set score menu\n", curSataus);
		curSataus = 16;//选择学生列表
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*13, w, h, "退出") ) {	
		_exit(-1); 
	}
}

void DrawWellcomeTea()
{
	drawLabel(winwidth * 0.1, winheight * 0.8, "欢迎老师：");
	drawLabel(winwidth * 0.1 + TextStringWidth("欢迎老师："), winheight * 0.8, user_name);
}