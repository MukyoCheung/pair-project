#include <fstream>     
#include <iostream>     
#include<algorithm>
#include<string>
#include<queue>
#include"CountChar.h"
#include"CountLines.h"
#include"CountWordnumber.h"
#include"TenFrequency.h"
#include"phraseFrequency.h"
using namespace std;
extern vector<pair<string, int>> word,phrases;
extern map<string, int> mCountMap ,phraseMap;
extern queue<string> wordque;
extern queue<string>charque;
extern int sum2;
int CountChar(string mInputFileName) //�����ַ����͵�����
{
	ifstream ifs(mInputFileName);
	char charTemp;
	string wordtemp;
	int sum = 0;
	int state = 0;
	while ((charTemp = ifs.get()) != EOF)
	{
		sum++;//�����ַ���
		if (charTemp >= 65 && charTemp <= 90)
			charTemp = charTemp + 32; //��дת��ΪСд
		switch (state)
		{
		case 0:
			if (charTemp >= 97 && charTemp <= 122) {
				wordtemp = wordtemp + charTemp;
				state = 1;
			}
			break;
		case 1:
			if (charTemp >= 97 && charTemp <= 122) {
				wordtemp = wordtemp + charTemp;
				state = 2;
			}
			else
			{
				state = 0;
				wordtemp = "";
			}
			break;
		case 2:
			if (charTemp >= 97 && charTemp <= 122) {
				wordtemp = wordtemp + charTemp;
				state = 3;
			}
			else
			{
				state = 0;
				wordtemp = "";
			}
			break;
		case 3:
			if (charTemp >= 97 && charTemp <= 122) {
				wordtemp = wordtemp + charTemp;
				state = 4;
			}
			else
			{
				state = 0;
				wordtemp = "";
			}
			break;
		case 4:
			if (charTemp >= 97 && charTemp <= 122 || (charTemp >= '0'&&charTemp <= '9')) {
				wordtemp = wordtemp + charTemp;
			}
			else
			{
				sum2++;
				state = 0;
				wordtemp = "";
			}
			break;
		}
	}
	if (state == 4) {
		sum2++;
	}
	ifs.close();
	ifs.clear();
	//ifs.seekg(0);
	return sum;
}
int CountLines(string mInputFileName)
{
	ifstream ifs(mInputFileName);
	int lines = 0;
	int line = 0;
	string str;
	while (!ifs.eof()) 
	{
		getline(ifs, str);
		int len = 0;
		for (unsigned int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' '&&str[i] != '\t')//�հ���
				len++;
		}
		if (len > 0)
		{
			lines++;
		}
	}
	ifs.close();
	ifs.clear();
	ifs.seekg(0);
	return lines;
}
void CountWordnumber(string mInputFileName,int weight)//�����ʶ�Ӧ��Ƶ�ʼ�¼��������Ҫ�ܵ�������
{

	ifstream ifs(mInputFileName);
	string str;
	int lines = 0;
	while (getline(ifs, str)) //��ԭ��ҳ���Թ۲쵽��title��һ�У�abstract��һ�У�
	{
		lines++;
		if (lines % 5 == 2) //title��
		{
			//cout << "lines % 5 == 2��һ����:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				if (charTemp >= 65 && charTemp <= 90)
					charTemp = charTemp + 32; //��дת��ΪСд
				switch (state)
				{
				case 0:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 1;
					}
					break;
				case 1:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 2;
					}
					else
					{
						state = 0;
						wordtemp = "";
					}
					break;
				case 2:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 3;
					}
					else
					{
						state = 0;
						wordtemp = "";
					}
					break;
				case 3:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 4;
					}
					else
					{
						state = 0;
						wordtemp = "";
					}
					break;
				case 4:
					if (charTemp >= 97 && charTemp <= 122 || (charTemp >= '0'&&charTemp <= '9')) {
						wordtemp = wordtemp + charTemp;
					}
					else
					{
						if (weight == 1) {//��Ȩ��
							mCountMap[wordtemp] = mCountMap[wordtemp] + 10;
						}
						else mCountMap[wordtemp]++;
						state = 0;
						wordtemp = "";
					}
					break;
				}
			}
			if (state == 4) {
				if (weight == 1) {//��Ȩ��
					mCountMap[wordtemp] = mCountMap[wordtemp] + 10;
				}
				else mCountMap[wordtemp]++;
			}
			mCountMap["title"]--;
		}
		
		if (lines % 5 == 3) //abstract��
		{
			//cout << "lines % 5 == 3��һ����:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				if (charTemp >= 65 && charTemp <= 90)
					charTemp = charTemp + 32; //��дת��ΪСд
				switch (state)
				{
				case 0:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 1;
					}
					break;
				case 1:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 2;
					}
					else
					{
						state = 0;
						wordtemp = "";
					}
					break;
				case 2:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 3;
					}
					else
					{
						state = 0;
						wordtemp = "";
					}
					break;
				case 3:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 4;
					}
					else
					{
						state = 0;
						wordtemp = "";
					}
					break;
				case 4:
					if (charTemp >= 97 && charTemp <= 122 || (charTemp >= '0'&&charTemp <= '9')) {
						wordtemp = wordtemp + charTemp;
					}
					else
					{
						if (weight == 1) {//��Ȩ��
							mCountMap[wordtemp] = mCountMap[wordtemp] + 10;
						}
						else mCountMap[wordtemp]++;
						state = 0;
						wordtemp = "";
					}
					break;
				}
			}
			if (state == 4) {
				if (weight == 1) {//��Ȩ��
					mCountMap[wordtemp] = mCountMap[wordtemp] + 10;
				}
				else mCountMap[wordtemp]++;
			}
			mCountMap["abstract"]--;
		}

	}
	ifs.close();
	ifs.clear();
	ifs.seekg(0);
	/*int sum = 0;
	for (map<string, int>::iterator iter = titleMap.begin(); iter != titleMap.end(); iter++) {
		sum = sum + iter->second;
	}
	//cout << "title�й��У�" <<sum<< endl;

	for (map<string, int>::iterator iter = mCountMap.begin(); iter != mCountMap.end(); iter++) {
		sum = sum + iter->second;
	}
	//cout << "ab�й��У�" << sum << endl;
	
	return sum;*/
}
void TenFrequency(int n)
{
	for (map<string, int>::iterator iter = mCountMap.begin(); iter != mCountMap.end(); iter++) {
		word.push_back(pair<string, int>(iter->first, iter->second));
	}
	if (n < 0)
		n = 10;
	int size = n;
	if (word.size() < size) {
		size = word.size();
	}
	vector<pair<string, int>>::iterator vit;
	for (int i = 0; i < size; i++) {
		pair<string, int> max = word[i];
		int pos, flag=i;
		for (vit = word.begin() + i,pos = i; vit != word.end(); vit++,pos++) {
			if (vit->second > max.second) { //�ı�max��ֵ
				max.first = vit->first;
				max.second = vit->second;
				flag = pos;
			};
		}
		swap(word[i], word[flag]);
	}
	//vector<pair<string, int>>::iterator vit;
	/*for (vit = word.begin(); vit != word.begin() + size; vit++) {
		cout << "<" << vit->first << ">:" << " " << vit->second << endl;
	}*/
}

void CountPhrase(string mInputFileName, int m,int weight)//ͳ�ƴ���,���ҽ����鰴���ܵ�Ȩ�ؼ�¼
{
	ifstream ifs(mInputFileName);
	string str;
	int lines = 0;
	while (getline(ifs, str)) //��ԭ��ҳ���Թ۲쵽��title��һ�У�abstract��һ�У�
	{
		lines++;

		//if(position(str)==1)
		//if(position(str)==2)
		//else 
		if (lines % 5 == 2) //title��
		{
			//cout << "lines % 5 == 2��һ����:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				//if (charTemp == ' ') cout << "lines % 5 == 2�ո�ĵ�ǰλ��Ϊ��" << i << endl;
				/*----------------------------���ڵ��ʵĲ���----------------*/
				if (charTemp >= 65 && charTemp <= 90) 
					charTemp = charTemp + 32; //��дת��ΪСд
				switch (state)
				{
				case 0:
					if (charTemp >= 97 && charTemp <= 122) {//��ĸ
						wordtemp = wordtemp + charTemp;
						state = 1;
						if (i != 0&&i!=6&&i!=7) {
							charque.push(chartmp);
							chartmp.clear();//���
						}
					}
					if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//�Ƿָ���
					{
						if (i != 5 && i != 6 && flag == 1) //���Ǳ����:����֮ǰҪ���ֹ����ʲſ�ʼ����
							chartmp = chartmp + charTemp;
					}
					///�����������ֻ�����ĸ��ʱ��ͽ�chartempѹջ
					//������ĸ��ʱ��Ž���ѹջ���������ֵ�ʱ��ȫ�����,��state=0��״̬�£����������ֵ�ʱ��Ҫ�������������
					/*if (charTemp >= 97 && charTemp <= 122&&i!=0) {//���Ǳ���
						charque.push(chartmp);
						chartmp = "";//���
					}*/
					if ((charTemp >= '0'&&charTemp <= '9')) {
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
					}
					break;
				case 1:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 2;
					}
					else
					{//�м䷢�������ȫ�����
						state = 0;
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
					}
					break;
				case 2:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 3;
					}
					else
					{
						state = 0;
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
					}
					break;
				case 3:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 4;
					}
					else
					{
						state = 0;
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
					}
					break;
				case 4:
					if (charTemp >= 97 && charTemp <= 122 || (charTemp >= '0'&&charTemp <= '9')) {
						wordtemp = wordtemp + charTemp;
					}
					else//���ʽ�����
					{
						if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//�Ƿָ����Ǿͱ�������,���Ҳ����ǿ�ͷ�ĵ���
						{
							if (i != 5) {
								chartmp = chartmp + charTemp;
							}
							
						}
						if (wordtemp != "title"&&i != 5)//���ǿ�ͷ��title
						{
							//�����ʷŽ�queue��
							wordque.push(wordtemp);
							flag = 1;//�й�����

						}
						if (wordque.size() == m)//�Ķ������ˣ��Ǿ��Ǵ��鵥����
						{
							string phrase;
							if (charque.front() == "")
								charque.pop();
							//����Ӧ�ĵ��ʺʹ���浽�����map��ȥ�����ҽ�queue�ײ��ߵ�
							//queue���ṩԪ�ص�������ʣ�������ֻ�ܽ�Ԫ�س�����������У�
							string x, y;//���ڱ�����ʱ�ĵ��ʺͷָ���
							for (int k = 0; k < m - 1; k++) {
								x = wordque.front(); //m
								y = charque.front();//m-1��
								phrase = phrase + x + y;
								wordque.pop();
								charque.pop();
								wordque.push(x);
								charque.push(y);
							}
							x = wordque.front(); //��m������
							//y = charque.front();
							phrase = phrase + x;
							wordque.pop();
							wordque.push(x);
							//�ϲ���֮������queue����Ԫ�ض�ȥ��
							wordque.pop();
							charque.pop();
							if (weight == 1)//��Ȩ��
							{
								phraseMap[phrase] = phraseMap[phrase] + 10;
							}
							else phraseMap[phrase]++;
							//phrase = "";
							//if (phrase == "visualquestion answering") cout << "visualquestion answering �����ڵ�" << lines << endl;
							//if (phrase == "visual question answering") cout << "visual question answering �����ڵ�" << lines << endl;
						}
						state = 0;
						wordtemp = "";
					}
					break;
				}

				//���ÿ�ֵ�chartmp��wordtemp
				/*cout << "��ǰ������->" << i << endl;
				cout << "wordtemp��->" << wordtemp <<" " << "chartemp��->" << chartmp <<"<-"<< endl;
				if (!wordque.empty()) {
					cout << "wordque�е���Ԫ����" << wordque.front() << endl;
				}
				if (!charque.empty()) {
					cout << "��ǰchartemp��size��" << charque.size() << endl;
					cout << " charque�е�Ԫ����------->" << charque.front() << "<-------" << endl;
				}*/
				
			}
			if (state == 4) {//��������������е���
				wordque.push(wordtemp);
				//�������������ɴ���Ļ�
				if (wordque.size() == m)//�Ķ������ˣ��Ǿ��Ǵ��鵥����
				{
					//����Ӧ�ĵ��ʺʹ���浽�����map��ȥ�����ҽ�queue�ײ��ߵ�
					//queue���ṩԪ�ص�������ʣ�������ֻ�ܽ�Ԫ�س�����������У�
					string x, y;//���ڱ�����ʱ�ĵ��ʺͷָ���
					string phrase;
					if (charque.front() == "")
						charque.pop();
					for (int k = 0; k < m - 1; k++) {
						x = wordque.front(); //m
						y = charque.front();//m-1��
						phrase = phrase + x + y;
						wordque.pop();
						charque.pop();
						//wordque.push(x);
						//charque.push(y);
					}
					x = wordque.front(); //��m������
					//y = charque.front();
					phrase = phrase + x;
					wordque.pop();
					wordque.push(x);
					if (weight == 1)//��Ȩ��
					{
						phraseMap[phrase] = phraseMap[phrase] + 10;
					}
					else phraseMap[phrase]++;
					//if (phrase == "visualquestion answering") cout << "visualquestion answering �����ڵ�" << lines << endl;
					//if (phrase == "visual question answering") cout << "visual question answering �����ڵ�" << lines << endl;
				}
			}
			
			//ÿ��abstract����֮�󶼽��������
			while (!wordque.empty()) wordque.pop();
			while (!charque.empty()) charque.pop();
		}
		if (lines % 5 == 3) //abstract��
		{
			//cout << "lines % 5 == 2��һ����:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				//if (charTemp == ' ') cout << "lines % 5 == 2�ո�ĵ�ǰλ��Ϊ��" << i << endl;
				/*----------------------------���ڵ��ʵĲ���----------------*/
				if (charTemp >= 65 && charTemp <= 90)
					charTemp = charTemp + 32; //��дת��ΪСд
				switch (state)
				{
				case 0:
					if (charTemp >= 97 && charTemp <= 122) {//��ĸ
						wordtemp = wordtemp + charTemp;
						state = 1;
						if (i != 0 && i != 9 && i != 10) {
							charque.push(chartmp);
							chartmp.clear();//���
						}
					}
					if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//�Ƿָ���
					{
						if (i != 8 && i != 9 && flag == 1) //���Ǳ����:����֮ǰҪ���ֹ����ʲſ�ʼ����
							chartmp = chartmp + charTemp;
					}
					///�����������ֻ�����ĸ��ʱ��ͽ�chartempѹջ
					//������ĸ��ʱ��Ž���ѹջ���������ֵ�ʱ��ȫ�����,��state=0��״̬�£����������ֵ�ʱ��Ҫ�������������
					/*if (charTemp >= 97 && charTemp <= 122&&i!=0) {//���Ǳ���
					charque.push(chartmp);
					chartmp = "";//���
					}*/
					if ((charTemp >= '0'&&charTemp <= '9')) {
						while (!wordque.empty()) wordque.pop();//�����к͵�ǰҪ���ȥ��Ԫ�ض����
						while (!charque.empty()) charque.pop();
					
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						
					}
					break;
				case 1:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 2;
					}
					else
					{//�м䷢�������ȫ�����
						state = 0;
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
					}
					break;
				case 2:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 3;
					}
					else
					{
						state = 0;
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
					}
					break;
				case 3:
					if (charTemp >= 97 && charTemp <= 122) {
						wordtemp = wordtemp + charTemp;
						state = 4;
					}
					else
					{
						state = 0;
						flag = 0;
						chartmp.clear();
						wordtemp.clear();
						while (!wordque.empty()) wordque.pop();
						while (!charque.empty()) charque.pop();
					}
					break;
				case 4:
					if (charTemp >= 97 && charTemp <= 122 || (charTemp >= '0'&&charTemp <= '9')) {
						wordtemp = wordtemp + charTemp;
					}
					else//���ʽ�����
					{
						if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//�Ƿָ����Ǿͱ�������,���Ҳ����ǿ�ͷ�ĵ���
						{
							if (i != 8) {
								chartmp = chartmp + charTemp;
							}

						}
						if (wordtemp != "abstract"&&i != 8)//���ǿ�ͷ��title
						{
							//�����ʷŽ�queue��
							wordque.push(wordtemp);
							flag = 1;//�й�����

						}
						if (wordque.size() == m)//�Ķ������ˣ��Ǿ��Ǵ��鵥����
						{
							string phrase;
							//����Ӧ�ĵ��ʺʹ���浽�����map��ȥ�����ҽ�queue�ײ��ߵ�
							//queue���ṩԪ�ص�������ʣ�������ֻ�ܽ�Ԫ�س�����������У�
							string x, y;//���ڱ�����ʱ�ĵ��ʺͷָ���
							//���ڶ��׿�����""�����ķָ����������Ȱ���������
							if(charque.front()=="")
								charque.pop();
							for (int k = 0; k < m - 1; k++) {//��ʱֻҪ�зָ����϶��Ͳ��ǡ���

								x = wordque.front(); //m
								y = charque.front();//m-1��
								phrase = phrase + x + y;
								wordque.pop();
								charque.pop();
								wordque.push(x);
								charque.push(y);
							}
							x = wordque.front(); //��m������
							phrase = phrase + x;
							wordque.pop();
							wordque.push(x);
							//�ϲ���֮������queue����Ԫ�ض�ȥ��
							wordque.pop();
							charque.pop();
							phraseMap[phrase]++;
							//if (phrase == "visualquestion answering") cout << "visualquestion answering �����ڵ�" << lines << endl;
							//if (phrase == "visual question answering") cout << "visual question answering �����ڵ�" << lines << endl;

						}
						state = 0;
						wordtemp = "";
						wordtemp.clear();
					}
					break;
				}

				//���ÿ�ֵ�chartmp��wordtemp
				/*cout << "��ǰ������->" << i << endl;
				cout << "wordtemp��->" << wordtemp << " " << "chartemp��->" << chartmp << "<-" << endl;
				if (!wordque.empty()) {
					cout << "wordque�е���Ԫ����" << wordque.front() << endl;
				}
				if (!charque.empty()) {
					cout << "��ǰchartemp��size��" << charque.size() << endl;
					cout << " charque�е�Ԫ����------->" << charque.front() << "<-------" << endl;
				}
				*/
			}
			if (state == 4) {//��������������е���
				wordque.push(wordtemp);
				//�������������ɴ���Ļ�
				if (wordque.size() == m)//�Ķ������ˣ��Ǿ��Ǵ��鵥����
				{
					//����Ӧ�ĵ��ʺʹ���浽�����map��ȥ�����ҽ�queue�ײ��ߵ�
					//queue���ṩԪ�ص�������ʣ�������ֻ�ܽ�Ԫ�س�����������У�
					string phrase;
					string x, y;//���ڱ�����ʱ�ĵ��ʺͷָ���
					if (charque.front() == "")
						charque.pop();
					for (int k = 0; k < m - 1; k++) {
						x = wordque.front(); //m
						y = charque.front();//m-1��
						phrase = phrase + x + y;
						wordque.pop();
						charque.pop();
						//wordque.push(x);
						//charque.push(y);
					}
					x = wordque.front(); //��m������
					phrase = phrase + x;
					wordque.pop();
					wordque.push(x);
					phraseMap[phrase]++;
					//if (phrase == "visualquestion answering") cout << "visualquestion answering �����ڵ�" << lines << endl;
					//if (phrase == "visual question answering") cout << "visual question answering �����ڵ�" << lines << endl;
				}
			}

			//ÿ��abstract����֮�󶼽��������
			while (!wordque.empty()) wordque.pop();
			while (!charque.empty()) charque.pop();
		}
		

	}
	ifs.close();
	ifs.clear();
	ifs.seekg(0);
}
void phraseFrequency(int n)
{

	//ͳ��Ƶ����ߵ�ʮ��������

	map<string, int>::iterator iter ; //��ʼ��
	for (iter = phraseMap.begin(); iter != phraseMap.end(); iter++)
	{
		phrases.push_back(pair<string, int>(iter->first, iter->second));
	}
	//��map�е�ֵ�ŵ�vector�н�������
	if (n < 0)
		n = 10;
	int size = n;
	if (phrases.size() < size) {
		size = phrases.size();
	}
	vector<pair<string, int>>::iterator vit;
	for (int i = 0; i < size; i++) {
		pair<string, int> max = phrases[i];
		int pos, flag = i;
		for (vit = phrases.begin() + i, pos = i; vit != phrases.end(); vit++, pos++) {
			if (vit->second > max.second) { //�ı�max��ֵ
				max.first = vit->first;
				max.second = vit->second;
				flag = pos;
			};
		}
		swap(phrases[i], phrases[flag]);
	}
}


