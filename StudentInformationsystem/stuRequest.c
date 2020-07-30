#include "graphicLib.h"
#include "stu.h"
#include "file.h"
#include "register.h"

//全局变量
extern char user_name[64]; // 用于编辑用户名
extern char password[64]; // 用于编辑密码
extern double winwidth, winheight; // 窗口尺寸
extern administrator administrators;//管理员用户
extern student students;//学生用户
extern class classes;//班级
extern int curSataus, requestNum;  //current status 当前状态. 
extern bool isDisplayConsole;

void DrawRequestTextboxStu()
{
	static char newContent[30];
	student* curStu = checkNameStu(user_name);
	if (curStu == NULL)//curStataus转换瞬间，有可能curStatuas的值已变，user_name已清空，但仍调用了此函数
		return;
	if (curStu->requests[4].content[0] != '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("请") * 7.5, winheight * 0.85, "请清理旧事项或等待旧事项审批！");
	}
	else {
		drawLabel(winwidth * 0.1, winheight * 0.85, "新事项：");
		if (textbox(GenUIID(0), winwidth * 0.2, winheight * 0.83, winwidth * 0.5, GetFontHeight() * 2, newContent, sizeof(newContent))) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,student : new content : %s\n", curSataus, newContent);
		}
		if (button(GenUIID(0), winwidth * 0.75, winheight * 0.83, TextStringWidth("请") * 4, GetFontHeight() * 2, "创建")) {
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
	if (curStu == NULL)//curStataus转换瞬间，有可能curStatuas的值已变，user_name已清空，但仍调用了此函数
		return;
	if (curStu->requests[0].content[0] == '\0') {
		drawLabel(winwidth * 0.5 - TextStringWidth("无") * 3, winheight * 0.75, "无审批事项！");
		if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.6, TextStringWidth("暂") * 3, GetFontHeight() * 2, "返回")) {
			if (isDisplayConsole)
				fprintf(stdout, "status : %d; NOTE : request,student : no request,press \"返回\",turn to student interface\n", curSataus);
			curSataus = 1;
		}
		return;
	}
	drawLabel(winwidth * 0.35 - TextStringWidth("审批事项") / 2, winheight * 0.78, "审批事项");
	drawLabel(winwidth * 0.75 - TextStringWidth("来"), winheight * 0.78, "状态");
	drawLabel(winwidth * 0.85 - TextStringWidth("来"), winheight * 0.78, "操作");
	for (i = 0; i < 5; ++i) {
		if (curStu->requests[i].content[0] == '\0')
			break;
		drawLabel(winwidth * 0.1, winheight * (0.75 - 0.13 * i), curStu->requests[i].content);
		switch (curStu->requests[i].isAdopt) {
			case 0:
				drawLabel(winwidth * 0.75 - TextStringWidth("未审批") / 2, winheight * (0.73 - 0.13 * i), "未审批");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("暂") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("暂") * 3, GetFontHeight() * 2, "取消")) {
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
				drawLabel(winwidth * 0.75 - TextStringWidth("同意") / 2, winheight * (0.73 - 0.13 * i), "同意");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("暂") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("暂") * 3, GetFontHeight() * 2, "删除")) {
					if (i < 4)
						memmove(curStu->requests + i, curStu->requests + i + 1, sizeof(request) * (4 - i));
					memset(curStu->requests + 4, 0, sizeof(request));
					if (isDisplayConsole)
						fprintf(stdout, "status : %d; NOTE : request,student : delete request,success\n", curSataus);
					saveToFile();
				}
				break;
			case 2:
				drawLabel(winwidth * 0.75 - TextStringWidth("驳回") / 2, winheight * (0.73 - 0.13 * i), "驳回");
				if (button(GenUIID(i), winwidth * 0.85 - TextStringWidth("暂") * 1.5, winheight * (0.71 - 0.13 * i), TextStringWidth("暂") * 3, GetFontHeight() * 2, "删除")) {
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
	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.1, TextStringWidth("暂") * 3, GetFontHeight() * 2, "返回")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : request,student : no request,press \"返回\",turn to student interface\n", curSataus);
		curSataus = 1;
	}
}

//画出个人信息修改栏
void DrawInfoTextboxStu(){
	
	student* curStu = checkNameStu(user_name);  // 检验用户名是否存在
	if (curStu == NULL)//curStataus转换瞬间，有可能curStatuas的值已变，user_name已清空，但仍调用了此函数
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
	//画出提示
	if (curStu->birth[0] == '\0') {
		drawLabel(TextStringWidth("请") * 7.5, winheight * 0.85, "请填写出生日期！");
	}
	else {
		drawLabel(TextStringWidth("请") * 7.5, winheight * 0.85, "出生日期:");
	}
	//出生日期
	if (curStu->home[0] == '\0') {
		drawLabel(TextStringWidth("请") * 7.5, winheight * 0.75, "请填写家庭住址！");
	}
	else {
		drawLabel(TextStringWidth("请") * 7.5, winheight * 0.75, "家庭住址:");
	}
	//电话
	if (curStu->phone[0] == '\0') {
		drawLabel(TextStringWidth("请") * 7.5, winheight * 0.65, "请填写电话！");
	}
	else {
		drawLabel(TextStringWidth("请") * 7.5, winheight * 0.65, "电话:");
	}

	if(button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.2, TextStringWidth("暂") * 5, GetFontHeight() * 2, "修改完毕")){
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; NOTE : student : create new birth,success : %s\n", curSataus, curStu->birth);
				MessageBox(NULL, TEXT("保存成功!"), TEXT("提示"), MB_OK);
				saveToFile();
	}

	if (button(GenUIID(0), winwidth * 0.5 - TextStringWidth("暂"), winheight * 0.1, TextStringWidth("暂") * 3, GetFontHeight() * 2, "返回")) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; NOTE : request,student : no request,press \"返回\",turn to student interface\n", curSataus);
		curSataus = 1;
	}
}
