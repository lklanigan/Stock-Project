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

void RSI_GainVector(vector<Data> &data, Probability &Prob);
void MACD_GainVector(vector<Data> &data, Probability &Prob);
void MACD_Signal_GainVector(vector<Data> &data, Probability &Prob);
void MACD_Histogram_GainVector(vector<Data> &data, Probability &Prob);


void RSI_GainVector(vector<Data> &data, Probability &Prob) {
	for (int i = 35; i <= 530 && i < static_cast<int>(data.size()); i += 5) {
		if (data[i].AdjCLose < data[i + 5].AdjCLose) {
			Prob.RSIGain.push_back(data[i].RSI14);
		}
		else if (data[i].AdjCLose > data[i + 5].AdjCLose) {
			Prob.RSILoss.push_back(data[i].RSI14);
		}
	}
}

void MACD_GainVector(vector<Data> &data, Probability &Prob) {
	for (int i = 35; i <= 530 && i < static_cast<int>(data.size()); i += 5) {
		if (data[i].AdjCLose < data[i + 5].AdjCLose) {
			Prob.MACDGain.push_back(data[i].MACD);
		}
		else if (data[i].AdjCLose > data[i + 5].AdjCLose) {
			Prob.MACDLoss.push_back(data[i].MACD);
		}
	}
}

void MACD_Signal_GainVector(vector<Data> &data, Probability &Prob) {
	for (int i = 35; i <= 530 && i < static_cast<int>(data.size()); i += 5) {
		if (data[i].AdjCLose < data[i + 5].AdjCLose) {
			Prob.MACD_SignalGain.push_back(data[i].MACD_Signal);
		}
		else if (data[i].AdjCLose > data[i + 5].AdjCLose) {
			Prob.MACD_SignalLoss.push_back(data[i].MACD_Signal);
		}
	}
}

void MACD_Histogram_GainVector(vector<Data> &data, Probability &Prob) {
	for (int i = 35; i <= 530 && i < static_cast<int>(data.size()); i += 5) {
		if (data[i].AdjCLose < data[i + 5].AdjCLose) {
			Prob.MACD_HistogramGain.push_back(data[i].MACD_Histogram);
		}
		else if (data[i].AdjCLose > data[i + 5].AdjCLose) {
			Prob.MACD_HistogramLoss.push_back(data[i].MACD_Histogram);
		}
	}
}