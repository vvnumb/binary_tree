#include <iostream>
#include <stack>
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


    //NEED TOTAL DEBUG
    //WATCH COMPAIRING

    //UPD: листы удаляет нормально
    //UPD2: да и вообще норм, кроме корня
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
        }
            Node *Father = _root; // удрес на родителя удаляемого элемента
            bool is_left = 1; // потомок слева?


            // идем по бин.дереву пока либо не уперлись в конец дерева
            // либо пока не нашли нужный элемент
            // имеем 2 флага для контроля ситуации
            bool is_not_found = 1;
            bool is_end = 0;
            while (is_not_found && !is_end){
                if (Current->Data < data){
                    //more
                    if(Current->right == NULL){
                        is_end = 1;
                    }
                    else{
                        is_left = 0;
                        Father = Current;
                        Current = Current->right;
                    }

                }
                else if(Current->Data > data){
                    //less
                    if (Current->left == NULL){
                        is_end = 1;
                    }
                    else{
                        is_left = 1;
                        Father = Current;
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

            Node *Deleting = Current; // записали удаляемый элемент
            Node *Past = Current; // сохраняем предыдущий элемент, чтобы в дальнейшем поменять связи

            // приорететная левая ветка
            if (Current->left != NULL){
                //пошли искать наибольший элемент в левой ветке

                Current = Current->left;
                while(Current->right != NULL){
                    Past = Current;
                    Current = Current->right;
                }
                //Current - адрес на ноду с наибольшим элементом в левой ветке

                // изменяем путь к потомкам наибольшего в левом поддереве
                if (Past != Deleting){
                Past->right = Current->left;

                //изменяем путь к удаляемому элементуи
                //и переназначаем сам элемент
                Current->left = Deleting->left;
                Current->right = Deleting->right;
                if (Deleting != _root)
                    if (is_left)
                        Father->left = Current;
                    else
                        Father->right = Current;

                else
                    _root = Current;

                delete Deleting;
                }
                else{
                    Current->right = Deleting->right;
                    if (is_left)
                        Father->left = Current;
                    else
                        Father->right = Current;

                }
            }
            else if(Current->right != NULL){
                // ищем наименьший элемент в правой ветке

                Current = Current->right;
                while(Current->right != NULL){
                    Past = Current;
                    Current = Current->left;
                }
                //Current - адрес на ноду с наименьшим эл-том правой ветки

                // изменяем путь к потомкам текущего
                if (Deleting != Past){
                Past->left = Current->right;

                //изменяем путь к удаляемому элементуи
                //и переназначаем сам элемент
                Current->left = Deleting->left;
                if(Deleting != Past)
                    Current->right = Deleting->right;
                if(Father  != NULL)
                if (is_left)
                    Father->left = Current;
                else
                    Father->right = Current;
                else
                    _root = Current;
                delete Deleting;
                }
                else{
                    Current->right  = Deleting->right;
                    if(Father  != NULL)
                    if (is_left)
                        Father->left = Current;
                    else
                        Father->right = Current;
                    else
                        _root = Current;
                    delete Deleting;
                }




            }
            else{
                //это лист
                if (is_left)
                    Father->left = NULL;
                else
                    Father->right = NULL;


                delete Deleting;
            }

            return 0;



    }



    //CORRECT
    void StrightWayPrint(){
        bool mas[1000];
        for (int i = 0; i < 1000; i++)
            mas[i] = 0;
        Node * Current = _root;
        stack<Node*> st;
        st.push(Current);
        while(st.size()){
            while(st.top()->left != NULL && !mas[Current->left->Data]){ // ?
                Current = st.top()->left;
                st.push(Current);
            }
            Current = st.top();
            mas[Current->Data] = 1;
            cout << st.top()->Data << " ";
            st.pop();
            if (Current->right != NULL){
                st.push(Current->right);
                Current = Current->right;}
            else
                if (st.size())
                    Current = st.top();
        }

    }
    //end of tree

};

int main()
{
    bin_tree BST;
    //BST.AddNode(11);    BST.AddNode(9); BST.AddNode(8);BST.AddNode(10);BST.AddNode(6); BST.AddNode(7); BST.AddNode(12); BST.AddNode(13);
    BST.AddNode(11); BST.AddNode(13); BST.AddNode(12); BST.AddNode(14); BST.AddNode(9); BST.AddNode(10); BST.AddNode(7); BST.AddNode(6); BST.AddNode(8);
    BST.StrightWayPrint();
    // удаление
    int k = BST.DeleteNode(14);
    cout << endl << k << endl;
    BST.StrightWayPrint();
    return 0;
}
