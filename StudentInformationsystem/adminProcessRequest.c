#include "graphicLib.h"
#include "admin.h"
#include "file.h"

//ȫ�ֱ���
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern teacher teachers;//��ʦ�û�
extern class classes;//�༶
extern int curSataus;
extern int requestNum;
extern bool isDisplayConsole;

void DrawResponseAdmin()
{
	double fH = GetFontHeight();
	double h = fH * 2; // �ؼ��߶�
	double x = winwidth * 0.1;
	double y = winheight * 0.75;
	double w = TextStringWidth("��") * 4;
	double dy = 2 * h + TextStringWidth("��") * 2;
	static int page = 0, pageNum = 0, rowNum = 0;

	int i, j, k;
	teacher* tmpTea;
	request* tmpResquest;

	if (requestNum == 0) {
		drawLabel(winwidth * 0.5 - TextStringWidth("�޴���������") / 2, winheight * 0.7, "�޴���������");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.5, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : adopt request : no request,press \"����\",turn to admin interface\n", curSataus);
			curSataus = 3;
		}
		return;
	}

	drawLabel(winwidth * 0.35 - TextStringWidth("����������") / 2, winheight * 0.85, "����������");
	drawLabel(winwidth * 0.7 - TextStringWidth("��"), winheight * 0.85, "����");
	drawLabel(winwidth * 0.85 - TextStringWidth("��"), winheight * 0.85, "����");

	
	if (rowNum == 0 || pageNum == 0) {
		rowNum = winheight * 0.7 / dy;
		pageNum = requestNum / rowNum;
	}
	{
		char pages[6];
		sprintf(pages, "%2d/%2d", page + 1, pageNum + 1);
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 1.25, winheight * 0.1, pages);
	}
	setButtonColors("White", "Blue", "White", "Red", 0);
	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��") * 2.5, winheight * 0.09, TextStringWidth("��"), h, "<<")) {
		if (page > 0)
			--page;
	}
	if (button(GenUIID(0), winwidth * 0.5 + TextStringWidth("��") * 1.5, winheight * 0.09, TextStringWidth("��"), h, ">>")) {
		if (page < pageNum)
			++page;
	}
	setButtonColors("Blue", "Blue", "Red", "Red", 0);
	if (button(GenUIID(0), winwidth * 0.8 + w * 0.75, winheight * 0.08, w, h, "����")) {
		pageNum = 0;
		page = 0;
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : adopt request : press \"����\",turn to admin interface\n", curSataus);
		curSataus = 3;
	}

	j = page * rowNum; k = 0;
	tmpTea = &teachers;
	tmpResquest = NULL;
	for (i = 0; i < rowNum; ++i) {
		tmpResquest = NULL;
		while (tmpTea->ID[0] != '\0' && tmpResquest == NULL) {
			if (k == 5)
				k = 0;
			for (; k < 5; ++k) {
				if (tmpTea->requests[k].content[1] != '\0' && tmpTea->requests[k].isAdopt == 0) {
					if (j > 0)
						--j;
					else {
						tmpResquest = tmpTea->requests + k;
						++k;
						break;
					}
				}
			}
			if (tmpResquest == NULL)
				tmpTea = tmpTea->next;
		}
		if (tmpResquest == NULL)
			break;
		drawLabel(winwidth * 0.1, y - i * dy, tmpResquest->content);
		drawLabel(winwidth * 0.6, y - i * dy, tmpTea->name);
		if (button(GenUIID(i), winwidth * 0.8, y - i * dy, w, h, "ͬ��")) {
			tmpResquest->isAdopt = 1;
			--requestNum;
			saveToFile();
		}
		if (button(GenUIID(i + rowNum), winwidth * 0.8, y - i * dy - h - TextStringWidth("��") / 2, w, h, "����")) {
			tmpResquest->isAdopt = 2;
			--requestNum;
			saveToFile();
		}
	}
}