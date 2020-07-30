//===========================================================================
//
// 
//  
//  初次创建：2020年5月6日，用于<<程序设计专题>>课程大作业
//            演示内容：
//            1. 学生登录
//            2. 
//            3. 
//            
//
//===========================================================================
#ifndef __stu_h______________________
#define __stu_h______________________

/*
 *  比较简单的比较大小宏定义
 */
#define MAX(a, b) ( ( a ) > ( b ) ? ( a ) : ( b ) )
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
void Setstuname( char* username );
void Setstumima( char* username );
int stulogin( void);
void DrawMenuStu();    //  student choice
void DrawWelcomeStu();   
void DrawRequestTextboxStu();
void DrawRequestStu();
void DrawInfoTextboxStu();


#endif // ifndef ___h______________________
