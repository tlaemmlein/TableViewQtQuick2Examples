#ifndef PROC_H
#define PROC_H

#include <QMap>
#include <QVariant>
#include <QVector>


enum fields
{
    F_PID = 0,
    F_PPID,
    F_PGID,
    F_SID,
    F_IMAGE,
    F_STAT1,
    F_STAT2,
    F_STAT3,
    F_STAT4,
    F_CMD,
    F_CMDLINE,
    F_END = -1
};


class ProcInfo
{
public:
    ProcInfo();
    ProcInfo(int pid);
    ~ProcInfo();

    int mpid;
    int ppid;
    int pgid;
    int sid;
    QString imageUrl;
    QString stat1;
    QString stat2;
    QString stat3;
    QString stat4;
    QString cmd;
    QString cmdline;

    QVariant toVariant(fields f);
};

using ProcList = QMap<int, ProcInfo>;


class Proc
{
public:
    Proc();
    void refresh();

    ProcList procs; // processes indexed by pid

    static const QMap<fields, QString> Header_Info;
};

#endif // PROC_H
