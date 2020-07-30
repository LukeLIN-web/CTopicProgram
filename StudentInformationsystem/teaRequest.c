#include "graphicLib.h"
#include "teacher.h"
#include "file.h"
#include "register.h"

//ȫ�ֱ���
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern teacher teachers;//��ʦ�û�
extern class classes;//�༶
extern int curSataus, requestNum;  //current status ��ǰ״̬. 
extern bool isDisplayConsole;

void DrawRequestTextboxTea()
{
	static char newContent[30];
	teacher* curTea = checkNameTea(user_name);
	if (curTea == NULL)//curStatausת��˲�䣬�п���curStatuas��ֵ�ѱ䣬user_name����գ����Ե����˴˺���
		return;
	if (curTea->requests[4].content[0] != '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 7.5, winheight * 0.85, "������������ȴ�������������");
	}
	else {
		drawLabel(winwidth * 0.1, winheight * 0.85, "�����");
		if (textbox(GenUIID(0), winwidth * 0.2, winheight * 0.83, winwidth * 0.5, GetFontHeight() * 2, newContent, sizeof(newContent))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,teacher : new content : %s\n", curSataus, newContent);
		}
		if (button(GenUIID(0), winwidth * 0.75, winheight * 0.83, TextStringWidth("��") * 4, GetFontHeight() * 2, "����")) {
			if (newContent[0] != '\0') {
				int i;
				for (i = 0; i < 5; ++i) {
					if (curTea->requests[i].content[0] == '\0') {
						strcpy(curTea->requests[i].content, newContent);
						curTea->requests[i].isAdopt = 0;
						break;
					}
				}
				++requestNum;
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : request,teacher : create new request,success : %s\n", curSataus, newContent);
				memset(newContent, 0, sizeof(newContent));
				saveToFile();
			}
		}
	}
}

void DrawRequestTea()
{
	teacher* curTea = checkNameTea(user_name);
	int i;
	if (curTea == NULL)//curStatausת��˲�䣬�п���curStatuas��ֵ�ѱ䣬user_name����գ����Ե����˴˺���
		return;
	if (curTea->requests[0].content[0] == '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 3, winheight * 0.75, "���������");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.6, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,teacher : no request,press \"����\",turn to teacher interface\n", curSataus);
			curSataus = 2;
		}
		return;
	}
	drawLabel(winwidth * 0.35 - TextStringWidth("��������") / 2, winheight * 0.78, "��������");
	drawLabel(winwidth * 0.75 - TextStringWidth("��"), winheight * 0.78, "״̬");
	drawLabel(winwidth * 0.85 - TextStringWidth("��"), winheight * 0.78, "����");
	for (i = 0; i < 5; ++i) {
		if (curTea->requests[i].content[0] == '\0')
			break;
		drawLabel(winwidth * 0.1, winheight * (0.75 - 0.13 * i), curTea->requests[i].content);
		switch (curTea->requests[i].isAdopt) {
			case 0:
				drawLabel(winwidth * 0.75 - TextStringWidth("δ����") / 2, winheight * (0.73 - 0.13 * i), "δ����");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("��") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("��") * 3, GetFontHeight() * 2, "ȡ��")) {
					if(i < 4)
						memmove(curTea->requests + i, curTea->requests + i + 1, sizeof(request) * (4 - i));
					memset(curTea->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,teacher : delete request,success\n", curSataus);
					saveToFile();
					--requestNum;
				}
				break;
			case 1:
				drawLabel(winwidth * 0.75 - TextStringWidth("ͬ��") / 2, winheight * (0.73 - 0.13 * i), "ͬ��");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("��") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("��") * 3, GetFontHeight() * 2, "ɾ��")) {
					if (i < 4)
						memmove(curTea->requests + i, curTea->requests + i + 1, sizeof(request) * (4 - i));
					memset(curTea->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,teacher : delete request,success\n", curSataus);
					saveToFile();
				}
				break;
			case 2:
				drawLabel(winwidth * 0.75 - TextStringWidth("����") / 2, winheight * (0.73 - 0.13 * i), "����");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("��") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("��") * 3, GetFontHeight() * 2, "ɾ��")) {
					if (i < 4)
						memmove(curTea->requests + i, curTea->requests + i + 1, sizeof(request) * (4 - i));
					memset(curTea->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,teacher : delete request,success\n", curSataus);
					saveToFile();
				}
				break;
		}
	}
	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.1, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : request,teacher : no request,press \"����\",turn to teacher interface\n", curSataus);
		curSataus = 2;
	}
}