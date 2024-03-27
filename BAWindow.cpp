#include"BAWindow.h"
#include<sstream>

BAWindow::BAWindow(QWidget* parent):QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("银行家算法执行结果");
	this->setGeometry(100,100 , 1080, 720);
	tb = new QTextBrowser(nullptr);
	tb->setText("empty!");
	tb->setGeometry(0, 0, 10, 10);
	ui.webEngineView->load(QUrl("qrc:/new/html/graph.html"));
	ui.webEngineView->show();
}

QString generateJs(int flag, vector<vector<int>> path, vector<int>& scores)
{
	QString jscode = "runBA(";
	jscode.append((char)(flag + '0'));
	jscode.append(",[");
	for (int i = 0; i < path.size(); i++)
	{
		jscode.append('[');
		for (int j = 0; j < path[i].size(); j++)
		{
			jscode.append(QString::number(path[i][j]));
			if (j != path[i].size() - 1)   jscode.append(',');
		}
		jscode.append(']');
		if (i != path.size() - 1)  jscode.append(',');
	}
	jscode.append("],[");
	for (int i = 0; i < scores.size(); i++)
	{
		jscode.append(std::to_string(scores[i] * 1.0 / path[0].size()));
		if (i != scores.size() - 1)	jscode.append(",");
	}
	jscode.append(']');
	jscode.append(");");
	return jscode;
}



typedef vector<int> VI;
static VI operator-(const VI& a, const VI& b)
{
	VI res;
	for (int i = 0; i < a.size(); i++)
	{
		res.push_back(a[i] - b[i]);
	}
	return res;
}
static VI operator+(const VI& a, const VI& b)
{
	VI res;
	for (int i = 0; i < a.size(); i++)
	{
		res.push_back(a[i] + b[i]);
	}
	return res;
}
static bool operator<=(const VI& a, const VI& b)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] > b[i])	return 0;
	}
	return 1;
}

vector<vector<int>> dneed;
vector<int> dwork;
vector<int> dflag;
vector<vector<int>> dallocation;
vector<vector<int>> dpaths;
vector<int> dpath;
vector<int> dTimes;
void bankAlgorithm(int now)							//内部使用
{
	int n = dneed.size(), m = dwork.size();
	if (now == n) {
		dpaths.push_back(dpath);
	}
	for (int i = 0; i < n; i++)
	{
		if (dneed[i] <= dwork && dflag[i] == 0)
		{
			dflag[i] = 1;
			dwork = dwork + dallocation[i];
			dpath[now] = i+1;
			bankAlgorithm(now + 1);
			dflag[i] = 0;
			dwork = dwork - dallocation[i];
		}
	}
}
long long cacutime(const vector<int>& path)
{
	int nowtime1 = 0;
	long long waittime1 = 0;
	for (int i = 0; i < path.size(); i++)
	{
		waittime1 += nowtime1;
		nowtime1 += dTimes[path[i]-1];
	}
	return waittime1;
}
static bool cmp(const vector<int>& path1, const vector<int>& path2)
{
	return cacutime(path1) < cacutime(path2);
}

void BAWindow::BankAlgorithm(vector<vector<int>>& Need, vector<vector<int>>& allocation, vector<int>& nowR, int needid, vector<int>& apply,vector<int>& Times)
{
	QString jscode;
	dpaths.clear();
	dTimes = Times;
	vector<int> scores;
	int n = Need.size(),m = apply.size();
	for (int j = 0; j < m; j++)
	{
		if (apply[j] + allocation[needid][j] > Need[needid][j])
		{
			jscode = generateJs(1, dpaths, scores);
		}
		else if (apply[j] > nowR[j]) {
			jscode = generateJs(2, dpaths,scores);
		}
	}
	dneed.resize(n);
	for (int i = 0; i < n; i++)
	{
		dneed[i].resize(m);
		for (int j = 0; j < m; j++)
		{
			dneed[i][j] = Need[i][j] - allocation[i][j];
		}
	}
	vector<int> work = nowR;
	work = work - apply;
	allocation[needid] = allocation[needid] + apply;

	dneed[needid] = dneed[needid] - apply;
	dallocation = allocation;
	dflag = vector<int>(n, 0);
	dwork = work;
	dpaths.clear();
	dpath.resize(n);
	bankAlgorithm(0);
	if (dpaths.empty()) {
		jscode = generateJs(3, dpaths,scores);
	}
	else {

		dpaths.resize(min(10, (int)dpaths.size()));
		sort(dpaths.begin(), dpaths.end(), cmp);
		
		for (int i = 0; i < dpaths.size(); i++)
		{
			scores.push_back(cacutime(dpaths[i]));
		}
		jscode = generateJs(4, dpaths,scores);
	}
	ui.webEngineView->page()->runJavaScript(jscode);
	cout << jscode.toStdString() << endl;
}