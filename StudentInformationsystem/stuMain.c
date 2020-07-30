//===========================================================================
//
// 
//  
//  初次创建：2020年5月3日，用于<<程序设计专题>>课程大作业
//            演示内容：
//            1. 学生登录
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

//全局变量保存各个参数
static void   draw_rect(double cx, double cy, double w, double h, int fill);
static char   applitem[64]; // 用于编辑用户名
extern double winwidth, winheight; // 窗口尺寸
extern bool isDisplayConsole;
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
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

//    data是结构体数组，filename是文件绝对地址，n保存读入的结构体数量 统计学生数量时会用到 
// 成功返回1  不成功返回0
/*int GetDataFromTxt( student* data, const char* filename, int* n)
{
	int i = 0; 
    FILE *fp = fopen(filename, "r");
    if( fp==NULL  ){
         //printf("Open file failed or no this file!\n");
        return 0;
    }  
    while( !feof(fp) )
    {     //输入八个学生数据。
		fscanf(fp, "%s %s %s %s  %s %s %s %s ",data[i].stuname,data[i].stuxuehao, data[i].stupsw, data[i].stugrade ,data[i].stumajor,data[i].stusex,data[i].stuborn,data[i].stuhome );
        i++;        
    }
    *n = i;    
	return 1 ; 
}
 
int stulogin()
{
    int i, n,flag;
    Student data[100];   //    获取数据 
    flag = GetDataFromTxt(data, "/stu.txt", &n);
	printf("login");
	if(flag == 0) return 0 ;
    //    登录示例 
    do{
        //    这里只是粗略地写了一个
        //    具体的账号错误或者密码错误自行发挥 
        for(i = 0; i < n; ++i)
        {   // 如果用户和密码正确
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
		"个人信息",
		"提交申请",
		"查看成绩"
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
			fprintf(stdout, "status : %d; NOTE : student : press 注销 in 文件 menu\n", curSataus);
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
		MessageBox(NULL, TEXT("没有权限!"), TEXT("提示"), MB_OK);
		break;
	case 2:
		MessageBox(NULL, TEXT("没有权限!"), TEXT("提示"), MB_OK);
		break;
	default:
		break;
	}
	// 班级菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCla, sizeof(menuListCla) / sizeof(menuListCla[0]));
	// 学生菜单
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListStu, sizeof(menuListStu) / sizeof(menuListStu[0]));
	switch (selection) {
	case 1:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press 个人信息录入和修改 in  menu\n", curSataus);
		curSataus = 12;
		break; //个人信息
	case 2:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press 提交事项 in  menu\n", curSataus);
		curSataus = 11;
		break;  //提交申请
	case 3:
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press 查看成绩 in  menu\n", curSataus);
		curSataus = 14 ;
		break;//查看成绩
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
	

	if( button(GenUIID(0), x+xindent*1.7, y-xindent*9, 3*w, h, "提交事项") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press 提交事项 in  menu\n", curSataus);
		curSataus = 11;
	}

	if( button(GenUIID(0), x+xindent*1.7, y-xindent*10, 3*w, h, "个人信息录入和修改") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press 个人信息录入和修改 in  menu\n", curSataus);
		curSataus = 12;// 显示个人信息。
	}

	if(button(GenUIID(0), x+xindent*1.7, y-xindent*11, 3*w, h, "查看成绩") ) {
		if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : student : press 查看成绩 in  menu\n", curSataus);
		curSataus = 14 ;//显示成绩
	}
	if(curSataus == 14){
		drawLabel(x+TextStringWidth("查看成绩")+3*w, y-xindent*11,"您的成绩为:");
		drawLabel(x+TextStringWidth("查看成绩")*3+3*w, y-xindent*11,curStu->scores);
	}
	if( button(GenUIID(0), x+xindent*1.7, y-xindent*12, w, h, "退出") ) {	
		_exit(-1); 
	}
	
}
void DrawWelcomeStu()
{
	drawLabel(winwidth * 0.1, winheight * 0.9, "欢迎同学：");
	drawLabel(winwidth * 0.1 + TextStringWidth("欢迎同学："), winheight * 0.9, user_name);
}