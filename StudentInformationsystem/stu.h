//===========================================================================
//
// 
//  
//  ���δ�����2020��5��6�գ�����<<�������ר��>>�γ̴���ҵ
//            ��ʾ���ݣ�
//            1. ѧ����¼
//            2. 
//            3. 
//            
//
//===========================================================================
#ifndef __stu_h______________________
#define __stu_h______________________

/*
 *  �Ƚϼ򵥵ıȽϴ�С�궨��
 */
#define MAX(a, b) ( ( a ) > ( b ) ? ( a ) : ( b ) )
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
void Setstuname( char* username );
void Setstumima( char* username );
int stulogin( void);
void DrawMenuStu();    //  student choice
void DrawWelcomeStu();   
void DrawRequestTextboxStu();
void DrawRequestStu();
void DrawInfoTextboxStu();


#endif // ifndef ___h______________________
