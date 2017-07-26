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
#include "Structures.h"
#include "Statistics.h"
#include "Probability.h"
#include "increment_vectors.h"
#include "Initialize_Vectors.h"



using namespace std;








bool Buy(vector<Data> &data, Probability &Prob, int day);

void Next(vector<Data> &data, Probability &Prob, int day);





void driver(vector<Data> &data, Probability &Prob);

int main() {
	vector<Data> data;
	Probability Prob;

	readData(data);
	calculateSMA(data);
	calculateRSI(data);
	calculateEMA(data);
	calculateMACD(data);
	calculateADL(data);
	calculateAROON(data);

	RSI_GainVector(data, Prob);
	MACD_GainVector(data, Prob);
	MACD_Signal_GainVector(data, Prob);
	MACD_Histogram_GainVector(data, Prob);

	driver(data, Prob);


	return 0;
}








bool Buy(vector<Data> &data, Probability &Prob, int day) {
	cout << Prob.MACDGain[0] << endl;
	if(MACD_Histo_Slope(data, day) && RSI(data, day)){
		return true;
	}
	return false;
}



void Next(vector<Data> &data, Probability &Prob, int day) {
	RSI_GainVector_Next(data, Prob, day);
	MACD_GainVector_Next(data, Prob, day);
	MACD_Signal_GainVector_Next(data, Prob, day);
	MACD_Histogram_GainVector_Next(data, Prob, day);
}

void driver(vector<Data> &data, Probability &Prob) {
	int correct_Buy = 0;
	int incorrect_Buy = 0;
	int correct_No_Buy = 0;
	int incorrect_No_Buy = 0;
	int total = 0;

	







	bool buy = false;
	for (int k = 535; k < static_cast<int>(data.size()) - 5; k += 5) {
		Next(data, Prob, k);

		buy = Buy(data, Prob, k);
		if (buy == true && (data[k].AdjCLose < data[k + 5].AdjCLose)) {
			++correct_Buy;
		}
		if (buy == true && (data[k].AdjCLose > data[k + 5].AdjCLose)) {
			++incorrect_Buy;
		}
		if (buy == false && (data[k].AdjCLose < data[k + 5].AdjCLose)) {
			++incorrect_No_Buy;
		}
		if (buy == false && (data[k].AdjCLose > data[k + 5].AdjCLose)) {
			++correct_No_Buy;
		}
		++total;
	}

	cout << "RSIGain.size() = " << Prob.RSIGain.size() << endl;
	cout << "RSILoss.size() = " << Prob.RSILoss.size() << endl;

	cout << "correct_Buy = " << correct_Buy << endl;
	cout << "incorrect_Buy = " << incorrect_Buy << endl << endl;
	
	cout << "correct_No_Buy = " << correct_No_Buy << endl;
	cout << "incorrect_No_Buy = " << incorrect_No_Buy << endl << endl;

	cout << "total = " << total << endl << endl;

	auto size = data.size() - 1;
	cout << "data[size].SMA5 = " << data[size].SMA5 << endl;
	cout << "data[size].SMA10 = " << data[size].SMA10 << endl;
	cout << "data[size].SMA20 = " << data[size].SMA20 << endl;
	cout << "data[size].SMA50 = " << data[size].SMA50 << endl;
	cout << "data[size].SMA100 = " << data[size].SMA100 << endl;
	cout << "data[size].SMA200 = " << data[size].SMA200 << endl;
	cout << "data[size].RSI14 = " << data[size].RSI14 << endl;
	cout << "data[size].EMA12 = " << data[size].EMA12 << endl;
	cout << "data[size].EMA26 = " << data[size].EMA26 << endl;
	cout << "data[size].MACD = " << data[size].MACD << endl;
	cout << "data[size].MACD_Signal = " << data[size].MACD_Signal << endl;
	cout << "data[size].MACD_Histogram = " << data[size].MACD_Histogram << endl;
	cout << "data[size].ADL = " << data[size].ADL << endl;
	cout << "data[size].AroonUP = " << data[size].AroonUP << endl;
	cout << "data[size].AroonDown = " << data[size].AroonDOWN << endl;
	cout << "data[size].AroonOsc = " << data[size].AroonOsc << endl;
}
