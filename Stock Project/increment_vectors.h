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

void RSI_GainVector_Next(vector<Data> &data, Probability &Prob, int day);
void MACD_GainVector_Next(vector<Data> &data, Probability &Prob, int day);
void MACD_Signal_GainVector_Next(vector<Data> &data, Probability &Prob, int day);
void MACD_Histogram_GainVector_Next(vector<Data> &data, Probability &Prob, int day);

void RSI_GainVector_Next(vector<Data> &data, Probability &Prob, int day) {

	if (data[day].AdjCLose < data[day - 5].AdjCLose) {
		Prob.RSIGain.push_back(data[day].RSI14);
	}
	else if (data[day].AdjCLose > data[day - 5].AdjCLose) {
		Prob.RSILoss.push_back(data[day].RSI14);
	}

}

void MACD_GainVector_Next(vector<Data> &data, Probability &Prob, int day) {
	if (data[day].AdjCLose < data[day - 5].AdjCLose) {
		Prob.MACDGain.push_back(data[day].MACD);
	}
	else if (data[day].AdjCLose > data[day - 5].AdjCLose) {
		Prob.MACDLoss.push_back(data[day].MACD);
	}
}

void MACD_Signal_GainVector_Next(vector<Data> &data, Probability &Prob, int day) {
	if (data[day].AdjCLose < data[day - 5].AdjCLose) {
		Prob.MACD_SignalGain.push_back(data[day].MACD_Signal);
	}
	else if (data[day].AdjCLose > data[day - 5].AdjCLose) {
		Prob.MACD_SignalLoss.push_back(data[day].MACD_Signal);
	}
}

void MACD_Histogram_GainVector_Next(vector<Data> &data, Probability &Prob, int day) {
	if (data[day].AdjCLose < data[day - 5].AdjCLose) {
		Prob.MACD_HistogramGain.push_back(data[day].MACD_Histogram);
	}
	else if (data[day].AdjCLose > data[day - 5].AdjCLose) {
		Prob.MACD_HistogramLoss.push_back(data[day].MACD_Histogram);
	}
}

