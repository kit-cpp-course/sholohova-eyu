#pragma once
#include <QAbstractTableModel>
#include "Catalog.h"

class FileDataModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	FileDataModel(QObject *parent = Q_NULLPTR);
	~FileDataModel();
	int rowCount(const QModelIndex &parent = QModelIndex()) const override { return dataSource->GetSize(); };
	int columnCount(const QModelIndex &parent = QModelIndex()) const override {	return 6;};
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex & index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	void setDataSource(Catalog *source);
private slots:
public slots :
	void SendFilesList(QString dirName);
	void OnCellClicked(const QModelIndex &index);
signals:
	void isFileChecked(bool check);
	void fileChoosen(bool choosen);
	void addFilesToDir(QString dirName, QList<int> chfiles);
private:
	Catalog *dataSource;
	QList<int> filesChecked;//
	void updateCatalog();
};
