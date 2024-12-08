using namespace std;

#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <random>

template<typename T>
 struct Node {
public:
    double data;
    Node* prev, * next;
    Node(double value)
    {
        data = value;
        this->prev = this->next = nullptr;
    }
};

template<typename T>
class LinkedList {
    private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
 LinkedList(): head(nullptr), tail(nullptr), size(0) {}
 LinkedList(const LinkedList& other): head(nullptr), size(0)
 {
    if (other.head == nullptr) {
       head == nullptr;
       return;
    }

    if (other.head != nullptr) {
        Node* currentOther = other.head;
        Node* previousNew = nullptr;

        while (currentOther != nullptr) {
            Node* newNode = new Node(currentOther->data);
            if (previousNew != nullptr) {
                previousNew->next = newNode;
                newNode->prev = previousNew;
            } else {
                head = newNode;
            }
            previousNew = newNode;
            currentOther = currentOther->next;
        }
        size = other.size;
    }
 }

LinkedList(int numElements, double minValue, double maxValue, unsigned int seed = std::random_device{}()) 
        : head(nullptr), tail(nullptr), size(0) {
        
        // Инициализация генератора случайных чисел
        std::default_random_engine generator(seed);
        std::uniform_real_distribution<double> distribution(minValue, maxValue);

        // Добавление случайных чисел в список
        for (int i = 0; i < numElements; ++i) {
            double randomValue = distribution(generator);
            this->append(randomValue);
        }
    }

~LinkedList()
{

}

LinkedList& operator=(const LinkedList& other)
{
     if (this != &other) {
            this->~LinkedList(); // уничтожаем текущий список
            new (this) LinkedList(other); // инициализируем новым копированием
        }
        return *this;
}

 void push_head(const T& data)
 {
     Node<T>* ptr = new Node<T>(data);
     if (head == nullptr)
{
    ptr->next = ptr->prev = ptr;
    head = ptr;
}
else
{
    ptr->next = head;
    ptr->prev = tail;
    head->prev = ptr;
    tail->next = ptr;
    head = ptr;
}
size++;
 }

  void push_head(const LinkedList<T>& other) {
    if (other.head == nullptr) return; 
    if (head==nullptr){
            head = other.head;
            return;
        }
    Node<T>* ptr = other.head; 
    do {
            push_head(ptr->data);  
            ptr = ptr->next;
        } while (ptr != other.head);  
    }   
}; 