/*

http://gamesmaker.ru/programming/c/realizaciya-odnosvyaznyh-i-dvusvyaznyh-spiskov-2/
https://github.com/hokum2004/OwnIterator

*/


#ifndef SIMPLE_VECTOR_H__
#define  SIMPLE_VECTOR_H__
#include "stdlib.h"
#include "iterator"

template <class _data_t>
class SListNode // SListNode - название класса, представляющего
{               // узел односвязного списка
public:
    SListNode();
    ~SListNode();
    _data_t data;   // целая переменная хранит данные узла
    SListNode<_data_t>* next; // указатель  на следующий узел списка
    void InsertAfter(_data_t);
};

template <class _data_t>
SListNode<_data_t>::SListNode() {
    next = NULL;
}

template <class _data_t>
SListNode<_data_t>::~SListNode() {
    delete data;
}



template <class _data_t>
void SListNode<_data_t>::InsertAfter( _data_t d)
{
    SListNode<_data_t>* new_node = new SListNode<_data_t>; // Создаём указатель  на узел.

    new_node->data = d;    // Заполняем поле data.
    new_node->next = next; // Заполняем поле next. Этому полю присваиваем
                            // значение поля next текущего элемента
    next = new_node;   // Меняем поле next текущего элемента. Теперь, текущий
}                    // узел указывает  на вновь созданный




/**
 *    Linked List
 */


template <class _value_t>
class SListIterator;


template <class _data_t>
class SLinkedList {
    private:
    SListNode<_data_t>* head; // первый элемент списка
    SListNode<_data_t>* tail; // последний элемент списка
    int count;

    public:

    typedef SListIterator<_data_t> iterator;
    // typedef SListIterator<const _data_t> const_iterator;

    ~SLinkedList();
    SLinkedList();
    void PushBack (_data_t);
    void PushFront (_data_t);
    void PopFront();
    void PopBack();

    // ?????????

    void Insert(iterator&, _data_t);
    void Remove(iterator&);

    // void Insert(const_iterator&, _data_t);
    // void Remove(const_iterator&);



    iterator begin();
    iterator end();

    // const_iterator begin() const;
    // const_iterator end() const;

};

template <class _data_t>
SLinkedList<_data_t>::SLinkedList () {
    count = 0;
    head = NULL;
    tail = NULL;
}

template <class _data_t>
SLinkedList<_data_t>::~SLinkedList()
{
    SListNode<_data_t>* delNode = head;
    SListNode<_data_t>* temp;
    while (delNode != NULL)
    {
        temp = delNode->next;
        delete delNode;
        delNode = temp;
    }
}

template <class _data_t>
void SLinkedList<_data_t>::PushBack (_data_t d)
{
    if (count == 0)  //  В списке нет элементов.
    {
        head = tail = new SListNode<_data_t>;
        head->data = d;
    }
    else //  В списке есть хотя бы один элемент
    {
        tail->InsertAfter(d);
        tail = tail->next;
    }
    count++;
}

template <class _data_t>
void SLinkedList<_data_t>::PushFront (_data_t d)
{
    if (count == 0) {
        head = tail = new SListNode<_data_t>;
        head->data = d;
    }
    else {
        SListNode<_data_t>* new_node = new SListNode<_data_t>;
        new_node->data = d;
        new_node->next = head;
        head = new_node;
    }
    count++;
}

template <class _data_t>
void SLinkedList<_data_t>::PopFront()
{
    if (count != 0) {
        SListNode<_data_t>* temp = head;
        head = head->next;
        delete temp;
        count--;
        if (head == NULL) //  в списке был один элемент
            tail = head;
    }
}

template <class _data_t>
void SLinkedList<_data_t>::PopBack()
{
    if (count == 1) {
        delete tail;
        head = tail = NULL;
        count--;
    }
    if (count > 1)  {
        SListNode<_data_t>* temp = new SListNode<_data_t>;
        temp = head;
        while (temp->next != tail)
            temp = temp->next;

        tail = temp;
        delete temp->next;
        tail->next = NULL;
        count--;
    }
}

template <class _data_t>
void SLinkedList<_data_t>::Insert(SLinkedList<_data_t>::iterator& itr, _data_t d)
{
    if (itr.Valid())  {
        itr.node->InsertAfter(d);
        if (itr.node == tail) {
            tail = itr.node->next;
        }
    count++;
    }
}

// template <class _data_t>
// void SLinkedList<_data_t>::Insert(const_iterator& itr, _data_t d)
// {
//     if (itr.Valid())  {
//         itr.node->InsertAfter(d);
//         if (itr.node == tail) {
//             tail = itr.node->next;
//         }
//     count++;
//     }
// }


template <class _data_t>
void SLinkedList<_data_t>::Remove(iterator& itr) {
    SListNode<_data_t>* temp = head;

    if (itr.node == head) {
        itr.Forward();
        PopFront();
    }
    else {
        while (temp->next != itr.node)
            temp = temp->next;

        itr.Forward();
        if (temp->next == tail)
            tail = temp;

        delete temp->next;
        temp->next = itr.node;
    }
    count--;
}

// template <class _data_t>
// void SLinkedList<_data_t>::Remove(const_iterator& itr) {
//     SListNode<_data_t>* temp = head;

//     if (itr.node == head) {
//         itr.Forward();
//         PopFront();
//     }
//     else {
//         while (temp->next != itr.node)
//             temp = temp->next;

//         itr.Forward();
//         if (temp->next == tail)
//             tail = temp;

//         delete temp->next;
//         temp->next = itr.node;
//     }
//     count--;
// }


template <class _data_t>
SListIterator<_data_t> SLinkedList<_data_t>::begin()
{
    return iterator(head, this);
}

template <class _data_t>
SListIterator<_data_t> SLinkedList<_data_t>::end()
{
    return iterator(tail, this);
}

// template <class _data_t>
// SListIterator<const _data_t> SLinkedList<_data_t>::begin() const
// {
//     return iterator(head, this);
// }

// template <class _data_t>
// SListIterator<const _data_t> SLinkedList<_data_t>::end() const
// {
//     return iterator(tail, this);
// }


/***********************************************************
 * 
 *  Iterator
 * 
 ***********************************************************/

template<class _value_t>
class SListIterator : public std::iterator<std::input_iterator_tag, _value_t> {
    friend class SLinkedList<_value_t>;

    private:
    SListNode<_value_t>* node;
    SLinkedList<_value_t>* list;

    public:
    SListIterator(SListNode<_value_t>*,SLinkedList<_value_t>*);
    void Start();
    bool Forward();
    _value_t& Item();
    bool Valid();

    // bool operator!=(SListIterator<_value_t>& other);
    // bool operator==(SListIterator<_value_t>& other); //need for BOOST_FOREACH

    // typename SListIterator<_value_t>::reference operator*();
    // SListIterator<_value_t>& operator++();

    bool operator!=(SListIterator<_value_t> other);
    bool operator==(SListIterator<_value_t> other); //need for BOOST_FOREACH

    typename SListIterator<_value_t>::reference operator*();
    SListIterator<_value_t> operator++();
    
};

template<class _value_t>
SListIterator<_value_t>::SListIterator(SListNode<_value_t>* n, SLinkedList<_value_t>* l) : node(n), list(l) {}

template<class _value_t>
void SListIterator<_value_t>::Start()
{
    node = list->head;
}

template<class _value_t>
bool SListIterator<_value_t>::Forward()
{
    if (node != NULL) {
        node = node->next;
        
    }
    return node != NULL;
}

template<class _value_t>
_value_t& SListIterator<_value_t>::Item()
{
    return node->data;
}

template<class _value_t>
bool SListIterator<_value_t>::Valid()
{
    return (node != NULL);
}


template<class _value_t>
bool SListIterator<_value_t>::operator!=(SListIterator<_value_t> other) {
    bool ret = ((_value_t)node->data != (_value_t)other.Item());

    return ret;
}
template<class _value_t> 
bool SListIterator<_value_t>::operator==(SListIterator<_value_t> other) {
    return (_value_t)node->data == (_value_t)other.Item();
}

template<class _value_t> 
typename SListIterator<_value_t>::reference SListIterator<_value_t>::operator*() {
    return *node;
}

template<class _value_t> 
SListIterator<_value_t> SListIterator<_value_t>::operator++() {
    Forward();
    return *this;
}





// #include "SVector.tpp"
#endif