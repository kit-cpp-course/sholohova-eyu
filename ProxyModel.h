#pragma once
#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT
private:
	QString strSearchName;
	QString strSearchType;
signals:
	void srcCellClicked(const QModelIndex &index);
public:
	ProxyModel(QObject *parent);
	~ProxyModel();
	bool filterAcceptsRow(int srcRow, const QModelIndex &srcParent) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public slots:
	void SetSearchString(QString strSearch);
	void SetFileType(QString strType);
	void OnCellClicked(const QModelIndex &index);
};
