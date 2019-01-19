#include "FileDataModel.h"
#include <qDebug>
#include <QCheckBox>
#pragma once

FileDataModel::FileDataModel(QObject *parent)
	: QAbstractTableModel(parent)
{	
	
}

FileDataModel::~FileDataModel()
{
}

QVariant FileDataModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();
	else if (index.row() >= dataSource->GetSize() || index.row() < 0)
		return QVariant();
	else
	{
		const QStringList curr = dataSource->GetNextFileData(index.row());

		if ((role == Qt::CheckStateRole) && (index.column() == 0)) {
			if (filesChecked.contains(curr.at(4).toInt()))	//if (index.column() == 0) //add a checkbox to cell(1,0)
			{
				return Qt::Checked;
			}
			else
				return Qt::Unchecked;
		}
		if (role == Qt::DisplayRole) {
			
			//qDebug() << "ADDED" << curr.at(0);
				// добавить проверку выхода индексов за границы QStringList
			if ((index.column() - 1 <= curr.length()) && (index.column() != 0)) {
				return curr.at(index.column() - 1);//можно вместо сдвига индексов вставлять колонку с checkIndex
			}
		}
	}
/**/
	return QVariant();
}

bool FileDataModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == Qt::EditRole)
	{
		//check value from editor
		if (value.toBool()) {
			// add file if it was checked
			filesChecked.append(index.row());	//recIndex
			emit fileChoosen(true);
			qDebug() << "LIST LENGTH+:  " << filesChecked.length();
		}
		else {
			//remove file if it was unchecked
			int i = filesChecked.indexOf(index.row());	//recIndex
			filesChecked.removeAt(i);
			if (filesChecked.isEmpty()) emit fileChoosen(false);// noFilesChoosen();
			qDebug() << "LIST LENGTH-:  " << filesChecked.length();
		}//emit editCompleted(result);// посылать сигнал вьюшке, чтобы она отображала галочку?
	}/**/
	return true;
}

void FileDataModel::OnCellClicked(const QModelIndex &index)
{
	QModelIndex ind = index;
	if (index.isValid() && (index.column() == 0)) {
		bool isChecked = data(index, Qt::CheckStateRole).toBool();
		setData(index, !isChecked, Qt::EditRole);
	}

}


Qt::ItemFlags FileDataModel::flags(const QModelIndex & index) const
{
	if (index.column() == 0) 
		return Qt::ItemIsUserCheckable | QAbstractTableModel::flags(index) | Qt::ItemIsEnabled;
	else
		return QAbstractTableModel::flags(index);
}

QVariant FileDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole) {
			switch (section)
			{
			case 0:
				return " ";
			case 1:
				return "File name";
			case 2:
				return "Type";
			case 3:
				return "Size";
			case 4:
				return "Catalog"; // ? IsOrganized
			case 5:
				return "Record index";
			default:
				break;
			}
		}
		else if (role == Qt::SizeHintRole)
		{
			switch (section)
			{
			case 0:
				return QSize(10,10);
			case 2:
				return QSize(20, 10);
			case 3:
				return QSize(30, 10);
			default:
				break;
			}
		}
	}
	else if (orientation == Qt::Vertical) {
				return QVariant();
		}

	return QAbstractTableModel::headerData(section, orientation, role);

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
	dataSource = source;//насколько это адекватная запись? указатель передаем по значению, достаточно ли присваивания
	//QObject::connect(dataSource, SIGNAL(dataChanged()), this, SLOT(updateCatalog()));
	//filesChecked = new QList<int>;
}

void FileDataModel::SendFilesList(QString dirName)
{
	emit addFilesToDir(dirName, filesChecked);
	filesChecked.clear();
	qDebug() << "LIST IS CLEARED!!!";
}

void FileDataModel::updateCatalog()
{
	//emit dataChanged();
	beginResetModel(); resetInternalData(); endResetModel();

	emit layoutChanged();
}

