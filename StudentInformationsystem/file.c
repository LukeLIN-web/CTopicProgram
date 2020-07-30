
#include <stdio.h>
#include <string.h>

#include "graphicLib.h"
#include "file.h"

administrator administrators;
student students;
teacher teachers;
class classes;
int adminNum, stuNum, teaNum, classNum, requestNum,scoreNum;
extern int curSataus;
extern bool isDisplayConsole;
//初始化链表,把 学生人数等数据存入stuNum

void initFromFile()
{
	int counter = 0;
	FILE* fp;	
	administrator* tmpAdmin;
	administrator* curAdmin;
	student* tmpStu, *curStu;
	teacher* tmpTea, *curTea;
	class* tmpClass, *curClass;

	memset(&administrators, 0, sizeof(administrator));
	memset(&students, 0, sizeof(student));
	memset(&teachers, 0, sizeof(teacher));

	counter = 0;
	fp = fopen(FILE_NAME_ADMIN, "rb");
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; ERROR : init : open \"%s\" failed\n", curSataus, FILE_NAME_ADMIN);
		_exit(-1);
	}
	tmpAdmin = (administrator*)malloc(sizeof(administrator));
	curAdmin = &administrators;
	while (fread(tmpAdmin, sizeof(administrator), 1, fp) == 1) {
		memcpy(curAdmin, tmpAdmin, sizeof(administrator));
		curAdmin->next = (administrator*)malloc(sizeof(administrator));
		memset(curAdmin->next, 0, sizeof(administrator));
		curAdmin = curAdmin->next;
		++counter;
	}
	adminNum = counter;
	free(tmpAdmin);
	fclose(fp);
	if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : init : %d admin datas init from file,success\n", curSataus, counter);


	//  读出学生的数据.
	counter = 0;
	fp = fopen(FILE_NAME_STU, "rb");
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; ERROR : init : open \"%s\" failed\n", curSataus, FILE_NAME_STU);
		_exit(-1);
	}

	tmpStu = (student*)malloc(sizeof(student));
	curStu = &students;
	while (fread(tmpStu, sizeof(student), 1, fp) == 1) {
		memcpy(curStu, tmpStu, sizeof(student));
		curStu->next = (student*)malloc(sizeof(student));
		memset(curStu->next, 0, sizeof(student));
		curStu = curStu->next;
		++counter;
	}
	stuNum = counter;
	free(tmpStu);
	fclose(fp);
	if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : init : %d student datas init from file,success\n", curSataus, counter);

	//  读出老师的数据
	counter = 0;
	requestNum = 0;
	fp = fopen(FILE_NAME_TEA, "rb");
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; ERROR : init : open \"%s\" failed\n", curSataus, FILE_NAME_TEA);
		_exit(-1);
	}
	tmpTea = (teacher*)malloc(sizeof(teacher));
	curTea = &teachers;
	while (fread(tmpTea, sizeof(teacher), 1, fp) == 1) {
		int i;
		for (i = 0; i < 5; ++i)
			if (tmpTea->requests[i].content[0] != '\0')
				++requestNum;
		memcpy(curTea, tmpTea, sizeof(teacher));
		curTea->next = (teacher*)malloc(sizeof(teacher));
		memset(curTea->next, 0, sizeof(teacher));
		curTea = curTea->next;
		++counter;
	}

	teaNum = counter;
	free(tmpTea);
	fclose(fp);
	if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : init : %d teacher datas init from file,success\n", curSataus, counter);

	counter = 0;
	fp = fopen(FILE_NAME_CLASS, "rb");
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; ERROR : init : open \"%s\" failed\n", curSataus, FILE_NAME_CLASS);
		_exit(-1);
	}
	tmpClass = (class*)malloc(sizeof(class));
	curClass = &classes;
	while (fread(tmpClass, sizeof(class), 1, fp) == 1) {
		memcpy(curClass, tmpClass, sizeof(class));
		curClass->next = (class*)malloc(sizeof(class));
		memset(curClass->next, 0, sizeof(class));
		curClass = curClass->next;
		++counter;
	}
	classNum = counter;
	free(tmpClass);
	fclose(fp);
	if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : init : %d class datas init from file,success\n", curSataus, counter);

	if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : init : all datas init from file,success\n", curSataus);
}
// 将管理员,老师,学生先后存入文件.
void saveToFile()
{  
	int counter = 0;
	FILE* fp;

	counter = 0;
	fp = fopen(FILE_NAME_ADMIN, "wb");   //管理员
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; WARNING : save : open \"%s\" failed\n", curSataus, FILE_NAME_ADMIN);
	}
	else {
		administrator* curAdmin = &administrators;
		while (curAdmin->ID[0] != '\0') {
			if (fwrite(curAdmin, sizeof(administrator), 1, fp) != 1) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; WARNING : save : write to \"%s\" failed\n", curSataus, FILE_NAME_ADMIN);
				counter = -1;
				break;
			}
			curAdmin = curAdmin->next;
			++counter;
		}
		fclose(fp); 
		if (isDisplayConsole && counter != -1)
			fprintf(stdout, "status : %d; NOTE : init : %d admin datas save to file,success\n", curSataus, counter);
	}

	counter = 0;
	fp = fopen(FILE_NAME_STU, "wb");   //打开学生
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; WARNING : save : open \"%s\" failed\n", curSataus, FILE_NAME_STU);
	}
	else {
		student* curStu = &students;
		while (curStu->ID[0] != '\0') {
			if (fwrite(curStu, sizeof(student), 1, fp) != 1) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; WARNING : save : write to \"%s\" failed\n", curSataus, FILE_NAME_STU);
				counter = -1;
				break;
			}
			curStu = curStu->next;
			++counter;
		}
		fclose(fp);
		if (isDisplayConsole && counter != -1)
			fprintf(stdout, "status : %d; NOTE : init : %d student datas save to file,success\n", curSataus, counter);
	}

	counter = 0;
	fp = fopen(FILE_NAME_TEA, "wb");// 打开老师
	if (fp == NULL) {
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; WARNING : save : open \"%s\" failed\n", curSataus, FILE_NAME_TEA);
	}
	else {
		teacher* curTea = &teachers;
		while (curTea->ID[0] != '\0') {
			if (fwrite(curTea, sizeof(teacher), 1, fp) != 1) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; WARNING : save : write to \"%s\" failed\n", curSataus, FILE_NAME_TEA);
				counter = -1;
				break;
			}
			curTea = curTea->next;
			++counter;
		}
		fclose(fp);
		if (isDisplayConsole && counter != -1)
			fprintf(stdout, "status : %d; NOTE : init : %d teacher datas save to file,success\n", curSataus, counter);
	}

	counter = 0;
	fp = fopen(FILE_NAME_CLASS, "wb");  //打开班级
	if (fp == NULL) { 
		if (isDisplayConsole)
			fprintf(stdout, "status : %d; WARNING : save : open \"%s\" failed\n", curSataus, FILE_NAME_CLASS);
	}
	else {
		class* curClass = &classes;
		while (curClass->ID[0] != '\0') {
			if (fwrite(curClass, sizeof(class), 1, fp) != 1) {
				if (isDisplayConsole)
					fprintf(stdout, "status : %d; WARNING : save : write to \"%s\" failed\n", curSataus, FILE_NAME_CLASS);
				counter = -1;
				break;
			}
			curClass = curClass->next;
			++counter;
		}
		fclose(fp);
		if (isDisplayConsole && counter != -1)
			fprintf(stdout, "status : %d; NOTE : init : %d class datas save to file,success\n", curSataus, counter);
	}

	if (isDisplayConsole)
		fprintf(stdout, "status : %d; NOTE : init : all datas save to file,success\n", curSataus);
}
