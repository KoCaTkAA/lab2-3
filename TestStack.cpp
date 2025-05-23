#include "Stack.h"
#include <iostream>
#include <cassert>

using namespace std;

int inc1(int x){ return x + 1; }
int inc2(int x){ return x + 2; }
int inc3(int x){ return x + 3; }
/*
int main(){
    IntStack s;
    s.push(1); 
    s.push(2); 
    s.push(3);
    auto filtered = s.where([](int x){ return x % 2 == 1; });
    int sum = s.reduce([](int x, int acc){ return x + acc; }, 0);
    
    
    FuncStack fs;
    fs.push(&inc1);
    fs.push(&inc2);
    fs.push(&inc3);
    auto results = fs.map([](Function f){ return f(0); }); 


    StudentStack st;
    Student a{1,"Ivan","Ivanovich","Ivanov",0};
    Student b{2,"Petr","Petrovich","Petrov",0};
    st.push(a); 
    st.push(b);
    auto sub = st.getSubsequence(0,1);                      
    bool has = st.containsSubsequence(sub);   
                 
    cout << "Sum: " << sum << "\n";
    return 0;
}
*/


void testIntStack() {
    IntStack s;
    assert(s.empty());
    s.push(1); s.push(2); s.push(3);
    assert(!s.empty());
    assert(s.size() == 3);
    assert(s.top() == 3);
    assert(s.pop() == 3);
    assert(s.size() == 2);

    // where: оставить только нечётные
    auto filtered = s.where([](int x){ return x % 2 == 1; });
    assert(filtered.size() == 1);
    assert(filtered.top() == 1);

    // map: удвоить
    auto mapped = s.map([](int x){ return x * 2; });
    assert(mapped.size() == 2);
    assert(mapped.pop() == 4);
    assert(mapped.pop() == 2);

    // reduce: сумма
    int sum = s.reduce([](int x, int acc){ return x + acc; }, 0);
    assert(sum == 3); 

    // concat
    IntStack a; a.push(4); a.push(5);
    auto conc = s.concat(a);
    assert(conc.size() == 4);
    assert(conc.pop() == 5);
    assert(conc.pop() == 4);
    assert(conc.pop() == 2);
    assert(conc.pop() == 1);

    // getSubsequence
    s.push(3); 
    auto sub = s.getSubsequence(0,2);
    assert(sub.size() == 3);
    assert(sub.pop() == 3);
    assert(sub.pop() == 2);
    assert(sub.pop() == 1);

    // containsSubsequence
    assert(s.containsSubsequence(sub) == false);
    auto s2 = s.getSubsequence(0,1); 
    assert(s.containsSubsequence(s2));
    cout << "testIntStack passed." << endl;
}

void testDoubleStack() {
    DoubleStack s;
    s.push(1.5); s.push(2.5);
    assert(s.size() == 2);
    double sum = s.reduce([](double x, double acc){ return x + acc; }, 0.0);
    assert(fabs(sum - 4.0) < 1e-9);
    cout << "testDoubleStack passed." << endl;
}

void testCharStringStack() {
    CharStack cs;
    cs.push('a'); cs.push('b'); cs.push('c');
    assert(cs.top() == 'c');
    auto afterA = cs.where([](char c){ return c > 'a'; }); // b,c
    assert(afterA.size() == 2);

    StringStack ss;
    ss.push("foo"); ss.push("bar");
    auto concat = ss.concat(ss); 
    assert(concat.size() == 4);
    assert(concat.pop() == "bar");
    cout << "testCharStringStack passed." << endl;
}

void testFuncStack() {
    FuncStack fs;
    fs.push(&inc1);
    fs.push(&inc2);
    fs.push(&inc3);
    auto results = fs.map([](Function f){ return f(0); });
    assert(results.size() == 3);
    assert(results.pop() == 3);
    assert(results.pop() == 2);
    assert(results.pop() == 1);
    cout << "testFuncStack passed." << endl;
}

void testPersonStack() {
    StudentStack st;
    Student a{1, "Ivan", "Ivanovich", "Ivanov", 0};
    Student b{2, "Petr", "Petrovich", "Petrov", 0};
    Student c{3, "Sasha", "Sergeevich", "Sidorov", 0};
    st.push(a); st.push(b); st.push(c);
    assert(st.size() == 3);
    auto sub = st.getSubsequence(1,2);
    assert(sub.size() == 2);
    assert(sub.pop() == c);
    assert(sub.pop() == b);
    auto probe = st.getSubsequence(0,1); // a,b
    assert(st.containsSubsequence(probe));
    cout << "testPersonStack passed." << endl;
}

int main() {
    testIntStack();
    testDoubleStack();
    testCharStringStack();
    testFuncStack();
    testPersonStack();
    cout << "All Stack tests passed successfully." << endl;
    return 0;
}

