/**
*   \file HwaFrameConfigManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��6��30��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HwaFRAMECONFIGMANAGER_H__
#define __HwaFRAMECONFIGMANAGER_H__

#include "resourcemanager_global.h"
#include "typedefs.h"

struct HwaFrameConfigManagerPrivate;
class TiXmlElement;

/**
*	\class HwaFrameConfigManager
*	\breif ֡���ù����ļ����ļ�λ�ôӿ�����û�ȡ.
*	
*			�ṩ֡���ֶλ�ȡ�ӿڣ���ֹ��������
*/
class RESOURCEMANAGERSHARED_EXPORT HwaFrameConfigManager
{
public:
	static HwaFrameConfigManager& getManager();
	
	/**
	*    \fn    getFrameInfor
	*    \brief ����֡ID��ȡ��֡��Ϣ.
	
	*    \param const HwaString & frameId
	*    \returns FrameInfor
	*/
	FrameInfor getFrameInfor(const HwaString& frameId) const;
	
	/**
	*    \fn    getSegmentInfor
	*    \brief ����֡ID���ֶ�ID������ȡһ���ֶ���Ϣ.
	
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
	*    \brief ����֡�����ļ�.
	
	*    \returns bool
	*/
	bool loadFile();
	
	/**
	*    \fn    hasKey
	*    \brief �ж��Ƿ�������֡������֡ID����.
	
	*    \param const HwaString & key
	*    \returns bool
	*/
	bool hasKey(const HwaString& key) const;
	
	/**
	*    \fn    loadFrame
	*    \brief ���ҵ����ڵ�󣬽���֡.
	
	*    \param TiXmlElement * root
	*    \returns void
	*/
	void loadFrame(TiXmlElement* root);
	
	/**
	*    \fn    loadSegment
	*    \brief ���ղ��ҵ���֡������֡�µ��ֶ�.
	
	*    \param FrameInfor & frame
	*    \param TiXmlElement * child
	*    \returns void
	*/
	void loadSegment(FrameInfor& frame, TiXmlElement* child);

private:
	HwaFrameConfigManagerPrivate* _p;
};

#endif //__HwaFRAMECONFIGMANAGER_H__
