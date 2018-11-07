#include <iostream>
#include "tree.h"
#include "queue.h"

typedef char Type;

int main(){
    class B_Tree<Type> tree;
    class Queue_Head<B_Tree<Type>*> head; // element`s of queue is pointer to tree
    Type* tree_mas = new Type(MAX);
    std::cin >> tree_mas;
    tree.create_tree(&tree, tree_mas); // create tree :)
    tree.print_tree(0);     //print beautiful
    std::cout << "input elemets of tree with queue: ";
    tree.print_tree(head);  //print with queue
    std::cout << std::endl;
    delete tree_mas;
    return 0;
}
