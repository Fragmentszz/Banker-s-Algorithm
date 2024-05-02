#pragma once

#include <QtWidgets>
#include"_basic.h"
class PopupDialog : public QDialog {
public:
    PopupDialog(QWidget* parent = nullptr);
    std::pair<int,int> getResult() const;

private:
    int rowcount, columncount;
};
