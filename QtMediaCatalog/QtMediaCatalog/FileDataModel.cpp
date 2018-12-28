#include "FileDataModel.h"
#include <qDebug>
#include <QCheckBox>

FileDataModel::FileDataModel(QObject *parent)
	: QAbstractTableModel(parent)
{	
	
}

FileDataModel::~FileDataModel()//catalog?
{
}

QVariant FileDataModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (index.row() >= dataSource->GetSize() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole) {
		const QStringList curr = dataSource->GetNextFileData(index.row());// надо прописать в методе возврат индекса вектора 

		switch (index.column()) {
		case 0:
			return "CheckBox is here";
		case 1:
			return "index";
		default:
			return curr.at(index.column() - 2);
		}}
	if ((role == Qt::CheckStateRole)&& (index.column() == 0)) {
		if (filesChecked->contains(index.row()))
		{
			return Qt::Checked;
		}
		else
			return Qt::Unchecked;
	}/**/
	return QVariant();
}

bool FileDataModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == Qt::EditRole)
	{
		//check value from editor
		if (value.toBool()) {
			filesChecked->append(index.row());
		}
		else{ 
			int i = filesChecked->indexOf(index.row());//решить как посылать реальные индексы
			filesChecked->removeAt(i);
			qDebug()<<"LIST LENGTH:  "<<filesChecked->length();
		}
	}
	return true;
}

Qt::ItemFlags FileDataModel::flags(const QModelIndex & index) const
{
	if (index.column() == 0) 
		return Qt::ItemIsUserCheckable | QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else
		return QAbstractTableModel::flags(index);
}

bool FileDataModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) 
	{

	}
	endInsertRows();
	return true;
}

void FileDataModel::setDataSource(Catalog * source)
{
	dataSource = source;
	filesChecked = new QList<int>;
}

void FileDataModel::addData()
{
}

void FileDataModel::updateCatalog()
{

	beginResetModel(); resetInternalData(); endResetModel();

	emit layoutChanged();
}

