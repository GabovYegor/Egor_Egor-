#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    list(): m_head(nullptr), m_tail(nullptr){}

    ~list(){
		clear();
    }
	  
    list(const list& other): m_head(nullptr), m_tail(nullptr){  
        for(auto currentNode = other.m_head; currentNode; currentNode = currentNode->next){
            push_back(currentNode->value);
        }
    }
	  
    list(list&& other){ 
        m_head = other.m_head;
        m_tail = other.m_tail;
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }
      
    list& operator=(const list& other){
        if(this == &other)
            return *this;
        clear();
        for(auto currentNode = other.m_head; currentNode; currentNode = currentNode->next){
            push_back(currentNode->value);
        }
        return *this;
    }
      
      void swap(list& lst)
	{
		std::swap(m_head, lst.m_head);
		std::swap(m_tail, lst.m_tail);
	}
      
   void push_back(const value_type& value){
        if(empty()){
            m_tail = m_head = new node<Type>(value, nullptr, nullptr);
            return;
        }
        m_tail->next = new node<Type>(value, nullptr,m_tail);
        m_tail=m_tail->next;
    }

    void push_front(const value_type& value){
        if(empty()){
            m_tail = m_head = new node<Type>(value, nullptr, nullptr);
            return;
        }
        m_head = new node<Type>(value, m_head, nullptr);
        m_head->next->prev = m_head;
    }

    reference front(){
        return m_head->value;
    }

    const_reference front() const{
        return m_head->value;
    }

    reference back(){
        return m_tail->value; 
    }

    const_reference back() const{
        return m_tail->value;
    }

    void pop_front(){
        if(m_head == m_tail){
            delete m_head;
            m_head = m_tail = nullptr;
            return;
        }
        m_head = m_head->next;
        delete m_head->prev;
        m_head->prev= nullptr;
    }

    void pop_back(){
        if(m_head == m_tail){
            delete m_head;
            m_head = m_tail = nullptr;
            return;
        }
        m_tail = m_tail->prev;
        delete m_tail->next;
        m_tail->next = nullptr;
    }

    void clear(){
        while(!empty())
            pop_back();
    }

    bool empty() const{
        return m_head == nullptr;
    }

    size_t size() const{
        size_t size = 0;
        for(node<Type>* currentNode = m_head; currentNode; currentNode = currentNode->next, ++size);
        return size;
    }


  private:
    //your private functions
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
