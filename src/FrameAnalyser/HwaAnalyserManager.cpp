
#include <QMetaType>
#include <QMutexLocker>

#include "HwaFrameConfigManager.h"
#include "HwaFrameAnalyser.h"
#include "HwaCommonFrameAnalyser.h"
#include "HwaCanDataFrameAnalyser.h"
#include "HwaAnalyserManager.h"

HwaAnalyserManager::HwaAnalyserManager()
{
	REGISTER_META_TYPE(HwaCommonFrameAnalyser);
	REGISTER_META_TYPE(HwaCanDataFrameAnalyser);
}

HwaAnalyserManager::~HwaAnalyserManager()
{

}

HwaAnalyserManager& HwaAnalyserManager::getManager()
{
	static HwaAnalyserManager mgr;

	return mgr;
}

SmartBitsets HwaAnalyserManager::analyse(uchar* data, const QString& id, const QVector<int>& segments)
{
	if (this->hasAnalyser(id))
	{
		HwaAnalyserBase* analyser = _analysers[id];
		return analyser->analyse(data, segments);
	}
	else
	{
		HwaAnalyserBase* analyser = this->createAnalyser(id);
		if (analyser != NULL)
		{
			return analyser->analyse(data, segments);
		}
	}

	return SmartBitsets();
}

bool HwaAnalyserManager::hasAnalyser(const QString& id) const
{
	return _analysers.contains(id);
}

HwaAnalyserBase* HwaAnalyserManager::createAnalyser(const QString& id)
{
	HwaFrameConfigManager& mgr = HwaFrameConfigManager::getManager();
	FrameInfor& frame = mgr.getFrameInfor(id.toStdString());
	int type = QMetaType::type(frame.analyser.c_str());
	HwaFrameAnalyser* analyser = (HwaFrameAnalyser*)(QMetaType::create(type));
	if (analyser != NULL)
	{
		analyser->setFrameInfor(frame);

		_analysers[id] = analyser;
	}

	return analyser;
}

