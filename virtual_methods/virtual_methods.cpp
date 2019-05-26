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

  virtual void B()
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

// Only 1 function needed
void PrintPtr(Base *p)
{
  p->A();
  p->B();
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

// Need 2 functions for pointer/no pointer
// With virtual function still need only 1 function
template<class T>
void PrintT(T *o)
{
  cout << "Template pointer print:\n";

  // No type checking
  o->A();
  o->B();
}

template<class T>
void PrintT(T o)
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
  PrintPtr(b_ptr); // Base
  cout << endl;

  cout << "b_ptr2: \n";
  PrintPtr(b_ptr2); // Derived
  cout << endl;

  cout << "b2_ptr2: \n";
  PrintPtr(b2_ptr2); // Base
  cout << endl;

  Base b;
  Base b2  = Derived(); // Yet no derived fuctions
  Base b22 = Derived2();

  cout << "b: \n";
  Print(b);
  cout << endl;

  cout << "b2: \n";
  Print(b2); // Base print. No derived fuctions
  cout << endl;

  cout << "b22: \n";
  Print(b22); // Base, compiler deletes A() function from Derived2 as unused.
  cout << endl;

  Derived d;
  //Derived d2 = Base(); // Can't do

  cout << "d: \n";
  Print(d); // Derived print
  cout << endl;

  cout << "b_ptr template: \n";
  PrintT(b_ptr); // Base
  cout << endl;

  cout << "b_ptr2 template: \n";
  PrintT(b_ptr2); // Derived
  cout << endl;

  cout << "b template: \n";
  PrintT(b); // Base
  cout << endl;

  cout << "b2 template: \n";
  PrintT(b2); // Base
  cout << endl;

  cout << "d template: \n";
  PrintT(d); // Derived
  cout << endl;

  cin.get();
}
