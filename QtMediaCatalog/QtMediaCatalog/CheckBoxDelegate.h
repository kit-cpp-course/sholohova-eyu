#pragma once

#include <QItemDelegate>
#include <QObject>
#include <QModelIndex>
#include <QSize>
#include <QCheckBox>

class CheckBoxDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	explicit CheckBoxDelegate(QObject *parent); //будет ли работать без explicit
	~CheckBoxDelegate();

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void	setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void	setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	QSize	sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void	updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	//void	paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
