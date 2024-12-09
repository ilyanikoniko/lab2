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
 LinkedList(const LinkedList& other): head(nullptr), tail(nullptr), size(0)
 {
   if (other.head == nullptr) {
            return;  
        }

        Node* ptr = other.head;  
        do {
            
            push_back(ptr->data);
            ptr = ptr->next;  
        } while (ptr != other.head);  

        size = other.size;  
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
  if(head==nullptr) return;
  while (head != nullptr) {
        pop_head();
    }
}

LinkedList& operator=(const LinkedList& other)
{
     if (this != &other) {
            this->~LinkedList(); 
            new (this) LinkedList(other); 
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
                    delete ptr;  
                    size--;  
                }
            }
            ptr = nextNode;  
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

friend std::ostream& operator<< (std::ostream& stream, const LinkedList<T>& list)
{
    if (list.head == nullptr) {
        stream << "()"; \
        return stream;
    }
    Node<T>* ptr = list.head;
    stream << "("; 
    do{
        stream<<ptr->list.data;
        ptr = ptr->next;
        if (ptr != list.head) {
            stream << ", "; 
        }
    }while(ptr!=list.head);

    stream << ")"; 
    return stream;
}
}; 

template<typename T>
void reverse(LinkedList<T>& list) {
    if (list.head == nullptr) return; 

    Node<T>* ptr = list.head;
    Node<T>* temp = nullptr;

    
    do {
        temp = ptr->prev; 
        ptr->prev = ptr->next; 
        ptr->next = temp; 
        ptr = ptr->prev; 
    } while (ptr != list.head); 

    
    temp = list.head; 
    list.head = list.tail; 
    list.tail = temp; 
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    LinkedList<int> a(1,2,3);
}