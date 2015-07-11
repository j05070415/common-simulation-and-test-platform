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

// \struct ProjectInfor
struct ProjectInfor
{
	HwaString name;
	HwaString className;
	HwaString icon;
	HwaString description;
};

struct ViewInfor
{
	HwaString name;
	HwaString binder;
};

// \struct ProjectCardInfor
struct ProjectCardInfor
{
	HwaString name;
	HwaString frameId;
};

struct SourceInfor
{
	HwaString id;
	HwaString path;
	std::vector<int> segments;
};

// \struct ItemInfor
struct ItemInfor 
{
	HwaString objName;
	std::vector<SourceInfor> sources;
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

typedef int (*InitModulePointer)();

#define REGISTER_META_TYPE(type) qRegisterMetaType<type>(#type)

#define INIT_MODULE(a) \
	extern "C" _declspec(dllexport) int initModule() \
{ \
	return qRegisterMetaType<a>(#a); \
}

#endif //__TYPEDEFS_H__
