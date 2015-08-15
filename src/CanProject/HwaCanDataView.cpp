
#include <QJsonDocument>
#include <QJsonObject>

#include "HwaViewBinder.h"
#include "HwaCanDataView.h"


QString HwaCanDataView::name() const
{
	return "HwaCanDataView";
}

HwaCanDataView::HwaCanDataView()
	: HwaProjectView()
{

}

HwaCanDataView::HwaCanDataView(const HwaCanDataView&)
{

}

HwaCanDataView::~HwaCanDataView()
{

}

void HwaCanDataView::onAction(const QString& action, const QVariant& param)
{
	printf("HwaCanDataView::onAction");
	// 处理视图命令
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(action.toLatin1(), &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject jObj = json.object();
		if (jObj.contains("action") && jObj.contains("objectName"))
		{
			int actionType = jObj.value("action").toInt();
			switch (actionType)
			{
			case NewItemData:
					if (_binder != NULL)
					{
						QString objName = jObj.value("objectName").toString();
						QVector<QString> infors;
						ItemInfor& item = this->getItemInfor(objName);
						//{view:"CanDataViewer", item:"label1", path:"ArincSimulation/CAN/port1", id="00000011111", row=0, count=1000}
						//TODO:默认为一个控件绑定一个path下数据，如有不同绑定子类化自行处理
						if (item.sources.size() > 0)
						{
							QJsonObject queryInfor;
							QJsonObject jObj = json.object();
							SourceInfor& source = item.sources[0];
							queryInfor["view"] = this->name();
							queryInfor["item"] = objName;
							queryInfor["path"] = source.path.c_str();
							queryInfor["id"] = source.id.c_str();
							queryInfor["row"] = jObj["row"];
							queryInfor["count"] = jObj["count"];
							_binder->query(queryInfor);
						}
					}
				break;
			}
		}
	}
}
