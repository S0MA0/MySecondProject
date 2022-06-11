#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

class interpretation
{
private:
	string key;
public:
	interpretation();
	interpretation(string key_);
	~interpretation();

	void toIntMassv(int* massv, int length); //massv - ������ ������� �������
	void toFloatMassv(float* massv, int length);

	string toString(); //������ ��� string
	int toInt(); //������ ��� int
	float toFloat(); //������ ��� float
};

class JsonDocument
{
private:
	string msg;
public:
	JsonDocument();
	JsonDocument(string d);

	interpretation value(string key);
private:
	bool sort(string key, string msg, int alk, int j); //���������� 

};