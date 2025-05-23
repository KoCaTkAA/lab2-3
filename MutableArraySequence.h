#ifndef MUTABLE_ARRAY_SEQUENCE_H
#define MUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequence.h"

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    MutableArraySequence(initializer_list<T> list) : ArraySequence<T>(list) {}

    ArraySequence<T>* Instance() override {
        return this;
    }

    MutableArraySequence<T>* Concat(Sequence<T>* seq) override {
        auto* otherArr = static_cast<ArraySequence<T>*>(seq)->GetArray();
        DynamicArray<T>* x = this->array->Concat(otherArr);
        auto* res = new MutableArraySequence<T>();
        delete res->array;
        res->array = x;
        return res;
    }

    MutableArraySequence<T>* GetSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= this->array->GetSize() || startIndex > endIndex)
            throw SetException(IndexOutOfRange);
        DynamicArray<T>* sub = this->array->GetSubArray(startIndex, endIndex);
        auto* res = new MutableArraySequence<T>();
        delete res->array;
        res->array = sub;
        return res;
    }
};

#endif