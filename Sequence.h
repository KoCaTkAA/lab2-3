#ifndef SEQUENCE_H
#define SEQUENCE_H

template <typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    
    // Декомпозиция
    virtual T& GetFirst() = 0;
    virtual T& GetLast() = 0;
    virtual T& Get(int index) = 0;
    virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) = 0;
    virtual int GetLength() = 0;
    
    // Операции
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    
};

#endif