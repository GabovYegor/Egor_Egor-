#ifndef AVL_TREE_H // for include only one time
#define AVL_TREE_H

#include <cmath>

void make_deep(int, int);
void make_hight(int);

template <class Type>
class Head_AVL_Tree;

template <class Type>
class Node_AVL_Tree{
public:
    friend class Head_AVL_Tree<Type>; // дружим с головой
    bool is_contain(Type);
    int set_height();
    int set_balance();
    void print_tree() const;
    void print_tree(int) const;
    void print_tree_grafics() const;
    void calculate_level_scheme_and_generate_mas(int, int *&, int &, int, int *&, int &) const;
    class Node_AVL_Tree<Type>* insert(Type);
    class Node_AVL_Tree<Type>* remove(const Type);
    class Node_AVL_Tree<Type>* remove_min();
    class Node_AVL_Tree<Type>* find_min();
    class Node_AVL_Tree<Type>* left_rotate();
    class Node_AVL_Tree<Type>* right_rotate();
    class Node_AVL_Tree<Type>* make_balance();
    Node_AVL_Tree();
    ~Node_AVL_Tree();
private:
    int height;
    int balance;
    Type data;
    class Node_AVL_Tree<Type>* left;
    class Node_AVL_Tree<Type>* right;
};

template <class Type>
class Head_AVL_Tree{
public:
    Head_AVL_Tree();
    ~Head_AVL_Tree();
    void insert(Type);
    void print_tree();
    bool is_contain(Type);
    void remove(Type);
private:
    class Node_AVL_Tree<Type>* head;
};

// методы класса Node_AVL_Tree //
template <class Type>
Node_AVL_Tree<Type>::Node_AVL_Tree(){
    left = nullptr;
    right = nullptr;
    height = 1;
    balance = 0;
    data = 0;
}

template <class Type>
Node_AVL_Tree<Type>::~Node_AVL_Tree(){ // очищаем память под дерево
    if(left)
        delete left;
    if(right)
        delete right;
}

template <class Type>
bool Node_AVL_Tree<Type>::is_contain(Type desired){ // ищем элемент как в упорядоченом дереве и выводим на экран наш путь
    if(data == desired)
        return true;
    if(left && data > desired){
        std::cout << "find in left" << std::endl;
        if(left->is_contain(desired))
            return true;
    }
    if(right && data < desired){
        std::cout << "find in right" << std::endl;
        return right->is_contain(desired);
    }
    return false;
}

template <class Type>
void Node_AVL_Tree<Type>::print_tree() const{ // печатает информацию об узлах дерева
    std::cout << data << " ";
    std::cout << height << " ";
    std::cout << balance << std::endl;
    if(left)
        left->print_tree();
    if(right)
        right->print_tree();
}

template <class Type>
void Node_AVL_Tree<Type>::print_tree(int depth) const{ // beautiful print tree
    make_hight(depth);
    std::cout << data << std::endl;
    if(right){
        right->print_tree(depth+1);
    }
    if(left){
        left->print_tree(depth+1);
    }
}

void make_horizontal(int height, bool order){ // order - порядок // true - сначало пробелы
    if(order){
        for(int i = 0 ; i < pow(2, (height - 1)) - 1; i++)
            std::cout << " ";
        for(int i = 0 ; i < pow(2, (height - 1)) - 1; i++)
            std::cout << "_";
    }else{
        for(int i = 0 ; i < pow(2, (height - 1)) - 1; i++)
            std::cout << "_";
        for(int i = 0 ; i < pow(2, (height - 1)) - 1; i++)
            std::cout << " ";
    }
}

void make_space(int height){
    for(int i = 0 ; i < 3; i++) // пробелы между сыновьями
        std::cout << " ";
}

void make_vertical(int height){
    std::cout << std::endl;
    int count = 0;
    while(count < 2){
        for(int i = 0 ; i < pow(2, height + 2); i++){ // расчитать максимум
            if((i == (pow(2, height) + pow(2, height-1) - 2)) || ( i== (pow(2, height) - pow(2, height-1) - 2))){
                std::cout << "|";
            }
            else
                std::cout << " ";
        }
        std::cout << std::endl;
        count++;
    }
}

template <class Type>
void Node_AVL_Tree<Type>::print_tree_grafics() const{
    if(!left && !right)
        return;
    int* level_scheme = new int[1000]; // схема уровня
    Type* level_data = new Type[1000]; // последовательно данные уровня
    int this_height = height;
    make_horizontal(this_height, true);   //
    std::cout << data;
    make_horizontal(this_height, false);  //
    make_vertical(this_height);           //
    while(this_height-1 > 0){
        int q = 0;
        int t = 0; // только для передачи по ссылке в Функции ниже
        int level_data_i = 0;
        calculate_level_scheme_and_generate_mas(this_height-1, level_scheme, q, height, level_data, t);
        for(int i = 0; level_scheme[i]; i++){
            if(level_scheme[i] == 1){
                make_horizontal(this_height - 1, true);
                std::cout << level_data[level_data_i++];
                make_horizontal(this_height - 1, false);
                make_space(this_height - 1);
            }
            if(level_scheme[i] == 2){
                for(int i = 0 ; i < pow(2, this_height); i++)
                    std::cout << " ";
            }
        }

        q = 0;
        t = 0;
        this_height--;
        if(this_height == 1)
            break;
        calculate_level_scheme_and_generate_mas(this_height - 1, level_scheme, q, height, level_data, t);
        int print_flag = 0;
        while(print_flag < 2){
            std::cout << std::endl;
            for(int i = 0; i < pow(2, this_height - 1) - 2; i++)
                std::cout <<" ";
            for(int i = 0; level_scheme[i]; i++){
                if(level_scheme[i] == 1)
                    std::cout << "|";
                if(level_scheme[i] == 2)
                    std::cout << " ";
                for(int i = 0 ; i < pow(2, this_height) - 1; i++)
                    std::cout << " ";
            }
            print_flag++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <class Type>
void Node_AVL_Tree<Type>::calculate_level_scheme_and_generate_mas(int level, int*& level_scheme, int &i, int current_level, int*& level_mas, int& j) const{
    if(current_level == level + 1){
        if(left){
            level_mas[j++] = left->data;
            level_scheme[i++] = 1;
        }
        else{
            level_scheme[i++] = 2;
        }

        if(right){
            level_mas[j++] = right->data;
            level_scheme[i++] = 1;
        }
        else{
            level_scheme[i++] = 2;
        }
    }

    if(left)
        left->calculate_level_scheme_and_generate_mas(level, level_scheme, i, current_level - 1, level_mas, j);
    if(right)
        right->calculate_level_scheme_and_generate_mas(level, level_scheme, i, current_level - 1, level_mas, j);
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::remove(const Type to_remove){
    if(data == to_remove){
        if(!left && !right)
            return nullptr;
        if(!right)
            return left;
        class Node_AVL_Tree<Type>* new_root;
        new_root = right->find_min();                // новый корень это минимальный элемент в правом сыне
        right = right->remove_min();
        new_root->left = left;
        new_root->right = right;
        new_root->height = new_root->set_height();
        new_root->balance = new_root->set_balance();          // устанавливаем высоту и восстанавливаем баланс
        return new_root->make_balance();
    }
    if(data < to_remove)
        right = right->remove(to_remove);
    if(data > to_remove)
        left = left->remove(to_remove);
    height = set_height();
    balance = set_balance();
    if(balance == 2)
        std::cout << "Need to rotate because balance of element " << data << " == 2" << std::endl;
    if(balance == -2)
        std::cout << "Need to rotate because balance of element " << data << " == -2" << std::endl;
    return make_balance();
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::find_min(){
    return left?left->find_min():this;
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::remove_min(){
    if(!left)
        return right;
    left = left->remove_min();
    height = set_height();
    balance = set_balance();                 // устанавливаем высоту и восстанавливаем баланс
    return make_balance();
}



template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::insert(Type value){ // вставка
    if(value >= data){
        if(!right){
            right = new Node_AVL_Tree<Type>; // находим нужный узел для вставки как в обычном упорядоченном дереве
            right->data = value;
        }
        else
            right = right->insert(value);
    }
    if(value < data){
        if(!left){
            left = new Node_AVL_Tree<Type>;
            left->data = value;
        }
        else
            left = left->insert(value);
        }
    height = set_height();
    balance = set_balance();                // устанавливаем высоту и восстанавливаем баланс
    if(balance == 2)
       std::cout << "Need to rotate because balance of element " << data << " == 2" << std::endl;
    if(balance == -2)
        std::cout << "Need to rotate because balance of element " << data << " == -2" << std::endl;
    return make_balance();                  // балансировке по возврату из рекурсии
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::right_rotate(){
    std::cout << "right rotate around element: " << this->data << std::endl;
    Node_AVL_Tree<Type>* temp;
    temp = left;
    left = temp->right;
    this->height = this->set_height();
    this->balance = this->set_balance();
    if(temp->left){
        temp->left->height = temp->left->set_height();
        temp->left->balance = temp->left->set_balance();
    }
    temp->right = this;
    temp->height = temp->set_height();
    temp->balance = temp->set_balance();
    return temp;
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::left_rotate(){
    std::cout << "left rotate around element: " << this->data << std::endl;
    Node_AVL_Tree<Type>* temp;
    temp = right;
    right = temp->left;
    this->height = this->set_height();
    this->balance = this->set_balance();
    if(temp->right){
        temp->right->height = temp->right->set_height();
        temp->right->balance = temp->right->set_balance();
    }
    temp->left = this;
    temp->height = temp->set_height();
    temp->balance = temp->set_balance();
    return temp;
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::make_balance(){
    Node_AVL_Tree<Type>* temp;
    temp = this;
    if(balance == 2){
        if(right->balance == -1)
            temp->right = right->right_rotate(); // случай право право
        temp = left_rotate(); // случай лево лево
    }
    if(balance == -2){
        if(left->balance == 1)
            temp->left = left->left_rotate(); // случай право лево
        temp = right_rotate(); // случай право право
    }
    return temp;
}

template <class Type>
int Node_AVL_Tree<Type>::set_height(){ // установка высоты
    if(!left && !right) // if sheet
         return 1;
    if(!left)
        return (right->height + 1);
    if(!right)
        return (left->height + 1);
    if(left->height >= right->height)
        return (1 + left->height);
    if(left->height < right->height)
        return (1 + right->height);
    return 0; // чтобы компилятор не ругался
}

template <class Type>
int Node_AVL_Tree<Type>::set_balance(){ // установка баланса в вершине
    if(!left && !right) // if sheet
         return 0;
    if(!left)
        return right->height;
    if(!right)
        return (left->height * (-1));
    return (right->height - left->height);
}

// методы класса Head_AVL_Tree//
template <class Type>
Head_AVL_Tree<Type>::Head_AVL_Tree(){
    head = nullptr;
}

template <class Type>
Head_AVL_Tree<Type>::~Head_AVL_Tree(){
    delete head;
}

template <class Type>
void Head_AVL_Tree<Type>::print_tree(){
    if(!head){
        std::cout << "tree is empty" << std::endl;
        return;
    }
    head->print_tree(0);
    head->print_tree_grafics();
}

template <class Type>
void Head_AVL_Tree<Type>::insert(Type value){
    if(!head){
        Node_AVL_Tree<Type>* temp = new Node_AVL_Tree<Type>;
        temp->data = value;
        temp->height = 1;
        head = temp;
        return;
    }
    head = head->insert(value);
}

template <class Type>
bool Head_AVL_Tree<Type>::is_contain(Type desired){
    if(!head)
        return false;
    if(head->data == desired)
        return true;
    if(head->left && head->data > desired){
        std::cout << "find in left " << std::endl;
        return head->left->is_contain(desired);
    }
    if(head->right && head->data < desired){
        std::cout << "find in right " << std::endl;
        return head->right->is_contain(desired);
    }
    return false;
}

template <class Type>
void Head_AVL_Tree<Type>::remove(Type to_remove){
    head = head->remove(to_remove);
}

// вспомогательные функции для печати //
void make_deep(int deep, int flag){
  if(flag)
    for(int i = 0 ; i < deep ; i++)
      std::cout << "        ";
  else{
    for(int i = 0 ; i < deep-1 ; i++)
      std::cout << "        ";
    if(deep > 0)
      std::cout << "--------";
  }
}

void make_hight(int deep){
  make_deep(deep , 0);
  std::cout << '|' << std::endl;
  make_deep(deep , 1);
  std::cout << '|' << std::endl;
  make_deep(deep , 1);
}
#endif
