#pragma once  // file include only one time

template <class Type> // class element of queue
class Queue{
public:
    Queue();
    ~Queue();
public:
    class Queue* next;
    Type data;
};

template <class Type> // class head of queue
class Queue_Head{
public:
    Queue_Head();
    ~Queue_Head();
    void del_back();
    Type give_back();
    void push_front(Type);
    void print_data();
    bool is_empty();
private:
    class Queue<Type>* head;
};

template <class Type>
Queue_Head<Type>::Queue_Head(){
    head = new Queue<Type>;
    head->next = nullptr;
}

template <class Type>
Queue_Head<Type>::~Queue_Head(){ // free memory to head
    delete head;
}

template <class Type>
Queue<Type>::Queue(){
    next = nullptr;
}

template <class Type>
Queue<Type>::~Queue(){  // free memory to elements of queue
    delete this->next;
}

template <class Type>
void Queue_Head<Type>::push_front(Type data){ // add element at the begin of queue
    Queue<Type>* temp = new Queue<Type>;
    temp->next = head->next;
    head->next = temp;
    temp->data = data;
}

template <class Type>
Type Queue_Head<Type>::give_back(){ // give last element of queue, but don`t delete it
    Queue<Type>* temp;
    if(!head->next)
        return nullptr;
    temp = head->next;
    if(!temp->next)
        return head->next->data;
    while(temp->next)
        temp = temp->next;
    return temp->data;
}

template <class Type>
void Queue_Head<Type>::del_back(){ // delete last element of queue
     Queue<Type>* temp;
    if(!head->next)
        return;
    temp = head->next;
    if(!temp->next){
        delete head->next;
        head->next = nullptr;
        return;
    }
    while(temp->next->next)
        temp = temp->next;
    delete temp->next;
    temp->next = nullptr;
}

template <class Type>
bool Queue_Head<Type>::is_empty(){ // checked to empty queue
    if(!head->next)
        return true;
    return false;
}

template <class Type>
void Queue_Head<Type>::print_data(){ // print all queue
    Queue<Type>* temp = new Queue<Type>;
    temp = head->next;
    if(!head->next)
        std::cout << "queue is empty!" << std::endl;
    while(temp){
        std::cout << temp->data;
        temp = temp->next;
    }
    delete temp;
}
