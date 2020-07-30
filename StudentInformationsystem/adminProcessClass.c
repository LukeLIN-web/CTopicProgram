#include "graphicLib.h"
#include "admin.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

//全局变量
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern teacher teachers;//教师用户
extern class classes;//班级
extern int curSataus;
extern int adminNum, stuNum, teaNum, classNum;
extern bool isDisplayConsole;

class* checkClassName(const char* name)
{
	class* tmp = &classes;
	while (tmp->ID[0] != '\0') {
		if (strcmp(name, tmp->name) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void DrawNewClassAdmin()
{
	static char newClassName[64] = { 0 };
	static bool isClassNameExit = false, isClassNameEmpty = false;
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = winwidth * 0.35;
	double y = winheight / 2;
	double w = TextStringWidth("暂") * 2;
	double dx = TextStringWidth("暂");
	double dy = h * 2;
	drawLabel(winwidth * 0.5 - TextStringWidth("创建新班级") / 2, winheight * 0.7, "创建新班级");
	drawLabel(x, y, "班名：");

	if (textbox(GenUIID(0), x + dx * 4, y, w * 4, h, newClassName, sizeof(newClassName))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : login : className textBox update : %s\n", curSataus, newClassName);
			isClassNameEmpty = false;
			isClassNameExit = false;
	}
		if(isClassNameExit)
			drawLabel(x + dx * 5 + w * 4, y, "该班名已存在！");
		if (button(GenUIID(0), winwidth * 0.5 - w * 1.5, y - dy, w * 3, h, "创建")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : new class admin : press \"创建\",name:%s\n", curSataus, newClassName);
			if (newClassName[0] == '\0')
				isClassNameEmpty = true;
			else if (checkClassName(newClassName))
				isClassNameExit = true;
			else {
				class* tmp = &classes;
				while (tmp->ID[0] != '\0') tmp = tmp->next;
				getID(tmp->ID);
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : new class admin : ID:%s\n", curSataus, tmp->ID);
				strcpy(tmp->name, newClassName);
				tmp->next = (class*)malloc(sizeof(class));
				memset(tmp->next, 0, sizeof(class));
				memset(newClassName, 0, sizeof(newClassName));
				++classNum;
				curSataus = 3;
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : new class admin : success,turn to admin interface\n", curSataus);
				MessageBox(NULL, TEXT("新班级创建成功!"), TEXT("提示"), MB_OK);
				saveToFile();
			}
		}
		if (button(GenUIID(0), winwidth * 0.5 + w * 2, y - dy, w * 3, h, "取消")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : new class admin : cancel create new class,turn to admin interface\n", curSataus);
			curSataus = 3;
		}
}
	
	
void DrawDeleteClassAdmin()
{	
	double fH = GetFontHeight();
	double h = fH * 2; // 控件高度
	double x = winwidth * 0.1;
	double y = winheight * 0.75;
	double w = TextStringWidth("暂") * 8;
	double dx = TextStringWidth("暂") * 10;
	double dy = h * 2;
	static int page = 0, pageNum = 0, classNumLocal = 0, colNum = 0, rowNum = 0, counter = 0;
	static bool* isSelected = NULL;

	int i, j;
	int index;
	class* tmpClass;

	if (classNum == 0) {
		drawLabel(winwidth * 0.5 - TextStringWidth("暂") * 2.5, winheight * 0.75, "暂无班级！");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.6, TextStringWidth("暂") * 3, GetFontHeight() * 2, "返回")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete class admin : no class,press \"返回\",turn to admin interface\n", curSataus);
			curSataus = 3;
		}
		return;
	}

	drawLabel(winwidth * 0.1, winheight * 0.85, "班级列表如下：");

	if (isSelected == NULL || classNumLocal != classNum) {
		classNumLocal = classNum;
		if (isSelected == NULL) {
			isSelected = (bool*)malloc(sizeof(bool) * classNumLocal);
			memset(isSelected, 0, sizeof(bool) * classNumLocal);
		}
		else {
			isSelected = (bool*)realloc(isSelected, sizeof(bool) * classNumLocal);
			memset(isSelected, 0, sizeof(bool) * classNumLocal);
		}
	}
	if (colNum == 0 || rowNum == 0 || pageNum == 0) {
		colNum = winwidth * 0.8 / (TextStringWidth("暂") * 9);
		rowNum = winheight * 0.7 / dy;
		pageNum = classNum / (colNum * rowNum);
	}
	{
		char pages[6];
		sprintf(pages, "%2d/%2d", page + 1, pageNum + 1);
		drawLabel(winwidth * 0.5 - TextStringWidth("暂") * 1.25, winheight * 0.1, pages);
	}
	setButtonColors("White", "Blue", "White", "Red", 0);
	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂") * 2.5, winheight * 0.09, TextStringWidth("暂"), h, "<<")) {
		if (page > 0)
			--page;
	}
	if (button(GenUIID(0), winwidth * 0.5 + TextStringWidth("暂") * 1.5, winheight * 0.09, TextStringWidth("暂"), h, ">>")) {
		if (page < pageNum)
			++page;
	}
	setButtonColors("Blue", "Blue", "Red", "Red", 0);


	if (button(GenUIID(0), winwidth * 0.8, winheight * 0.08, w  * 0.5, h, "删除")) {
		if (counter == 0) {
			MessageBox(NULL, TEXT("没有选中班级!"), TEXT("提示"), MB_OK);
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete class admin : press \"删除\",no selected class\n", curSataus);
		}
		else {
			class* tmpClass, * curClass;
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete class admin : start deleting class : ", curSataus);			
			MessageBox(NULL, TEXT("开始删除!"), TEXT("提示"), MB_OK);
			curClass = &classes;
			for (i = 0; i < classNumLocal; ++i) {
				if (isSelected[i]) {
					if (isDisplayConsole)
						fprintf(stdout, "%s, ", curClass->name);
					tmpClass = curClass->next;
					memcpy(curClass, tmpClass, sizeof(class));
					free(tmpClass);
					--classNum;
				}
				else
					curClass = curClass->next;
			}
			if (isDisplayConsole)
				fprintf(stdout, "\n");
			memset(isSelected, 0, sizeof(bool) * classNumLocal);
			counter = 0;
			pageNum = 0;
			page = 0;
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : delete class admin : finish deleting class, turn to admin interface\n", curSataus);
			saveToFile();
			MessageBox(NULL, TEXT("删除成功!"), TEXT("提示"), MB_OK);
			curSataus = 3;
		}
	}
	if (button(GenUIID(0), winwidth * 0.8 + w * 0.75, winheight * 0.08, w * 0.5, h, "取消")) {
		memset(isSelected, 0, sizeof(bool) * classNumLocal);
		counter = 0;
		pageNum = 0;
		page = 0;
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : delete class admin : press \"取消\",turn to admin interface\n", curSataus);
		curSataus = 3;
	}

	index = page * colNum * rowNum;
	tmpClass = &classes;
	for (i = 0; i < index; ++i) tmpClass = tmpClass->next;
	for (i = 0; i < rowNum; ++i) {
		for (j = 0; j < colNum; ++j) {
			bool tmpFlag;
			if (index + j >= classNumLocal || tmpClass->ID[0] == '\0')
				return;
			tmpFlag = isSelected[index + j];
			if (tmpFlag)
				setButtonColors("Blue", "White", "Blue", "White", 1);
			if (button(GenUIID(index + j), x + dx * j, y - dy * i, w, h, tmpClass->name)) {//GenUIID(index + j)见GenUIID(N)备注
				isSelected[index + j] = !isSelected[index + j];
				if (isDisplayConsole) {
					if (isSelected[index + j]) {
						++counter;
						fprintf(stdout, "status : %d; NOTE : delete class admin : select class \"%s\",total:%d\n", curSataus, tmpClass->name, counter);
					}
					else {
						--counter;
						fprintf(stdout, "status : %d; NOTE : delete class admin : deselect class \"%s\",total:%d\n", curSataus, tmpClass->name, counter);
					}
				}
			}
			if (tmpFlag)
				setButtonColors("Blue", "Blue", "Red", "Red", 0);
			tmpClass = tmpClass->next;
		}
		index += colNum;
	}

}