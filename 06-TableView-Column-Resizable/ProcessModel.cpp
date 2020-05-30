#include "ProcessModel.h"

#include <QDebug>
#include <QFontMetrics>
#include <QGuiApplication>

ProcessModel::ProcessModel(QObject *parent) : QAbstractTableModel (parent)
{
    m_roleNames = QAbstractTableModel::roleNames();
    // TODO loop over the QMetaEnum
    m_roleNames.insert(int(Role::Sort), QByteArray("sort"));
    m_roleNames.insert(int(Role::Number), QByteArray("number"));
    m_roleNames.insert(int(Role::Type), QByteArray("type"));
    update();
}

ProcessModel::~ProcessModel()
{

}

QHash<int, QByteArray> ProcessModel::roleNames() const
{
    return m_roleNames;
}

int ProcessModel::rowCount(const QModelIndex &) const
{
    return m_pids.count();
}

int ProcessModel::columnCount(const QModelIndex &) const
{
    return F_CMDLINE + 1;
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    fields field = fields(index.column());
    int pid = m_pids[index.row()];
    ProcInfo pi = m_proc.procs.value(pid);
    switch (role) {
    case Qt::DisplayRole:
        return pi.toVariant(field);
    case Qt::InitialSortOrderRole: {
        bool numeric = false;
        pi.toVariant(field).toFloat(&numeric);
        if (numeric)
            return Qt::DescendingOrder;
        return Qt::AscendingOrder;
    }
    case int(ProcessModel::Role::Sort):
        return pi.toVariant(field);
    case int(ProcessModel::Role::Number):
        return pi.toVariant(field).toDouble();
    case int(ProcessModel::Role::Type):
        // TODO this is silly: make a virtual in the Category perhaps?
        switch (field) {
        case F_PID:
        case F_PPID:
            return QLatin1String("readonly");
        case F_PGID:
        case F_SID:
            return QLatin1String("id");
        case F_STAT1:
        case F_STAT2:
        case F_STAT3:
        case F_STAT4:
            return QLatin1String("stat");
        case F_CMD:
        case F_CMDLINE:
            return QLatin1String("string");
        default:
            return QLatin1String("string");
        }
    default:
        return QVariant();
    }

    return pi.toVariant(field);
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
            ret = qMax(ret, fm.horizontalAdvance(pi.toVariant(fields(c)).toString()));
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




