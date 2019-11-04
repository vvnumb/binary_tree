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

    int Add(int data){
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
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
