#pragma once
#include"_basic.h"
class QTtry1;
class MyTable :
	public QTableWidget
{
    friend class QTtry1;
public:
    MyTable(QWidget* parent = nullptr);
    ~MyTable();

public:
    std::vector<std::vector<int>> tb;
    virtual void initTable(pair<int,int> size);
protected slots:
    void newProject();
    void fillAllBlank();
    void fillAll();
    virtual void bindtb(QTableWidgetItem* item);
    void addRow();
    void addRow_r();
    void addColumn();
    bool hasEmpty() const;
};

class AllocationTable :
    public MyTable
{
    friend class QTtry1;
public:
    AllocationTable(QWidget* parent = nullptr, MyTable* nowR = nullptr, MyTable* apply = nullptr);

protected:
    MyTable* t_nowR, *t_apply;
    vector<int> maxR;
    vector<int> nowR;
    vector<vector<int>> Need;
protected slots:
    void initTable(pair<int, int> size, vector<int>& _maxR, vector<vector<int>>& _Need);
    void bindtb(QTableWidgetItem* item);
    void createAllocation();
    void createRequst();
};

class TimeTable :
    public MyTable
{
public:
    TimeTable(QWidget* parent = nullptr);
    void initTable(pair<int, int> size);
    void addColumn();
};