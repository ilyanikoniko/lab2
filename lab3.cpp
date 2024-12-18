using namespace std;
#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
#include <chrono>

struct stats 
{ 
    size_t comparison_count = 0; 
    size_t copy_count = 0; 
};

stats sort_insert(vector<int>& a)
{
    stats result;
    for(int i=1; i<a.size(); i++)
    {   
        for(int j=i; j>0; j--)
        {
            result.comparison_count++;
            if(a[j-1]>a[j])
            {  
            int tmp=a[j-1];
			a[j-1]=a[j];
			a[j]=tmp;
            result.copy_count += 3;
            }
        }
    }
    return result;
}

stats comb_sort(vector<int>& a) 
{	int tmp,k;
    stats result;
    size_t size = a.size();
	int s=size; // готовим начальный шаг

	while(size>1) {
		s/=1.247f;

		if (s<1) 
        {
            s=1; 
        }
		k=0; // нет перестановок
		for (int i=0; i+s<size;++i) { // двигаемся, пока сравниваемый элемент (на s от текущего) в массиве
            result.comparison_count++;
			if(a[i]>a[i+s]) 
            {
				tmp=a[i];
				a[i]=a[i+s];
				a[i+s]=tmp; 	
                result.copy_count+=3;
				k=i;
			}
		}
		if (s==1) // шаг 1, как в обычном пузырьке. Включаем контроль
        {
           
		    size=k+1; 
        }
	}
    return result;
}

void heapify(vector<int>& arr, int n, int i, stats& result)
{
    int largest = i;  
    int tmp; 
// Инициализируем наибольший элемент как корень
    int l = 2*i + 1; // левый = 2*i + 1
    int r = 2*i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
    result.comparison_count++;
    if (l < n )
    {
        result.comparison_count++;
        if(arr[l] > arr[largest])
        {
            largest = l;
        }
    }
    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    result.comparison_count++;
    if (r < n )
    {
        result.comparison_count++;
        if(arr[r] > arr[largest])
        {
        largest = r;
        }
    }
    // Если самый большой элемент не корень
    if (largest != i)
    {
        tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        result.copy_count+=3;
    // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest, result);
    }
}

stats heap_sort(vector<int>& arr)
{
    stats result;
    size_t n = arr.size();
    int tmp; 
  // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, result);

   // Один за другим извлекаем элементы из кучи
    for (int i=n-1; i>=0; i--)
    {
        // Перемещаем текущий корень в конец
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        result.copy_count+=3;
        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0, result);
    }
    return result;
}

// Функция для генерации случайного массива
vector<int> generate_random_array(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Функция для генерации отсортированного массива
vector<int> generate_sorted_array(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

// Функция для генерации обратно отсортированного массива
vector<int> generate_reverse_sorted_array(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

void task_sort_insert(vector<stats>& statistic, size_t size,  vector<vector<int>>& num,  vector<vector<int>>& num1,  vector<vector<int>>& num2)
{
	stats stat1;
	stats stat2;
	stats stat3;

	
	for (size_t i = 0; i < 100; i++)
	{
		stats result1 = sort_insert(num[i]);
		stat1.comparison_count += result1.comparison_count;
		stat1.copy_count += result1.copy_count;
	}

	stat1.comparison_count = stat1.comparison_count / 100;
	stat1.copy_count = stat1.copy_count / 100;
	statistic.push_back(stat1);

	
	stats result2 = sort_insert(num1[0]);
	stat2.comparison_count += result2.comparison_count;
	stat2.copy_count += result2.copy_count;
	statistic.push_back(stat2);

	
	stats result3 = sort_insert(num2[0]);
	stat3.comparison_count += result3.comparison_count;
	stat3.copy_count += result3.copy_count;
	statistic.push_back(stat3);
}

void task_comb_sort(vector<stats>& statistic, size_t size,  vector<vector<int>>& num,  vector<vector<int>>& num1,  vector<vector<int>>& num2)
{
	stats stat1;
	stats stat2;
	stats stat3;

	for (size_t i = 0; i < 100; i++)
	{
		stats result1 = comb_sort(num[i]);
		stat1.comparison_count += result1.comparison_count;
		stat1.copy_count += result1.copy_count;
	}
	stat1.comparison_count = stat1.comparison_count / 100;
	stat1.copy_count = stat1.copy_count / 100;
	statistic.push_back(stat1);

	
	stats result2 = comb_sort(num1[0]);
	stat2.comparison_count += result2.comparison_count;
	stat2.copy_count += result2.copy_count;
	statistic.push_back(stat2);


	stats result3 = comb_sort(num2[0]);
	stat3.comparison_count += result3.comparison_count;
	stat3.copy_count += result3.copy_count;
	statistic.push_back(stat3);
}

void task_heap_sort(vector<stats>& statistic, size_t size,  vector<vector<int>>& num,  vector<vector<int>>& num1,  vector<vector<int>>& num2)
{
	stats stat1;
	stats stat2;
	stats stat3;

	for (size_t i = 0; i < 100; i++)
	{
		stats result1 = heap_sort(num[i]);
		stat1.comparison_count += result1.comparison_count;
		stat1.copy_count += result1.copy_count;
	}
	stat1.comparison_count = stat1.comparison_count / 100;
	stat1.copy_count = stat1.copy_count / 100;
	statistic.push_back(stat1);

	
	stats result2 = heap_sort(num1[0]);
	stat2.comparison_count += result2.comparison_count;
	stat2.copy_count += result2.copy_count;
	statistic.push_back(stat2);


	stats result3 = heap_sort(num2[0]);
	stat3.comparison_count += result3.comparison_count;
	stat3.copy_count += result3.copy_count;
	statistic.push_back(stat3);
}

ostream& operator<<(ostream& stream, const stats& s) 
{
    stream << "Количество сравнений: " << s.comparison_count << ", Количество копирований: " << s.copy_count;
    return stream;
}

ostream& operator<<(ostream& stream, const vector<int>& v)
{
    stream<< "(";
    for (size_t i = 0; i < v.size() - 1; ++i) 
    {
        cout << v[i] << ",";  
    }
    cout<<v[v.size()-1];
    cout<<")";
    return stream;
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(65001);   
    SetConsoleOutputCP(65001);

    vector<int> arr = {6,4,2,8,9};
    vector<int> arr1 = {6,4,2,9,8};
    vector<int> arr2 = {6,4,2,8,9};
    cout<<"Исходный массив:"<<endl;
    cout<<arr<<endl;
    stats result = sort_insert(arr);
    cout<<"Отсортированный массив:"<<endl;
    cout<<arr<<endl;
    cout<<result<<endl;
    cout<<"Исходный массив:"<<endl;
    cout<<arr1<<endl;
    stats result2 = comb_sort(arr1);
    cout<<"Отсортированный массив:"<<endl;
    cout<<arr1<<endl;
    cout<<result2<<endl;
    cout<<"Исходный массив:"<<endl;
    cout<<arr2<<endl;
    stats result3 = heap_sort(arr2);
    cout<<"Отсортированный массив:"<<endl;
    cout<<arr2<<endl;
    cout<<result3<<endl;

    auto start = chrono::high_resolution_clock::now();
    vector<stats> stat_sort_insert;
    vector<stats> stat_comb_sort;
    vector<stats> stat_heap_sort;

    int size[] = {1000};
    for (size_t i = 0; i < sizeof(size) / sizeof(size[0]); i++)
    {
        vector<vector<int>> num;
        vector<vector<int>> num1;
        vector<vector<int>> num2;
        vector<int> arr(size[i]);
        for (size_t g = 0; g < size[i]; g++)
        {
            arr.push_back(g);
        }
        vector<int> arr2(size[i]);
        for (size_t j = size[i]; j > 0; j--)
        {
            arr2.push_back(j);
        }
        for (size_t j = 0; j < 100; j++)
        {
            num.push_back(generate_random_array(size[i]));
        }
        num1.push_back(arr);
        num2.push_back(arr2);
        task_sort_insert(stat_sort_insert, size[i], num, num1, num2);
        task_comb_sort(stat_comb_sort, size[i], num, num1, num2);
        task_heap_sort(stat_heap_sort, size[i], num, num1, num2);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    std::cout << "printf: " << duration.count() << '\n';

   for (size_t i = 0; i < sizeof(size) / sizeof(size[0]); i++)
{
    cout << "\nСтатистика для массива размером " << size[i] << ":" << endl;

    cout << "\n  Сортировка вставками:" << endl;
    // Вывод статистики для сортировки вставками
    cout << "  Средняя статистика для случайных массивов: " << stat_sort_insert[i * 3 + 0] << endl;
    cout << "  Статистика для отсортированного массива: " << stat_sort_insert[i * 3 + 1] << endl;
    cout << "  Статистика для обратного отсортированного массива: " << stat_sort_insert[i * 3 + 2] << endl;

    cout << "\n  Сортировка расчёской:" << endl;
    // Вывод статистики для сортировки расчёской
    cout << "  Средняя статистика для случайных массивов: " << stat_comb_sort[i * 3 + 0] << endl;
    cout << "  Статистика для отсортированного массива: " << stat_comb_sort[i * 3 + 1] << endl;
    cout << "  Статистика для обратного отсортированного массива: " << stat_comb_sort[i * 3 + 2] << endl;

    cout << "\n  Пирамидальная сортировка:" << endl;
    // Вывод статистики для пирамидальной сортировки
    cout << "  Средняя статистика для случайных массивов: " << stat_heap_sort[i * 3 + 0] << endl;
    cout << "  Статистика для отсортированного массива: " << stat_heap_sort[i * 3 + 1] << endl;
    cout << "  Статистика для обратного отсортированного массива: " << stat_heap_sort[i * 3 + 2] << endl;
}
    return 0;
}