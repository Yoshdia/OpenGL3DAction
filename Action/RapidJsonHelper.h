#pragma once

#include "document.h"
#include "filereadstream.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


//JSON�t�@�C���̃I�[�v��
bool openJsonFile(rapidjson::Document& inoutDoc, const char* inFileName);

// Doc���ɂ��̃����o�[�͑��݂��邩�H
bool IsExistMember(const rapidjson::Document& inDoc, const char* memberName);

// ���̃����o�[�����݂��A���l����v���邩�H
bool IsExistMemberAndValue(const rapidjson::Document& inDoc, const char* memberName, const char* matchValue);

// Doc���� memberName�Ƃ������O�̔z��͂��邩�H
bool IsExistArrayName(const rapidjson::Document& inDoc, const char* memberName);


