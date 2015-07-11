/**
*   \file HwaAnalyserManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��8��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWAANALYSERMANAGER_H__
#define __HWAANALYSERMANAGER_H__

#include "frameanalyser_global.h"
#include "analysertypedefs.h"

class HwaAnalyserBase;

/**
*	\class HwaAnalyserManager
*	\breif ���ֽ����������࣬�ṩ����֡ID����������ֶι���.
*	Details
*/
class FRAMEANALYSERSHARED_EXPORT HwaAnalyserManager
{
public:
	static HwaAnalyserManager& getManager();

	SmartBitsets analyse(uchar* data, const QString& id, const QVector<int>& segments);
	bool hasAnalyser(const QString& id) const;

private:
	Q_DISABLE_COPY(HwaAnalyserManager);
	HwaAnalyserManager();
	~HwaAnalyserManager();

	HwaAnalyserBase* createAnalyser(const QString& id);
	
private:
	QHash<QString, HwaAnalyserBase*> _analysers;
};

#endif //__HWAANALYSERMANAGER_H__
