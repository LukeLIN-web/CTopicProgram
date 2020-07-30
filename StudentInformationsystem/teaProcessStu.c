#include "graphicLib.h"
#include "teacher.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

//ȫ�ֱ���
extern char user_name[64]; // ���ڱ༭�û���
extern char password[64]; // ���ڱ༭����
extern double winwidth, winheight; // ���ڳߴ�
extern administrator administrators;//����Ա�û�
extern student students;//ѧ���û�
extern teacher teachers;//��ʦ�û�
extern int curSataus;
extern int requestNum;
extern int  stuNum, teaNum;
extern bool isDisplayConsole;

student * checkStuName(const char* name)
{
	student * tmp = &students;
	while (tmp->ID[0] != '\0') {
		if (strcmp(name, tmp->name) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void DrawNewstuTea()
{
	static char newStuName[64] = { 0 };
	static char newPassword[64] = { 0 };
	static bool isstuNameExit = false, isstuNameEmpty = false, isstuPasswordEmpty = false;
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth * 0.35;
	double y = winheight / 2;
	double w = TextStringWidth("��") * 2;
	double dx = TextStringWidth("��");
	double dy = h * 2;
	drawLabel(winwidth * 0.5 - TextStringWidth("����ѧ��") / 2, winheight * 0.7, "����ѧ��");
	drawLabel(x, y, "ѧ������");
	drawLabel(x, y-dy, "ѧ�����룺");

	if (textbox(GenUIID(0), x + dx * 4, y, w * 4, h, newStuName, sizeof(newStuName))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : login : stuName textBox update : %s\n", curSataus, newStuName);
			isstuNameEmpty = false;
			isstuNameExit = false;
	}
	if (textbox(GenUIID(0), x + dx * 4, y-dy, w * 4, h, newPassword, sizeof(newPassword))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : login : stupassword textBox update : %s\n", curSataus, newPassword);
			isstuPasswordEmpty = false;
	}
		if(isstuNameExit)
			drawLabel(x + dx * 5 + w * 4, y, "��ѧ���Ѵ��ڣ�");
		if(isstuPasswordEmpty)  
			MessageBox(NULL, TEXT("���벻��Ϊ�գ�!"), TEXT("��ʾ"), MB_OK);
		if (button(GenUIID(0), winwidth * 0.5 - w * 1.5, y - 2*dy, w * 3, h, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : new stu teacher : press \"����\",name:%s\n", curSataus, newStuName);
			if (newStuName[0] == '\0')
				isstuNameEmpty = true;
			else if (newPassword[0] == '\0')
				isstuPasswordEmpty = true;   //password is empty
			else if (checkStuName(newStuName))
				isstuNameExit = true;
			else {
				student * tmp = &students;
				while (tmp->ID[0] != '\0') tmp = tmp->next;
				getID(tmp->ID);
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : new student : ID:%s\n", curSataus, tmp->ID);
				strcpy(tmp->name, newStuName);
				strcpy(tmp->password,newPassword); 
				tmp->next = (student*)malloc(sizeof(student));
				memset(tmp->next, 0, sizeof(student));  //��ʼ��Ϊ0,��ֹ��������. 
				memset(newStuName, 0, sizeof(newStuName));
				memset(newPassword, 0, sizeof(newPassword));
				++stuNum;
				curSataus = 2;  //�ص���ʦ��¼����
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : new stu teacher : success,turn to teacher interface\n", curSataus);
				MessageBox(NULL, TEXT("������ѧ���ɹ�!"), TEXT("��ʾ"), MB_OK);
				saveToFile();
			}
	}
	if (button(GenUIID(0), winwidth * 0.5 + w * 2, y - 2*dy, w * 3, h, "ȡ��")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : new stu teacher : cancel create new stu,turn to teacher interface\n", curSataus);
			curSataus = 2;
	}
	

}

void DrawDeleteStuTea()
{	
	double fH = GetFontHeight();
	double h = fH * 2; // �ؼ��߶�
	double x = winwidth * 0.1;
	double y = winheight * 0.75;
	double w = TextStringWidth("��") * 8;
	double dx = TextStringWidth("��") * 10;
	double dy = h * 2;
	static int page = 0, pageNum = 0, stuNumLocal = 0, colNum = 0, rowNum = 0, counter = 0;  //col Ϊ����, rowΪ����.
	static bool* isSelected = NULL;

	int i, j;
	int index;
	student* tmpStu;
 // ���û��ѧ��
	if (stuNum == 0) {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 2.5, winheight * 0.75, "����ѧ����");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.6, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete stu teacher : no stu,press \"����\",turn to teacher interface\n", curSataus);
			curSataus = 2;
		}
		return;
	}

	drawLabel(winwidth * 0.1, winheight * 0.85, "ѧ���б����£�");

	if (isSelected == NULL || stuNumLocal != stuNum) {
		stuNumLocal = stuNum;
		if (isSelected == NULL) {
			isSelected = (bool*)malloc(sizeof(bool) * stuNumLocal);
			memset(isSelected, 0, sizeof(bool) * stuNumLocal);
		}
		else {
			isSelected = (bool*)realloc(isSelected, sizeof(bool) * stuNumLocal);
			memset(isSelected, 0, sizeof(bool) * stuNumLocal);
		}
	}
	if (colNum == 0 || rowNum == 0 || pageNum == 0) {   //set row  ,page and column
		colNum = winwidth * 0.8 / (TextStringWidth("��") * 9);
		rowNum = winheight * 0.7 / dy;
		pageNum = stuNum / (colNum * rowNum);
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

	if (button(GenUIID(0), winwidth * 0.8, winheight * 0.08, w  * 0.5, h, "ɾ��")) {
		if (counter == 0) {
			MessageBox(NULL, TEXT("û��ѡ��ѧ��!"), TEXT("��ʾ"), MB_OK);
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete student : press \"ɾ��\",no selected stu\n", curSataus);
		}
		else {
			student* tmpStu, * curStu;
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete stu teacher : start deleting stu : ", curSataus);		
			curStu = &students;
			for (i = 0; i < stuNumLocal; ++i) {
				if (isSelected[i]) {
					if (isDisplayConsole)
						fprintf(stdout, "%s, ", curStu->name);
					tmpStu = curStu->next;
					memcpy(curStu, tmpStu, sizeof(student));
					free(tmpStu);
					--stuNum;
				}
				else
					curStu = curStu->next;
			}
			if (isDisplayConsole)
				fprintf(stdout, "\n");
			memset(isSelected, 0, sizeof(bool) * stuNumLocal);
			counter = 0;
			pageNum = 0;
			page = 0;
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete stu teacher : finish deleting stu, turn to teacher interface\n", curSataus);
			saveToFile();
			MessageBox(NULL, TEXT("ɾ���ɹ�!"), TEXT("��ʾ"), MB_OK);
			curSataus = 10;  //���ڽ���
		}
	}
	if (button(GenUIID(0), winwidth * 0.8 + w * 0.6, winheight * 0.08, w * 0.5, h, "ȡ��")) {
		memset(isSelected, 0, sizeof(bool) * stuNumLocal);
		counter = 0;
		pageNum = 0;
		page = 0;
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : delete stu teacher : press \"ȡ��\",turn to teacher interface\n", curSataus);
		curSataus = 2;
	}
	//��ѧ�����г���
	index = page * colNum * rowNum;
	tmpStu = &students;
	for (i = 0; i < index; ++i) tmpStu = tmpStu->next;
	for (i = 0; i < rowNum; ++i) {
		for (j = 0; j < colNum; ++j) {
			bool tmpFlag;
			if (index + j >= stuNumLocal || tmpStu->ID[0] == '\0')
				return;
			tmpFlag = isSelected[index + j];
			if (tmpFlag)
				setButtonColors("Blue", "White", "Blue", "White", 1);
			if (button(GenUIID(index + j), x + dx * j, y - dy * i, w, h, tmpStu->name)) {//GenUIID(index + j)��GenUIID(N)��ע
				isSelected[index + j] = !isSelected[index + j];
				if (isDisplayConsole) {
					if (isSelected[index + j]) {
						++counter;
						fprintf(stdout, "status : %d; NOTE : delete stu teacher : select stu \"%s\",total:%d\n", curSataus, tmpStu->name, counter);
					}
					else {
						--counter;
						fprintf(stdout, "status : %d; NOTE : delete stu teacher : deselect stu \"%s\",total:%d\n", curSataus, tmpStu->name, counter);
					}
				}
			}
			if (tmpFlag)
				setButtonColors("Blue", "Blue", "Red", "Red", 0);
			tmpStu = tmpStu->next;
		}
		index += stuNum;
	}

}
//��ʦ����ѧ��������
void DrawResponseTea()
{
	double fH = GetFontHeight();
	double h = fH * 2; // �ؼ��߶�
	double x = winwidth * 0.1;
	double y = winheight * 0.75;
	double w = TextStringWidth("��") * 4;
	double dy = 2 * h + TextStringWidth("��") * 2;
	static int page = 0, pageNum = 0, rowNum = 0;

	int i, j, k;
	student* tmpStu;
	request* tmpResquest;

	if (requestNum == 0) {
		drawLabel(winwidth * 0.5 - TextStringWidth("�޴���������") / 2, winheight * 0.7, "�޴���������");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.5, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : adopt request : no request,press \"����\",turn to admin interface\n", curSataus);
			curSataus = 2;
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
	if (button(GenUIID(0), winwidth * 0.8 + w * 0.6, winheight * 0.08, w, h, "����")) {
		pageNum = 0;
		page = 0;
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : adopt request : press \"����\",turn to teacher interface\n", curSataus);
		curSataus =2;
	}// ������ʦ����.

	j = page * rowNum; k = 0;
	tmpStu = &students;
	tmpResquest = NULL;
	for (i = 0; i < rowNum; ++i) {
		tmpResquest = NULL;
		while (tmpStu->ID[0] != '\0' && tmpResquest == NULL) {
			if (k == 5)
				k = 0;
			for (; k < 5; ++k) {
				if (tmpStu->requests[k].content[1] != '\0' && tmpStu->requests[k].isAdopt == 0) {
					if (j > 0)
						--j;
					else {
						tmpResquest = tmpStu->requests + k;
						++k;
						break;
					}
				}
			}
			if (tmpResquest == NULL)
				tmpStu = tmpStu->next;
		}
		if (tmpResquest == NULL)
			break;
		drawLabel(winwidth * 0.1, y - i * dy, tmpResquest->content);
		drawLabel(winwidth * 0.6, y - i * dy, tmpStu->name);
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

//����ѧ���ɼ�
void DrawSetScoreTea()
{	
	double fH = GetFontHeight();
	double h = fH * 2; // �ؼ��߶�
	double x = winwidth * 0.1;
	double y = winheight * 0.75;
	double w = TextStringWidth("��") * 8;
	double dx = TextStringWidth("��") * 10;
	double dy = h * 2;
	static int page = 0, pageNum = 0, stuNumLocal = 0, colNum = 0, rowNum = 0, counter = 0;  //col Ϊ����, rowΪ����.
	static bool* isSelected = NULL;

	int i, j;
	int index;
	student* tmpStu;
 // ���û��ѧ��
	if (stuNum == 0) {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 2.5, winheight * 0.75, "����ѧ����");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("��"), winheight * 0.6, TextStringWidth("��") * 3, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete stu teacher : no stu,press \"����\",turn to teacher interface\n", curSataus);
			curSataus = 2;
		}
		return;
	}

	drawLabel(winwidth * 0.1, winheight * 0.85, "ѧ���б����£�");

	if (isSelected == NULL || stuNumLocal != stuNum) {
		stuNumLocal = stuNum;
		if (isSelected == NULL) {
			isSelected = (bool*)malloc(sizeof(bool) * stuNumLocal);
			memset(isSelected, 0, sizeof(bool) * stuNumLocal);
		}
		else {
			isSelected = (bool*)realloc(isSelected, sizeof(bool) * stuNumLocal);
			memset(isSelected, 0, sizeof(bool) * stuNumLocal);
		}
	}
	if (colNum == 0 || rowNum == 0 || pageNum == 0) {   //set row  ,page and column
		colNum = winwidth * 0.8 / (TextStringWidth("��") * 9);
		rowNum = winheight * 0.7 / dy;
		pageNum = stuNum / (colNum * rowNum);
	}
	{
		char pages[6];
		sprintf(pages, "%2d/%2d", page + 1, pageNum + 1);
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 1.25, winheight * 0.1, pages);
	}
	drawLabel(winwidth * 0.1, winheight * 0.05,"�����ť��ѧ���ɼ���,�ٴε������ɼ�");
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

	if (button(GenUIID(0), winwidth * 0.7 + w * 0.6, winheight * 0.08, w * 0.5, h, "����")) {
		memset(isSelected, 0, sizeof(bool) * stuNumLocal);
		counter = 0;
		pageNum = 0;
		page = 0;
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : delete stu teacher : press \"ȡ��\",turn to teacher interface\n", curSataus);
		curSataus = 2;
	}
	//��ѧ�����г���
	index = page * colNum * rowNum;
	tmpStu = &students;   //ͷ�ڵ� 
	for (i = 0; i < index; ++i) tmpStu = tmpStu->next;
	for (i = 0; i < rowNum; ++i) {
		for (j = 0; j < colNum; ++j) {
			bool tmpFlag;
			if (index + j >= stuNumLocal || tmpStu->ID[0] == '\0')
				return;
			tmpFlag = isSelected[index + j];
			if (tmpFlag)
				setButtonColors("Blue", "White", "Blue", "White", 1);
			if (isSelected[index + j]) {
					textbox(GenUIID(0), x + dx * j, y - dy * i-dy, w, h, tmpStu->scores, sizeof(tmpStu->scores));  //��ʾ�ɼ�
			}
			if (button(GenUIID(index + j), x + dx * j, y - dy * i, w, h, tmpStu->name)){ //GenUIID(index + j)��GenUIID(N)��ע
				isSelected[index + j] = !isSelected[index + j];
				if (!isSelected[index + j]){
					if(atoi(tmpStu->scores)<=100&&atoi(tmpStu->scores)>=0){
					saveToFile();
					MessageBox(NULL, TEXT("�ɼ�����ɹ�!"), TEXT("��ʾ"), MB_OK);
					}
					else{
						isSelected[index + j] = 1 ;
						MessageBox(NULL, TEXT("�ɼ�ӦΪ0-100!"), TEXT("��ʾ"), MB_OK);
						memset(tmpStu->scores,'\0',sizeof(tmpStu->scores));
					}
				}
			}
			if (tmpFlag)
				setButtonColors("Blue", "Blue", "Red", "Red", 0);
			tmpStu = tmpStu->next;
		}
		index += stuNum;
	}

}


  // ͳ��ѧ���ɼ�
void DrawStuScoreStatis(){

	int a, b, c, d;  //ͳ������
	double H=winheight/40;
	student *p;
	double fH = GetFontHeight();
	double h = winheight/2;  // �ؼ��߶�
	double x = winwidth/8;  
	double y = winheight/3.5; 
	double dx=winwidth/32+x;
	double w = winwidth/10; // �ؼ����
	double A_height,B_height,C_height,D_height;
	string PicColor="Blue";
	static int change_color=0;
	static int picCo;
	static int times;
	static char p1[10]="Blue";
	static int fill_flag=0;
	static int pen_size;
	char tmpCount[10]={ 0 };
	a=b=c=d=0;
	pen_size=GetPenSize();


	//���ĸ��ȼ�����˵��
	SetPenColor("Blue");
	drawLabel(winwidth*0.6, winheight-fH*2,   "Grade-A: score between 85 and 100");
	drawLabel(winwidth*0.6, winheight-fH*3.5, "Grade-B: score between 70 and 84");
	drawLabel(winwidth*0.6, winheight-fH*5,   "Grade-C: score between 60 and 69");
	drawLabel(winwidth*0.6, winheight-fH*6.5, "Grade-D: score less than 60, i.e. fail");

	drawLabel(winwidth*0.6, winheight-fH*8.5, "Color chosen from:");
    drawLabel(winwidth*0.6, winheight-fH*10, "Black, Green, Gray, Orange, Blue");

	//ͳ��ͼ��λ�ú͵���
	MovePen (x,y);
	DrawLine (winwidth-2*x,0);
	
	//ͳ��ͼ�±�λ��
	SetPenColor("Blue");
	drawLabel(dx, y-2*fH, "    Grade-A");
	drawLabel(dx+2*w, y-2*fH, "    Grade-B");
	drawLabel(dx+4*w, y-2*fH, "    Grade-C");
	drawLabel(dx+6*w, y-2*fH, "    Grade-D");

	
	if (stuNum == 0) {
		drawLabel(winwidth * 0.5 - TextStringWidth("��") * 2.5, winheight * 0.75, "����ѧ����");
		
	}
	if (button(GenUIID(0), winwidth-2*x, y-6.5*fH, TextStringWidth("��") * 5, GetFontHeight() * 2, "����")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete stu teacher : no stu,press \"����\",turn to teacher interface\n", curSataus);
			curSataus = 2;
	}
		
	//�û�ѡ��ͳ��ͼ�Ƿ����
	drawLabel(x-0.4*dx,winheight*0.7+fH*5.5,"�Ƿ����:");

	if (button(GenUIID(0), x+0.4*dx, winheight*0.7+fH*5, TextStringWidth("��") * 5, GetFontHeight() * 2, fill_flag ? "�����":"���"))
		fill_flag=!fill_flag;

	//�û�����������ϸ
	drawLabel(x-0.4*dx,winheight*0.7+fH*3,"���Ĵ�ϸ:");

	if (button(GenUIID(0), x+0.4*dx, winheight*0.7+fH*2.5, TextStringWidth("��") * 5, GetFontHeight() * 2, "�Ӵ�"))
		pen_size++;
	   
	if (button(GenUIID(0), x+1.2*dx, winheight*0.7+fH*2.5, TextStringWidth("��") * 5, GetFontHeight() * 2, "��ϸ"))
		pen_size--;

	
	//ͳ��ABCD�ȼ�������
	for ( p = &students; p != NULL; p = p->next )
	{
		if(atoi((*p).scores)<60) d++;
		else if(atoi(p->scores)>=60&&atoi((*p).scores)<=69) c++;
		else if(atoi((*p).scores)>=70&&atoi((*p).scores)<=84) b++;
		else a++;
	}


	A_height= H * a;  //������״ͳ��ͼ�߶ȵ�������ͳ�������������
	B_height= H * b;
	C_height= H * c;
	D_height= H * d;
	itoa(a, tmpCount  , 10);
	drawLabel(0.7*dx, y-3*fH,"��������:");
	drawLabel(dx+3*TextStringWidth("��"), y-3*fH,tmpCount );
	itoa(b, tmpCount  , 10);
	drawLabel(0.7*dx+2*w, y-3*fH,"��������:");
	drawLabel(dx+2*w+3*TextStringWidth("��"), y-3*fH,    tmpCount);
	itoa(c, tmpCount  , 10);
	drawLabel(0.7*dx+4*w, y-3*fH,"��������:");
	drawLabel(dx+4*w+3*TextStringWidth("��"), y-3*fH, tmpCount);
	itoa(d, tmpCount  , 10);
	drawLabel(0.7*dx+6*w, y-3*fH,"����������:");
	drawLabel(dx+6*w+4*TextStringWidth("��"), y-3*fH, tmpCount);

	//�û��޸�ͳ��ͼ��ɫ
	drawLabel(x-0.4*dx,winheight*0.7,"�޸���ɫ:");
	textbox(GenUIID(0),x+0.4*dx, winheight * 0.7, TextStringWidth("��") * 5, GetFontHeight() * 2, p1, sizeof(p1));
    
	
	if (button(GenUIID(0), x+1.2*dx, winheight * 0.7, TextStringWidth("��") * 5, GetFontHeight() * 2, change_color ? "ȡ���޸�":"ȷ���޸�"))
		  change_color=!change_color;

	

	if(change_color){
	    if(strcmp(p1,"Black")==0||strcmp(p1,"black")==0)            SetPenColor("Black");
		else if(strcmp(p1,"Gray")==0||strcmp(p1,"gray")==0)         SetPenColor ("Gray");
		else if(strcmp(p1,"Green")==0||strcmp(p1,"green")==0)		SetPenColor("Green");
		else if(strcmp(p1,"Orange")==0||strcmp(p1,"orange")==0)		SetPenColor("Orange");
		else SetPenColor("Blue");
	}
	
	//��״ͳ��ͼ
	SetPenSize(pen_size);
	drawRectangle(dx,y,w,A_height,fill_flag);
	drawRectangle(dx+2*w,y,w,B_height,fill_flag);
	drawRectangle(dx+4*w,y,w,C_height,fill_flag);
	drawRectangle(dx+6*w,y,w,D_height,fill_flag);
} 

