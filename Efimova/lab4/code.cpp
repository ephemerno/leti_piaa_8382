#include <iostream>
#include <vector>

//вычисление префикс-функции, возвр. знач = макс.длине совпад. преф. и суфф. подстроки в образе
/*
vector<int>* vector - массив pi[i],хранит макс.
pi[0] = 0; i = 1; j = 0;
пока не законч. образ и провер. одно условие:
if(ai == aj) -> pi[i] = j + 1; i++; j++;
else if(j == 0) -> pi[i] = 0; i++ (j стоит в нач. образа)
else j = pi[j - 1] (ai != aj && j != 0)
*/
void Array_Pi(std::vector<int>* vector, std::string* string, int length) {

    int j = 0;
    int i = 1;

    vector->emplace_back(0);//первый символ всегда в ноль

    while (length > i) {
        if (string->at(i) == string->at(j)) {
            vector->emplace_back(j + 1);
            i++;
            j++;
        }
        else {
            if (j == 0) {
                vector->emplace_back(0);
                i++;
            }
            else {
                j = vector->at(j - 1);
            }
        }
    }
}

/*
int k = индекс,указывающий на символ в строке-тексте
int n - это длина строки образа
сравнивается текущий символ(char c) строки-текста и текущий l -й элемент строки-образа.
Если равны,то сдвиг l -го элемента строки-образа; k++.
после совпадения символов,проверка на равенство l номера строки-образа и переменной n.
если это верно, то вхождение найдено и происходит запись индекса начала вхождения вектор ответа(vector<int> output).
*/
void function(std::vector<int>* vector, char symbol, int l, int n, std::string string,  int k, std::vector<int>* output)
{
    while (true) {
        bool input = true;//флаг для считывания

        if (symbol == string[l]) {//проверка совпадает ли текущий символ текста с символом строки-образца
            std::cout << symbol << std::endl;
            l++;
            k++;
            if (l == n) {
                std::cout << "Вхождение строки = " << k - n << std::endl;
                output->emplace_back(k - n);
            }
        }
        /*
        текущий символ строки-текста и текущий l -й элемент строки-образа не равны, то проверка,на индекс в нуле.
        Если это верно, увеличиваем на единицу индекс, который указывает на символ в строке-тексте.
        Иначе, если индекс не равен 0, то происходит перемещение позиции индекса l из одной позиции в другую.
        */
        else {
            if (l == 0) {
                k++;
            }
            else {
                std::cout << "Двигаем строку" << std::endl;
                l = vector->at(l - 1);
                input = false;
            }
        }

        if (input) {
            std::cin.get(symbol);
        }

        if (symbol == '\n') {
            break;
        }
    }
}
/*
прописан ввод строки-образа и посимвольное считывание строки-текста),
вызов функции для составления массива pi для заданного образа и функции нахождения образа в тексте и вывод ответа
*/
int main() {
    std::string string;
    std::cin >> string;

    std::vector<int> vector;
    vector.reserve(0);
    std::vector<int> output;
    vector.reserve(0);
    
    Array_Pi(&vector, &string, string.length());
    std::cout << "Ввод строки" << std::endl;
    int l = 0;
    int n = string.size();
    int k = 0;
    char symbol;
    std::cin.get(symbol);
    std::cin.get(symbol);//считываем первый символ строки-текста
    function(&vector, symbol, l, n, string,  k, &output) ;

    if (!output.empty()) {
        for (size_t z = 0; z < output.size(); ++z) {//output the response
            std::cout << output[z];
            if (z != output.size() - 1)
                std::cout << ",";
        }
    }
    else {
        std::cout << -1 << std::endl;
    }

    return 0;
} 

