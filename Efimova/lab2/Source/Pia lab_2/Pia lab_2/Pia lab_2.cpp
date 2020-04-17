// Pia lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

struct Input_El { // структура вводимого элемента
	char top1;
	char top2;
	double weigth;
};

bool Sort(const pair<int, double >& a, const pair<int, double >& b) {// функция сортировки
	return (a.second < b.second);
}

void Sort_Weigth(vector<vector<pair<int, double>>>& nodes) {//функция сортировки весов
	int len = nodes.size();
	for (int i = 0; i < len; i++) {
		sort(nodes[i].begin(), nodes[i].end(), Sort);
	}
}

void Print_Output(map<int, char>& convert_to_char, vector<int>& road) {//функция печатает вывод
	for (int i = 0; i < road.size(); i++) {
		cout << convert_to_char[road[i]];
	}
}

void From_List(vector<vector<pair<int, double>>>& nodes, map<char, int>& convert_to_int, vector<Input_El>& input_seq) {
	int top1;
	int top2;
	double weigth;
	for (int i = 0; i < input_seq.size(); i++) {
		top1 = convert_to_int[input_seq[i].top1];
		top2 = convert_to_int[input_seq[i].top2];
		weigth = input_seq[i].weigth;
		nodes[top1].push_back(make_pair(top2, weigth));
	}
}

void Find_Way(vector<vector<pair<int, double>>>& nodes, vector<int>& road, int top1, int top2, bool& check) {//ищем путь
	road.push_back(top1);
	if (top1 == top2) {
		check = true;//проверка
		return;
	}
	for (int i = 0; i < nodes[top1].size(); i++) {
		Find_Way(nodes, road, nodes[top1][i].first, top2, check);//вызов функции с проверкой
		if (check)
			return;
		road.pop_back();
	}
}

void Input(vector<vector<pair<int, double>>>& nodes, map<int, char>& convert_to_char, map<char, int>& convert_to_int) {
	vector<Input_El> input_seq;//вводимая последовательность
	Input_El elem;
	char top1;
	char top2;
	top1 = ' ';
	double weigth;
	int k = 0;  //счетчик
	while (cin >> top1) {
		if (!top1)
			break;
		cin >> top2;
		cin >> weigth;
		elem.top1 = top1;
		elem.top2 = top2;
		elem.weigth = weigth;
		input_seq.push_back(elem);
		if (convert_to_int.find(top1) == convert_to_int.end()) {
			convert_to_int[top1] = k;
			convert_to_char[k] = top1;
			k++;
		}
		if (convert_to_int.find(top2) == convert_to_int.end()) {
			convert_to_int[top2] = k;
			convert_to_char[k] = top2;
			k++;
		}
	}
	nodes.resize(k);
	From_List(nodes, convert_to_int, input_seq);
}

int main() {
	char c1;
	char c2;
	cin >> c1;
	cin >> c2;
	int top1;
	int top2;
	bool check = false;
	vector<vector<pair<int, double >>> nodes;
	vector<int> road;
	map<char, int> convert_to_int;
	map<int, char> convert_to_char;
	Input(nodes, convert_to_char, convert_to_int);
	Sort_Weigth(nodes);
	top1 = convert_to_int[c1];
	top2 = convert_to_int[c2];
	Find_Way(nodes, road, top1, top2, check);
	Print_Output(convert_to_char, road);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
