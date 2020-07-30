#pragma once
#include "file.h"

void DrawMenuRegister();
void DrawTextBoxRegister();

administrator* checkNameAdmin(const char* name);
student* checkNameStu(const char* name);
teacher* checkNameTea(const char* name);