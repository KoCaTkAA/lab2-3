#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Exception.h"
#include <initializer_list>

using namespace std;

template <class T>

class LinkedList{
    private:

        struct Item {
            Item* next = nullptr;
            Item* prev = nullptr;
            T data;
        };

        struct List {
            Item* head = nullptr;
            Item* tail = nullptr;
        };

        int size = 0;
        List* items;
        
        List* CreateList(){
            List* list;
            try {
                list = new List;
            }
            catch (bad_alloc){
                throw SetException(MemoryAllocateError);
            }
            list->head = nullptr;
            list->tail = nullptr;
            return list;
        }

        void clear() {
            Item* cur = items->head;
            while (cur != nullptr) {
                Item* cur2 = cur->next;
                delete cur;
                cur = cur2;
            }
            if (items) {
                delete items;
            }
        }

        void push_back(T data){
            Item* cur;
            try{
                cur = new Item;
            }
            catch (bad_alloc){
                throw SetException(MemoryAllocateError);
            }
            int len = size;
            cur->data = data;
            cur->prev = items->tail;
            cur->next = nullptr;
            if (len != 0){
                items->tail->next = cur;
            }
            items->tail = cur;
            if (len == 0){
                items->head = cur;
            }        
            size++;
        }

        void push_tobegin(T data) {
            Item* cur = nullptr;
            try {
                cur = new Item;
            }
            catch (bad_alloc) {
                throw SetException(MemoryAllocateError);
            }
            int len = size;
            cur->next = items->head;
            cur->prev = nullptr;
            cur->data = data;
            size++;
            items->head->prev = cur;
            items->head = cur;
            if (len == 0) items->tail = cur;
        }

        void push(T data, int index) {
            Item* cur = items->head;
            if (index < 0) {
                throw SetException(IndexOutOfRange);
            }
            for (int i = 0; cur != nullptr && i < index; i++) {
                cur = cur->next;
            }
            if (cur == nullptr) {
                throw SetException(IndexOutOfRange);
            }
            Item* newitem;
            try {
                newitem = new Item;
            }
            catch (bad_alloc) {
                throw SetException(MemoryAllocateError);
            }
            newitem->next = cur;
            newitem->prev = cur->prev;
            newitem->data = data;
            if (cur->prev != nullptr) {
                cur->prev->next = newitem;
            } else {
                items->head = newitem;
            }
            cur->prev = newitem;
            size++;
        }

        T& GetItem(int index) {
            if (index < 0 || index >= size || items->head == nullptr) {
                throw SetException(IndexOutOfRange);
            }
            Item* cur = items->head;
            for (int i = 0; cur != nullptr && i < index; i++) {
                cur = cur->next;
            }
            if (cur == nullptr) {
                throw SetException(IndexOutOfRange);
            }
            return cur->data;
        }

    public:
        // Конструкторы
        LinkedList();
        LinkedList(T*, int);
        LinkedList(LinkedList<T>*);
        LinkedList(initializer_list<T>);
        
        // Деструктор
        ~LinkedList();

        // Декомпозиция
        T& GetFirst();
        T& GetLast();
        T& Get(int);
        int GetLength();

        // Операции
        LinkedList<T>* Append(T);
        LinkedList<T>* Prepend(T);
        LinkedList<T>* InsertAt(T, int);
        LinkedList<T>* Concat(LinkedList<T>*);

        LinkedList<T>* GetSubList(int, int);

};

// Конструкторы
template<class T>
LinkedList<T>::LinkedList() {
	items = CreateList();
}

template<class T>
LinkedList<T>::LinkedList(T* items, int count) {
	this->items = CreateList();

	for (int i = 0; i < count; i++) {
		push_back(items[i]);
	}
	size = count;
}

template<class T>
LinkedList<T>::LinkedList(LinkedList<T>* LL) {
	items = CreateList();
	for (int i = 0; i < LL->size; i++) {
		push_back(LL->Get(i));
	}
	size = LL->size;
}

template<class T>
LinkedList<T>::LinkedList(initializer_list<T> list) {
    items = CreateList();
	for (auto i : list) {
		push_back(i);
	}
	size = int(list.size());
}   

// Деструктор
template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

// Декомпозиция
template<class T>
T& LinkedList<T>::GetFirst() {
	return this->GetItem(0);
}

template<class T>
T& LinkedList<T>::GetLast() {
	return this->GetItem(this->size-1);
}

template<class T>
T& LinkedList<T>::Get(int index) {
	return this->GetItem(index);
}

template<class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) {
	if (endIndex < startIndex){
        throw SetException(NegativeRange);
    }
	LinkedList<T>* list = new LinkedList;
	for (int i = startIndex; i <= endIndex; i++) {
		list->Append(this->Get(i));
	}
	return list;
}

template<class T>
int LinkedList<T>::GetLength() {
	return size;
}

// Операции
template<class T>
LinkedList<T>* LinkedList<T>::Append(T item) {
	push_back(item);
    return this;
}

template<class T>
LinkedList<T>* LinkedList<T>::Prepend(T item) {
	push_tobegin(item);
    return this;
}

template<class T>
LinkedList<T>* LinkedList<T>::InsertAt(T item, int index) {
	push(item, index);
    return this;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
	LinkedList<T>* list_res = new LinkedList;
	for (int i = 0; i < size; i++) {
		list_res->Append(this->Get(i));
	}
	for (int i = 0; i < list->size; i++) {
		list_res->Append(list->Get(i));
	}
	return list_res;
}

#endif