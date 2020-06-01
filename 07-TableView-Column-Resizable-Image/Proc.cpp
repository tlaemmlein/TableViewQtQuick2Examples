#include "Proc.h"

#include <QRandomGenerator>
#include <QTime>
#include <random>
std::random_device dev;
std::mt19937 rng(dev());

const QMap<fields, QString> Proc::Header_Info = {
    {F_PID, {"PID"}},
    {F_PPID, {"PPID"}},
    {F_PGID,    {"PGID"}},
    {F_SID,     {"SID"}},
    {F_IMAGE,   {"IMAGE"}},
    {F_STAT1,   {"STAT1"}},
    {F_STAT2,   {"STAT2"}},
    {F_STAT3,   {"STAT3"}},
    {F_STAT4,   {"STAT4"}},
    {F_CMD,     {"CMD"}},
    {F_CMDLINE, {"CMDLINE"}}
};

QString random_string(int length=32, QString allow_symbols=QString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")) {
    QString result;
    QRandomGenerator(QTime::currentTime().msec());
    for (int i = 0; i < length; ++i) {
        std::uniform_int_distribution<std::mt19937::result_type> dist1(0,allow_symbols.length());
        result.append(allow_symbols.at(dist1(rng)));
    }
    return result;
}

ProcInfo::ProcInfo()
{

}

ProcInfo::ProcInfo(int pid)
{
    mpid = pid;
    std::uniform_int_distribution<std::mt19937::result_type> dist1(1,6);
    ppid = dist1(rng);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0,100);
    pgid = dist2(rng);
    std::uniform_int_distribution<std::mt19937::result_type> dist3(100,1000);
    sid = dist3(rng);
    imageUrl = QString("qrc:/images/%0.jpg").arg(ppid);
    stat1 = QString("%1%").arg(pgid);
    stat2 = QString("%1 bytes be or not to be is the question.").arg(pgid + sid);
    stat3 = QString("%1 bytes").arg(pgid - sid);
    stat4 = QString("%1 bytes").arg(pgid * sid);
    cmd = random_string();
    cmdline = random_string();
}

ProcInfo::~ProcInfo()
{

}

QVariant ProcInfo::toVariant(fields f)
{
    switch (f) {
    case F_PID:  return mpid;
    case F_PPID:  return ppid;
    case F_PGID:  return pgid;
    case F_SID:  return sid;
    case F_IMAGE: return imageUrl;
    case F_STAT1:  return stat1;
    case F_STAT2:  return stat2;
    case F_STAT3:  return stat3;
    case F_STAT4:  return stat4;
    case F_CMD:  return cmd;
    case F_CMDLINE:  return cmdline;
    default: return "";
    }
}



Proc::Proc()
{

}

void Proc::refresh()
{
    procs.clear();
    std::uniform_int_distribution<std::mt19937::result_type> dist(1000,2500);

    const int numOfPids = dist(rng);

    for (int i = 0; i < numOfPids; ++i)
    {
        procs.insert(i, ProcInfo(i));
    }
}


