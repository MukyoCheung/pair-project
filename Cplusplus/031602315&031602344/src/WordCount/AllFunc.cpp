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
int CountChar(string mInputFileName) //计算字符数和单词数
{
	ifstream ifs(mInputFileName);
	char charTemp;
	string wordtemp;
	int sum = 0;
	int state = 0;
	while ((charTemp = ifs.get()) != EOF)
	{
		sum++;//计算字符数
		if (charTemp >= 65 && charTemp <= 90)
			charTemp = charTemp + 32; //大写转化为小写
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
			if (str[i] != ' '&&str[i] != '\t')//空白行
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
void CountWordnumber(string mInputFileName,int weight)//将单词对应的频率记录下来（不要管单词数）
{

	ifstream ifs(mInputFileName);
	string str;
	int lines = 0;
	while (getline(ifs, str)) //从原网页可以观察到，title是一行，abstract是一行，
	{
		lines++;
		if (lines % 5 == 2) //title行
		{
			//cout << "lines % 5 == 2这一行是:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				if (charTemp >= 65 && charTemp <= 90)
					charTemp = charTemp + 32; //大写转化为小写
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
						if (weight == 1) {//有权重
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
				if (weight == 1) {//有权重
					mCountMap[wordtemp] = mCountMap[wordtemp] + 10;
				}
				else mCountMap[wordtemp]++;
			}
			mCountMap["title"]--;
		}
		
		if (lines % 5 == 3) //abstract行
		{
			//cout << "lines % 5 == 3这一行是:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				if (charTemp >= 65 && charTemp <= 90)
					charTemp = charTemp + 32; //大写转化为小写
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
						if (weight == 1) {//有权重
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
				if (weight == 1) {//有权重
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
	//cout << "title中共有：" <<sum<< endl;

	for (map<string, int>::iterator iter = mCountMap.begin(); iter != mCountMap.end(); iter++) {
		sum = sum + iter->second;
	}
	//cout << "ab中共有：" << sum << endl;
	
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
			if (vit->second > max.second) { //改变max的值
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

void CountPhrase(string mInputFileName, int m,int weight)//统计词组,并且将词组按可能的权重记录
{
	ifstream ifs(mInputFileName);
	string str;
	int lines = 0;
	while (getline(ifs, str)) //从原网页可以观察到，title是一行，abstract是一行，
	{
		lines++;

		//if(position(str)==1)
		//if(position(str)==2)
		//else 
		if (lines % 5 == 2) //title行
		{
			//cout << "lines % 5 == 2这一行是:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				//if (charTemp == ' ') cout << "lines % 5 == 2空格的当前位置为：" << i << endl;
				/*----------------------------对于单词的操作----------------*/
				if (charTemp >= 65 && charTemp <= 90) 
					charTemp = charTemp + 32; //大写转化为小写
				switch (state)
				{
				case 0:
					if (charTemp >= 97 && charTemp <= 122) {//字母
						wordtemp = wordtemp + charTemp;
						state = 1;
						if (i != 0&&i!=6&&i!=7) {
							charque.push(chartmp);
							chartmp.clear();//清空
						}
					}
					if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//是分隔符
					{
						if (i != 5 && i != 6 && flag == 1) //不是标题的:并且之前要出现过单词才开始计数
							chartmp = chartmp + charTemp;
					}
					///当遇到是数字或者字母的时候就将chartemp压栈
					//碰到字母的时候才将其压栈，碰到数字的时候全部清空,在state=0的状态下，当碰到数字的时候要将两个队列清空
					/*if (charTemp >= 97 && charTemp <= 122&&i!=0) {//不是标题
						charque.push(chartmp);
						chartmp = "";//清空
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
					{//中间发生错误就全部清空
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
					else//单词结束了
					{
						if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//是分隔符那就保存起来,并且不能是开头的单词
						{
							if (i != 5) {
								chartmp = chartmp + charTemp;
							}
							
						}
						if (wordtemp != "title"&&i != 5)//不是开头的title
						{
							//将单词放进queue中
							wordque.push(wordtemp);
							flag = 1;//有过单词

						}
						if (wordque.size() == m)//改队列满了，那就是词组单词了
						{
							string phrase;
							if (charque.front() == "")
								charque.pop();
							//将对应的单词和词组存到词组的map中去，并且将queue首部踢掉
							//queue不提供元素的随机访问，，所以只能将元素出队列再入队列？
							string x, y;//用于保存临时的单词和分隔符
							for (int k = 0; k < m - 1; k++) {
								x = wordque.front(); //m
								y = charque.front();//m-1次
								phrase = phrase + x + y;
								wordque.pop();
								charque.pop();
								wordque.push(x);
								charque.push(y);
							}
							x = wordque.front(); //第m个单词
							//y = charque.front();
							phrase = phrase + x;
							wordque.pop();
							wordque.push(x);
							//合并完之后将两个queue的首元素都去掉
							wordque.pop();
							charque.pop();
							if (weight == 1)//有权重
							{
								phraseMap[phrase] = phraseMap[phrase] + 10;
							}
							else phraseMap[phrase]++;
							//phrase = "";
							//if (phrase == "visualquestion answering") cout << "visualquestion answering 出现在第" << lines << endl;
							//if (phrase == "visual question answering") cout << "visual question answering 出现在第" << lines << endl;
						}
						state = 0;
						wordtemp = "";
					}
					break;
				}

				//输出每轮的chartmp和wordtemp
				/*cout << "当前局数是->" << i << endl;
				cout << "wordtemp是->" << wordtemp <<" " << "chartemp是->" << chartmp <<"<-"<< endl;
				if (!wordque.empty()) {
					cout << "wordque中的首元素是" << wordque.front() << endl;
				}
				if (!charque.empty()) {
					cout << "当前chartemp的size是" << charque.size() << endl;
					cout << " charque中的元素是------->" << charque.front() << "<-------" << endl;
				}*/
				
			}
			if (state == 4) {//最后结束如果还是有单词
				wordque.push(wordtemp);
				//并且如果还能组成词组的话
				if (wordque.size() == m)//改队列满了，那就是词组单词了
				{
					//将对应的单词和词组存到词组的map中去，并且将queue首部踢掉
					//queue不提供元素的随机访问，，所以只能将元素出队列再入队列？
					string x, y;//用于保存临时的单词和分隔符
					string phrase;
					if (charque.front() == "")
						charque.pop();
					for (int k = 0; k < m - 1; k++) {
						x = wordque.front(); //m
						y = charque.front();//m-1次
						phrase = phrase + x + y;
						wordque.pop();
						charque.pop();
						//wordque.push(x);
						//charque.push(y);
					}
					x = wordque.front(); //第m个单词
					//y = charque.front();
					phrase = phrase + x;
					wordque.pop();
					wordque.push(x);
					if (weight == 1)//有权重
					{
						phraseMap[phrase] = phraseMap[phrase] + 10;
					}
					else phraseMap[phrase]++;
					//if (phrase == "visualquestion answering") cout << "visualquestion answering 出现在第" << lines << endl;
					//if (phrase == "visual question answering") cout << "visual question answering 出现在第" << lines << endl;
				}
			}
			
			//每个abstract结束之后都将两者清空
			while (!wordque.empty()) wordque.pop();
			while (!charque.empty()) charque.pop();
		}
		if (lines % 5 == 3) //abstract行
		{
			//cout << "lines % 5 == 2这一行是:" << str << endl;
			int state = 0;
			int flag = 0;
			string wordtemp, chartmp;
			for (int i = 0; i < str.length(); i++)
			{
				char charTemp = str[i];
				//if (charTemp == ' ') cout << "lines % 5 == 2空格的当前位置为：" << i << endl;
				/*----------------------------对于单词的操作----------------*/
				if (charTemp >= 65 && charTemp <= 90)
					charTemp = charTemp + 32; //大写转化为小写
				switch (state)
				{
				case 0:
					if (charTemp >= 97 && charTemp <= 122) {//字母
						wordtemp = wordtemp + charTemp;
						state = 1;
						if (i != 0 && i != 9 && i != 10) {
							charque.push(chartmp);
							chartmp.clear();//清空
						}
					}
					if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//是分隔符
					{
						if (i != 8 && i != 9 && flag == 1) //不是标题的:并且之前要出现过单词才开始计数
							chartmp = chartmp + charTemp;
					}
					///当遇到是数字或者字母的时候就将chartemp压栈
					//碰到字母的时候才将其压栈，碰到数字的时候全部清空,在state=0的状态下，当碰到数字的时候要将两个队列清空
					/*if (charTemp >= 97 && charTemp <= 122&&i!=0) {//不是标题
					charque.push(chartmp);
					chartmp = "";//清空
					}*/
					if ((charTemp >= '0'&&charTemp <= '9')) {
						while (!wordque.empty()) wordque.pop();//将队列和当前要填进去的元素都清空
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
					{//中间发生错误就全部清空
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
					else//单词结束了
					{
						if ((charTemp < '0') || (charTemp > '9'&&charTemp < 97) || (charTemp > 122))//是分隔符那就保存起来,并且不能是开头的单词
						{
							if (i != 8) {
								chartmp = chartmp + charTemp;
							}

						}
						if (wordtemp != "abstract"&&i != 8)//不是开头的title
						{
							//将单词放进queue中
							wordque.push(wordtemp);
							flag = 1;//有过单词

						}
						if (wordque.size() == m)//改队列满了，那就是词组单词了
						{
							string phrase;
							//将对应的单词和词组存到词组的map中去，并且将queue首部踢掉
							//queue不提供元素的随机访问，，所以只能将元素出队列再入队列？
							string x, y;//用于保存临时的单词和分隔符
							//由于队首可能是""这样的分隔符，所以先把他弹出来
							if(charque.front()=="")
								charque.pop();
							for (int k = 0; k < m - 1; k++) {//这时只要有分隔符肯定就不是“”

								x = wordque.front(); //m
								y = charque.front();//m-1次
								phrase = phrase + x + y;
								wordque.pop();
								charque.pop();
								wordque.push(x);
								charque.push(y);
							}
							x = wordque.front(); //第m个单词
							phrase = phrase + x;
							wordque.pop();
							wordque.push(x);
							//合并完之后将两个queue的首元素都去掉
							wordque.pop();
							charque.pop();
							phraseMap[phrase]++;
							//if (phrase == "visualquestion answering") cout << "visualquestion answering 出现在第" << lines << endl;
							//if (phrase == "visual question answering") cout << "visual question answering 出现在第" << lines << endl;

						}
						state = 0;
						wordtemp = "";
						wordtemp.clear();
					}
					break;
				}

				//输出每轮的chartmp和wordtemp
				/*cout << "当前局数是->" << i << endl;
				cout << "wordtemp是->" << wordtemp << " " << "chartemp是->" << chartmp << "<-" << endl;
				if (!wordque.empty()) {
					cout << "wordque中的首元素是" << wordque.front() << endl;
				}
				if (!charque.empty()) {
					cout << "当前chartemp的size是" << charque.size() << endl;
					cout << " charque中的元素是------->" << charque.front() << "<-------" << endl;
				}
				*/
			}
			if (state == 4) {//最后结束如果还是有单词
				wordque.push(wordtemp);
				//并且如果还能组成词组的话
				if (wordque.size() == m)//改队列满了，那就是词组单词了
				{
					//将对应的单词和词组存到词组的map中去，并且将queue首部踢掉
					//queue不提供元素的随机访问，，所以只能将元素出队列再入队列？
					string phrase;
					string x, y;//用于保存临时的单词和分隔符
					if (charque.front() == "")
						charque.pop();
					for (int k = 0; k < m - 1; k++) {
						x = wordque.front(); //m
						y = charque.front();//m-1次
						phrase = phrase + x + y;
						wordque.pop();
						charque.pop();
						//wordque.push(x);
						//charque.push(y);
					}
					x = wordque.front(); //第m个单词
					phrase = phrase + x;
					wordque.pop();
					wordque.push(x);
					phraseMap[phrase]++;
					//if (phrase == "visualquestion answering") cout << "visualquestion answering 出现在第" << lines << endl;
					//if (phrase == "visual question answering") cout << "visual question answering 出现在第" << lines << endl;
				}
			}

			//每个abstract结束之后都将两者清空
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

	//统计频率最高的十个词组数

	map<string, int>::iterator iter ; //初始化
	for (iter = phraseMap.begin(); iter != phraseMap.end(); iter++)
	{
		phrases.push_back(pair<string, int>(iter->first, iter->second));
	}
	//将map中的值放到vector中进行排序
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
			if (vit->second > max.second) { //改变max的值
				max.first = vit->first;
				max.second = vit->second;
				flag = pos;
			};
		}
		swap(phrases[i], phrases[flag]);
	}
}


