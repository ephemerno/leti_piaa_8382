/******************************************************************************

 //                             Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

//класс квадрата
class Square{
    int x;
    iny y;
    int lenght;
};

 // функция для вывода массива
 
 void demo(int **arr, int N){
     for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cout << arr[i][j] << ' ' << endl;
            
            
        
 }

 // функция для инициализации квадрата в массиве в соотв. с параметрами х,у,lenght_sq
 
 void fill_square(int **arr, int x, int y, int lenght_sq){
     for(int i = 0; i < lenght_sq; i++)
        for( int j = 0; j < lenght_sq; j++)
            arr[x+i][y+j] = lenght_sq;
 }
 
 
 // функция копирования стека
 
 void stack_copy(stack <Square> *sqrs, stack <Square> *sqrs_copy){
     while(!sqrs->empty()){
         sqrs_copy->push(sqrs->top());
         sqrs->pop();
     }
 }
 
 // функция нахождения пустой клетки в массиве arr. Переводит значения x и y в соответствии с ее координатами  
 // Возвращает 1, когда нет пустых клеток, и 0 в обратном
 
 int find_emptycell(int **arr, int &x, int &y, int N){
     for( int x = 0; x < N; x++)
        for(int y = 0; y < N; y++)
            if(arr[x][y] == 0)
                return 0;
    if(x == N)
        return 1;
    else
        return 0;
}


// функция опустошения стека 

void empty_stack(stack <Square> *sqrs){
    while(!sqrs->empte())
        sqrs->pop();
}


// функция нахождения максимальной длины квадрата, которого можно вписать в массив 

int find_max_lenght(int **arr, int &x, int &y, int N){
    int distance_to_border = (N - x > N - y) ? (N - y - !arr[0][0]) : (N - x - !arr[0][0]);
    int length_square = 2;
    for(; length_square <= distance_to_border; length_square++){
        for( int i = 0; i < length_square; i++){
            if(arr[x + length_square - 1][y + i] || arr[x + i][y + length_square - 1])
                return length_square - 1;
        }
    }
    return length_square - 1;
}

// рекурсивная функция для перебора возможных значений расстановки квадратов 
int find_min_sqrs(int limit, stack <Square> *sqrs,int **arr, int N, int count_rec){ 
     if(limit < count_rec)
        return -1;
    #ifdef DEBUG
    demo(arr, N);
    #endif
    int x, y;
    if(find_empty_cell(arr, x, y, N))
        return 0; 
     stack <Square> sqrs_tmp;
     stack <Square> sqrs_max;
     
     int max_length = find_max_length(arr, x, y, N);
     int length_square, k_min = limit + 1, k, need_length = 1;
     
     for(length_square = 1; length_square <= max_length; length_square++){   
         fill_square(arr, x, y, length_square);
          k = find_min_sqrs(limit, &sqrs_tmp, arr, N, count_rec+1)+1;
    #ifdef DEBUG
    cout << "CURRENT K : " << k << ", K_MIN : " << k_min << endl;
    demo(arr, N);
    #endif 
    
     if(k < k_min && k != 0){ 
          k_min = k;
          need_length = length_square;
          while(!sqrs_max.empty()){
                sqrs_max.pop();
          }
           stack_copy(&sqrs_tmp, &sqrs_max); 
     }
      else
        empty_stack(&sqrs_tmp);
         for(int i = 0; i < length_square; i++)
            for(int j = 0; j < length_square; j++)
                arr[x+i][y+j] = 0;
     }
    
     while(!sqrs->empty())
        sqrs->pop();
    stack_copy(&sqrs_max, sqrs);
    sqrs->push({x, y, need_length});
    return k_min;
    }
    
    int main(){
        int N;
        int min_k;
        cin >> N;
        unsigned int start = clock(); // определение начала времени работы 
         
        stack <Square> sqrs;
        int mul = multiplicity(N);
        int limit = 6.37 * sqrt(sqrt((mul == 1) ? N : mul));
        int arr*;

        if(mul != 1){
            arr = new int *[mul];
            for( int i = 0; i < mul; i++)
                arr[i] = new int[mul];
            min_k = find_min_sqrs(limit, &sqrs, arr, mul, 0); 
        }
        else{
            arr = new int *[N];
            for(int i = 0; i < N; i++)
                arr[i] = new int[N]();
            int half = N-N/2;
            fill_square(arr, 0, 0, half); 
            fill_square(arr, half, 0, half - 1); 
            fill_square(arr, 0, half, half - 1); 

            min_k = find_min_sqrs(limit - 3, &sqrs, arr, N, 0) + 3;
            sqrs.push({half, 0, half - 1});
            sqrs.push({0, half, half - 1});
            sqrs.push({0, 0, half}); 
        }
        cout << min_k << endl;

        Square tmp;
        int scale = (mul != 1) ? N/mul : 1; 
        while(!sqrs.empty()){
            tmp = sqrs.top();
            cout << tmp.x * scale + 1 << " " << tmp.y*scale +1 << " " << tmp.length*scale << endl;
            sqrs.pop();  
        }

        unsigned int finish = clock(); // определение конца времени работы 
        cout << "TIME : " << finish - start << endl;
        if(mul!=1) // отчистка массива 
             for(int i = 0; i < mul; i++) 
                delete [] arr[i]; 
            else
                 for(int i = 0; i < N; i++) 
                    delete [] arr[i]; 
                delete [] arr;
                return 0;
}
    