#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
 
using namespace std;
 
void Intialization(int** square,int N){//инициализация нулями изначальных квадратов
    for(int i = 0;i < N /2 + 1;i++)
        for(int j = 0;j < N / 2 + 1;j++)
            square[i][j] = 1;
    for(int i = 0;i < N / 2;i++)
        for(int j = N / 2 + 1;j < N;j++)
            square[i][j] = 2;
    for(int i = N / 2 + 1;i < N;i++)
        for(int j = 0;j < N / 2;j++)
            square[i][j] = 3;
    square[N / 2 + 1][N / 2] = 4;
}
void Initialize(int** square,int N,int number1,int number2){
    for(int i = 0;i < number1;i++)
        for(int j = 0;j < number1;j++)
            square[i][j] = 1;
    for(int i = 0;i < number2;i++)
        for(int j = number1;j < N;j++)
            square[i][j] = 2;
    for(int i = number2;i < number2 * 2;i++)
        for(int j = number1;j < N;j++)
            square[i][j] = 3;
    for(int i = number1;i < N;i++)
        for(int j = 0;j < number2;j++)
            square[i][j] = 4;
    square[number1][number2] = 5;
    //printBoard(square,N);
}
void copy(int**square,int** best_square,int N){//сохранение наилучшего расположения квадратов
    for (int i = 0; i < N ; i++) {
        for(int j = 0;j < N;j++){
            best_square[i][j] = square[i][j];
        }
    }
}
 
void printBoard(int** best_square,int N){//вывод текущего положения квадратов на экран
    cout << "-------------------- " << "\n";
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++)
            cout << best_square[i][j] << " ";
        printf("\n");
    }
}
 
void clear(int** square,int** best_square,int N){//освобождение памяти по завершению работы алгоритма
    for(int i = 9;i < N;i++){
        delete square[i];
        delete best_square[i];
    }
}
 
void remove_numbers(int** square,int N,int curr_square,int x_start,int y_start){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            if(square[i][j] > curr_square || (square[i][j] == curr_square && (i > x_start || j > y_start)))
                square[i][j] = 0;
        }
    }
}
 
void search_first_elem(int** square,int &x_new,int &y_new,int N){//функция поиска свободного места для квадртата
    x_new = -1;
    y_new = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!square[i][j]) {
                x_new = i;
                y_new = j;
                break;
            }
        }
        if (x_new != -1)
            break;
    }
}
 
void memoryInitialization(int** square,int** best_square,int N){
    for(int i = 0;i < N;i++) {
        square[i] = new int[N];
        best_square[i] = new int[N];
    }
}
void printMultipleTwo(int N){
    cout << 4 << "\n";
    cout << 1 << " " << 1 << " " <<  N / 2 << "\n";
    cout << 1 << " " << N / 2 + 1 << " " << N / 2 << "\n";
    cout << N / 2 + 1 << " " << 1 << " " << N / 2 << "\n";
    cout << N / 2 + 1 << " " << N / 2 + 1 << " " << N / 2 << "\n";
}
void printMultipleThree(int N){
    cout << 6 << "\n";
    cout << 1 << " " << 1 << " " << N - N/3 << "\n";
    cout << 1 << " " << N - N/3 + 1 << " " << N / 3 << "\n";
    cout << N / 3 + 1 << " " << N - N/3 + 1 << " " << N / 3 << "\n";
    cout << N - N/3 + 1 << " " << 1 << " " << N / 3 << "\n";
    cout << N - N/3 + 1 << " " << N/3 + 1 << " " << N / 3 << "\n";
    cout << N - N/3 + 1 << " " << N - N/3 + 1 << " " << N / 3 << "\n";
}
void printResult(int** best_sq,int N,int min){//вывод оезультатов на основе заполнения матрицы
    int x,y,len;
    bool find;
    for(int k= 1;k <= min;k++){
        x = 0;
        len = 0;
        y = 0;
        find = false;
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                if(find){
                    if(i + 1 >= N || j + 1 >= N || best_sq[i + 1][j + 1] != k) {
                        len = i - x + 2;
                        break;
                    } else
                        i++;
                }
                if(!find && best_sq[i][j] == k){
                    find = true;
                    x = i + 1;
                    y = j + 1;
                    if(i + 1 >= N || j + 1 >= N || best_sq[i + 1][j + 1] != k){
                        len = 1;
                        break;
                    }
                    i++;
                }
            }
            if(len)
                break;
        }
        cout << x << " " << y << " " << len << "\n";
    }
}
 
void setPosition(int** square,int** best_square_version,int N,int x,int y,int number_of_squares,int &min,deque<pair<int,int>> &components_of_square, bool &forward) {
    int x_new = -1;
    int y_new = -1;
    unsigned long size_of_queue = components_of_square.size();
    bool check = true;
    pair<int, int> coordinates;
    vector<pair<int, int>> curr_components;
    for (int i = 0; i < size_of_queue; i++) {//проверка на то, можно ли на свободных позициях увеличить квадрат
        coordinates = components_of_square.front();
        components_of_square.pop_front();
        x_new = coordinates.first;
        y_new = coordinates.second;
        if (((x_new + 1 < N && y_new + 1 < N && number_of_squares != 1) ||
             (x_new + 1 < N - 1 && y_new + 1 < N - 1)) &&
            (!square[x_new + 1][y_new + 1] || square[x_new + 1][y_new + 1] == number_of_squares) &&
            (!square[x_new + 1][y_new] || square[x_new + 1][y_new] == number_of_squares)
            && (!square[x_new][y_new + 1] || square[x_new][y_new + 1] == number_of_squares)) {
            if (!square[x_new + 1][y_new]) {
                components_of_square.emplace_back(make_pair(x_new + 1, y_new));
                curr_components.emplace_back(make_pair(x_new + 1, y_new));
            }
            if (!square[x_new][y_new + 1]) {
                components_of_square.emplace_back(make_pair(x_new, y_new + 1));
                curr_components.emplace_back(make_pair(x_new, y_new + 1));
            }
            if (!square[x_new + 1][y_new + 1]) {
                components_of_square.emplace_back(make_pair(x_new + 1, y_new + 1));
                curr_components.emplace_back(make_pair(x_new + 1, y_new + 1));
            }
        } else
            check = false;
    }
    if (check) {//если можно. рекурсивно запускаем процесс для следующей вершины
        for (int i = 0; i < curr_components.size(); i++) {
            coordinates = curr_components[i];
            x_new = coordinates.first;
            y_new = coordinates.second;
            square[x_new][y_new] = number_of_squares;
        }
        //printBoard(square,N);
        setPosition(square, best_square_version, N, x + 1, y + 1, number_of_squares, min, components_of_square,
                    forward);
    } else {
        search_first_elem(square, x_new, y_new, N);//если нельзя, ищем свободную позицию для построения следующего квадрата
    }
    if (x_new != -1) {
        if (!forward) {//вернувшись до ближайшего не единичного квадрата, изменяем его размер и продолжаем построение
            if(number_of_squares + 1 >= min)
                return;
            remove_numbers(square, N, number_of_squares, x, y);
            search_first_elem(square, x_new, y_new, N);
            forward = true;
        }
        forward = true;
        components_of_square.resize(0);
        components_of_square.emplace_back(make_pair(x_new, y_new));
        square[x_new][y_new] = number_of_squares + 1;
        if(number_of_squares + 1 < min) {
            setPosition(square, best_square_version, N, x_new, y_new, number_of_squares + 1, min, components_of_square,
                        forward);
        }
        else {
            forward = false;
        }
    } else {
        if (number_of_squares < min) {//если все клетки заняты, возвращаемся до ближайшего не единичного квадрата
            min = number_of_squares;
            copy(square, best_square_version, N);//если к-ство квадратов при данной конфигурации минимально, сохраняем текущее расположение
            // cout << "Печать наилучшего на данное время решения" << "\n";
            //printBoard(best_square_version,N);
        }
        forward = false;
    }
}
 
void menu(int N,int** square,int** best_square_version){
    bool forward = true;
    deque<pair<int,int>> components_of_square;
    int min = (N * N) - (N - 1) * (N - 1) + 1;
    memoryInitialization(square,best_square_version,N);
    if((N % 2 && N % 5 && N % 3) || (N == 3) || (N == 5)) {
        components_of_square.emplace_back(make_pair(N / 2 + 1,N / 2));
        Intialization(square,N);
        setPosition(square, best_square_version, N, N / 2 + 1, N / 2, 4, min, components_of_square, forward);
    }
    else
    if(!(N % 2))
        printMultipleTwo(N);
    else
    if(!(N % 3))
        printMultipleThree(N);
    else
    if(!(N % 5)){
        int coord1 = N - N / 5 - N /5;
        int coord2 = N - coord1;
        Initialize(square, N, coord1, coord2);
        components_of_square.emplace_back(make_pair(coord1, coord2));
        setPosition(square, best_square_version, N, coord1, coord2, 5, min, components_of_square, forward);
        cout << min << "\n";
        printResult(best_square_version, N, min);
    }if((N % 2 && N % 5 && N % 3) || (N == 3) || (N == 5)) {
        cout << min << "\n";
        printResult(best_square_version, N, min);
    }
}
 
int main() {
    srand(time(0));
    time_t start;
    time(&start);
    start = clock();
    deque<pair<int,int>> components_of_square;
    int N;
    cin >> N;
    int** square = new int*[N];//массив для текущей конфигурации
    int** best_square_version = new int*[N];//массив для наилучшей конфигурации.
    menu(N,square,best_square_version);
    clear(square,best_square_version,N);
    time_t end;
    end = clock();
    std::cout << (end - start)/1000 << "sec\n";
    return 0;
}