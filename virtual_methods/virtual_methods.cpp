#include <iostream>

using namespace std;

class Base
{
  public:

  void A()
  {
    cout << "Base A\n";
  }

  virtual void B()
  {
    cout << "Base B\n";
  }
};

class Derived : public Base
{
  public:

  void A()
  {
    cout << "Derived A\n";
  }

  // Not just adding new virtual B(), but actually orerriding old B().
  virtual void B() override
  {
    cout << "Derived B\n";
  }
};

class Derived2 : public Base
{
  public:

  void A()
  {
    cout << "Derived2 A\n";
  }

  // B() is not pure-virtual, don't have to override it.
};

void Print_ptr(Base *p)
{
  cout << "Accessing through pointer...\n";
  p->A();
  p->B();
}

void Print_ref(Base& p)
{
  cout << "Accessing through reference...\n";
  p.A();
  p.B();
}

// Here we need additional versions of this function
void Print(Base b)
{
  cout << "Base print:\n";

  b.A();
  b.B();
}

void Print(Derived b)
{
  cout << "Derived print:\n";

  b.A();
  b.B();
}

template<class T>
void Print_T_ptr(T *o)
{
  cout << "Template pointer print:\n";

  // No type checking
  o->A();
  o->B();
}

template<class T>
void Print_T_ref(T& o)
{
  cout << "Template reference print:\n";

  // No type checking
  o.A();
  o.B();
}

template<class T>
void Print_T(T o)
{
  cout << "Template print:\n";

  // No type checking
  o.A();
  o.B();
}

int main()
{
  Base *b_ptr   = new Base();
  Base *b_ptr2  = new Derived(); // Derived functions present
  Base *b2_ptr2 = new Derived2();

  cout << "b_ptr: \n";
  Print_ptr(b_ptr); // Base
  cout << endl;

  cout << "b_ptr2: \n";
  Print_ptr(b_ptr2); // Derived
  cout << endl;

  cout << "b2_ptr2: \n";
  Print_ptr(b2_ptr2); // Base
  cout << endl;

  cout << "b_ptr template: \n";
  Print_T_ptr(b_ptr); // Base
  cout << endl;

  cout << "b_ptr2 template: \n";
  Print_T_ptr(b_ptr2); // Derived
  cout << endl;

  cout << "b2_ptr2 template: \n";
  Print_T_ptr(b2_ptr2); // Derived
  cout << endl;

  Base& b_ref   = *b_ptr;
  Base& b_ref2  = *b_ptr2;
  Base& b2_ref2 = *b2_ptr2;

  cout << "b_ref: \n";
  Print_ref(b_ref); // Base
  cout << endl;

  cout << "b_ref2: \n";
  Print_ref(b_ref2); // Derived
  cout << endl;

  cout << "b2_ref2: \n";
  Print_ref(b2_ref2); // Base
  cout << endl;

  cout << "b_ref template: \n";
  Print_T_ref(b_ref); // Base
  cout << endl;

  cout << "b_ref2 template: \n";
  Print_T_ref(b_ref2); // Derived
  cout << endl;

  cout << "b2_ref2 template: \n";
  Print_T_ref(b2_ref2); // Derived
  cout << endl;

  Base b;
  Base b2  = Derived(); // Yet no derived fuctions
  Base b22 = Derived2();
  Derived d;
  //Derived d2 = Base(); // Can't do

  cout << "b: \n";
  Print(b);
  cout << endl;

  cout << "b template: \n";
  Print_T(b); // Base
  cout << endl;

  cout << "b2: \n";
  Print(b2); // Base print. No derived fuctions
  cout << endl;

  cout << "b2 template: \n";
  Print_T(b2); // Base
  cout << endl;

  cout << "b22: \n";
  Print(b22); // Base, compiler deletes A() function from Derived2 as unused.
  cout << endl;

  cout << "b22 template: \n";
  Print_T(b22); // Base
  cout << endl;

  cout << "d: \n";
  Print(d); // Derived print
  cout << endl;

  cout << "d template: \n";
  Print_T(d); // Derived
  cout << endl;

  cin.get();
}
