/**
*   \file HwaAnalyserManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月8日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWAANALYSERMANAGER_H__
#define __HWAANALYSERMANAGER_H__

#include "frameanalyser_global.h"
#include "analysertypedefs.h"

class HwaAnalyserBase;

/**
*	\class HwaAnalyserManager
*	\breif 各种解析器管理类，提供按照帧ID解析其相关字段功能.
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
