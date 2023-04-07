
#include <iostream>
#include <string>
#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <regex>

using namespace std;
string ABC = "��������������������������������";

string Text() {
	//string str1 = " ���� � ����� ����� ������ ,����� � ����� ������ �������  ";
	string path = "..\\file2.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "������ ������ ����� " << endl;
	}
	else
	{
		cout << "���� ������" << endl;
		//char ch;
		//fin.get(ch) ������� ������ �� ��������� 

		string str;
		while (!fin.eof()) // ���������� ����� ����� 
		{
			str = ""; //��� ����������� ������	
			getline(fin, str);
			res += str;
		}
	}

	//cout << res << endl;

	fin.close();

	return res;
}


string filterWithoutSpace(string& text, string& ABC) { //����� ���������� ������ ��� �������� 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);

		if (v == '�')v = '�';//������ ����

		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filterText += v;
		}
		else if (isspace(v)) {
			continue; //���������� ������� 
		}
	}

	return filterText;
}

string filterSpace(string& text, string& ABC) {
	string filteredText = "";

	regex pattern("\\s+");//��� ���������� ������������������ �������� 
	string result = regex_replace(text, pattern, " ");  // ����� �� ���� �����

	for (char& c : result) {
		char v = tolower(c);

		if (v == '�')v = '�';//������ ����

		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filteredText += v;
		}
		else if (isspace(v)) {
			filteredText += ' '; //+ ������� 
		}
	}
	if (filteredText.back() == ' ') {
		filteredText.pop_back();
	}
	if (filteredText.front() == ' ') {
		filteredText.erase(0, 1);
	}
	return filteredText;
}

// ������� ��������� ���� �������
int keycode(char s) {//�������� �� ������������ ������� ����� �������� 
	for (int i = 0; i < ABC.length(); i++) {
		if (s == ABC[i]) return i;
	}
	return 0;
}

string Encode(string& text, string& key) {//������� ��� ���������� (��������� ����� � ����)
	string code;
	char keyChar;
	for (int i = 0; i < text.length(); i++) {
		keyChar = keycode(key[i % key.length()]); //��� ���������� �������� ����� �� ����� ������ 
		code += ABC[(keycode(text[i]) + keyChar) % ABC.length()];//������� ������ ��� ��������� ������ 
	}
	return code;
}

string Decode(string& text, string& key) { //������� ������������ 
	string code;
	for (int i = 0; i < text.length(); i++) {//���� ���������� �� ���� ��������� ������ 
		code += ABC[(keycode(text[i]) - keycode(key[i % key.length()]) + ABC.length()) % ABC.length()];// ����� �������� ������������� ������� - �������� ����� 
	}
	return code;
}

void bloc(string plaintext) { //����� ��� �������� ������ �� ����� ��� ����������� � ������� unit
	
	string g = "";
	int r = 16; // ����� ����� 
	for (int j = 0 ; j < plaintext.size(); j += r) {//���� ��� �������� �������� � ������� ����� ������ ������� �� ������� �� �������� ������� ����� ����� 
		g = plaintext.substr(j, r);//���������� � ������ 
		 cout<<g<<endl;
	}
	
}

//string ABC = "��������������������������������";
void Log() {
	string text = Text(), key;

	/*cout << "������� ���� ��� ���������� :\t" ;
	cin >> key;*/

	key = "����������������";
	//key = "����������������";
	
	cout<<key<<endl;


	//string withoutSpace = filterWithoutSpace(text, ABC); //��� ���
	//string withSpace = filterSpace(text, ABC);//  � ���������
	//cout << "\n����� ��������������� ������ \n" << endl;
	//cout << withoutSpace << endl; 
	//cout << "\n����� ������������� ������\n" << endl;
	//cout << Encode(withoutSpace, key) << endl;
	cout << "\n����� �������������� ������\n" << endl;
	//cout << Decode(text, key) << endl;
	bloc(Decode(text, key));
	const int SIZE = 33; // ������ �������

	
		// ������� ��������� ������ ��� �������� �������
		char table[SIZE][SIZE];

		// ��������� ������ ������ ������� ���������
		for (int i = 0; i < SIZE; i++) {
			table[0][i] = '�' + i;
		}

		// ��������� ��������� ������ ������� � ������ ������ ��������
		for (int i = 1; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				table[i][j] = table[i - 1][(j + 1) % SIZE];
			}
		}

		// ������� ������� �� �����
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				cout << table[i][j] << " ";
			}
			cout << endl;
		}
}



int main() {
	setlocale(LC_ALL, "RU");
	Log();
	return 0;
}