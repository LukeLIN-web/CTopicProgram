#include "graphicLib.h"
#include "teacher.h"
#include "file.h"
#include "register.h"

//全局变量
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern teacher teachers;//教师用户
extern class classes;//班级
extern int curSataus, requestNum;  //current status 当前状态. 
extern bool isDisplayConsole;

void DrawRequestTextboxTea()
{
	static char newContent[30];
	teacher* curTea = checkNameTea(user_name);
	if (curTea == NULL)//curStataus转换瞬间，有可能curStatuas的值已变，user_name已清空，但仍调用了此函数
		return;
	if (curTea->requests[4].content[0] != '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("请") * 7.5, winheight * 0.85, "请清理旧事项或等待旧事项审批！");
	}
	else {
		drawLabel(winwidth * 0.1, winheight * 0.85, "新事项：");
		if (textbox(GenUIID(0), winwidth * 0.2, winheight * 0.83, winwidth * 0.5, GetFontHeight() * 2, newContent, sizeof(newContent))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,teacher : new content : %s\n", curSataus, newContent);
		}
		if (button(GenUIID(0), winwidth * 0.75, winheight * 0.83, TextStringWidth("请") * 4, GetFontHeight() * 2, "创建")) {
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
	if (curTea == NULL)//curStataus转换瞬间，有可能curStatuas的值已变，user_name已清空，但仍调用了此函数
		return;
	if (curTea->requests[0].content[0] == '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("无") * 3, winheight * 0.75, "无审批事项！");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.6, TextStringWidth("暂") * 3, GetFontHeight() * 2, "返回")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,teacher : no request,press \"返回\",turn to teacher interface\n", curSataus);
			curSataus = 2;
		}
		return;
	}
	drawLabel(winwidth * 0.35 - TextStringWidth("审批事项") / 2, winheight * 0.78, "审批事项");
	drawLabel(winwidth * 0.75 - TextStringWidth("来"), winheight * 0.78, "状态");
	drawLabel(winwidth * 0.85 - TextStringWidth("来"), winheight * 0.78, "操作");
	for (i = 0; i < 5; ++i) {
		if (curTea->requests[i].content[0] == '\0')
			break;
		drawLabel(winwidth * 0.1, winheight * (0.75 - 0.13 * i), curTea->requests[i].content);
		switch (curTea->requests[i].isAdopt) {
			case 0:
				drawLabel(winwidth * 0.75 - TextStringWidth("未审批") / 2, winheight * (0.73 - 0.13 * i), "未审批");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("暂") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("暂") * 3, GetFontHeight() * 2, "取消")) {
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
				drawLabel(winwidth * 0.75 - TextStringWidth("同意") / 2, winheight * (0.73 - 0.13 * i), "同意");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("暂") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("暂") * 3, GetFontHeight() * 2, "删除")) {
					if (i < 4)
						memmove(curTea->requests + i, curTea->requests + i + 1, sizeof(request) * (4 - i));
					memset(curTea->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,teacher : delete request,success\n", curSataus);
					saveToFile();
				}
				break;
			case 2:
				drawLabel(winwidth * 0.75 - TextStringWidth("驳回") / 2, winheight * (0.73 - 0.13 * i), "驳回");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("暂") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("暂") * 3, GetFontHeight() * 2, "删除")) {
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
	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.1, TextStringWidth("暂") * 3, GetFontHeight() * 2, "返回")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : request,teacher : no request,press \"返回\",turn to teacher interface\n", curSataus);
		curSataus = 2;
	}
}