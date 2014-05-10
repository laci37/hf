#include "List.h"
/**
 * Egy fésűs listát implementáló osztály
 **/ 
template <class T>
class NestedList : public List< List<T> >{
  public:
    NestedList(int (*)(List<T>&,List<T>&));
    NestedList(T**, int* ,int, int (*)(List<T>&,List<T>&));
    NestedList(ListElem< List<T> >*, int (*)(List<T>&,List<T>&));
    /**
     * Rendezi a belső listákat
     */ 
    void orderInner();
};
