#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"
#include "Exception.h"
#include <initializer_list>
 
using namespace std;
template <typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;
public:
    // Конструкторы
    ListSequence() {
        list = new LinkedList<T>;
    }
    
    ListSequence(T* items, int count) {
        list = new LinkedList<T>(items, count);
    }
    
    ListSequence(Sequence<T>* list) {
        this->list = new LinkedList<T>(((ListSequence<T>*)list)->list);
    }
    
    ListSequence(initializer_list<T> list) {
        this->list = new LinkedList<T>(list);
    }    
    
    ~ListSequence() override{
        delete list;
    }
    
    // Декомпозиция
    T& GetFirst() override{
        return this->list->GetFirst();
    }

    T& GetLast() override{
        return this->list->GetLast();
    }

    T& Get(int index)  override{
        return this->list->Get(index);
    }

    Sequence<T>* GetSubSequence(int startIndex, int endIndex) override{
        if (startIndex < 0 || endIndex >= array->GetSize() || startIndex > endIndex) {
            throw SetException(IndexOutOfRange);
        }
        LinkedList<T>* x = this->list->GetSubList(startIndex, endIndex);
        ListSequence<T>* resseq = new ListSequence<T>;
        delete resseq->list;
        resseq->list = x;
        return resseq;
    }

    int GetLength() override{
        return this->list->GetLength();
    }
    
    // Операции
    Sequence<T>* Append(T item) override{
        list->Append(item);
        return this;
    }

    Sequence<T>* Prepend(T item) override{
        list->Prepend(item);
        return this;    
    }

    Sequence<T>* InsertAt(T item, int index) override{
        list->InsertAt(item, index);
        return this;    
    }
    
    Sequence<T>* Concat(Sequence<T>* seq) override{
        LinkedList<T>* x = this->list->Concat(((ListSequence<T>*)seq)->list);
        ListSequence<T>* resseq = new ListSequence<T>;
        delete resseq->list;
        resseq->list = x;
        return resseq;
    }
};

#endif