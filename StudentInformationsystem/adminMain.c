
#include "graphicLib.h"
#include "admin.h"
#include "file.h"

//全局变量
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern teacher teachers;//教师用户
extern class classes;//班级
extern int curSataus;
extern bool isDisplayConsole;

void DrawMenuAdmin()
{
	static char* menuListFile[] = {
		"文件",
		"注销  | Ctrl-R", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"学院",
		"事项审批"
	};
	static char* menuListCla[] = {
		"班级",
		"新建",
		"删除",
		"修改成绩",
		"搜索",
		"统计",
		
	};
	static char* menuListStu[] = {
		"学生",
		"登录"
	};
	static char * menuListHelp[] = {"帮助",
		"关于本软件",
	    "使用方法",
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
				fprintf(stdout, "status : %d; NOTE : admin : press 注销 in 文件 menu\n", curSataus);
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
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : admin : press 事项审批 in 学院 menu\n", curSataus);
			curSataus = 7;
			break;
		default:
			break;
	}

	// 班级菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	switch (selection) {
		case 1:
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : admin : press 新建 in 班级 menu\n", curSataus);
			curSataus = 5;
			break;
		case 2:
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : admin : press 删除 in 班级 menu\n", curSataus);
			curSataus = 6;
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
	}


void DrawWellcomeAdmin()
{
	drawLabel(winwidth * 0.1, winheight * 0.9, "欢迎管理员：");
	drawLabel(winwidth * 0.1 + TextStringWidth("欢迎管理员："), winheight * 0.9, user_name);
}

