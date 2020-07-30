#pragma once

#define FILE_NAME_ADMIN "admin.data"
#define FILE_NAME_STU "student.data"
#define FILE_NAME_TEA  "teacher.data"
#define FILE_NAME_CLASS  "class.data"
#define PASSWORDLENGTH   30   
#define LOGINNAMELENGTH   30
#define USERSETLENGTH   30

typedef struct REQUEST {
	char content[50];
	int isAdopt;//0 = �������� 1 = ͬ�⣬ 2 = ����
}request;
typedef struct ADMIN{
	char name[20];
	char ID[20];
	char password[17];
	struct ADMIN* next;
}administrator;

typedef struct STUDENT {
	char name[20];
	char ID[20];
	char password[17];
	char birth[20];
	int sex;
	char  home[30];
	char  phone[30];
	char  scores[30];
	struct REQUEST requests[5];
	struct STUDENT* next;
}student;

typedef struct TEACHER {
	char name[20];
	char ID[20];
	char password[17];
	struct REQUEST requests[5];
	struct TEACHER* next;
}teacher;


typedef struct CLASS {
	char name[20];
	char ID[20];
	int sum;
	struct CLASS* next;
}class;

void initFromFile();

void saveToFile();