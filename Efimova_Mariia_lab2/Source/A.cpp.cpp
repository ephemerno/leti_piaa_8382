// A.cpp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <math.h>
using namespace std;

struct InputEl {
    char top1; //первая вершина
    char top2; //вторая вершина
    double weigth;
};

void fromNeighbor_list(vector<vector<pair<int, double>>>& nodes, map<char, int>& convert_to_int, vector<InputEl>& input_consistency) {
    //pair<int,double> через конструктор инициализируем пару целого типа и двойной точности
    double weigth;
    int top1, top2;
    for (int i = 0; i < input_consistency.size(); i++) { //меньше размера последовательности
        top1 = convert_to_int[input_consistency[i].top1];
        top2 = convert_to_int[input_consistency[i].top2];
        weigth = input_consistency[i].weigth;
        nodes[top1].push_back(make_pair(top2, weigth)); //добавление в конец элемент и обеспечивает присвоение знач.полям top2, weigth
    }
}

int counting_sum_of_weigth(vector<vector<pair<int, double>>>& nodes) {
    int sum = 0;
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes[i].size(); j++) {
            sum += nodes[i][j].second;//second - второй элемент пары sec структуры pair
        }
    }
    return sum + 1;
}

void recovery_way(vector<int>& prev, map<int, char>& convert_to_char, int top) {
    stack<int> steck;//создаем стек
    while (prev[top] != -1) {
        steck.push(top);//добавляем top
        top = prev[top];
    }
    steck.push(top);//добавляем top
    int way = steck.size();//размер стека
    for (int i = 0; i < way; i++) {
        cout << convert_to_char[steck.top()];
        steck.pop();//удаляем верхний элемент стека
    }
}

void input(vector<vector<pair<int, double>>>& nodes, map<int, char>& convert_to_char, map<char, int>& convert_to_int) {
    char top1;
    char top2;
    int i = 0;
    double weigth;
    top1 = ' ';
    int k = 0; //счетчик
    cout << "Input n: ";
    int n;
    cin >> n;
    vector<InputEl> input_consistency;//объявление массива структуры InputEl
    InputEl elem;//элемент структуры

    while (i < n) {
        cin >> top1;
        if (!top1) {
            break;
        }
        cin >> top2;
        cin >> weigth;
        elem.top1 = top1;
        elem.top2 = top2;
        elem.weigth = weigth;
        input_consistency.push_back(elem);//добавление в конец элемента
        if (convert_to_int.find(top1) == convert_to_int.end()) {//если найденный элемент в контейнере с первой вершиной = указателю на конец контейнера
            convert_to_int[top1] = k; //a -> 1
            convert_to_char[k] = top1;// 1-> a
            k++;//2
        }
        if (convert_to_int.find(top2) == convert_to_int.end()) {//если найденный элемент в контейнере со второй вершиной = указателю на конец контейнера
            convert_to_int[top2] = k;
            convert_to_char[k] = top2;
            k++;
        }
        i++;
    }
    nodes.resize(k); //устанавливаем размер счетчика для вектора
    fromNeighbor_list(nodes, convert_to_int, input_consistency);
}

//!!!!!
void change_dist(vector<vector<pair<int, double>>>& nodes, priority_queue<pair<double, int>>& near_ways, vector<double>& dist, vector<int>& prev, map<int, char>& convert_to_char, int top, int top2) {
    for (int i = 0; i < nodes[top].size(); i++) {
        if (dist[nodes[top][i].first] > dist[top] + nodes[top][i].second) {
            dist[nodes[top][i].first] = dist[top] + nodes[top][i].second;
            prev[nodes[top][i].first] = top; //предыдущему даем знаение top
            near_ways.push(make_pair(-(dist[nodes[top][i].first] + (int)convert_to_char[top2] - (int)convert_to_char[nodes[top][i].first]), nodes[top][i].first));
        }
    }
}

void AStar(vector<vector<pair<int, double >>>& nodes, map<int, char>& convert_to_char, int top1, int top2) {
    int current_top;
    int min;
    vector<double > dist(nodes.size());
    vector<int> prev(nodes.size());
    vector<bool> visited(nodes.size());
    priority_queue<pair<double, int>> near_ways;
    double max_dist = counting_sum_of_weigth(nodes);
    for (int i = 0; i < nodes.size(); i++)
        dist[i] = max_dist;
    dist[top1] = 0;
    prev[top1] = -1;
    near_ways.push(make_pair(-(dist[top1] + top2 - top1), top1));
    while (!near_ways.empty()) {
        while (1) {
            if (near_ways.empty())
                break;
            pair<int, int> current_min = near_ways.top();
            near_ways.pop();
            current_top = current_min.second;
            min = -current_min.first;
            if (!visited[current_top])
                break;
        }
        if (dist[top2] < min)
            break;
        visited[current_top] = true;
        change_dist(nodes, near_ways, dist, prev, convert_to_char, current_top, top2);
    }
    if (dist[top2] == max_dist)
        cout << -1;
    else {
        recovery_way(prev, convert_to_char, top2);
    }
}

int main() {
    char c1;
    char c2;
    cin >> c1;
    cin >> c2;
    int top1;
    int top2;
    map<char, int> convert_to_int;
    map<int, char> convert_to_char;
    vector<vector<pair<int, double >>> nodes;
    input(nodes, convert_to_char, convert_to_int);
    top1 = convert_to_int[c1];
    top2 = convert_to_int[c2];
    AStar(nodes, convert_to_char, top1, top2);
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
