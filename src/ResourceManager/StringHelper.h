/**
*   \file StringHelper.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��1��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __STRINGHELPER_H__
#define __STRINGHELPER_H__

#include <vector>
#include <string>

/**
*	\class StringHelper
*	\breif �ַ�����������ָȥ�հ׵�.
*/
namespace StringHelper
{
	std::vector<std::string> Split(const std::string& value, char rep);
	std::vector<int> SplitInt(const std::string& value, char rep);
	std::string Trim(const std::string& value);
};

#endif //__STRINGHELPER_H__
