#include"newProjectWindow.h"

PopupDialog::PopupDialog(QWidget* parent) : QDialog(parent),rowcount(0),columncount(0)
{
    setWindowTitle("新建项目");
    // 创建布局
    QVBoxLayout* layout = new QVBoxLayout(this);

    // 创建图片
    QLabel* imageLabel = new QLabel(this);
    QPixmap pixmap("image.jpg");  // 图片路径
    imageLabel->setPixmap(pixmap);
    layout->addWidget(imageLabel);

    // 创建文字
    QLabel* textLabel = new QLabel("资源数:", this);
    layout->addWidget(textLabel);
    // 创建选项框_column
    QLineEdit* inputLineEdit_column = new QLineEdit(this);
    layout->addWidget(inputLineEdit_column);
    layout->addWidget(inputLineEdit_column);


    // 创建文字
    QLabel* textLabel2 = new QLabel("进程数:", this);
    layout->addWidget(textLabel2);
    // 创建输入框_row
    QLineEdit* inputLineEdit_row = new QLineEdit(this);
    layout->addWidget(inputLineEdit_row);

    

    // 创建按钮
    QPushButton* okButton = new QPushButton("确定", this);
    connect(okButton, &QPushButton::clicked, [this, inputLineEdit_row, inputLineEdit_column]() {
        QString inputText_row = inputLineEdit_row->text();
        QString inputText_column = inputLineEdit_column->text();
        rowcount = S2N(inputText_row);
        columncount = S2N(inputText_column);
        // 根据输入框的内容和选项来修改变量a的值
        // 这里只是一个简单示例，可以根据业务逻辑进行具体实现
            if(rowcount == -1 || columncount == -1){
                stringstream ss;
                ss << "进程数和资源数都必须是一个自然数!!!!" << endl;
                string s;
                getline(ss, s);
                auto critical = QMessageBox::critical(this, "填写错误!!", QString::fromStdString(s));
            }
            else if(rowcount == -2 || rowcount >= 10000)
            {
                stringstream ss;
                ss << "进程数输入的数字太大了！！" << endl << "请输入一个范围在[0,10000]的整数!" << endl;
                string s = stringFromSS(ss);
                auto critical = QMessageBox::critical(this, "填写错误!!", QString::fromStdString(s));
            }
            else if (columncount == -2 || columncount >= 5000)
            {
                stringstream ss;
                ss << "资源数输入的数字太大了！！" << endl << "请输入一个范围在[0,5000]的整数!" << endl;
                string s = stringFromSS(ss);
                auto critical = QMessageBox::critical(this, "填写错误!!", QString::fromStdString(s));
            }
            else {
                accept();
            }
        });
    layout->addWidget(okButton);

    setLayout(layout);
}

std::pair<int,int> PopupDialog::getResult() const {
    return {rowcount,columncount};
}