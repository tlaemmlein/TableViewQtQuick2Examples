#include "TableModel.h"

#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel (parent)
{
    update();
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&TableModel::update));
    m_timer->start(5000);
}

TableModel::~TableModel()
{

}

int TableModel::rowCount(const QModelIndex &) const
{
    return m_pids.count();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return F_CMDLINE + 1;
}

QVariant TableModel::data(const QModelIndex &index, int /*role*/) const
{
    fields field = fields(index.column());
    int pid = m_pids[index.row()];
    ProcInfo pi = m_proc.procs.value(pid);
    return pi.toString(field);
}

void TableModel::update()
{
    qDebug() << __FUNCTION__;
    beginResetModel();
    m_proc.refresh();
    m_pids = m_proc.procs.keys().toVector();
    std::sort(m_pids.begin(), m_pids.end());
    endResetModel();
}




