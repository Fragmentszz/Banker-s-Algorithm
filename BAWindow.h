#pragma once
#include <QtWidgets>
#include"_basic.h"
#include<QtWebEngineWidgets/QWebEngineView>
#include"ui_BAWindow.h"
class BAWindow: 
	public QWidget
{
public:
	BAWindow(QWidget* parent = nullptr);
	void BankAlgorithm(vector<vector<int>>& Need, vector<vector<int>>& allocation, vector<int>& nowR,int needid, vector<int>& apply,vector<int>& Times);

	QTextBrowser* tb;
	Ui::Form ui;
	QWebEngineView *web;
private:

};
