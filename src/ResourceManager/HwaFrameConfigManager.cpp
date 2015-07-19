
#include "tinyxml.h"

#include "HwaPlatformConfigManager.h"
#include "HwaFrameConfigManager.h"

struct HwaFrameConfigManagerPrivate
{
	std::hash_map<HwaString, FrameInfor> frames;
};

HwaFrameConfigManager& HwaFrameConfigManager::getManager()
{
	static HwaFrameConfigManager mgr;
	return mgr;
}

FrameInfor HwaFrameConfigManager::getFrameInfor(const HwaString& frameId) const
{
	if (this->hasKey(frameId))
	{
		return _p->frames[frameId];
	}

	return FrameInfor();
}

SegmentInfor HwaFrameConfigManager::getSegmentInfor(const HwaString& frameId, int segId) const
{
	SegmentInfor segment;
	if (this->hasKey(frameId))
	{
		const FrameInfor& frame = _p->frames[frameId];
		std::vector<SegmentInfor>::const_iterator iter = frame.segments.begin();
		while (iter != frame.segments.end())
		{
			if ((*iter).id == segId)
			{
				segment = *iter;
				break;
			}
		}
	}

	return segment;
}

HwaFrameConfigManager::HwaFrameConfigManager()
	: _p(new HwaFrameConfigManagerPrivate)
{
	this->loadFile();
}

HwaFrameConfigManager::~HwaFrameConfigManager()
{
	delete _p;
}

bool HwaFrameConfigManager::loadFile()
{
	HwaPlatformConfigManager& platformMgr = HwaPlatformConfigManager::getManager();
	HwaString protoConfigPath = platformMgr.getProtocalConfigPath();
	TiXmlDocument doc(protoConfigPath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		this->loadFrame(root);

		return true;
	}

	return false;
}

bool HwaFrameConfigManager::hasKey(const HwaString& key) const
{
	std::hash_map<HwaString, FrameInfor>::iterator iter = _p->frames.begin();
	for (; iter != _p->frames.end(); ++iter)
	{
		if (key == (*iter).first)
		{
			return true;
		}
	}

	return false;
}

void HwaFrameConfigManager::loadFrame(TiXmlElement* root)
{
	while (root != NULL)
	{
		FrameInfor frame;
		frame.id = root->Attribute("ID");
		frame.name = root->Attribute("name");
		frame.type = root->Attribute("type");
		frame.analyser = root->Attribute("class");
		TiXmlElement* child = root->FirstChildElement();
		this->loadSegment(frame, child);

		root = root->NextSiblingElement();

		_p->frames[frame.id] = frame;
	}
}

void HwaFrameConfigManager::loadSegment(FrameInfor& frame, TiXmlElement* child)
{
	if (child != NULL)
	{
		do 
		{
			SegmentInfor segment;
			const char* pValue = child->Attribute("id");
			if (pValue)
				segment.id = atoi(pValue);

			pValue = child->Attribute("name");
			if (pValue)
				segment.name = pValue;

			pValue = child->Attribute("size");
			if (pValue)
				segment.size = atoi(pValue);

			pValue = child->Attribute("offset");
			if (pValue)
				segment.offset = atoi(pValue);

			pValue = child->Attribute("ref");
			if (pValue)
				segment.reference = atoi(pValue);

			pValue = child->Attribute("prev");
			if (pValue)
				segment.previous = atoi(pValue) != 0;

			pValue = child->Attribute("desc");
			if (pValue)
				segment.description = pValue;

			frame.segments.push_back(segment);
		} while (child = child->NextSiblingElement());
	}
}
