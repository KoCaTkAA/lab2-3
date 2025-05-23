#include <iostream>
#include <cassert>
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"

using namespace std;

void testLinkedList() {
    // Конструктор без всего
    LinkedList<int> l1;
    assert(l1.GetLength() == 0);

    // Append 
    l1.Append(1)->Append(2);
    assert(l1.GetLength() == 2);
    assert(l1.GetFirst() == 1);
    assert(l1.GetLast() == 2);

    // Prepend и InsertAt 
    auto* lptr = l1.Append(3)->Prepend(0)->InsertAt(5, 2);
    assert(lptr == &l1);
    assert(l1.Get(0) == 0);
    assert(l1.Get(1) == 1);
    assert(l1.Get(2) == 5);
    assert(l1.Get(3) == 2);
    assert(l1.Get(4) == 3);

    // Конструктор через массив
    int arr[] = {10, 20, 30};
    LinkedList<int> l2(arr, 3);
    assert(l2.GetLength() == 3);
    assert(l2.Get(0) == 10 && l2.Get(1) == 20 && l2.Get(2) == 30);

    // Копирующий конструктор
    LinkedList<int> l3(&l2);
    assert(l3.GetLength() == 3);
    assert(l3.Get(1) == 20);

    // Initializer-list конструктор
    LinkedList<int> l4 = {7, 8, 9};
    assert(l4.GetLength() == 3);
    assert(l4.GetFirst() == 7 && l4.GetLast() == 9);

    // Concat
    auto* l5 = l2.Concat(&l4);
    assert(l5->GetLength() == 6);
    assert(l5->Get(3) == 7);

    // GetSubList
    auto* l6 = l5->GetSubList(1, 3);
    assert(l6->GetLength() == 3);
    assert(l6->Get(0) == 20 && l6->Get(2) == 7);

    delete l5;
    delete l6;
}

void testMutableArraySequence() {
    // Конструктор без всего
    MutableArraySequence<int> s1;
    assert(s1.GetLength() == 0);

    // Append
    s1.Append(1)->Append(2);
    assert(s1.GetLength() == 2);
    assert(s1.GetFirst() == 1 && s1.GetLast() == 2);

    // Prepend и InsertAt
    s1.Prepend(0)->InsertAt(5, 2);
    // Now contents: [0,1,5,2]
    assert(s1.Get(0) == 0);
    assert(s1.Get(2) == 5);

    // Конструктор через массив
    int arr[] = {10, 20, 30};
    MutableArraySequence<int> s2(arr, 3);
    assert(s2.GetLength() == 3);
    assert(s2.Get(1) == 20);

    // Копирующий конструктор
    MutableArraySequence<int> s3(s2);
    s2.Append(40);
    assert(s2.GetLength() == 4);
    assert(s3.GetLength() == 3);

    // Initializer-list конструктор
    MutableArraySequence<int> s4{7, 8, 9};
    assert(s4.GetLength() == 3);

    // Concat
    auto* s5 = s2.Concat(&s4);
    assert(s5->GetLength() == 7);
    assert(s5->Get(3) == 40 && s5->Get(4) == 7);

    // GetSubSequence
    auto* s6 = s5->GetSubSequence(2, 5);
    assert(s6->GetLength() == 4);
    assert(s6->Get(0) == 30 && s6->Get(3) == 8);

    delete s5;
    delete s6;
}

void testImmutableArraySequence() {
    // Конструктор без всего
    ImmutableArraySequence<int> i1;
    assert(i1.GetLength() == 0);

    // Конструктор через массив
    int arr[] = {5, 6, 7};
    ImmutableArraySequence<int> i2(arr, 3);
    assert(i2.GetLength() == 3);
    assert(i2.Get(1) == 6);

    // Копирующий конструктор
    ImmutableArraySequence<int> i3(i2);
    assert(i3.GetLength() == 3);
    assert(i3.GetFirst() == 5 && i3.GetLast() == 7);

    // Initializer-list конструктор
    ImmutableArraySequence<int> i4{1, 2, 3};
    assert(i4.GetLength() == 3);

    // Append 
    auto* i1p = i1.Append(10)->Append(20);
    assert(i1p->GetLength() == 2);
    assert(i1p->Get(0) == 10 && i1p->Get(1) == 20);
    delete i1p;

    // Concat
    auto* i5 = i2.Concat(&i4);
    assert(i5->GetLength() == 6);
    assert(i5->Get(3) == 1);
    
    // GetSubSequence
    auto* i6 = i5->GetSubSequence(1, 4);
    assert(i6->GetLength() == 4);
    assert(i6->Get(0) == 6 && i6->Get(3) == 2);
    
    delete i5;
    delete i6;
    
}

int main() {
    testLinkedList();
    cout << "All tests passed successfully." << endl;
    testMutableArraySequence();
    cout << "All tests passed successfully." << endl;
    testImmutableArraySequence();
    cout << "All tests passed successfully." << endl;
    return 0;
}
