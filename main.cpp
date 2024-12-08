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
    Node<T>* ptr = other.tail; 
    do  {
            push_head(ptr->data);  
            ptr = ptr->prev;
        } while (ptr != other.tail);  
    }   

    void push_back(const T& data)
    {
         Node<T>* ptr = new Node<T>(data);
 if (tail == nullptr)
 {
     ptr->next = ptr->prev = ptr;
     tail = ptr;
     head = ptr;
 }
 else
 {
     ptr->next = head;
     ptr->prev = tail;
     head->prev = ptr;
     tail->next = ptr;
     tail = ptr;
 }
 size++;
    }

void push_back(const LinkedList<T>& other)
{
    if (other.tail == nullptr) return; 
    if (tail==nullptr){
            tail = other.tail;
            return;
        }
       Node<T>* ptr = other.head; 
    do {
            push_back(ptr->data);  
            ptr = ptr->next;
        } while (ptr != other.head);  
    }    

void pop_head()
{
     if (head == nullptr) return;
       if (head->next == head)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node<T>* ptr = head->next;
        tail->next = ptr;
        ptr->prev = tail;
        delete head;
        head = ptr;
    }
    size--;
}

void pop_tail()
{
 if (tail == nullptr) return;
 if (tail->prev == tail)
 {
     delete tail;
     tail == nullptr;
 }
 else 
 {
     Node<T>* ptr = tail->prev;
     head->prev = ptr;
     ptr->next = head;
     delete tail;
     tail = ptr;
 }
 size--;
}

void delete_node(const T& value) {
        if (head == nullptr) {  
            return;
        }
    Node<T>* ptr = head->next;
    Node<T>* first = head;
    do{
       Node<T>* nextNode = ptr->next;
       if (ptr->data == value) {  
                if (ptr == head) {
                    pop_head();  
                } 
                else 
                {
                    Node<T>* nextNode = ptr->next;
                    prevNode->next = nextNode;  
                    nextNode->prev = prevNode;  
                    delete ptr;  // Удаляем узел
                    size--;  // Уменьшаем размер списка
                }
            }
            ptr = nextNode;  // Переходим к следующему узлу
                }
    }while(ptr!=first); 

T& operator [] (int index)
{
    Node* ptr = head;
    int n = 0;
    while(n!=index || ptr!=head)
    {
        ptr = ptr->next;
        n++;
    }
    return ptr->data;
}

const T& operator [] (int index) const
{
    Node* ptr = head;
    int n = 0;
    while(n!=index || ptr!=head)
    {
        ptr = ptr->next;
        n++;
    }
    return ptr->data;
}
}; 