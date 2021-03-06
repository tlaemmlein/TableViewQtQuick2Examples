#ifndef TABLEMODEL_H
#define TABLEMODEL_H


#include "Proc.h"

#include <QAbstractTableModel>
#include <QTimer>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent= nullptr);
    ~TableModel();

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int) const override;

private slots:
    void update();

private:
    Proc m_proc;
    QVector<int> m_pids;
    QTimer* m_timer;

};


#endif

