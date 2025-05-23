#ifndef DYNAMIC_ARRAY_H  
#define DYNAMIC_ARRAY_H
#include <iostream>
#include <cstring>
#include <iostream>
#include "Exception.h"
#include "Sequence.h"
using namespace std;

template <typename T>
class DynamicArray{
    private:
        T* array = nullptr;
        int size = 0;
    public:

        // Конструкторы
        DynamicArray() {
            array = nullptr;
            size = 0;
        }

        DynamicArray(int count) {
            if (count < 0) throw SetException(SizeBelowZero);
            try {
                array = new T[count];
            }
            catch (bad_alloc) {
               throw SetException(MemoryAllocateError);
            }
            size = count;
        }

        DynamicArray(T* items, int count) {
            if (count < 0) throw SetException(SizeBelowZero);
            try {
                array = new T[count];
            }
            catch (bad_alloc) {
                throw SetException(MemoryAllocateError);
            }
            size = count;
            for (int i = 0; i < size; i++) {
                array[i] = items[i];
            }
        }

        DynamicArray(const DynamicArray<T>& dynamic_array) {
            try {
                array = new T[dynamic_array.size];
            }
            catch (bad_alloc) {
                throw SetException(MemoryAllocateError);
            }
            size = dynamic_array.size;
            for (int i = 0; i < size; i++) {
                array[i] = dynamic_array.array[i];
            }
        }

        DynamicArray(initializer_list<T> list) :DynamicArray(int(list.size())) {
            int j = 0;
            for (auto i : list) {
                array[j] = i;
                j++;
            }
        }

        // Деструктор
        ~DynamicArray() {
            delete[] array;
        }

        // Декомпозиция
        T& Get(int index) {
            if (index >= size || index < 0) {
                throw SetException(IndexOutOfRange);
            }
            return array[index];
        }


        T& GetFirst() {
            return Get(0);
        }

        T& GetLast() {
            return Get(size - 1);
        }

        const T& Get(int index) const {
            if (index < 0 || index >= size) throw SetException(IndexOutOfRange);
            return array[index];
        }

        int GetSize() {
            return size;
        }

        // Операции
        DynamicArray<T>& Set(int index, T value) {
            if (index >= size || index < 0) {
                throw SetException(IndexOutOfRange);
            }
            array[index] = value;
            return *this;
        }

        DynamicArray<T>& Resize(int NewSize) {
            if (NewSize < 0) {
                throw SetException(SizeBelowZero);
            }
            try {
                T* array_cur = new T[NewSize];
                int cpy_num = (NewSize > size ? size : NewSize);
                
                for (int i = 0; i < cpy_num; ++i) {
                    array_cur[i] = array[i];  
                }
                delete[] array;
                array = array_cur;
                size = NewSize;
            }
            catch (bad_alloc) {
                throw SetException(MemoryAllocateError);
            }
            return *this;
        }

        DynamicArray<T>* Append(T item) {
            Resize(size + 1);
            Set(size - 1, item);
            return this;
        }

        DynamicArray<T>* Prepend(T item) {
            Resize(size + 1);
            memmove(array + 1, array, (size - 1) * sizeof(T));
            Set(0, item);
            return this;
        }

        DynamicArray<T>* InsertAt(T item, int index) {
            if (index >= size || index < 0) {
                throw SetException(IndexOutOfRange);
            }
            Resize(size + 1);
            memmove(array + (index + 1), array + (index), (size - 1 - index) * sizeof(T));
            Set(index, item);
            return this;
        }

        DynamicArray<T>* GetSubArray(int startIndex, int endIndex) {
            if (startIndex >= size || startIndex < 0 || endIndex >= size || endIndex < 0) {
                throw SetException(IndexOutOfRange);
            }
            if (endIndex < startIndex) {
                throw SetException(NegativeRange);
            }
            DynamicArray<T>* res = new DynamicArray<T>;
            for (int i = startIndex; i <= endIndex; i++) {
                res->Append(Get(i));
            }
            return res;
        }

        DynamicArray<T>* Concat(DynamicArray<T>* arr) {
            DynamicArray<T>* res = new DynamicArray<T>;
            for (int i = 0; i < size; i++) {
                res->Append(Get(i));
            }
            for (int i = 0; i < arr->GetSize(); i++) {
                res->Append(arr->Get(i));
            }
            return res;
        }

        // Операторы
        T& operator[] (int index) {
            return Get(index);
        }

        const T& operator[](int index) const {
            return Get(index);
        }

        DynamicArray<T>& operator=(const DynamicArray<T>& other) {
            if (this != &other) {  
                delete[] array;    
        
                if (other.size > 0) {
                    array = new T[other.size];
                    size = other.size;
                    for (int i = 0; i < size; ++i) {
                        array[i] = other.array[i];
                    }
                } else {
                    array = nullptr;
                    size = 0;
                }
            }
            return *this;
        }





};

#endif