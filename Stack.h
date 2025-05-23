#pragma once

#include "MutableArraySequence.h"
#include "Exception.h"
#include <functional>
#include <complex>
#include <string>
#include <ctime>

using namespace std;

struct Person {
    int id;
    string firstName, middleName, lastName;
    time_t birthDate;
    bool operator==(const Person& o) const {
        return id==o.id
            && firstName==o.firstName
            && middleName==o.middleName
            && lastName==o.lastName
            && birthDate==o.birthDate;
    }
};
using Student = Person;
using Teacher = Person;


template<typename T>
class Stack {
private:
    MutableArraySequence<T> seq;
public:
    Stack() = default;

    // Основные операции

    // Добавление элемента
    void push(const T& x) {
        seq.Append(x);
    }

    // Удалить последний элемент
    T pop() {
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        if (s.GetLength() == 0) throw SetException(IndexOutOfRange);
        T v = s.GetLast();
        s.Resize(s.GetLength() - 1);
        return v;
    }

    // Получить последний элемент
    T top() const {
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        if (s.GetLength() == 0) throw SetException(IndexOutOfRange);
        return s.GetLast();
    }

    // Проверка пустой ли список
    bool empty() const {
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        return s.GetLength() == 0;
    }

    // Размер
    int size() const {
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        return s.GetLength();
    }

    // map: применить f ко всем элементам
    template<typename F>
    auto map(F f) const {
        using U = invoke_result_t<F, T>;
        Stack<U> out;
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        for (int i = 0; i < s.GetLength(); ++i) {
            out.push(f(s.Get(i)));
        }
        return out;
    }

    // where: отфильтровать по predicate
    Stack<T> where(function<bool(const T&)> predicate) const {
        Stack<T> out;
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        for (int i = 0; i < s.GetLength(); ++i) {
            const T& x = s.Get(i);
            if (predicate(x)) out.push(x);
        }
        return out;
    }

    // reduce: свернуть в одно значение, стартуя с init
    T reduce(function<T(const T&, const T&)> f, T init) const {
        T acc = init;
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        for (int i = 0; i < s.GetLength(); ++i) {
            acc = f(s.Get(i), acc);
        }
        return acc;
    }

    // Конкатенация
    Stack<T> concat(const Stack<T>& other) const {
        Stack<T> out;
        auto& s1 = const_cast<MutableArraySequence<T>&>(seq);
        auto& s2 = const_cast<MutableArraySequence<T>&>(other.seq);
        int n1 = s1.GetLength(), n2 = s2.GetLength();
        for (int i = 0; i < n1; ++i) out.push(s1.Get(i));
        for (int i = 0; i < n2; ++i) out.push(s2.Get(i));
        return out;
    }

    // Извлечение подпоследовательности (по заданным индексам)
    Stack<T> getSubsequence(int start, int end) const {
        auto& s = const_cast<MutableArraySequence<T>&>(seq);
        MutableArraySequence<T>* raw = s.GetSubSequence(start, end);
        Stack<T> out;
        for (int i = 0; i < raw->GetLength(); ++i) out.push(raw->Get(i));
        delete raw;
        return out;
    }

    // Поиск на вхождение подпоследовательности
    bool containsSubsequence(const Stack<T>& sub) const {
        auto& s1 = const_cast<MutableArraySequence<T>&>(seq);
        auto& s2 = const_cast<MutableArraySequence<T>&>(sub.seq);
        int n = s1.GetLength();
        int m = s2.GetLength();
        if (m == 0) return false;
        if (m > n) return false;
        for (int i = 0; i <= n - m; ++i) {
            bool ok = true;
            for (int j = 0; j < m; ++j) {
                if (!(s1.Get(i + j) == s2.Get(j))) { ok = false; break; }
            }
            if (ok) return true;
        }
        return false;
    }
};


using IntStack = Stack<int>;
using DoubleStack = Stack<double>;
using ComplexStack = Stack<complex<double>>;
using StringStack = Stack<string>;
using CharStack = Stack<char>;

using Function = int(*)(int);
using FuncStack = Stack<Function>;

using StudentStack  = Stack<Student>;
using TeacherStack  = Stack<Teacher>;
