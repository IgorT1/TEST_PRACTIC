
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
string ABC = "абвгдежзийклмнопрстуфхцчшщъыьэюя";

string Text() {
	//string str1 = " Карл у Клары Украл корали ,Карла у Карлы украла кларнет  ";
	string path = "..\\file2.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "Ошибка вывода файла " << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;
		//char ch;
		//fin.get(ch) выводит данные по символьно 

		string str;
		while (!fin.eof()) // отлвливает конец вайла 
		{
			str = ""; //для корректного счетия	
			getline(fin, str);
			res += str;
		}
	}

	//cout << res << endl;

	fin.close();

	return res;
}


string filterWithoutSpace(string& text, string& ABC) { //метод фильтрации текста без пробелов 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);

		if (v == 'ё')v = 'е';//замена букв

		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filterText += v;
		}
		else if (isspace(v)) {
			continue; //пропускаем пробелы 
		}
	}

	return filterText;
}

string filterSpace(string& text, string& ABC) {
	string filteredText = "";

	regex pattern("\\s+");//для нахождения последовательности пробелов 
	string result = regex_replace(text, pattern, " ");  // заміна на один пробіл

	for (char& c : result) {
		char v = tolower(c);

		if (v == 'ё')v = 'е';//замена букв

		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filteredText += v;
		}
		else if (isspace(v)) {
			filteredText += ' '; //+ пробелы 
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

// функция получения кода символа
int keycode(char s) {//проверка на соответствие символа ключа алфавиту 
	for (int i = 0; i < ABC.length(); i++) {
		if (s == ABC[i]) return i;
	}
	return 0;
}

string Encode(string& text, string& key) {//функция для шифрования (принимает текст и ключ)
	string code;
	char keyChar;
	for (int i = 0; i < text.length(); i++) {
		keyChar = keycode(key[i % key.length()]); //для цикличного перебора ключа по длине текста 
		code += ABC[(keycode(text[i]) + keyChar) % ABC.length()];//заносит символ для получения строки 
	}
	return code;
}

string Decode(string& text, string& key) { //функция разкодировки 
	string code;
	for (int i = 0; i < text.length(); i++) {//цикл проходится по всем елементам текста 
		code += ABC[(keycode(text[i]) - keycode(key[i % key.length()]) + ABC.length()) % ABC.length()];// берет значение зашифрованого символа - значение ключа 
	}
	return code;
}

void bloc(string plaintext) { //метод для разбития текста на блоки для разшифровки с помошью unit
	
	string g = "";
	int r = 16; // длина ключа 
	for (int j = 0 ; j < plaintext.size(); j += r) {//цикл для перебора символов в периоде ключа сдвига перебор от первого до элемента равного длине ключа 
		g = plaintext.substr(j, r);//добавление к строке 
		 cout<<g<<endl;
	}
	
}

//string ABC = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
void Log() {
	string text = Text(), key;

	/*cout << "Введите ключ для шифрования :\t" ;
	cin >> key;*/

	key = "декелисоборойдей";
	//key = "делолисоборотней";
	
	cout<<key<<endl;


	//string withoutSpace = filterWithoutSpace(text, ABC); //без них
	//string withSpace = filterSpace(text, ABC);//  с пробелами
	//cout << "\nВЫВОД ОТФИЛЬТРОВАНОГО ТЕКСТА \n" << endl;
	//cout << withoutSpace << endl; 
	//cout << "\nВЫВОД ЗАШИФРОВАНОГО ТЕКСТА\n" << endl;
	//cout << Encode(withoutSpace, key) << endl;
	cout << "\nВЫВОД РОЗШИФРОВАНОГО ТЕКСТА\n" << endl;
	//cout << Decode(text, key) << endl;
	bloc(Decode(text, key));
	const int SIZE = 33; // размер таблицы

	
		// Создаем двумерный массив для хранения таблицы
		char table[SIZE][SIZE];

		// Заполняем первую строку таблицы алфавитом
		for (int i = 0; i < SIZE; i++) {
			table[0][i] = 'а' + i;
		}

		// Заполняем остальные строки таблицы с учетом сдвига алфавита
		for (int i = 1; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				table[i][j] = table[i - 1][(j + 1) % SIZE];
			}
		}

		// Выводим таблицу на экран
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