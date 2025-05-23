#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "DynamicArray.h"
#include "Sequence.h"
#include "Exception.h"
using namespace std;

template <typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* array;

    virtual ArraySequence<T>* Instance() {
        return this;
    }
public:

    // Конструкторы

    ArraySequence() {
        array = new DynamicArray<T>();
    }

    ArraySequence(T* items, int count) {
        array = new DynamicArray<T>(items, count);
    }
    
    ArraySequence(const ArraySequence<T>& other) {
        array = new DynamicArray<T>(*other.array);  // Используем копирующий конструктор DynamicArray
    }


    ArraySequence(initializer_list<T> list) {
        array = new DynamicArray<T>(list);
    }

    DynamicArray<T>* GetArray() const { return array; }
    
    // Деструктор
    ~ArraySequence() {
        delete array;
    }
    
    // Декомпозиция
    T& GetFirst() override {
        return array->Get(0);
    }
    
    T& GetLast() override {
        return array->Get(array->GetSize() - 1);
    }
    
    T& Get(int index) override {
        return array->Get(index);
    }
    
    ArraySequence<T>* GetSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= array->GetSize() || startIndex > endIndex)
            throw SetException(IndexOutOfRange);

        DynamicArray<T>* subArr = array->GetSubArray(startIndex, endIndex);
        auto* result = new ArraySequence<T>();
        delete result->array;
        result->array = subArr;
        return result;
    }
    
    int GetLength() override {
        return array->GetSize();
    }
    
    // Операции
   Sequence<T>&Set(int index, T value) {
        Instance()->array->Set(index, value);
        return *this;
    }

    Sequence<T>&Resize(int newSize) {
        Instance()->array->Resize(newSize);
        return *this;
    }

    Sequence<T>* Append(T item) override { 
        auto* inst = Instance();
        inst->array->Append(item);
        return inst;
    }

    Sequence<T>* Prepend(T item) override {
        auto* inst = Instance();
        inst->array->Prepend(item);
        return inst;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        auto* inst = Instance();
        inst->array->InsertAt(item, index);
        return inst;
    }
    
    ArraySequence<T>* Concat(Sequence<T>* seq) override {
        auto* otherArr = static_cast<ArraySequence<T>*>(seq)->GetArray();
        DynamicArray<T>* merged = array->Concat(otherArr);
        auto* result = new ArraySequence<T>();
        delete result->array;
        result->array = merged;
        return result;
    }
};

#endif