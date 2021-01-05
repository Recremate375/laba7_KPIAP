#include <iostream>
#include <string>
#include <ostream>

class MyException {
private:
    std::string error;
public:
    MyException(std::string _error = "Something wrong") : error(_error) {};
    const char* what() {
        return error.c_str();
    }
};


class exam
{
private:
    int id;
    std::string name;
    float result;
public:
    exam() : name(" "), result(0.0)
    {
        id++;
    }
    exam(std::string n) : name(n), result(0.0)
    {
        id++;
    }
    exam(std::string n, float r) : name(n), result(r)
    {
        id++;
    }
    ~exam()
    { }
    std::string get_name()
    {
        return this->name;
    }
    int get_id()
    {
        return this->id;
    }
    float get_result()
    {
        return this->result;
    }
    bool operator< (exam ex)
    {
        return this->name < ex.name;
    }
    bool operator==(exam ex)
    {
        return (this->name == ex.name) && (this->result == ex.result);
    }
    friend std::ostream& operator <<(std::ostream &out, exam &ex);
    exam& operator= (exam ex)
    {
        this->name = ex.name;
        this->result = ex.result;
        return *this;
    }
};

std::ostream& operator <<(std::ostream &out, exam &ex)
{
    return out << "name: " << ex.get_name() << "/t" << "Result: " << ex.get_result();
}

template <typename T>
class Double_list {
public:
    static int size;

    class Node {
    public:
        Node *next;
        Node *prev;
        T data;
        Node() {};
        Node(T _data) {
            size++;
            this->data = _data;
        }
    };

    class Iterator {
    private:
        Node *node;
    public:
        Iterator() : node() {};
        Iterator(Iterator &it) : node(it.node) {};
        Iterator(Node *node) : node(node) {};
        Iterator& operator++() {
            node = node->next;
            return *this;
        }
        Iterator& operator+(int value) {
            int i = 0;
            while (i < value) {
                node = node->next;
                i++;
            }
            return *this;
        }
        Iterator& operator-(int value) {
            int i = 0;
            while (i < value) {
                node = node->prev;
                i++;
            }
            return *this;
        }
        Iterator& operator--() {
            node = node->prev;
            return *this;
        }
        Iterator& operator=(Iterator it) {
            this->node = it.node;
            return *this;
        }
        T& operator*() {
            return node->data;
        }
        bool operator==(Iterator it) {
            return this->node == it.node;
        }
        bool operator!=(Iterator it) {
            return this->node != it.node;
        }
        bool operator>(Iterator it) {
            return this->node > it.node;
        }
        bool operator<(Iterator it) {
            return this->node < it.node;
        }

    };

    int getSize() {
        return size;
    }

private:
    Node *head;
    Node *tail;
    Iterator *headIterator;
    Iterator *tailIterator;

public:
    Double_list() {
        head = tail = nullptr;
    }

    Double_list(T _data) {
        tail = head = new Node(_data);
        headIterator = tailIterator = new Iterator(head);
    }

    int find(T _data) {
        Node *tmp = head;
        int index = 0;
        while (tmp != nullptr) {
            if (tmp->data == _data) {
                return index;
            }
            index++;
            tmp = tmp->next;
        }
        return index;
    }

    void remove_back() {
        Node *tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
        size--;
        tailIterator = new Iterator(tail);
    }

    void remove_front() {
        Node *tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
        size--;
        headIterator = new Iterator(head);
    }

    void push_back(T _data) {
        Node *current = new Node(_data);
        if (head == nullptr) {
            current->next = nullptr;
            current->prev = nullptr;
            tail = current;
            head = current;
        }
        else {
            current->next = nullptr;
            current->prev = tail;
            tail->next = current;
            tail = current;
            tailIterator = new Iterator(tail);
        }
    }

    void push_front(T _data) {
        Node *current = new Node(_data);
        if (head == nullptr) {
            current->next = nullptr;
            current->prev = nullptr;
            tail = current;
            head = current;
        }
        else {
            current->prev = nullptr;
            current->next = head;
            head->prev = current;
            head = current;
            headIterator = new Iterator(head);
        }
    }

    void add_without_duplicates(T _data) {
        Node *tmp = head;
        while (tmp != nullptr) {
            if (tmp->data == _data) {
                throw MyException("Duplicate");
                return;
            }
            tmp = tmp->next;
        }
        Node *current = new Node(_data);
        current->next = nullptr;
        current->prev = tail;
        tail->next = current;
        current->data = _data;
        tail = current;
        tailIterator = new Iterator(tail);
    }

    void print_list() {
        if (size != 0) {
            Node *tmp = head;
            while (tmp != nullptr) {
                std::cout << tmp->data << std::endl;
                tmp = tmp->next;
            }
        }
        else {
            throw MyException("Empty list");
        }
    }

    Iterator& begin() {
        return *headIterator;
    }

    Iterator& end() {
        return *tailIterator;
    }

    bool is_empty() {
        return head == tail;
    }

    T& operator[](int index) {
        Node *tmp = head;
        int cnt = 0;
        while (cnt != index) {
            cnt++;
            tmp = tmp->next;
        }
        return tmp->data;
    }

};

template <typename T>
void bubble_sort(Double_list<T> &list) {
    for (int i = 0; i < list.getSize() - 1; i++) {
        for (int j = 0; j < list.getSize() - 1 - i; j++) {
            if (list[j + 1] < list[j]) {
                T tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
}


template <typename T>
int Double_list<T>::size = 0;


int main() {
    std::cout << "Word with int" << std::endl;
    Double_list<int> intec;

    try
    {
        intec.print_list();
    }
    catch(MyException &ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    intec.push_back(33);
    intec.push_back(15);
    intec.push_front(46);

    try {
        intec.add_without_duplicates(15);
    }
    catch (MyException &ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    intec.add_without_duplicates(24);
    intec.remove_back();

    std::cout << "Before sort: " << std::endl;
    intec.print_list();

    bubble_sort(intec);

    std::cout << "First element after sort: " << *intec.begin() << std::endl;

    std::cout << "Index of Alex: " << intec.find(14) << std::endl;
    std::cout << "Size of list: " << intec.getSize() << std::endl;

    std::cout << std::endl;

    intec.print_list();

    std::cout << "After changing" << std::endl;

    auto i = intec.begin();
    *i = 12 ;
    *(i + 1) = 40;

    intec.print_list();

    std::cout << "Work with double" << std::endl;

    Double_list<double> doublic;

    try
    {
        doublic.print_list();
    }
    catch (MyException &ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    doublic.push_back(33.1);
    doublic.push_back(15.2342);
    doublic.push_front(46.1314);

    try {
        doublic.add_without_duplicates(15.2342);
    }
    catch (MyException &ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    doublic.add_without_duplicates(24);
    doublic.remove_back();

    std::cout << "Before sort: " << std::endl;
    doublic.print_list();

    bubble_sort(doublic);

    std::cout << "First element after sort: " << *doublic.begin() << std::endl;

    std::cout << "Index of Alex: " << doublic.find(14) << std::endl;
    std::cout << "Size of list: " << doublic.getSize() << std::endl;

    std::cout << std::endl;

    doublic.print_list();

    std::cout << "After changing" << std::endl;

    auto b = doublic.begin();
    *b = 11.9;
    *(b + 1) = 39.5;

    doublic.print_list();

    std::cout << "Work with My class" << std::endl;

    Double_list<exam> list;

    try {
        list.print_list();
    }
    catch (MyException &ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    list.push_back({ "John", 99.9 });
    list.push_back({ "Alex", 80.2 });
    list.push_front({ "Leo", 12 });

    try {
        list.add_without_duplicates({ "Alex", 80.2 });
    }
    catch (MyException &ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    list.add_without_duplicates({ "Bob", 60.1 });
    list.remove_back();

    std::cout << "Before sort: " << std::endl;
    list.print_list();

    bubble_sort(list);

    std::cout << "First element after sort: " << *list.begin() << std::endl;

    std::cout << "Index of Alex: " << list.find({ "Alex", 80.2 }) << std::endl;
    std::cout << "Size of list: " << list.getSize() << std::endl;

    std::cout << std::endl;

    list.print_list();

    std::cout << "After changing" << std::endl;

    auto a = list.begin();
    *a = { "Harry", 12 };
    *(a + 1) = { "Joseph", 40 };

    list.print_list();

    system("pause;");
    return 0;
}