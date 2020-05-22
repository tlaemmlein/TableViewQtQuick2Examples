#include "ProcessModel.h"

#include <QDebug>
#include <QFontMetrics>
#include <QGuiApplication>

ProcessModel::ProcessModel(QObject *parent) : QAbstractTableModel (parent)
{
    update();
}

ProcessModel::~ProcessModel()
{

}

int ProcessModel::rowCount(const QModelIndex &) const
{
    return m_pids.count();
}

int ProcessModel::columnCount(const QModelIndex &) const
{
    return F_CMDLINE + 1;
}

QVariant ProcessModel::data(const QModelIndex &index, int /*role*/) const
{
    fields field = fields(index.column());
    int pid = m_pids[index.row()];
    ProcInfo pi = m_proc.procs.value(pid);
    return pi.toString(field);
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        // section is interpreted as column
        return m_proc.Header_Info.value(static_cast<fields>(section));
    } else {
        return QString();
    }
}

int ProcessModel::columnWidth(int c, const QFont *font)
{
    if (!m_columnWidths[c]) {
        QString header = m_proc.Header_Info.value(static_cast<fields>(c));
        QFontMetrics defaultFontMetrics = QFontMetrics(QGuiApplication::font());
        QFontMetrics fm = (font ? QFontMetrics(*font) : defaultFontMetrics);
        int ret = fm.horizontalAdvance(headerData(c, Qt::Horizontal).toString() + QLatin1String(" ^")) + 8;
        for (int r = 0; r < m_pids.count(); ++r) {
            ProcInfo pi = m_proc.procs.value(m_pids[r]);
            ret = qMax(ret, fm.horizontalAdvance(pi.toString(fields(c))));
        }
        m_columnWidths[c] = ret;
    }
    return m_columnWidths[c];

}

void ProcessModel::update()
{
    qDebug() << __FUNCTION__;
    beginResetModel();
    m_proc.refresh();
    m_pids = m_proc.procs.keys().toVector();
    std::sort(m_pids.begin(), m_pids.end());
    endResetModel();
}




