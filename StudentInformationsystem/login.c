#include "graphicLib.h"
#include "login.h"
#include "file.h"
#include "md5.h"
#include "register.h"

//全局变量
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern teacher teachers;//教师用户
extern int curSataus;
extern bool isDisplayConsole;

void DrawMenuLogin()
{
	static char* menuListFile[] = {
		"文件",
		"Exit      | Ctrl-E"
	};
	static char* menuListCol[] = {
		"学院",
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
	static char * menuListHelp[] = {
		"帮助",
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
	if (selection == 1)
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
			fprintf(stdout, "status : %d; NOTE : login : press 学院 in main menu\n", curSataus);
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
	selection = menuList(GenUIID(0),x+4*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==1 ) 
		//TODO：显示本软件信息
		help_about = !help_about;
		if(help_about==1) 
			drawBox (x+6.5*w,y-2.8*h,1.8*wlist,1.5*h,0,"实现学生信息管理的信息化",'c',"Dark Gray");
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

void DrawTextBoxLogin()
{
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double dy = h * 2;
	double x = winwidth / 4;
	double y = winheight / 4;
	double w = TextStringWidth("暂") * 8;
	double xindent =  0.7*w + TextStringWidth("暂");
	static bool isUserNameExist = false, isUserNameEmpty = false;
	static bool isPasswordEmpty = false, isPasswordRight = true, isTryLogin = false;

	// 输入学号密码
	drawLabel(x, y + xindent, "用户名：");
	drawLabel(x, y, "密码：");
	if (textbox(GenUIID(0), x + xindent * 0.7, y + xindent * 0.8, w, h, user_name, sizeof(user_name))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : userName textBox update : %s\n", curSataus, user_name);
		isUserNameEmpty = false;
		isUserNameExist = false;
		isTryLogin = false;
	}
	if (isUserNameEmpty)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("暂"), y + xindent * 0.8, "名字为空！");
	if(isUserNameExist)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("暂") * 6, y + xindent * 0.8, "用户不存在！");
	if (textbox(GenUIID(0), x + xindent * 0.7, y, w, h, password, sizeof(password))) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : userPassword textBox update : %s\n", curSataus, password);
		isPasswordEmpty = false;
		isPasswordRight = true;
		isTryLogin = false;
	}
	if (isPasswordEmpty)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("暂"), y, "密码为空！");
	if(isTryLogin && !isPasswordRight)
		drawLabel(x + xindent * 0.7 + w + TextStringWidth("暂"), y, "密码不正确！");

	if (button(GenUIID(0), x + xindent * 1.7, y - xindent, w, h, "登录")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : press \"登录\",user:%s,password:%s\n", curSataus, user_name, password);
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
					MessageBox(NULL, TEXT("管理员成功登录!"), TEXT("提示"), MB_OK);
					curSataus = 3;
				}
				else
					isPasswordRight = false;
			}
			else if (tmpStu = checkNameStu(user_name)) {
				if (strcmp(password, tmpStu->password) == 0) {
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : login : success,user:%s,ID:%s,type:student\n", curSataus, user_name, tmpStu->ID);
					MessageBox(NULL, TEXT("学生登录成功!"), TEXT("提示"), MB_OK);
					curSataus = 1;   //学生main是1状态 .
				}
				else
					isPasswordRight = false;
			}
			else if (tmpTea = checkNameTea(user_name)) {
				if (strcmp(password, tmpTea->password) == 0) {
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : login : success,user:%s,ID:%s,type:teacher\n", curSataus, user_name, tmpTea->ID);
					MessageBox(NULL, TEXT("教师登录成功!"), TEXT("提示"), MB_OK);
					curSataus = 2;
				}
				else
					isPasswordRight = false;
			}
			else
				isUserNameExist = true;
		}
	}

	if (button(GenUIID(0), x + xindent * 3, y - xindent, w, h, "注册")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : login : press \"注册\",turn to register interface\n", curSataus);
		memset(password, 0, sizeof(password));
		curSataus = 4;
	}

	      //初始界面欢迎
        drawBox(x,y+2.2*dy,6*dy,2.5*dy,0,"欢迎使用学生信息管理系统",'c',"Brown");  //c 为放置在正中间。0 为不填充。
}