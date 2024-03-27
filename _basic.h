#pragma once
#include<qstring.h>
#include<iostream>
#include<qtablewidget.h>
#include<sstream>
static const wchar_t* libxl_cracked_name = L"libxl";
#if defined(WIN32) || defined(WIN64)
static const wchar_t* libxl_cracked_key = L"windows-28232b0208c4ee0369ba6e68abv6v5i3";
#else
static const std::string libxl_cracked_key = "linux-i8i3ibi2i8i4iei3i9iaiei8ibx6x5i3";
#endif
using namespace std;
int randint(int l, int r);
QString N2S(int num);
int S2N(QString);
string stringFromSS(stringstream& ss);