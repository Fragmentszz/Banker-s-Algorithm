#include"MyTable.h"
#include<qmessagebox.h>
#include<sstream>

MyTable::MyTable(QWidget* parent)
    :QTableWidget(parent)
{
    connect(this, &QTableWidget::itemChanged, this, &MyTable::bindtb);
}

void MyTable::fillAllBlank()         //填充全部空白
{
    for (int i = 0; i < this->rowCount(); i++)
    {
        for (int j = 0; j < this->columnCount(); j++)
        {
            if (this->item(i, j) == nullptr || this->item(i,j)->text() == "")
            {
                int rd = randint(0, 100);
                this->setItem(i, j, new QTableWidgetItem(N2S(rd)));
            }
        }
    }
}

void MyTable::fillAll()          //填充全部
{
    for (int i = 0; i < this->rowCount(); i++)
    {
        for (int j = 0; j < this->columnCount(); j++)
        {
            int rd = randint(0, 100);
            this->setItem(i, j, new QTableWidgetItem(N2S(rd)));
        }
    }
}

void MyTable::bindtb(QTableWidgetItem* item)
{
    int i = item->row(), j = item->column();
    tb[i][j] = S2N(item->text());
}

void MyTable::initTable(pair<int, int> result)
{
    this->clearContents();
    tb.resize(result.first);
    for (int i = 0; i < result.first; i++) {
        tb[i].resize(result.second);
        for (int j = 0; j < result.second; j++) {
            tb[i][j] = 0;
        }
    }
    this->setRowCount(result.first);
    this->setColumnCount(result.second);
    QStringList header_column;
    QStringList header_row;
    for (int i = 0; i < result.second; i++) {
        QString s = "资源";
        s.append(N2S(i + 1));
        header_column << s;
    }
    for (int i = 0; i < result.first; i++) {
        QString s = "进程";
        s.append(N2S(i + 1));
        tb[i].resize(result.second);
        header_row << s;
    }
    this->setHorizontalHeaderLabels(header_column);
    this->setVerticalHeaderLabels(header_row);
}


void MyTable::addRow()
{
    int nowrow = this->rowCount();
    tb.resize(++nowrow);
    cout << nowrow << " " << tb.size() << endl;
    tb[nowrow - 1].resize(this->columnCount());
    for (int j = 0; j < this->columnCount(); j++)
    {
        tb[nowrow - 1][j] = 0;
    }
    QString s = "进程";
    s.append(N2S(nowrow));
    this->setRowCount(nowrow);
    auto tmpItem = new QTableWidgetItem(s);
    this->setVerticalHeaderItem(nowrow - 1, tmpItem);
}


void MyTable::addRow_r()
{
    addRow();
    int nowrow = this->rowCount();
    for (int j = 0; j < this->columnCount(); j++)
    {
        int rd = randint(0, 100);
        this->setItem(nowrow-1, j, new QTableWidgetItem(N2S(rd)));
    }
}

void MyTable::addColumn()
{
    int nowcolumn = this->columnCount();
    nowcolumn++;
    for (int i = 0; i < tb.size(); i++){
        tb[i].resize(nowcolumn);
        tb[i][nowcolumn - 1] = 0;
    }
    QString s = "资源";
    s.append(N2S(nowcolumn));
    this->setColumnCount(nowcolumn);
    auto tmpItem = new QTableWidgetItem(s);
    this->setHorizontalHeaderItem(nowcolumn - 1, tmpItem);
}

bool MyTable::hasEmpty()    const
{
    for (int i = 0; i < this->rowCount(); i++)
    {
        for (int j = 0; j < this->columnCount(); j++)
        {
            
            if (this->item(i, j) == nullptr)
            {
                return 1;
            }
            else if (this->item(i, j)->text() == "")
            {
                return 1;
            }
        }
    }
    return 0;
}
MyTable::~MyTable()
{

}



//////////////////////////////////////////////////////////////////////////

AllocationTable::AllocationTable(QWidget* parent, MyTable* nowR, MyTable* apply) :MyTable(parent), t_nowR (nowR),t_apply(apply)
{
   
}
void AllocationTable::initTable(pair<int, int> size, vector<int>& _maxR,vector<vector<int>>& _Need)
{
    
    MyTable::initTable(size);
    
    Need = _Need;
    //cout << Need.size() << endl;
    maxR.clear();
    nowR.clear();
    for (int i = 0; i < _maxR.size(); i++) {
        maxR.push_back(_maxR[i]);
        nowR.push_back(_maxR[i]);
        if (t_nowR->item(0, i) == nullptr)
        {
            t_nowR->setItem(0, i, new QTableWidgetItem(N2S(_maxR[i])));
        }
        else
        {
            t_nowR->item(0, i)->setText(N2S(_maxR[i]));
        }
    }
}
void AllocationTable::bindtb(QTableWidgetItem* item)
{
    int i = item->row(), j = item->column();
    int after = S2N(item->text());
    if (after > Need[i][j])                     //分配的数量大于最大需求量
    {
        item->setText(N2S(tb[i][j]));
        stringstream ss;
        ss << "进程" << i+1 << "的资源" << j + 1 << "超过最大请求量。<br>" << "最大请求量:" << Need[i][j] << " 您试图分配的资源数:" << after << endl;
        string s;
        getline(ss, s);
        auto critical = QMessageBox::critical(this, "分配有误!!", QString::fromStdString(s));
    }
    else if(after - tb[i][j] > nowR[j])        //分配的数量超过当前剩余的资源数量
    {
        item->setText(N2S(tb[i][j]));
        stringstream ss;
        ss << "资源" << j+1 << "已分配的资源数量超过最大资源数量。<br>" << "可分配的最大资源数:" << nowR[j]+tb[i][j] << " 您试图分配的资源数:" << after << endl;
        string s;
        getline(ss, s);
        auto critical = QMessageBox::critical(this, "分配有误!!", QString::fromStdString(s));
    }
    else
    {
        nowR[j] -= (after - tb[i][j]);
        tb[i][j] = after;
    }

    // 更改剩余资源t_nowR
    if (t_nowR->item(0, j) == nullptr)
    {
        t_nowR->setItem(0, j, new QTableWidgetItem(N2S(nowR[j])));
    }
    else
    {
        t_nowR->item(0, j)->setText(N2S(nowR[j]));
    }
}


void AllocationTable::createAllocation()
{
    for (int j = 0; j < this->columnCount(); j++)
    {
        nowR[j] = maxR[j];
        int left = randint(0, maxR[j] / 3);
        int allocated = maxR[j] - left;
        vector<int> a;
        for (int i = 0; i < this->rowCount()-1; i++)
        {
            a.push_back(randint(0, allocated));
        }
        a.emplace_back(0);
        sort(a.begin(), a.end());
        a.push_back(allocated);
        for (int i = 0; i < this->rowCount(); i++)
        {
            int now = min(Need[i][j],a[i + 1] - a[i]);
            if (this->item(i, j) == nullptr)
            {
                this->setItem(i, j, new QTableWidgetItem(N2S(now)));
            }
            else
            {
                this->item(i, j)->setText(N2S(now));
            }
        }
    }
}


void AllocationTable::createRequst()
{
    for (int i = 0; i < maxR.size(); i++)
    {
        int rd = randint(0, nowR[i]);
        t_apply->setItem(0, i, new QTableWidgetItem(N2S(rd)));
    }
}



//////////////////////////////////////////////////////////////////////////


TimeTable::TimeTable(QWidget* parent):MyTable(parent)
{

}

void TimeTable::initTable(pair<int, int> result)
{
    this->clearContents();
    tb.resize(result.first);
    for (int i = 0; i < result.first; i++) {
        tb[i].resize(result.second);
        for (int j = 0; j < result.second; j++) {
            tb[i][j] = 0;
        }
    }
    this->setRowCount(result.first);
    this->setColumnCount(result.second);
    QStringList header_column;
    for (int i = 0; i < result.second; i++) {
        QString s = "进程";
        s.append(N2S(i + 1));
        header_column << s;
    }

    this->setHorizontalHeaderLabels(header_column);
}

void TimeTable::addColumn()
{
    //cout << "here" << endl;
    int nowcolumn = this->columnCount();
    nowcolumn++;
    //cout << nowcolumn << endl;
    for (int i = 0; i < tb.size(); i++) {
        tb[i].resize(nowcolumn);
        tb[i][nowcolumn - 1] = 0;
    }
    QString s = "进程";
    s.append(N2S(nowcolumn));
    this->setColumnCount(nowcolumn);
    auto tmpItem = new QTableWidgetItem(s);
    this->setHorizontalHeaderItem(nowcolumn - 1, tmpItem);
}