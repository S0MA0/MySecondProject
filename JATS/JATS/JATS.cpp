#include "JATS.h"

JsonDocument::JsonDocument()
{

}

JsonDocument::JsonDocument(string d)
{
	for (int j = 0; j < d.length(); j++) {
		string d_; d_ = d[j];
		msg.append(d_.c_str());
		if (msg[j] == '}') break; //������� �� ����� ����-������� 
	}
}

interpretation JsonDocument::value(string key)
{
	int len = key.length();
	string itog;

	for (int j = 1; j < msg.length(); j++) 
		if (msg[j] == key[len - 1] && msg[j - 1] == key[len - 2] && sort(key, msg, len, j))
		{
			for (int c = 0; c < msg.length(); c++)
				if (msg[j + 4 + c] == '"') {
					for (int i = j + 4; i < c + j + 4; i++) 
						itog += msg[i];
					break;
				}
			break;
		}

	interpretation inc(itog);
	return inc;
}


bool JsonDocument::sort(string key, string msg, int alk, int j)
{ 
	if (key.length() == 2) return true; //���� �������� ����� 2, �� ����������
	if (key.length() > 2 && msg[j - 2] == key[alk - 3]) return true; //���� ���, �� ��������� ���
	return false;                                                        //��� ����������� ������
}


//----------------------------------------------interpretation
interpretation::interpretation()
{
	key = "";
}
interpretation::interpretation(string key_)
{
	key = key_;
}
interpretation::~interpretation()
{

}

void interpretation::toIntMassv(int* massv, int length_)
{
	if (key == "") return;
	if (key[key.length() - 1] != ' ')
		key += ' '; //��������� ������ �� ������

	string data; //��������� ���������
	vector<int> vec(1); //���������� ��������� � ������ (����.�������������)
	int length = key.length() + 1; //������ ������

	for (int j = 0, n = 0; j < length; j++)
	{
		if (key[j] != ' ') {
			data += key[j];
			continue;
		}
		vec[n] = atoi(data.c_str()); //��������� ����� � int
		data.clear();
		n++; //��� �� ����� (��� ����� �������� �����)
		vec.push_back(0); //����� �����
	}

	//��������� � ������
	for (int j = 0; j < vec.size() && j < length_ / sizeof(int); j++) { //length ��������� ����.��� �� �������� �������
		*massv = vec[j]; 
		massv++;
	}
}

void interpretation::toFloatMassv(float* massv, int length_)
{
	if (key == "") return;
	if (key[key.length() - 1] != ' ')
		key += " "; //��������� ������

	string data; //����� ������� ����� � ���������
	vector<float> vec(1); //���������� ��������� � ������ (����.�������������)
	int length = key.length() + 1;

	for (int j = 0; j < length; j++) //���������� ��� ����� � ������� ���� stof
		if (key[j] == '.') key[j] = ',';

	for (int j = 0, n = 0; j < length; j++)
	{
		if (key[j] != ' ') {
			data += key[j];
			continue;
		}

		vec[n] = stof(data); //��������� ����� � float
		data.clear(); //�������
		n++; //��� �� ����� (��� ����� �������� �����)
		vec.push_back(0); //����� �����
	}
	
	//��������� � ������
	for (int j = 0; j < vec.size() && j < length_ / sizeof(float); j++) { //length ��������� ����.��� �� �������� �������
		*massv = vec[j];
		massv++;
	}
}


string interpretation::toString()
{
	return key;
}

int interpretation::toInt()
{
	string nool;
	for (int j = 0; j < key.length(); j++)
		if (key[j] == ' ') key.erase(j);

	return  (key != nool) ? atoi(key.c_str()) : 0;
}

float interpretation::toFloat()
{
	string nool;

	for (int j = 0; j < key.length(); j++) //���������� ��� ����� � ������� ���� stof
		if (key[j] == '.') key[j] = ',';

	for (int j = 0; j < key.length(); j++)
		if (key[j] == ' ') key.erase(j);

	return (key != nool) ? stof(key) : 0;
}
