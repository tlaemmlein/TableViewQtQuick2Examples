#ifndef SortFilterTableModel_H
#define SortFilterTableModel_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "ProcessModel.h"

class SortFilterTableModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(ProcessModel *processModel READ processModel CONSTANT)
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
    Q_CLASSINFO("DefaultProperty", "data")
public:
    SortFilterTableModel(QObject *parent = nullptr);

    ProcessModel *processModel() { return &m_ProcessModel; }
    QString filterText() const  {return m_filterText;}
    void setFilterText(QString filterText);
    Q_INVOKABLE void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);
    Q_INVOKABLE Qt::SortOrder initialSortOrder(int column) const;

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;


signals:
    void filterTextChanged(QString filterText);

private:
    ProcessModel m_ProcessModel;
    QVector<fields> m_fields;
    QString m_filterText;
};

#endif // SortFilterTableModel_H
