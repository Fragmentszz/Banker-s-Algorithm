#include"BAWindow.h"

BAWindow::BAWindow(QWidget* parent):QWidget(parent)
{
	this->setWindowTitle("银行家算法执行结果");
	this->setGeometry(360, 270, 720, 540);
}