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


double Prob_RSI(vector<Data> &data, Probability &Prob, int day);
double Prob_MACD(vector<Data> &data, Probability &Prob, int day);
double Prob_MACD_Signal(vector<Data> &data, Probability &Prob, int day);
double Prob_MACD_Hisogram(vector<Data> &data, Probability &Prob, int day);

bool MACD_Histo_Slope(vector<Data> &data,  int day);
bool RSI(vector<Data> &data, int day);


double Prob_RSI(vector<Data> &data, Probability &Prob, int day) {
	double RSI = data[day].RSI14;

	sort(Prob.RSIGain.begin(), Prob.RSIGain.end());
	sort(Prob.RSILoss.begin(), Prob.RSILoss.end());

	double gain;
	gain = static_cast<double>((lower_bound(Prob.RSIGain.begin(), Prob.RSIGain.end(), RSI) - Prob.RSIGain.begin())) / static_cast<double>(Prob.RSIGain.size());

	double loss;
	loss = static_cast<double>((lower_bound(Prob.RSILoss.begin(), Prob.RSILoss.end(), RSI) - Prob.RSILoss.begin())) / static_cast<double>(Prob.RSILoss.size());

	

	double output = gain - loss;

	return output;

}

double Prob_MACD(vector<Data> &data, Probability &Prob, int day) {
	double MACD = data[day].MACD;

	sort(Prob.MACDGain.begin(), Prob.MACDGain.end());
	sort(Prob.MACDLoss.begin(), Prob.MACDLoss.end());

	double gain;
	gain = static_cast<double>((lower_bound(Prob.MACDGain.begin(), Prob.MACDGain.end(), MACD) - Prob.MACDGain.begin())) / static_cast<double>(Prob.MACDGain.size());

	double loss;
	loss = static_cast<double>((lower_bound(Prob.MACDLoss.begin(), Prob.MACDLoss.end(), MACD) - Prob.MACDLoss.begin())) / static_cast<double>(Prob.MACDLoss.size());

	double output = gain - loss;

	return output;
}

double Prob_MACD_Signal(vector<Data> &data, Probability &Prob, int day) {
	double MACD_Signal = data[day].MACD_Signal;

	sort(Prob.MACD_SignalGain.begin(), Prob.MACD_SignalGain.end());
	sort(Prob.MACD_SignalLoss.begin(), Prob.MACD_SignalLoss.end());

	double gain;
	gain = static_cast<double>((lower_bound(Prob.MACD_SignalGain.begin(), Prob.MACD_SignalGain.end(), MACD_Signal) - Prob.MACD_SignalGain.begin())) / static_cast<double>(Prob.MACD_SignalGain.size());

	double loss;
	loss = static_cast<double>((lower_bound(Prob.MACD_SignalLoss.begin(), Prob.MACD_SignalLoss.end(), MACD_Signal) - Prob.MACD_SignalLoss.begin())) / static_cast<double>(Prob.MACD_SignalLoss.size());

	double output = gain - loss;

	return output;
}

double Prob_MACD_Hisogram(vector<Data> &data, Probability &Prob, int day) {
	double MACD_Histogram = data[day].MACD_Histogram;

	sort(Prob.MACD_HistogramGain.begin(), Prob.MACD_HistogramGain.end());
	sort(Prob.MACD_HistogramLoss.begin(), Prob.MACD_HistogramLoss.end());

	double gain;
	gain = static_cast<double>((lower_bound(Prob.MACD_HistogramGain.begin(), Prob.MACD_HistogramGain.end(), MACD_Histogram) - Prob.MACD_HistogramGain.begin())) / static_cast<double>(Prob.MACD_HistogramGain.size());

	double loss;
	loss = static_cast<double>((lower_bound(Prob.MACD_HistogramLoss.begin(), Prob.MACD_HistogramLoss.end(), MACD_Histogram) - Prob.MACD_HistogramLoss.begin())) / static_cast<double>(Prob.MACD_HistogramLoss.size());

	double output = gain - loss;

	return output;
}

bool MACD_Histo_Slope(vector<Data> &data, int day) {
	int count = 0;
	double rise1 = 0;
	double rise2 = 0;
	double rise3 = 0;

	double run1 = 2;
	double run2 = 4;
	double run3 = 8;

	rise1 = data[day].MACD_Histogram - data[day - 2].MACD_Histogram;
	rise2 = data[day].MACD_Histogram - data[day - 4].MACD_Histogram;
	rise3 = data[day].MACD_Histogram - data[day - 8].MACD_Histogram;

	double slope1 = rise1 / run1;
	double slope2 = rise2 / run2;
	double slope3 = rise3 / run3;

	cout << "data[day].EMA12 = " << data[day].EMA12 << endl;
	cout << "data[day].EMA26 = " << data[day].EMA26 << endl;
	cout << "data[day].MACD = " << data[day].MACD << endl;
	cout << "data[day].MACD_Signal = " << data[day].MACD_Signal << endl;
	cout << "data[day].MACD_Histogram = " << data[day].MACD_Histogram << endl;
	cout << "rise1 = " << rise1 << endl;
	cout << "run1 = " << run1 << endl;
	cout << "slope1 = " << slope1 << endl;



	if (slope1 > 0) {
		++count;
	}
	if (slope2 > 0) {
		++count;
	}
	if (slope3 > 0) {
		++count;
	}

	if (count >= 2) {
		return true;
	}

	return false;
}
bool RSI(vector<Data> &data, int day) {
	if (data[day].RSI14 < 50) {
		return true;
	}
	return false;
}
