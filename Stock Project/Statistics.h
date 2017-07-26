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


void readData(vector<Data> &data);
void calculateSMA(vector<Data> &data);
void calculateRSI(vector<Data> &data);
void calculateEMA(vector<Data> &data);
void calculateMACD(vector<Data> &data);
void calculateADL(vector<Data> &data);
void calculateAROON(vector<Data> &data);


void readData(vector<Data> &data) {
	string filename;
	filename = "XOM.csv";

	cout << "Reading file " << filename << '\n';

	vector<double> AdjClose;
	vector<double> open;
	vector<double> high;
	vector<double> low;
	vector<double> close;
	vector<double> volume;

	csvstream csvin(filename);
	csvstream::row_type row;
	string content = "";
	while (csvin >> row) {
		for (auto col : row) {
			if (col.first == "Open") {
				open.push_back(stod(col.second));
			}
			else if (col.first == "High") {
				high.push_back(stod(col.second));
			}
			else if (col.first == "Low") {
				low.push_back(stod(col.second));
			}
			else if (col.first == "Close") {
				close.push_back(stod(col.second));
			}
			else if (col.first == "Volume") {
				volume.push_back(stod(col.second));
			}
			else if (col.first == "Adj Close") {
				//cout << col.second << endl;
				AdjClose.push_back(stod(col.second));
			}

		}
	}

	data.resize(AdjClose.size());
	for (int k = 0; k < static_cast<int>(AdjClose.size()); k++) {
		data[static_cast<int>(AdjClose.size()) - k - 1].AdjCLose = close[k];
		data[static_cast<int>(open.size()) - k - 1].open = open[k];
		data[static_cast<int>(high.size()) - k - 1].high = high[k];
		data[static_cast<int>(low.size()) - k - 1].low = low[k];
		data[static_cast<int>(close.size()) - k - 1].close = close[k];
		data[static_cast<int>(volume.size()) - k - 1].volume = volume[k];
	}

	cout << data[0].AdjCLose << endl;
}

void calculateSMA(vector<Data> &data) {
	//Set SMA values that cannot be calculated as 0
	

	double sum = 0.0;
	//calculate SMA5
	for (int i = 4; i < static_cast<int>(data.size()); i++) {
		sum = 0.0;
		for (int k = i - 4; k <= i; k++) {
			sum = sum + data[k].AdjCLose;
		}
		data[i].SMA5 = sum / 5.0;
	}
	//calculate SMA10
	for (int i = 9; i < static_cast<int>(data.size()); i++) {
		sum = 0.0;
		for (int k = i - 9; k <= i; k++) {
			sum = sum + data[k].AdjCLose;
		}
		data[i].SMA10 = sum / 10.0;
	}
	//calculate SMA20
	for (int i = 19; i < static_cast<int>(data.size()); i++) {
		sum = 0.0;
		for (int k = i - 19; k <= i; k++) {
			sum += data[k].AdjCLose;
		}
		data[i].SMA20 = sum / 20.0;
	}
	//calculate SMA50
	for (int i = 49; i < static_cast<int>(data.size()); i++) {
		sum = 0.0;
		for (int k = i - 49; k <= i; k++) {
			sum += data[k].AdjCLose;
		}
		data[i].SMA50 = sum / 50.0;
	}
	//calculate SMA100
	for (int i = 99; i < static_cast<int>(data.size()); i++) {
		sum = 0.0;
		for (int k = i - 99; k <= i; k++) {
			sum += data[k].AdjCLose;
		}
		data[i].SMA100 = sum / 100.0;
	}
	//calculate SMA200
	for (int i = 199; i < static_cast<int>(data.size()); i++) {
		sum = 0.0;
		for (int k = i - 199; k <= i; k++) {
			sum += data[k].AdjCLose;
		}
		data[i].SMA200 = sum / 200.0;
	}
}

void calculateRSI(vector<Data> &data) {
	double AVG_gain = 0;
	double GainSum = 0;
	double AVG_loss = 0;
	double LossSum = 0;
	double RS = 0;
	//calculate first RSI
	for (int i = 1; i < 15 && i < static_cast<int>(data.size()); i++) {
		if (data[i].AdjCLose > data[i - 1].AdjCLose) {
			GainSum += abs(data[i].AdjCLose - data[i - 1].AdjCLose);
		}
		if (data[i].AdjCLose < data[i - 1].AdjCLose) {
			LossSum += abs(data[i].AdjCLose - data[i - 1].AdjCLose);
		}
	}

	AVG_gain = GainSum / 14;
	AVG_loss = LossSum / 14;

	RS = AVG_gain / AVG_loss;

	data[14].RSI14 = (100 - (100 / (1 + RS)));

	//Calculare RSI for remaining daya
	for (int i = 15; i < static_cast<int>(data.size()); i++) {
		if (data[i].AdjCLose > data[i - 1].AdjCLose) {
			GainSum = (AVG_gain * 13) + abs(data[i].AdjCLose - data[i - 1].AdjCLose);
			LossSum = (AVG_loss * 13);
		}
		else if (data[i].AdjCLose < data[i - 1].AdjCLose) {
			LossSum = (AVG_loss * 13) + abs(data[i].AdjCLose - data[i - 1].AdjCLose);
			GainSum = (AVG_gain * 13);
		}
		AVG_loss = LossSum / 14;
		AVG_gain = GainSum / 14;
		RS = AVG_gain / AVG_loss;
		data[i].RSI14 = (100 - (100 / (1 + RS)));
	}
}

void calculateEMA(vector<Data> &data) {
	

	double sum = 0.0;
	//Calculate SMA12 for day 12
	for (int k = 0; k <= 11; k++) {
		sum  = sum + data[k].AdjCLose;
	}
	data[11].EMA12 = sum / 12.0;
	
	//calculate SMA26
	sum = 0.0;
	for (int k = 0; k <= 25; k++) {
		sum += data[k].AdjCLose;
	}
	data[25].EMA26 = sum / 26.0;
	
	//Calculate all EMA12

	double Mult12 = (2.0 / (12.0 + 1.0));
	for (int i = 12; i < static_cast<int>(data.size()); i++) {
		data[i].EMA12 = ((data[i].AdjCLose - data[i - 1].EMA12) * Mult12) + data[i - 1].EMA12;
		
	}
	//Calculate all EMA26
	double Mult26 = (2.0 / (26.0 + 1.0));
	for (int i = 26; i < static_cast<int>(data.size()); i++) {
		data[i].EMA26 = ((data[i].AdjCLose - data[i - 1].EMA26) * Mult26) + data[i - 1].EMA26;
		
	}

}

void calculateMACD(vector<Data> &data) {
	//Calculate MACD line
	for (int i = 25; i < static_cast<int>(data.size()); i++) {
		data[i].MACD = data[i].EMA12 - data[i].EMA26;
	}

	//Calculate Signal Line, 9-day EMA of MACD
	double sum = 0.0;
	for (int k = 25; k < 34; k++) {
		sum += data[k].MACD;
	}
	data[33].MACD_Signal = sum / 9.0;

	double Mult9 = (2.0 / (9.0 + 1.0));
	for (int i = 34; i < static_cast<int>(data.size()); i++) {
		data[i].MACD_Signal = (data[i].MACD - data[i - 1].MACD_Signal) * Mult9 + data[i - 1].MACD_Signal;
	}

	//Calculate MACD Histogram
	for (int i = 33; i < static_cast<int>(data.size()); i++) {
		data[i].MACD_Histogram = data[i].MACD - data[i].MACD_Signal;
	}
}

void calculateADL(vector<Data> &data) {
	double MFM = ((data[0].close - data[0].low) - (data[0].high - data[0].close)) / (data[0].high - data[0].low);
	double MFV = MFM * data[0].volume;
	data[0].ADL = MFV;

	for (int i = 1; i < static_cast<int>(data.size()); i++) {
		MFM = ((data[i].close - data[i].low) - (data[i].high - data[i].close)) / (data[i].high - data[i].low);
		MFV = MFM * data[i].volume;
		data[i].ADL = data[i - 1].ADL + MFV;
	}
}

void calculateAROON(vector<Data> &data) {
	double high = data[0].AdjCLose;
	int highDay = 0;
	int sinceHigh = 0;
	double low = data[0].AdjCLose;
	int lowDay = 0;
	int sinceLow = 0;

	for (int i = 1; i <= 24; i++) {
		if (data[i].AdjCLose > high) {
			high = data[i].AdjCLose;
			highDay = i;
		}
		if (data[i].AdjCLose < low) {
			low = data[i].AdjCLose;
			lowDay = i;
		}
	}
	sinceHigh = 24 - highDay;
	sinceLow = 24 - lowDay;
	data[24].AroonUP = ((25.0 - static_cast<double>(sinceHigh)) / 25.0) * 100.0;
	data[24].AroonDOWN = ((25.0 - static_cast<double>(sinceLow)) / 25.0) * 100.0;
	data[24].AroonOsc = data[24].AroonUP - data[24].AroonDOWN;
	for (int k = 25; k < static_cast<int>(data.size()); k++) {
		high = data[k].AdjCLose;
		highDay = 0;
		sinceHigh = 0;
		low = data[k].AdjCLose;
		lowDay = 0;
		sinceLow = 0;
		for (int i = k - 23; i <= k; i++) {
			if (data[i].AdjCLose > high) {
				high = data[i].AdjCLose;
				highDay = i;
			}
			if (data[i].AdjCLose < low) {
				low = data[i].AdjCLose;
				lowDay = i;
			}
		}
		sinceHigh = k - highDay;
		sinceLow = k - lowDay;
		data[k].AroonUP = ((25.0 - static_cast<double>(sinceHigh)) / 25.0) * 100.0;
		data[k].AroonDOWN = ((25.0 - static_cast<double>(sinceLow)) / 25.0) * 100.0;
		data[k].AroonOsc = data[k].AroonUP - data[k].AroonDOWN;
	}
}
