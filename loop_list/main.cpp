#include <iostream>
#include <string>

template <class Type>
class Node{
public:
    Type value;
    Node* next;
    Node(const Type& value, Node<Type>* next)
      : value(value), next(next){}
    Node();
};

template <class Type>
class List_Iterator{
public:
    List_Iterator(Node<Type>* node = nullptr): it(node){}
    Type operator*(){
        return it->value;
    }

    Node<Type>* operator ->(){
        return &it->value;
    }

    bool operator ==(const List_Iterator& other){
        return other.it == it;
    }

    bool operator !=(const List_Iterator& other){
        return  other.it != it;
    }

    List_Iterator& operator=(const List_Iterator<Type>& other){
        it = other.it;
        return *this;
    }

    List_Iterator& operator++(){
        it = it->next;
        return *this;
    }

    List_Iterator operator++(int){
        auto temp = *this;
        it = it->next;
        return temp;
    }

    ~List_Iterator(){}

private:
    Node<Type>* it;
};

template <class Type>
class list{
public:
    list(){
        head_ = new Node<Type>(0, nullptr);
        head_->next = head_;
    }

    list(const list& other): list(){
        std::cout << "copy" << std::endl;
        for(Node<Type>* currentNode = other.head_->next; currentNode != other.head_; currentNode = currentNode->next){
            push_back(currentNode->value);
        }
    }

    list(const list&& other) noexcept{
        head_ = other.head_;
        other.head_ = nullptr;
    }

    list& operator=(const list& other){
        std::cout << "assigment" << std::endl;
        if(this != &other){
            clear();

            for(Node<Type>* currentNode = other.head_->next; currentNode != other.head_; currentNode = currentNode->next){
                push_back(currentNode->value);
            }
        }
        return *this;
    }

    ~list(){
        clear();
        delete head_;
    }

    void push_back(const Type& value){
        Node<Type>* currentNode = head_;
        do{
            currentNode = currentNode->next;
        }while(currentNode->next != head_);
        Node<Type>* newNode = new Node<Type>(value, head_);
        currentNode->next = newNode;
    }

    void push_front(const Type& value){
        Node<Type>* newNode = new Node<Type>(value, head_->next);
        head_->next = newNode;
    }

    void pop_front(){
        if(isEmpty()){
            std::cout << "delete from empty list" << std::endl;
            return;
        }
        Node<Type>* deleteNode = head_->next;
        head_->next = head_->next->next;
        delete deleteNode;
    }

    void pop_back(){
        if(isEmpty()){
            std::cout << "delete from empty list" << std::endl;
            return;
        }
        Node<Type>* currentNode = head_;
        do{
            currentNode = currentNode->next;
        }while(currentNode->next->next != head_);
        delete currentNode->next;
        currentNode->next = head_;
    }

    int size() const{
        unsigned size = 0;
        for(Node<Type>* currentNode = head_->next; currentNode != head_; currentNode = currentNode->next, ++size);
        return size;
    }

    bool isEmpty(){
        return size() == 0;
    }

    void clear(){
        while(!isEmpty())
            pop_front();
    }

    Node<Type>* begin(){
        return head_->next;
    }

    void printLoopList(){
        Node<Type>* currentNode = head_->next;
        std::cout << "Elements: ";
        while(currentNode != head_){
            std::cout << currentNode->value << " ";
            currentNode = currentNode->next;
        }
        std::cout << "size: " << size() << std::endl;
    }

private:
    Node<Type>* head_;
};

int main(){
    list<int> loopList;
    loopList.push_back(3);
    loopList.push_back(7);
    loopList.push_back(9);
    loopList.push_front(11);
    loopList.printLoopList();
    List_Iterator<int> listIt(loopList.begin());
    std::cout << *listIt++;
    return 0;
}


