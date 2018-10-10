#include <fstream>     
#include <iostream>    
#include<stdio.h>
#include<algorithm>
#include<string>
#include<queue>
#include"CountChar.h"
#include"CountLines.h"
#include"CountWordnumber.h"
#include"TenFrequency.h"
#include"CountPhrase.h"
#include"phraseFrequency.h"
vector<pair<string, int>> word, phrases;
map<string, int> mCountMap,phraseMap;
queue<string> wordque;
queue<string>charque;
int sum2;
using namespace std;
/*
int main()
{
	cout << "please cin you want to test:" << endl;
	string mInputFileName="result1.txt";

	//cin >> mInputFileName;
	//string mInputFileName = "input1."
	//int sum = CountChar(mInputFileName);
	//int wordnum = CountWordnumber();
	//int lines = CountLines(mInputFileName);
	//TenFrequency();

	//ofstream out("result.txt");

	//out << "characters: " << sum << endl;
	//out << "words: " << wordnum << endl;
	//out << "lines: " << lines << endl;
	CountPhrase(mInputFileName, 3,1);
	//cout << "belowCountPhrase" << endl;
	phraseFrequency(10);
	///cout << "belowphraseFrequency" << endl;
	int size = 10;
	if (phrases.size() < 10) {
		size = phrases.size();
	}
	vector<pair<string, int>>::iterator vit;
	for (vit = phrases.begin(); vit != phrases.begin() + size; vit++) {
		cout << "<" << vit->first << ">:" << " " << vit->second << endl;
	}
	system("pause");
	return 0;
}
*/

int main(int argc, const char* argv[])
{
	string names[15];
	for (int i = 1; i < argc; i++) {
		names[i] = argv[i];
		//cout << "��������������"<<names[i] << endl;
	}
	//��ʾ��һ�еĴ��������//�����argvӦ���Զ�ȷ���������˼�������)
	int sum ;//�ܵ��ַ���
	//int sum2 = 0; //������
	int wordnum ;
	int lines;
	int n=-1;
	int m=-1;
	sum2 = 0;
	sum = 0;
	int weight;
	string mInputFileName;
	int flag = 0;
	for (int i = 1; i < argc; i++) {
		//cout << "�ļ�����" << argc << endl;
		if (names[i] == "-i")//����
		{
			ifstream file;
			file.open(names[i+1], ios::in);
			if (!file) {
				cout << "�޷����ļ�\n";
				return -1;
			}
			file.close();
			mInputFileName = names[i+1];
			//cout << "filename is:" << mInputFileName << endl;
		}
		if (names[i] == "-w") //����Ȩ��
		{
			weight = stoi(names[i + 1]);
			//cout << weight << endl;
		}
		if (names[i] == "-o")//����ļ�,�ļ�·������һ��
		{
			flag = i;
		}
		if (names[i] == "-n") //ǰn����
		{
			n = stoi(names[i + 1]);
		}
		if (names[i] == "-m") //ǰm����
		{
			m= stoi(names[i + 1]);
		}
		
	}
	if (m > 0) {//ͳ�ƴ��鲻ͳ�Ƶ���
		if (n < 0)
			n = 10;
		lines = CountLines(mInputFileName);//����
		sum = CountChar(mInputFileName); //sum-(17+1+1+2)*ƪ�����ַ���
		//CountWord(mInputFileName);
		sum = sum - lines * 21/3;
		wordnum = sum2 - lines / 3 * 2;//������ 
		//wordnum = CountWordnumber();
		CountPhrase(mInputFileName, m,weight);
		phraseFrequency(n);
		ofstream out(names[flag + 1]);
	//ofstream out("result.txt");
		//cout << "to out in :" << names[flag + 1] << endl;
		lines = lines / 3 * 2;
		out << "characters: " << sum << endl;
		out << "words: " << wordnum << endl;
		out << "lines: " << lines << endl;
		int size = n;
		if (phrases.size() < n) {
			size = phrases.size();
		}
		vector<pair<string, int>>::iterator vit;
		for (vit = phrases.begin(); vit != phrases.begin() + size; vit++) {
			out << "<" << vit->first << ">:" << " " << vit->second << endl;
		}
		out.close();

	}
	else {//û�д���ͳ�ƣ����ǵ���ͳ��
		if (n < 0)
			n = 10;
		lines = CountLines(mInputFileName);
		sum = CountChar(mInputFileName);
		//CountWord(mInputFileName);
		sum = sum - lines * 21/3;
		wordnum = sum2-lines/3*2;
		//wordnum = CountWordnumber();
		CountWordnumber(mInputFileName, weight);
		TenFrequency(n);
		ofstream out(names[flag + 1]);
		//ofstream out("result.txt");
		//cout << "to out in :" << names[flag + 1] << endl;
		lines = lines / 3 * 2;
		out << "characters: " << sum << endl;
		out << "words: " << wordnum << endl;
		out << "lines: " << lines << endl;
		int size = n;
		if (word.size() < n) {
			size = word.size();
		}
		vector<pair<string, int>>::iterator vit;
		for (vit = word.begin(); vit != word.begin() + size; vit++) {
			out << "<" << vit->first << ">:" << " " << vit->second << endl;
		}
		out.close();

	}
	
	system("pause");
	return 0;
}


		//cout << "else Ҳִ�й�" << endl;
		/*ifstream file;
		file.open(argv[i], ios::in);
		if (!file) {
			cout << "�޷����ļ�\n";
			return -1;
		}
		file.close();
		string mInputFileName = argv[i];
		int sum = CountChar(mInputFileName);
		int wordnum = CountWordnumber();
		int lines = CountLines(mInputFileName);
		TenFrequency();
		
		ofstream out("result.txt");
		
		out << "characters: " << sum << endl;
		out << "words: " << wordnum << endl;
		out << "lines: " << lines << endl;
		int size = 10;
		if (word.size() < 10) {
			size = word.size();
		}
		vector<pair<string, int>>::iterator vit;
		for (vit = word.begin(); vit != word.begin() + size; vit++) {
			out << "<"<<vit->first <<">:"<< " " << vit->second << endl;
		}
		out.close();*/
