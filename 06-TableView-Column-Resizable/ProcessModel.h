#ifndef ProcessModel_H
#define ProcessModel_H


#include "Proc.h"

#include <QAbstractTableModel>
#include <QTimer>

class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    // supplemental roles beyond Qt::ItemDataRole
    enum class Role {
        Sort = Qt::UserRole,
        Number,
        Type
    };
    Q_ENUM(Role)

    explicit ProcessModel(QObject *parent= nullptr);
    ~ProcessModel();

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);
    Q_INVOKABLE void update();


private:
    Proc m_proc;
    QVector<int> m_pids;
    QVector<int> m_columnWidths = QVector<int>(F_CMDLINE + 1);
    QHash<int, QByteArray> m_roleNames;
};


#endif

