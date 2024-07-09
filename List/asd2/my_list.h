#include <initializer_list>
#include <memory>
#include <iterator>


//template<typename T>
//class MyList
//{
//private:
//    struct mynode {
//        T data;
//        mynode* next;
//        mynode* prev;
//        mynode(T d, mynode* p, mynode* n) : data(d), prev(p), next(n) {}
//    };
//
//    mynode* head, * tail;
//    size_t _size;
//public:
//
//    using value_type = T;
//    using size_type = size_t;
//    using difference_type = ptrdiff_t;
//    using pointer = value_type*;
//    using const_pointer = const value_type*;
//    using reference = value_type&;
//    using const_reference = const value_type&;
//
//    class iterator {
//        mynode* p;
//    public:
//        using value_type = T;
//        using iterator_category = std::bidirectional_iterator_tag;
//        using difference_type = ptrdiff_t;
//        using pointer = T*;
//        using reference = value_type&;
//
//        iterator(mynode* pp) : p(pp) {}
//        T& operator*() { return p->data; }
//        iterator& operator++() {
//            p = p->next;
//            return *this;
//        }
//        iterator operator++(int) {
//            iterator rez(*this);
//            p = p->next;
//            return rez;
//        }
//        friend bool operator==(iterator v1, iterator v2) {
//            return v1.p == v2.p;
//        }
//        friend bool operator!=(iterator v1, iterator v2) {
//            return !(v1 == v2);
//        }
//
//    };
//
//    class const_iterator {
//        mynode* p;
//    public:
//        using value_type = T;
//        using iterator_category = std::bidirectional_iterator_tag;
//        using difference_type = ptrdiff_t;
//        using pointer = const T*;
//        using reference = const value_type&;
//
//        const_iterator(mynode* pp) : p(pp) {}
//        const T& operator*() const { return p->data; }
//        const_iterator& operator++() {
//            p = p->next;
//            return *this;
//        }
//        const_iterator operator++(int) {
//            const_iterator rez(*this);
//            p = p->next;
//            return rez;
//        }
//        friend bool operator==(const_iterator v1, const_iterator v2) {
//            return v1.p == v2.p;
//        }
//        friend bool operator!=(const_iterator v1, const_iterator v2) {
//            return !(v1 == v2);
//        }
//    };
//
//    MyList() : head(nullptr), tail(nullptr), _size(0) {};
//
//    MyList(const MyList& other) : MyList(other.cbegin(), other.cend()) {};
//
//    MyList(MyList&& other) : head(other.head), tail(other.tail), _size(other._size) {
//        other.head = nullptr;
//        other.tail = nullptr;
//        other._size = 0;
//    };
//
//    MyList(std::initializer_list<T> init) : MyList() {
//        for (auto x : init)
//            push_back(x);
//    }
//
//    template<typename iter>
//    MyList(iter start, iter fin) : MyList() {
//        while (start != fin)
//            push_back(*start++);
//    }
//
//    int countPositive() {
//        mynode* current = head;
//        int count = 0;
//        while (current != nullptr) {
//            if (current->data > 0) {
//                count++;
//            }
//            current = current->next;
//        }
//        return count;
//    }
//
//    void findMax() {
//        mynode* current = head;
//        int max = current->data;
//        int count = 1;
//        while (current != nullptr) {
//            if (current->data > max) {
//                max = current->data;
//                count = 1;
//            }
//            else if (current->data == max) {
//                count++;
//            }
//            current = current->next;
//        }
//
//        std::cout << max;
//    }
//
//    void splitList() {
//        MyList positiveList;
//        MyList negativeList;
//        mynode* current = head;
//        while (current != nullptr) {
//            if (current->data >= 0) {
//                positiveList.addNode(current->data);
//            }
//            else {
//                negativeList.addNode(current->data);
//            }
//            current = current->next;
//        }
//    }
//
//    void reverseList() {
//        mynode* temp = nullptr;
//        mynode* current = head;
//
//        while (current != nullptr) {
//            temp = current->prev;
//            current->prev = current->next;
//            current->next = temp;
//            current = current->prev;
//        }
//    }
//
//    void push_back(const T& value) {



//template<typename T>
//class MyList
//{
//public:
//    using value_type      = T;
//    using size_type       = size_t;
//    using difference_type = ptrdiff_t;
//    using pointer         = value_type*;
//    using const_pointer   = const value_type*;
//    using reference       = value_type&;
//    using const_reference = const value_type&;
//
//    template<typename Pointer, typename Reference>
//    class BaseIterator : public std::iterator<std::bidirectional_iterator_tag, value_type, difference_type, Pointer, Reference>
//    {
//    public:
//        bool operator==(const BaseIterator& other);
//        bool operator!=(const BaseIterator& other);
//        pointer operator->();
//        BaseIterator& operator--();
//        BaseIterator& operator--(int);
//        BaseIterator& operator++();
//        BaseIterator& operator++(int);
//        Reference operator*();
//    };
//
//    using iterator               = BaseIterator<pointer, reference>;
//    using const_iterator         = BaseIterator<const_pointer, const_reference>;
//    using reverse_iterator       = std::reverse_iterator<iterator>;
//    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
//
//    MyList();
//    MyList(const MyList& other);
//    MyList(MyList&& other);
//    MyList(std::initializer_list<T> init);
//
//    MyList& operator=(const MyList& other);
//    MyList& operator=(MyList&& other) noexcept;
//    MyList& operator=(std::initializer_list<T> ilist);
//
//    reference front();
//    const_reference front() const;
//    reference back();
//    const_reference back() const;
//
//    iterator begin() noexcept;
//    const_iterator begin() const noexcept;
//    const_iterator cbegin() const noexcept;
//    iterator end() noexcept;
//    const_iterator end() const noexcept;
//    const_iterator cend() const noexcept;
//
//    reverse_iterator rbegin() noexcept;
//    const_reverse_iterator rbegin() const noexcept;
//    const_reverse_iterator crbegin() const noexcept;
//    reverse_iterator rend() noexcept;
//    const_reverse_iterator rend() const noexcept;
//    const_reverse_iterator crend() const noexcept;
//
//    bool empty() const noexcept;
//    size_type size() const noexcept;
//
//    void clear() noexcept;
//
//    iterator insert(const_iterator pos, const T& value);
//    iterator insert(const_iterator pos, T&& value);
//
//    iterator erase(iterator pos);
//    iterator erase(const_iterator pos);
//    iterator erase(iterator first, iterator last);
//    iterator erase(const_iterator first, const_iterator last);
//
//    void push_back(const T& value);
//    void push_back(T&& value);
//    void pop_back();
//    void push_front(const T& value);
//    void push_front(T&& value);
//    void pop_front();
//
//    void swap(MyList& other) noexcept;
//
//    void reverse() noexcept;
//
//    ~MyList();
//};

#pragma once
#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template<typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    ~List() {
        Node<T>* temp = head;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    List() : head(nullptr), tail(nullptr) {
        head = new Node<T>(T());
        tail = new Node<T>(T());
        head->next = tail;
        tail->prev = head;
    }

    List(const List& other) : List() {
        Node<T>* current = other.head->next;
        while (current != other.tail) {
            push_back(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            // clear current list
            while (head->next != tail) {
                pop_front();
            }

            Node<T>* current = other.head->next;
            while (current != other.tail) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;


    }


    class Iterator {
    public:
        Node<T>* current;
        Iterator(Node<T>* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };



    Iterator begin() {
        return Iterator(head->next);
    }

    Iterator end() {
        return Iterator(tail);
    }



    void push_back(const T& data) {
        Node<T>* temp = new Node<T>(data);
        temp->prev = tail->prev;
        temp->next = tail;
        tail->prev->next = temp;
        tail->prev = temp;
    }

    void push_front(const T& data) {
        Node<T>* temp = new Node<T>(data);
        temp->next = head->next;
        temp->prev = head;
        head->next->prev = temp;
        head->next = temp;
    }

    void find_max() {
        T max = head->next->data;
        int count = 1;
        Node<T>* current = head->next->next;
        while (current != tail) {
            if (current->data > max) {
                max = current->data;
                count = 1;
            }
            else if (current->data == max) {
                count++;
            }
            current = current->next;
        }
        std::cout << "Max element: " << max << ", Number of occurrences: " << count << std::endl;
    }

    int count_positive() {
        int count = 0;
        Node<T>* current = head->next;
        while (current != tail) {
            if (current->data > 0) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    void pop_back() {
        if (tail->prev == head) {
            std::cout << "пустой лист\n";
            return;
        }
        Node<T>* temp = tail->prev;
        tail->prev = temp->prev;
        temp->prev->next = tail;
        delete temp;
    }

    void pop_front() {
        if (head->next == tail) {
            std::cout << "пустой лист\n";
            return;
        }
        Node<T>* temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
    }

    void print() {
        Node<T>* current = head->next;
        while (current != tail) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

