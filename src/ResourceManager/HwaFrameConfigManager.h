/**
*   \file HwaFrameConfigManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年6月30日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HwaFRAMECONFIGMANAGER_H__
#define __HwaFRAMECONFIGMANAGER_H__

#include "resourcemanager_global.h"
#include "typedefs.h"

struct HwaFrameConfigManagerPrivate;
class TiXmlElement;

/**
*	\class HwaFrameConfigManager
*	\breif 帧配置管理文件，文件位置从框架配置获取.
*	
*			提供帧和字段获取接口，禁止拷贝复制
*/
class RESOURCEMANAGERSHARED_EXPORT HwaFrameConfigManager
{
public:
	static HwaFrameConfigManager& getManager();
	
	/**
	*    \fn    getFrameInfor
	*    \brief 按照帧ID获取此帧信息.
	
	*    \param const HwaString & frameId
	*    \returns FrameInfor
	*/
	FrameInfor getFrameInfor(const HwaString& frameId) const;
	
	/**
	*    \fn    getSegmentInfor
	*    \brief 按照帧ID、字段ID索引获取一个字段信息.
	
	*    \param const HwaString & frameId
	*    \param int segId
	*    \returns SegmentInfor
	*/
	SegmentInfor getSegmentInfor(const HwaString& frameId, int segId) const;

private:
	HwaFrameConfigManager();
	~HwaFrameConfigManager();
	HwaFrameConfigManager(const HwaFrameConfigManager& c);
	HwaFrameConfigManager& operator=(const HwaFrameConfigManager& c);

	
	/**
	*    \fn    loadFile
	*    \brief 加载帧配置文件.
	
	*    \returns bool
	*/
	bool loadFile();
	
	/**
	*    \fn    hasKey
	*    \brief 判断是否有索引帧，按照帧ID索引.
	
	*    \param const HwaString & key
	*    \returns bool
	*/
	bool hasKey(const HwaString& key) const;
	
	/**
	*    \fn    loadFrame
	*    \brief 查找到根节点后，解析帧.
	
	*    \param TiXmlElement * root
	*    \returns void
	*/
	void loadFrame(TiXmlElement* root);
	
	/**
	*    \fn    loadSegment
	*    \brief 按照查找到的帧，解析帧下的字段.
	
	*    \param FrameInfor & frame
	*    \param TiXmlElement * child
	*    \returns void
	*/
	void loadSegment(FrameInfor& frame, TiXmlElement* child);

private:
	HwaFrameConfigManagerPrivate* _p;
};

#endif //__HwaFRAMECONFIGMANAGER_H__
