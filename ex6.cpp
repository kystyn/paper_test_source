#include "tests.h"

class A6
{
public:
    A6() { std::cout<< "A6" << std::endl; m_a = 5; }
    A6 ( const A6& a) { std::cout<< "A6->A6" << std::endl; m_a = 5; }
    A6( int a) { std::cout << "0->A6" << std::endl; m_a = 0; }
    A6& operator =(const A6& a) {
        std::cout << "A6 = A6 " << std::endl;
        m_a = a.m_a;
        return *this;
    }
    ~A6() { std::cout << "~A6" << std::endl; }
    void print ( ) { std::cout << m_a << std::endl;  }
private:
    int m_a;
};
class D6: public A6
{
public:
    D6() { std::cout << "D6" << std::endl; m_a = 5; }
    D6(int a) { std::cout << "int->D6" << std::endl; m_a = a; }
    D6& operator =(const D6& a) {
        std::cout << "D6 = D6 " << std::endl;
        m_a = a.m_a;
        return *this;
    }
    ~D6() { std::cout << "~D6" << std::endl; }
    virtual void print() { std::cout << "D::print" << std::endl; }
protected:
    int m_a;
};
class B6 {
public:
    B6() { std::cout << "B6" << std::endl; }
    ~B6() { std::cout << "~B6" << std::endl; }
    void operator = (A6 &a_) { std::cout << "B6 = A6" << std::endl; a = a_; }
    A6& do_some_stuff ( ) {
        class C: public D6, private A6 {
        public:
            C  (A6 a): A6(D6::m_a), D6(15) { std::cout << "A6->C" << std::endl; }  
            C  ()     { std::cout << "C" << std::endl;     }
            ~C ()     { std::cout << "~C" << std::endl;    }
            void print() { std::cout << "C::print" << std::endl; }
        };
        C c(a);
        return static_cast<D6&>(c);
    }
private:
    A6 a;
};
void nir::run_test_6() {
	std::cout << "54:\n"; B6 b;
	std::cout << "55:\n"; A6 *a = new A6;
	std::cout << "56:\n"; *a = b.do_some_stuff();
	std::cout << "57:\n"; [&b](A6* c) ->void { b = *c; c->print(); } (a);
	std::cout << "58:\n"; delete a;
}