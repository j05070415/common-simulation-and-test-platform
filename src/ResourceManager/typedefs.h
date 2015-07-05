/**
*   \file typedefs.h
*   \brief 配置文件的类型定义.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年6月30日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include <string>
#include <hash_map>
#include <vector>

typedef std::string HwaString;
typedef std::hash_map<HwaString, std::vector<int> > HwaItemBindingHash;

// \struct ProjectInfor
struct ProjectInfor
{
	HwaString name;
	HwaString className;
	HwaString icon;
	HwaString description;
};

// \struct ProjectCardInfor
struct ProjectCardInfor
{
	HwaString name;
	HwaString frameId;
};

// \struct ItemInfor
struct ItemInfor 
{
	HwaString objName;
	HwaItemBindingHash id2Segments;
};

struct SegmentInfor 
{
	SegmentInfor() : size(0), offset(0), reference(0), previous(false) {}
	int id;
	HwaString name;
	int size;
	int offset;
	int reference;//offset = refOffset + refSize + refValue
	bool previous;//offset = preOffset + preSize
	HwaString description;
};

typedef std::vector<SegmentInfor> HwaSegments;

struct FrameInfor 
{
	HwaString id;
	HwaString name;
	HwaString type;// rtti或static
	HwaString analyser;
	HwaSegments segments;
};

#define H_DECLARE_PRIVATE(Class) \
	protected: \
		inline Class##Private* d_func() { return static_cast<Class##Private*>(_p); }

#define H_D(Class) \
	Class##Private* const d = d_func()

#endif //__TYPEDEFS_H__
