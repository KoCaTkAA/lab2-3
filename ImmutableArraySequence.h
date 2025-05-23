#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H
#include "ArraySequence.h"

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    ImmutableArraySequence(initializer_list<T> list) : ArraySequence<T>(list) {}

    ArraySequence<T>* Instance() override {
        return new ImmutableArraySequence<T>(*this); 
    }

    ImmutableArraySequence<T>* Concat(Sequence<T>* seq) override {
        auto* otherArr = static_cast<ArraySequence<T>*>(seq)->GetArray();
        DynamicArray<T>* x = this->array->Concat(otherArr);
        auto *res = new ImmutableArraySequence<T>();
        delete res->array;
        res->array = x;
        return res;
    }

    ImmutableArraySequence<T>* GetSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= this->array->GetSize() || startIndex > endIndex)
            throw SetException(IndexOutOfRange);
        DynamicArray<T> *sub = this->array->GetSubArray(startIndex, endIndex);
        auto *res = new ImmutableArraySequence<T>();
        delete res->array;
        res->array = sub;
        return res;
    }

    ImmutableArraySequence<T>& operator=(const Sequence<T>& other) {
        const ArraySequence<T>* arrSeq = dynamic_cast<const ArraySequence<T>*>(&other);
        if (arrSeq) {
            delete this->array;
            this->array = new DynamicArray<T>(*arrSeq->GetArray());
        }
        return *this;
    }

};

#endif