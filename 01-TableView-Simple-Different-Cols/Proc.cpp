#include "Proc.h"

#include <random>
std::random_device dev;
std::mt19937 rng(dev());

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
    stat1 = QString("%1%").arg(pgid);
    stat2 = QString("%1 bytes").arg(pgid + sid);
    stat3 = QString("%1 bytes").arg(pgid - sid);
    stat4 = QString("%1 bytes").arg(pgid * sid);
    cmd = QString("cmd%1").arg(sid);
    cmdline = "cmdline";
}

ProcInfo::~ProcInfo()
{

}

QString ProcInfo::toString(fields f)
{
    switch (f) {
    case F_PID:  return QString("%1").arg(mpid);
    case F_PPID:  return QString("%1").arg(ppid);
    case F_PGID:  return QString("%1").arg(pgid);
    case F_SID:  return QString("%1").arg(sid);
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
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,100);

    const int numOfPids = dist(rng);

    for (int i = 0; i < numOfPids; ++i)
    {
        procs.insert(i, ProcInfo(i));
    }
}


