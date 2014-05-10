#include "List.h"
#include "NestedList.h"
#include <string>
#include <iostream>

using namespace std;

template<class T>
int dummy(T& a, T& b){
  return 1;
}

class Person{
  string name;
public:
  Person(string name): name(name){}
  Person(const char* name): name(name) {}
  string getName(){ return name; }
  bool operator>(const Person& that) const{
     return this->name > that.name;
  }
};

void test1(){
  NestedList<Person> list(dummy);
  Person t[]={ Person("Béla"), Person("Aladár")};
  Person t2[]= { Person("Cecil"), Person("Dénes")};
  list += List<Person>(t,2,dummy);
  list += List<Person>(t2,2,dummy);
  list.orderInner();
  list.debugPrint(cout);
}

int main(){
  test1(); 
}
