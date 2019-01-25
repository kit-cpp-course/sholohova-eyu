#include "ProxyModel.h"
#include <QRegularExpression>
#include <qDebug>
#pragma once

ProxyModel::ProxyModel(QObject *parent)
	: QSortFilterProxyModel(parent)
{
	strSearchName = "";
	strSearchType = "";
}

ProxyModel::~ProxyModel()
{
}

bool ProxyModel::filterAcceptsRow(int srcRow, const QModelIndex & srcParent) const
{
	QModelIndex index = sourceModel()->index(srcRow, 4, srcParent);
	QModelIndex indexName = sourceModel()->index(srcRow, 1, srcParent);
	QModelIndex indexType = sourceModel()->index(srcRow, 2, srcParent);
	if (!sourceModel()->data(index).toString().isEmpty())
	{
		return false;
	}
	QRegExp re("*" + strSearchName + "*",Qt::CaseInsensitive, QRegExp::Wildcard);
	qDebug() << strSearchName;
	QString str = sourceModel()->data(indexName).toString();
	if (!re.exactMatch(str))
	{
		return false;
	}
	return true;
}

QVariant ProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return sourceModel()->headerData(section, orientation, role);
}

void ProxyModel::SetSearchString(QString str)
{
	if (str != strSearchName)
		strSearchName = str;
	invalidateFilter();
}

void ProxyModel::SetFileType(QString type)
{
	if (type != strSearchType)
		strSearchType = type;
	invalidateFilter();
}

void ProxyModel::OnCellClicked(const QModelIndex & index)
{
	QModelIndex srcIndex = this->mapToSource(index);
	emit srcCellClicked(srcIndex);
}
