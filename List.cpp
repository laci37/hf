#include "List.h"

template<class T>
ListElem<T>::ListElem(T* data, ListElem<T>* next=NULL){
  this->data=data;
  this->next=next;
}

template<class T>
const T* ListElem<T>::getData() const{
  return this->data;
}

template<class T>
void ListElem<T>::setData(const T* data){
  this->data=data;
}

template<class T>
ListElem<T>* ListElem<T>::getNext() const{
  return this->next;
}

template<class T>
void ListElem<T>::setNext(const ListElem<T>* next){
  this->next=next;
}

template<class T>
ListElem<T>::~ListElem(){
  delete data;
  delete next;
}


template<class T>
List<T>::List(int (*ord)(T&,T&)=defaultOrdering){
  sentinel= new ListElem<T>(NULL);
}

template<class T>
List<T>::List(T data[], int len, int(*ord)(T&,T&)=defaultOrdering): ordering(ord){
  sentinel= new ListElem<T>(NULL);
  ListElem<T>* last=sentinel;
  for(int i=0; i<len; i++){
    ListElem<T>* elem= new ListElem<T>(new T(data[i]));
    last->setNext(elem);
    last=elem;
  }
}

template<class T>
List<T>::List(ListElem<T>* sentinel, int(*ord)(T&,T&)=defaultOrdering): ordering(ord), sentinel(sentinel) {}

template<class T>
List<T>::iterator::iterator(ListElem<T>* next): next(next){}

template<class T>
const T* List<T>::iterator::operator*(){
  return next->getData();
}

template<class T>
bool List<T>::iterator::isAtEnd(){
  return next==NULL;
}

template<class T>
void List<T>::iterator::operator++(){
  next=next->next;
}

template<class T>
typename List<T>::iterator List<T>::getIterator(){
  return iterator(sentinel->getNext());
}

template<class T>
void List<T>::setOrdering(bool (*ord)(T&,T&)){
  ordering=ord;
}

template<class T>
void List<T>::order(){
  ListElem<T>* tail = sentinel->getNext();
  ListElem<T>* newEnd = sentinel;
  while(tail!=NULL){
    //minimum kiválasztás
    ListElem<T>* min = tail;
    for(ListElem<T>* akt=tail;akt!=NULL;akt=akt->getNext()){
      if(ordering(min->getData(),akt->getData())>1) min = akt;
    }

    //kifűzzük a listából
    if(min==tail){
      tail=tail->getNext();
    } else {
      ListElem<T>* last=tail;
      for(ListElem<T>* akt=tail->getNext();akt!=NULL;akt=akt->getNext()){
        if(min==akt){
          last->setNext(akt->getNext());
          break;
        }
        last=akt;
      }
    }
    //berakjuk a helyére
    newEnd->setNext(min);
    min->setNext(NULL);
  }
}

template<class T>
void List<T>::foreach(void (*f)(T&)){
  for(iterator i=getIterator();!i.isAtEnd();i++){
    f(**i);
  }
}

template<class T, class U>
List<U> ListMapper<T,U>::map(List<T> l, U* (*f)(const T*)){
  ListElem<U> * sentinel= new ListElem<U>(NULL);
  ListElem<U> *last=sentinel;
  for(typename List<T>::iterator i=l.getIterator();!i.isAtEnd();i++){
    U* data=f(*i);
    ListElem<U> *act = new ListElem<U>(data);
    last->setNext(act);
    last=act;
  }
  return List<U>(sentinel);
}

template<class T, class U>
List<U> ListMapper<T,U>::flatMap(List<T> l, List<U> (*f)(const T*)){
  ListElem<U> *s = new ListElem<U>(NULL);
  ListElem<U> *last=s;
  for(typename List<T>::iterator i=l.getIterator();!i.isAtEnd;i++){
    List<U> l2 = f(*i);
    for (typename List<U>::iterator j=l2.getIterator();!j.isAtEnd();j++){
      ListElem<U> *elem= new ListElem<U>(new U(**j));
      last->setNext(elem);
      last=elem;
    }
  }
  return List<U>(s);
}

template<class T>
void List<T>::operator+=(T data){
  ListElem<T>* last=sentinel;
  ListElem<T>* act=sentinel->getNext();
  while(act!=NULL){
    if(0 < ordering(act->getData(),data)){
      break;
    }
    last=act;
    act=act->getNext();
  }
  ListElem<T> *elem= new ListElem<T>(new T(data),act);
  last->setNext(elem);
}

template<class T>
void List<T>::operator-=(T data){
  ListElem<T>* last=sentinel;
  ListElem<T>* act=sentinel->getNext();
  while(act!=NULL){
    if(0==ordering(act->getData(),data)){
      last.setNext(act.getNext());
      delete act;
      break;
    }
    last=act;
    act=act->getNext();
  }
}

template<class T>
void List<T>::debugPrint(ostream&){}

template<class T>
List<T>::~List(){
  delete sentinel;
}
