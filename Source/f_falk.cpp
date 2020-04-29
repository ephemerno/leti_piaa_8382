#include <iostream> 
#include <vector>
#include <stack> 
#include <limits.h> 
#include <algorithm>
using namespace std;

//структура для вершины
struct Top{
    char from_top;//идет из вершины
    char to_top;//идет в вершину
    int weigth; //вес ребра
};

//сортировка вершин
bool compareTop(Top a, Top b){
    if (a.from_top < b.from_top) return true;
	else if (a.from_top == b.from_top) {
		if (a.to_top < b.to_top) return true;
	}
    return false;
}

//поиск в глубину
bool dfs(vector<vector<int>> Graph, int s, int t, vector<int>&parent, int U, string node){
    // массив флагов посещаемости вершин
    //создаем стек
    vector<bool> visited(U,0);
    stack <int> stak;
    //кладем исходную вершину в стек
    stak.push(s);
    //used[s] = true;
    //вектор посещенных уже вершин
    
    visited[s] = true;//посетили вершину
    parent[s] = -1;
    
    //считаем длину пути
   while (!stak.empty()) {       //обработка, пока стек не пуст
		int i = stak.top();    //обработка первой вершины
		stak.pop();
        //если смежная вершина не обработана и имеет ребро с обрабатываемой вершиной
        for( int j = 0 ; j < U; j++){
            if(Graph[i][j] > 0 && visited[j] == false){
                //add смежную вершину
                stak.push(j);
                parent[j] = i;
                visited[j] = true;
            }
        }
    }
    if(visited[t] == true){
        string Sr;
        for( int i = t; i != s; i = parent[i]){
            Sr = node[i] + Sr;
        }
        Sr = node[s] + Sr;
    }
    return visited[t] == true;
}

int f_Fulkerson(vector<vector<int>>& graph, vector<vector<int>>& Graph, int s, int t, int U, string node) {
	int u, v;

	for (u = 0; u < U; u++)
		for (v = 0; v < U; v++) {
			Graph[u][v] = graph[u][v];
			graph[u][v] = 0;
		}
	//изначально поток = 0		
	int max_flow = 0;
    // массив для хранения пути
	vector <int> parent(U, 0);  
    //увеличивается поток, пока есть путь от истока к стоку
	while (dfs(Graph, s, t, parent, U, node)) {  
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, Graph[u][v]);
		}
		//обновление пропускной способности каждого ребра
		for (v = t; v != s; v = parent[v]) {		
			u = parent[v];
			Graph[u][v] -= path_flow;
			Graph[v][u] += path_flow;
			graph[u][v] += path_flow;
			graph[v][u] -= path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}

int main() {
    char start; //исток
	char finish;//сток
	char temp_from;
	char temp_to;
	int N = 0; //количество ориентированных рёбер графа
	int weigth;
	string from;
	string to;
	string node;  //названия узлов
    cin >> N >> start >> finish;
	vector <int> Nw;
	node = node + start;
	for (int i = 0; i < N; i++) {
		cin >> temp_from;
		cin >> temp_to;//input
		cin >> weigth;
		from = from + temp_from;
		to = to + temp_to;
		Nw.push_back(weigth);
		if (node.length() == 0) 
		    node = node + temp_to;
		else if (node.find(temp_to) == string::npos)//макс/ значениt, которое может предоставить тип size_type
		    node = node + temp_to;
	}
	sort(node.begin(), node.end());
	int U = node.length();//смотрим размер
	vector<vector<int>> graph(U, vector<int>(U, 0));
	
    //поиск всех ребер, ведущих из вершины node[q]
	for (int q = 0; q < node.length(); q++) {
		vector <int> Temp;
		for (int j = 0; j < N; j++) {         
			if (from[j] == node[q]) {
				Temp.push_back(j);
			}
		}
    //поиск в строке node[q] вершины, в которую ведут ребра из вектора temp
		vector <int> nodeTemp;
		for (int i = 0; i < Temp.size(); i++) {    
			for (int j = 0; j < node.length(); j++) {
				if (node[j] == to[Temp[i]])
					nodeTemp.push_back(j);
			}
		}
		for (int i = 0; i < Temp.size(); i++) {
			graph[q][nodeTemp[i]] = Nw[Temp[i]];
		}
	}

	int start_ind = 0;
	int finish_ind = 0;
	for (int i = 0; i < U; i++) {
		if (node[i] == start)
		start_ind = i;
		else if (node[i] == finish)
		finish_ind = i;
	}

	vector<vector<int> > Graph(U, vector<int>(U, 0));
	int max_flow = f_Fulkerson(graph, Graph, start_ind, finish_ind, U, node);

    vector <Top> One;
	for (int i = 0; i < U; i++){
		vector <int> pointer;  //индексы
		for (int j = 0; j < N; j++) {
			if (node[i] == from[j]) pointer.push_back(j);
		}
		for (int j = 0; j < pointer.size(); j++) {
			Top tops;
			tops.from_top = from[pointer[j]];
			tops.to_top = to[pointer[j]];
			int tempF = 0;
			int tempT = 0;
			for (int k = 0; k < U; k++) {
				if (node[k] == from[pointer[j]]) tempF = k;
				else if (node[k] == to[pointer[j]]) tempT = k;
			}
			if (graph[tempT][tempF] >= 0) tops.weigth = 0;
			else tops.weigth = abs(graph[tempT][tempF]);
			One.push_back(tops);
		}
	}
	sort(One.begin(), One.end(), compareTop);
	cout << max_flow << endl;
	for (int i = 0; i < One.size(); i++){
	    cout << One[i].from_top << " " << One[i].to_top << " " << One[i].weigth << endl;
	}

	return 0;
}


