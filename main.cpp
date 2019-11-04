#include <iostream>

using namespace std;



//Лаба 6 , задание 9
/*
Заданы 2 бинарных дерева. Удалить из второго бинарного дерева информацию,
содержащуюся в обоих деревьях.
*/


class Node{
public:
    int Data;
    Node *left, *right;


    Node(int data){
        Data = data;
        left = NULL;
        right = NULL;
    }
};


class bin_tree{
private:
    Node *_root = NULL;
public:
    Node* getRoot(){
        return _root;
    }

    int AddNode(int data){ // 0- успешно добавлено, 1- не добавлено тк элемент уже есть, 2- добавлен корень
        Node *newNode = new Node(data);

        //первый элемент
        if (_root == NULL){
            _root = newNode;
            return 2;
        }

        //не первый
        Node *Current = _root;
        while (1){
            if (Current->Data == newNode->Data) // вставка не требуется, если элемент существует
                return 1;
            if (newNode->Data > Current->Data){
                    // работа с элементом большем, чем текущая вершина
                if (Current->right == NULL)
                {   // если нужно вставить справа, а там связи нет, то осуществляем вставку
                    Current->right = newNode;
                    return 0;
                }
                else
                {   //иначе перемещаемся к правому поддереву
                    Current = Current->right;
                }
            }
            else{
                    //работа с элементом меньшим чем текущий элемент
                if (Current->left == NULL)
                {   // если нужно вставить слева, а там связи нет, то осуществляем вставку
                    Current->left = newNode;
                    return 0;
                }
                else
                {   //иначе перемещаемся к левому поддереву
                    Current = Current->left;
                }
            }
        }
    }

    int DeleteNode(int data){ // 2 - удаление корня, 1- удаление не произведено тк элемента нет, 0- успешное удаление
        Node *Current = _root;
        if (Current->left == NULL && Current->right == NULL){
            if (Current->Data == data)
            {
                delete _root;
                return 2;
            }
            else
            {
                return 1;
            }
            bool is_not_found = 1;
            bool is_end = 0;
            // идем по бин.дереву пока либо не уперлись в конец дерева
            // либо пока не нашли нужный элемент
            // имеем 2 флага для контроля ситуации
            while (is_not_found && !is_end){
                if (Current->Data > data){
                    //more
                    if(Current->right == NULL){
                        is_end = 1;
                    }
                    else{
                        Current = Current->right;
                    }

                }
                else if(Current->Data < data){
                    //less
                    if (Current->left == NULL){
                        is_end = 1;
                    }
                    else{
                        Current= Current->left;
                    }
                }
                else{
                    //equal
                    is_not_found = 0;
                }
            }
            //Если не конец, то Current - адрес удаляемого элемента
            if (is_end){ // удаление не требуется, если не нашли нашего элемента
                return 1;
            }
            // приорететная левая ветка
            if (Current->left != NULL){
                //пошли искать наибольший элемент в левой ветке

            }
            else if(Current->right != NULL){
                // ищем наименьший элемент в правой ветке

            }
            else{
                //это лист
            }




        }
    }
    //end of tree

};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
