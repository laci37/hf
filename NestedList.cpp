#include "NestedList.h"

template<class T>
NestedList<T>::NestedList(int (*ord)(List<T>&,List<T>&)): List< List<T> >(ord) {}

template<class T>
NestedList<T>::NestedList(T **data, int *sizes, int nLists, 
  int (*ord)(List<T>&,List<T>&)){
  List< List<T> >::sentinel = new ListElem< List<T> >(NULL);
  List< List<T> >::ordering=ord;
  ListElem< List<T> > *last = List< List<T> >::sentinel;
  for(int i=0; i<nLists; i++){
    ListElem< List<T> > *elem = new ListElem< List<T> >
        (new List<T>(data[i],sizes[i]));
    last->setNext(elem);
    last=elem;
  }
}

template<class T>
NestedList<T>::NestedList(ListElem< List<T> > *sentinel, 
  int (*ord)(List<T>&,List<T>&)): List< List<T> >(sentinel,ord){

}

template<class T>
void NestedList<T>::orderInner(){
  for(typename List< List<T> >::iterator i=List< List<T> >::getIterator();!i.isAtEnd();i++){
    (*i)->order();
  }
}
