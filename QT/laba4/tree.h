#include <iostream>
#include "queue.h"

#define MAX 200
//#define bad_print
//(a(d(e(wq)f)b(c)))
//(a(b(d(hk)e)c(f(lm)g))

template <typename Type>
bool is_data(Type letter);

void make_deep(int, int);
void make_hight(int);

template <typename Type> // class of binary tree
class B_Tree{
public:
    B_Tree();
    ~B_Tree();
    void create_tree(class B_Tree<Type>*, Type* tree_mas);
    void print_tree(Queue_Head<B_Tree*>&);  //overload of function
    void print_tree(int);

private:
    class B_Tree* left;
    class B_Tree* right;
    Type data;
};

template <typename Type>
B_Tree<Type>::B_Tree(){
    left = nullptr;
    right = nullptr;
}

template <typename Type>
B_Tree<Type>::~B_Tree(){
    if(left)
        delete left;
    if(right)
        delete right;
}

template <typename Type>
void B_Tree<Type>::print_tree(Queue_Head<B_Tree*>& queue){ // this method used queue to print tree
    std::cout << data << " " << std::endl;
    if(left){
        std::cout << "push " << left->data << std::endl;

        queue.push_front(left);  // add to the queue left data
    }
    if(right){
        std::cout << "push " << right->data << std::endl;
        queue.push_front(right); // add to the queue right data
    }
    if(!queue.is_empty()){
        B_Tree<Type>* temp_tree;
        temp_tree = queue.give_back(); // pop from queue next element to print
        queue.del_back();
        std::cout << "pop " << temp_tree->data << std::endl;
        temp_tree->print_tree(queue);
    }
}

template <typename Type>
void B_Tree<Type>::print_tree(int deep){ // beautiful print tree
    make_hight(deep);
    std::cout << data << std::endl;
    if(left){
        left->print_tree(deep+1);
    }
    if(right){
        right->print_tree(deep+1);
    }
}

template <typename Type> // all delete were checked
void B_Tree<Type>::create_tree(class B_Tree<Type>* tree, Type* tree_mas){
    Type* temp_str = new Type(MAX);
    for(int i = 0; tree_mas[i]; i++){
        if(is_data(tree_mas[i])){
            #ifdef bad_print
            std::cout << "data " << tree_mas[i] <<std::endl; //add data to tree
            #endif
            tree->data = tree_mas[i];
            if(tree_mas[i+1] == ')' || tree_mas[i+1] == '\0'){ // if it was last data
                delete temp_str;
                return;
            }
            for(int j = i+1, k = 0; tree_mas[j+1]; j++, k++)  //string without added data
                temp_str[k] = tree_mas[j];
            #ifdef bad_print
            std::cout << "temp_str " << temp_str << std::endl;
            #endif
            int count_data_level = 0;
            int depth = 0;
            for(int j = 0; temp_str[j]; j++){
                if(is_data(temp_str[j]) && is_data(temp_str[j+1]) && depth == 1){ // if 2 data in succession
                    tree->left = new B_Tree;
                    tree->left->data = temp_str[j];
                    tree->right = new B_Tree;
                    tree->right->data = temp_str[j+1];
                    delete temp_str;
                    return;
                }
                if(temp_str[j] == '(')
                    depth++;
                if(temp_str[j] == ')')
                    depth--;
                if(depth == 1 && is_data(temp_str[j])) // counted count of data in needed level
                    count_data_level++;
            }
            if(count_data_level == 1){
                tree->left = new B_Tree;
                create_tree(tree->left, temp_str);
            }
            if(count_data_level == 2){ //if depth equal 2 divide in 2 parts
                Type* left_str = new Type(MAX);
                Type* right_str = new Type(MAX);
                depth = 0;
                int j = 0;
                for(;temp_str[j] && !(depth == 1 && temp_str[j-1] == ')'); j++){
                    if(temp_str[j] == '(')
                        depth++;
                    if(temp_str[j] == ')')
                        depth--;
                    left_str[j] = temp_str[j];
                }
                for(int i = 0; temp_str[j+i-1]; i++)
                    right_str[i] = temp_str[j+i];
                #ifdef bad_print
                std::cout << "left_str  " << left_str << std::endl; // call recursion function
                #endif
                tree->left = new B_Tree;                            // for left and right part
                create_tree(tree->left, left_str);                  // create left tree
                tree->right = new B_Tree;
                #ifdef bad_print
                std::cout << "right_str " << right_str << std::endl;
                #endif
                create_tree(tree->right, right_str);                // create right tree
                delete left_str;
                delete right_str;
            }
            delete temp_str;
            return;
        }
    }
}

template <typename Type> // checked is element data or not
bool is_data(Type letter){
    if(isalpha(letter) || isdigit(letter))
        return true;
    return false;
}

void make_deep(int deep , int flag){
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
