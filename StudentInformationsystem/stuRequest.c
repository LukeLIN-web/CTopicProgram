#include "graphicLib.h"
#include "stu.h"
#include "file.h"
#include "register.h"

//ȫ�ֱ���
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern class classes;//�༶
extern int curSataus, requestNum;  //current status ��ǰ״̬. 
extern bool isDisplayConsole;

void DrawRequestTextboxStu()
{
	static char newContent[30];
	student* curStu = checkNameStu(user_name);
	if (curStu == NULL)//curStatausת��˲�䣬�п���curStatuas��ֵ�ѱ䣬user_name����գ����Ե����˴˺���
		return;
	if (curStu->requests[4].content[0] != '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 7.5, winheight * 0.85, "������������ȴ�������������");
	}
	else {
		drawLabel(winwidth * 0.1, winheight * 0.85, "�����");
		if (textbox(GenUIID(0), winwidth * 0.2, winheight * 0.83, winwidth * 0.5, GetFontHeight() * 2, newContent, sizeof(newContent))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,student : new content : %s\n", curSataus, newContent);
		}
		if (button(GenUIID(0), winwidth * 0.75, winheight * 0.83, TextStringWidth("��") * 4, GetFontHeight() * 2, "����")) {
			if (newContent[0] != '\0') {
				int i;
				for (i = 0; i < 5; ++i) {
					if (curStu->requests[i].content[0] == '\0') {
						strcpy(curStu->requests[i].content, newContent);
						curStu->requests[i].isAdopt = 0;
						break;
					}
				}
				++requestNum;
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : request,student : create new request,success : %s\n", curSataus, newContent);
				memset(newContent, 0, sizeof(newContent));
				saveToFile();
			}
		}
	}
}


void DrawRequestStu()
{
	student* curStu = checkNameStu(user_name);
	int i;
	if (curStu == NULL)//curStatausת��˲�䣬�п���curStatuas��ֵ�ѱ䣬user_name����գ����Ե����˴˺���
		return;
	if (curStu->requests[0].content[0] == '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 3, winheight * 0.75, "���������");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.6, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,student : no request,press \"����\",turn to student interface\n", curSataus);
			curSataus = 1;
		}
		return;
	}
	drawLabel(winwidth * 0.35 - TextStringWidth("��������") / 2, winheight * 0.78, "��������");
	drawLabel(winwidth * 0.75 - TextStringWidth("��"), winheight * 0.78, "״̬");
	drawLabel(winwidth * 0.85 - TextStringWidth("��"), winheight * 0.78, "����");
	for (i = 0; i < 5; ++i) {
		if (curStu->requests[i].content[0] == '\0')
			break;
		drawLabel(winwidth * 0.1, winheight * (0.75 - 0.13 * i), curStu->requests[i].content);
		switch (curStu->requests[i].isAdopt) {
			case 0:
				drawLabel(winwidth * 0.75 - TextStringWidth("δ����") / 2, winheight * (0.73 - 0.13 * i), "δ����");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("��") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("��") * 3, GetFontHeight() * 2, "ȡ��")) {
					if(i < 4)
						memmove(curStu->requests + i, curStu->requests + i + 1, sizeof(request) * (4 - i));
					memset(curStu->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,student : delete request,success\n", curSataus);
					saveToFile();
					--requestNum;
				}
				break;
			case 1:
				drawLabel(winwidth * 0.75 - TextStringWidth("ͬ��") / 2, winheight * (0.73 - 0.13 * i), "ͬ��");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("��") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("��") * 3, GetFontHeight() * 2, "ɾ��")) {
					if (i < 4)
						memmove(curStu->requests + i, curStu->requests + i + 1, sizeof(request) * (4 - i));
					memset(curStu->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,student : delete request,success\n", curSataus);
					saveToFile();
				}
				break;
			case 2:
				drawLabel(winwidth * 0.75 - TextStringWidth("����") / 2, winheight * (0.73 - 0.13 * i), "����");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("��") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("��") * 3, GetFontHeight() * 2, "ɾ��")) {
					if (i < 4)
						memmove(curStu->requests + i, curStu->requests + i + 1, sizeof(request) * (4 - i));
					memset(curStu->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,student : delete request,success\n", curSataus);
					saveToFile();
				}
				break;
		}
	}
	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.1, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : request,student : no request,press \"����\",turn to student interface\n", curSataus);
		curSataus = 1;
	}
}

//����������Ϣ�޸���
void DrawInfoTextboxStu(){
	
	student* curStu = checkNameStu(user_name);  // �����û����Ƿ����
	if (curStu == NULL)//curStatausת��˲�䣬�п���curStatuas��ֵ�ѱ䣬user_name����գ����Ե����˴˺���
		return;
	if (textbox(GenUIID(0), winwidth * 0.4, winheight * 0.83, winwidth * 0.5, GetFontHeight() * 2, curStu->birth, sizeof(curStu->birth))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : student create new birth,success : %s\n", curSataus, curStu->birth);
	}
	if (textbox(GenUIID(0), winwidth * 0.4, winheight * 0.73, winwidth * 0.5, GetFontHeight() * 2, curStu->home, sizeof(curStu->home))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : student create new birth,success : %s\n", curSataus, curStu->home);
	}
	if (textbox(GenUIID(0), winwidth * 0.4, winheight * 0.63, winwidth * 0.5, GetFontHeight() * 2, curStu->phone, sizeof(curStu->phone))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : student create new birth,success : %s\n", curSataus, curStu->phone);
	}
	//������ʾ
	if (curStu->birth[0] == '\0') {
		drawLabel(TextStringWidth("��") * 7.5, winheight * 0.85, "����д�������ڣ�");
	}
	else {
		drawLabel(TextStringWidth("��") * 7.5, winheight * 0.85, "��������:");
	}
	//��������
	if (curStu->home[0] == '\0') {
		drawLabel(TextStringWidth("��") * 7.5, winheight * 0.75, "����д��ͥסַ��");
	}
	else {
		drawLabel(TextStringWidth("��") * 7.5, winheight * 0.75, "��ͥסַ:");
	}
	//�绰
	if (curStu->phone[0] == '\0') {
		drawLabel(TextStringWidth("��") * 7.5, winheight * 0.65, "����д�绰��");
	}
	else {
		drawLabel(TextStringWidth("��") * 7.5, winheight * 0.65, "�绰:");
	}

	if(button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.2, TextStringWidth("��") * 5, GetFontHeight() * 2, "�޸����")){
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : student : create new birth,success : %s\n", curSataus, curStu->birth);
				MessageBox(NULL, TEXT("����ɹ�!"), TEXT("��ʾ"), MB_OK);
				saveToFile();
	}

	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.1, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : request,student : no request,press \"����\",turn to student interface\n", curSataus);
		curSataus = 1;
	}
}
