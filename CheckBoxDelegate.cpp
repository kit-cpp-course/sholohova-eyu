#include "CheckBoxDelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

CheckBoxDelegate::~CheckBoxDelegate()
{
}

QWidget * CheckBoxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QCheckBox *checkBox = new QCheckBox(parent);
	checkBox->setChecked(false);
	return checkBox;
}

void CheckBoxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	bool value = index.model()->data(index, Qt::EditRole).toBool();//Qt::CheckStateRole
	QCheckBox *checkBox = static_cast<QCheckBox*>(editor);//thats how the program know what type is editor
	checkBox->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
	model->setData(index, checkBox->isChecked(), Qt::EditRole);
}

QSize CheckBoxDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	return QSize();
}

void CheckBoxDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}

/*void CheckBoxDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (index.column() == 1)
	{
		// ohh it's my column
		// better do something creative
	}
	else 
		QItemDelegate::paint(painter, option, index);
}*/
