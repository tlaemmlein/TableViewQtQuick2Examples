#include "SortFilterTableModel.h"
#include <QDebug>

SortFilterTableModel::SortFilterTableModel(QObject *parent)
  : QSortFilterProxyModel (parent)
{
    setSourceModel(&m_ProcessModel);
    setSortRole(int(ProcessModel::Role::Sort));
    // default fields that "top" displays
    m_fields << F_PID
             << F_PPID
             << F_PGID
             << F_SID
             << F_STAT1
             << F_STAT2
             << F_STAT3
             << F_STAT4
             << F_CMD
             << F_CMDLINE;
    setFilterKeyColumn(F_CMDLINE);
}

void SortFilterTableModel::setFilterText(QString filterText)
{
    if (m_filterText == filterText)
        return;

    m_filterText = filterText;
    setFilterRegularExpression(filterText);
    emit filterTextChanged(m_filterText);
}


void SortFilterTableModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << column << m_fields[column] << order;
    QSortFilterProxyModel::sort(m_fields[column], order);
}

int SortFilterTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_fields.count();
}

int SortFilterTableModel::columnWidth(int c, const QFont *font)
{
    if (c < 0 || c >= m_fields.count())
        return 0;
    return m_ProcessModel.columnWidth(m_fields[c], font);
}

Qt::SortOrder SortFilterTableModel::initialSortOrder(int column) const
{
    bool ok = false;
    if (column < 0 || column >= m_fields.count())
        return Qt::AscendingOrder;
    int ret = m_ProcessModel.data(m_ProcessModel.index(0, m_fields[column]), Qt::InitialSortOrderRole).toInt(&ok);
    if (ok)
        return Qt::SortOrder(ret);
    else
        return Qt::AscendingOrder;
}

QModelIndex SortFilterTableModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    int row = QSortFilterProxyModel::mapFromSource(sourceIndex).row();
    fields field = fields(sourceIndex.column());
    return m_ProcessModel.index(row, m_fields.indexOf(field));
}

QModelIndex SortFilterTableModel::mapToSource(const QModelIndex &proxyIndex) const
{
    QModelIndex rowIndex = QSortFilterProxyModel::mapToSource(proxyIndex);
    int col = -1;
    if (proxyIndex.column() >= 0 && proxyIndex.column() < m_fields.count())
        col = m_fields[proxyIndex.column()];
    return m_ProcessModel.index(rowIndex.row(), col);
}

