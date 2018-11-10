#include <iostream>
#include <fstream>
#include "avl_tree.h"

typedef int Type;
//#define FROM_FILE // input from file
//#define RANDOM_TEST
#define RANGE 1000

int main(int argc, char* argv[])
{
    Head_AVL_Tree<Type> head;
    #ifdef FROM_FILE
    std::ifstream fin;
    if(argc == 2) // если файл как аргумент командной строки
        fin.open(argv[1], std::ios::in);
    else{
        std::string file_name;
        std::cout << "input filename" << std::endl;
        std::cin >> file_name;
        fin.open(file_name, std::ios::in);
    }
    if(!fin){
        std::cout << "ошибка открытия файла" << std::endl;
        return 0;
    }
    #endif

    std::string main_str;
    #ifdef FROM_FILE
        getline(fin, main_str);
        std::cout << std::endl << "create AVL_Tree from file " << std::endl; // считываем входную строку
    #else
        std::cout << "input your element of AVL_tree: " << std::endl;
        getline(std::cin, main_str);
    #endif

    int count_num = 0;
    for(size_t i = 0; i < main_str.size(); i++){
        int temp = 0;
        bool is_num = false;
        for(size_t j = i; isdigit(main_str[j]); j++, i++){ // create tree from string
            temp = temp*10 + main_str[j]-'0';
            is_num = true;
        }
        if(is_num){
            count_num++;
            std::cout << "add to the tree: " << temp << std::endl;
            head.insert(temp);                                       // по очереди добавляем элементы в АВЛ_дерево
            std::cout << "tree after added " << temp << std::endl;
            head.print_tree();
            std::cout << std::endl;
        }
    }

    if(!count_num){
        std::cout << "no one element to tree. Program will end" << std::endl; // в программе нет ни одного элемента
        exit(0);
    }
    if(argc != 2){	
        std::cout << "choice action with AVL_tree: " << std::endl << "input '0' to end program " << std::endl <<
                "input '1' to add element to the AVL_tree" << std::endl <<
                 "input '2' to delete element from the AVL_tree" << std::endl;
    }
    
    int action = 0;
    if(argc != 2)
    	std::cout << "your action: ";
    #ifndef RANDOM_TEST
        std::cin >> action;
    #else
        action = 1 + rand() % 2;
    #endif
    if(std::cin.fail()){
        std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
        return 0;
    }

    while(1){                   // меню выбора действий: добавление, удаление и завершение работы
        switch (action) {
            case 0:
                #ifdef FROM_FILE
                    fin.close(); // закрываем файл
                #endif
                return 0;
                break;
            case 1:
                Type insert_tree_element;
                if(argc != 2)
                    std::cout << "input element to add: ";
                #ifndef RANDOM_TEST
                    std::cin >> insert_tree_element;
                #else
                    insert_tree_element = 1 + rand() % RANGE;
                #endif
                if(argc == 2)
                    std::cout << "add to tree new element: " << insert_tree_element  << std::endl;
                if(std::cin.fail()){
                    std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                    return 0;
                }
                std::cout << std::endl << "find this element in AVL_tree: " << std::endl;
                if(!head.is_contain(insert_tree_element)){
                    std::cout << "tree isn`t have this element" << std::endl << std::endl;
                    head.insert(insert_tree_element);
                    std::cout << "tree after add new element:" << std::endl;
                    head.print_tree();
                }
                else
                    std::cout << "element already in tree" << std::endl << std::endl;
                if(argc != 2)
                    std::cout << "input next action: ";
                #ifndef RANDOM_TEST
                    std::cin >> action;
                #else
                    action = 1 + rand()%2;
                #endif
                if(std::cin.fail()){
                    std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                    return 0;
                }
                break;
            case 2:
                if(argc != 2)
                    std::cout << "input element to delete: " << std::endl;
                Type element_to_delete;               
                #ifndef RANDOM_TEST
                    std::cin >> element_to_delete;
                #else
                    element_to_delete = 1 + rand() % RANGE;
                #endif
                if(std::cin.fail()){
                    std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                    return 0;
                }
                std::cout << "delete from tree: " << element_to_delete << std::endl;
                std::cout << std::endl << "find this element in AVL_tree: " << std::endl;
                if(!head.is_contain(element_to_delete)){
                    std::cout << "tree isn`t have this element" << std::endl << std::endl;
                }
                else{
                    head.remove(element_to_delete);
                    std::cout << std::endl << "tree after delete: " << element_to_delete << std::endl;
                    head.print_tree();
                }
                if(argc != 2)
                    std::cout << "input next action: ";
                #ifndef RANDOM_TEST
                    std::cin >> action;
                #else
                    action = 1 + rand()%2;
                #endif
                if(std::cin.fail()){
                    std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                    return 0;
                }
                break;
            default:
                std::cout << "It`s not an action. Repeat please" << std::endl;
                std::cout << "input next action: ";
                std::cin >> action;
                if(std::cin.fail()){
                    std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                    return 0;
                }
                break;
        }
    }
    return 0;
}
\


