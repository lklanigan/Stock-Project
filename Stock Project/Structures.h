#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <utility>
#include <string>
#include "csvstream.h"
#include <vector>
#include <cmath>
#include <algorithm>





using namespace std;

struct Data {
	double AdjCLose;
	double open;
	double high;
	double low;
	double close;
	double volume;
	double SMA5;
	double SMA10;
	double SMA20;
	double SMA50;
	double SMA100;
	double SMA200;
	double RSI14;
	double EMA12;
	double EMA26;
	double MACD;
	double MACD_Signal;
	double MACD_Histogram;
	double ADL;
	double AroonUP;
	double AroonDOWN;
	double AroonOsc;
};

struct Probability {
	vector<double> RSIGain;
	vector <double> RSILoss;
	vector<double> MACDGain;
	vector <double> MACDLoss;
	vector<double> MACD_SignalGain;
	vector <double> MACD_SignalLoss;
	vector<double> MACD_HistogramGain;
	vector <double> MACD_HistogramLoss;
};

