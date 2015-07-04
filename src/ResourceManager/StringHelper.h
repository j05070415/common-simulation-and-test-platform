/**
*   \file StringHelper.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月1日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __STRINGHELPER_H__
#define __STRINGHELPER_H__

#include <vector>
#include <string>

/**
*	\class StringHelper
*	\breif 字符串操作，如分割，去空白等.
*/
namespace StringHelper
{
	std::vector<std::string> Split(const std::string& value, char rep);
	std::vector<int> SplitInt(const std::string& value, char rep);
	std::string Trim(const std::string& value);
};

#endif //__STRINGHELPER_H__
