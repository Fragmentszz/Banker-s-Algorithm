
#include "QTtry1.h"
#include"_basic.h"
#include <QtWebEngineWidgets/QWebEngineView>

QTtry1::QTtry1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    t_now = new MyTable(this->ui.MaxAndNeed);
    t_process = new MyTable(this->ui.MaxAndNeed);
    time_process = new TimeTable(this->ui.MaxAndNeed);
    
    t_nowR = new MyTable(this->ui.Allocation);
    t_apply = new MyTable(this->ui.Allocation);
    t_allocation = new AllocationTable(this->ui.Allocation, t_nowR, t_apply);

    
    int width = 1920;

    t_process->setGeometry(0, 30, width, 700);
    t_now->setGeometry(0, 760, width, 70);
    time_process->setGeometry(0, 860, width, 70);


    t_allocation->setGeometry(0, 30, width, 600);
    t_nowR->setGeometry(0, 650, width, 70);
    t_nowR->setEditTriggers(QAbstractItemView::NoEditTriggers);

    t_apply->setGeometry(0, 740, width, 70);

    connect(ui.newProject, &QAction::triggered, this, &QTtry1::newProject);

    connect(ui.fillAll, &QAction::triggered, t_process, &MyTable::fillAll);
    connect(ui.fillAll, &QAction::triggered, t_now, &MyTable::fillAll);

    connect(ui.run, &QAction::triggered, this, &QTtry1::runBA);                                     //运行银行家算法


    connect(ui.fromExcel, &QAction::triggered, this, &QTtry1::fromExcel);                           //从excel导入

    connect(ui.AllocationFromExcel, &QAction::triggered, this, &QTtry1::AllocationfromExcel);

    connect(ui.fillAll1, &QAction::triggered, t_process, &MyTable::fillAll);                        //随机生成所有
    connect(ui.fillAllBlank1, &QAction::triggered, t_process, &MyTable::fillAllBlank);              //随机填充空白
    connect(ui.createBProcess, &QAction::triggered, t_process, &MyTable::addRow);                   //添加空白进程
    connect(ui.createRProcess, &QAction::triggered, t_process, &MyTable::addRow_r);                 //添加空白进程
    connect(ui.createBProcess, &QAction::triggered, time_process, &TimeTable::addColumn);           //添加空白进程
    connect(ui.createRProcess, &QAction::triggered, time_process, &TimeTable::addColumn);           //添加空白进程
    connect(ui.createTime, &QAction::triggered, time_process, &TimeTable::fillAll);
    connect(ui.newResource, &QAction::triggered, t_process, &MyTable::addColumn);                   //添加资源

    connect(ui.fillAll2, &QAction::triggered, t_now, &MyTable::fillAll);                            //随机生成所有现有资源
    connect(ui.fillAllBlank2, &QAction::triggered, t_now, &MyTable::fillAllBlank);                  //随机填充空白现有资源
    connect(ui.newResource, &QAction::triggered, t_now, &MyTable::addColumn);                       //添加资源

    initTable({ 3, 3 });

    connect(ui.tabWidget, &QTabWidget::currentChanged, this, &QTtry1::tabChange);                   //更换页面

    connect(ui.createAllocation, &QAction::triggered, t_allocation, &AllocationTable::createAllocation);        //创建分配方案

    connect(ui.createRequest, &QAction::triggered, t_allocation, &AllocationTable::createRequst);                                  //创建请求向量


    connect(ui.help, &QAction::triggered, this, &QTtry1::Help);                                         //帮助

    baw = new BAWindow();
    baw->hide();
    this->ui.tabWidget->setCurrentIndex(0);

    helpw = new QWidget();
    helpw->hide();
    
    QWebEngineView* helpPage = new QWebEngineView(helpw);
    helpw->setGeometry(100, 100, 1080, 720);
    helpPage->setGeometry(0, 0, 1080, 720);
    helpPage->load(QString("qrc:/new/html/help.html"));

}

void QTtry1::allocationChange(QTableWidgetItem* item)
{
    int i = item->row(), j = item->column();
    int num = S2N(item->text());
}

void QTtry1::newProject()           //新项目
{
    PopupDialog pw(this);
    // 显示弹窗，并等待弹窗关闭
    if (pw.exec() == QDialog::Accepted) {                      // 返回回调
        // 获取弹窗中的变量a的值
        auto result = pw.getResult();
        initTable(result);
        stringstream ss;
        ss << "生成了一个" << result.first << "个进程, " << result.second << "种资源的空项目！！" << endl;
        QMessageBox message(QMessageBox::Information, QString("项目创建成功"), QString::fromStdString(stringFromSS(ss)),QMessageBox::Yes);
        message.button(QMessageBox::Yes)->setText("好耶!!");
        int Ret = message.exec();
    }
}

void QTtry1::initTable(pair<int,int> result)
{
    t_process->clearContents();
    t_now->clearContents();
    
    t_process->initTable(result);
    t_now->initTable({1, result.second });

    t_now->verticalHeader()->setVisible(false);

    time_process->initTable({ 1,result.first });
    time_process->verticalHeader()->setVisible(false);
}

void QTtry1::runBA()
{
    if (ui.tabWidget->currentIndex() == 0)
    {
        auto critical = QMessageBox::critical(this, "拒绝运行！", "请将页面切换到Allocation页面，并且确认资源的分配！");
    }
    else if (t_allocation->hasEmpty())                  //进程的当前分配值有空值
    {
        auto critical = QMessageBox::critical(this, "拒绝运行！", "进程的当前分配值有空值！！");
    }
    else if(t_apply->hasEmpty())                        //申请的资源向量有空值
    {
        auto critical = QMessageBox::critical(this, "拒绝运行！", "申请的资源向量有空值！！");
    }
    else if (ui.needid->value() < 1 || ui.needid->value() > t_process->rowCount())      //申请资源的进程号不对
    {
        auto critical = QMessageBox::critical(this, "拒绝运行！", "申请资源的进程号不对！！！");
    }
    else
    {
        baw->show();
        baw->BankAlgorithm(t_process->tb, t_allocation->tb, (t_nowR->tb)[0], ui.needid->value() - 1, (t_apply->tb)[0],(time_process->tb)[0]);
    }
    
}

void QTtry1::tabChange()
{
    if (ui.tabWidget->currentIndex() == 0) 
    {
        ui.Run->setEnabled(0);
        ui.menu_Allocation->setEnabled(0);

        ui.start->setEnabled(1);
        ui.Project->setEnabled(1);
        ui.Process->setEnabled(1);
        ui.Now->setEnabled(1);
    }
    else 
    {
        if (t_process->hasEmpty())
        {
            ui.tabWidget->setCurrentIndex(0);
            auto critical = QMessageBox::critical(this, "初始化错误", "进程需求资源量有空值未填！");
        }
        else if (t_now->hasEmpty())
        {
            ui.tabWidget->setCurrentIndex(0);
            auto critical = QMessageBox::critical(this, "初始化错误", "资源最大量有空值未填！");
        }
        else
        {
            //t_nowR->clear();
            t_nowR->initTable({ 1,t_process->columnCount() });

            //t_apply->clear();
            t_apply->initTable({ 1,t_process->columnCount() });
            //t_allocation->clear();
            vector<int> tmp = (t_now->tb)[0];
            vector < vector<int>> tmp2 = t_process->tb;
            t_allocation->initTable({ t_process->rowCount(),t_process->columnCount() }, tmp, tmp2);
            ui.Run->setEnabled(1);
            ui.menu_Allocation->setEnabled(1);

            ui.start->setEnabled(0);
            ui.Project->setEnabled(0);
            ui.Process->setEnabled(0);
            ui.Now->setEnabled(0);
        }
    }

}


void QTtry1::AllocationfromExcel()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "选择excel文件",
        "./",
        "excel files(*.xlsx *.xls)");

    wchar_t str[1000] = { 0 };
    using namespace libxl;
    Book* book = xlCreateXMLBookW();
    book->setKey(libxl_cracked_name, libxl_cracked_key);
    int len = filename.toWCharArray(str);
    if (book)
    {
        book->load(str);
        if (book)
        {
            Sheet* sheet = book->getSheet(0);
            const wchar_t* ss = book->getSheetName(0);
            if (sheet)
            {
                int n = sheet->lastRow(), m = sheet->lastCol();
                //initTable({ n - 1,m - 1 });
                for (int i = sheet->firstRow() + 1; i < n; i++)
                {
                    for (int j = sheet->firstCol() + 1; j < m; j++)
                    {
                        t_allocation->setItem(i - 1, j - 1, new QTableWidgetItem(N2S(sheet->readNum(i, j))));
                    }
                }
                stringstream ss;
                ss << "成功导入了一种分配方案" << endl;
                QMessageBox message(QMessageBox::Information, QString("分配方案导入成功"), QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
                message.button(QMessageBox::Yes)->setText("好耶!!");
                int Ret = message.exec();
            }
            else {
                cout << "没打开sheet" << endl;
            }
            book->release();
        }
        else {
            cout << "没打开啊" << endl;
        }
    }
}


void QTtry1::fromExcel()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "选择excel文件",
        "./",
        "excel files(*.xlsx *.xls)");

    wchar_t str[1000] = { 0 };
    using namespace libxl;
    Book* book = xlCreateXMLBookW();
    book->setKey(libxl_cracked_name, libxl_cracked_key);
    int len = filename.toWCharArray(str);
    if (book)
    {
        book->load(str);
        if (book)
        {
            Sheet* sheet = book->getSheet(0);
            const wchar_t* ss = book->getSheetName(0);
            if (sheet)
            {
                int n = sheet->lastRow(), m = sheet->lastCol();
                initTable({ n-1,m-1 });
                for (int i = sheet->firstRow()+1; i < n; i++)
                {
                    for (int j = sheet->firstCol()+1; j < m; j++)
                    {
                        t_process->setItem(i-1, j-1, new QTableWidgetItem(N2S(sheet->readNum(i, j))));
                    }
                }
                stringstream ss;
                ss << "导入了一个" << n-1 << "个进程, " << m-1 << "中资源的项目！！" << endl;
                QMessageBox message(QMessageBox::Information, QString("项目导入成功"), QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
                message.button(QMessageBox::Yes)->setText("好耶!!");
                int Ret = message.exec();
            }
            else {
                cout << "没打开sheet" << endl;
            }
            book->release();
        }
        else {
            cout << "没打开啊" << endl;
        }
    }

}
void QTtry1::Help()
{
    helpw->show();
}
QTtry1::~QTtry1()
{
    
}
