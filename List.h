#ifndef LIST_H_INC
#define LIST_H_INC
#include <iostream>
using namespace std;

/**
 * Egy listaelem
 */
template<class T>
class ListElem{
  T* data;
  ListElem<T>* next;
public:
  /**
   * Létrehoz egy listaelemet adott adattal, és next pointerrel.
   * A next pointer defaultja NULL.
   */ 
  ListElem(T*,ListElem<T>*);

  /**
   * Visszaadja a listaelem adatpointerét.
   */ 
  T* getData();

  /**
   * Visszaadja a listaelem adatpointerét.
  */
  const T* getData() const;

  /**
   * Átállítja a listelem adatpointerét.
   */ 
  void setData(const T*);

  /**
   * Visszaadja a következő listaelemre mutató pointert.
   */ 
  ListElem<T>* getNext() const;
  
  /**
   * Átálítja a következő listelemre mutató pointert.
   */ 
  void setNext(const ListElem<T>*);
  
  /**
   * Destruktor
   * felaszbadítja az adatot, és a következő listaelemet is.
   */ 
  ~ListElem();
};

/**
 * Egy lácolt lista osztálya
 */ 
template<class T>
class List{
  protected:
  /**
   * Az őrszem listaelemre mutató pointer.
   */ 
  ListElem<T>* sentinel;

  /**
   * Az összehasonlító függvény amit a rendezéshez használunk.
   * Pozitív számot adjon vissza ha az első paraméter hátrébb 
   * van a rendezésben mint a második, 0-t ha egyenlőek, egyébként negatívat.
   */ 
  int (*ordering)(T&,T&);

public:
  /**
   * Létrehoz egy üres listát megadott rendező függvénnyel.
   * A rendező függvény defaultja a defaultOrdering, ami 
   * a > operátort használja.
   */ 
  List(int (*)(T&,T&));


  /**
   * Létrehoz egy listát adott elemekkel és a megadott rendező függvénnyel.
   * Az elemek egy tömbbel és annak hosszával vannak megadva.
   * A rendező függvény defaultja a defaultOrdering, ami 
   * a > operátort használja.
   */ 
  List(T[],int, int (*)(T&,T&));
  
  /**
   * Létrehoz egy listát adott elemekkel és a megadott rendező függvénnyel.
   * Az elemek egy őrszemes ListElem<T> példányokból felépülő listában 
   * vannak megadva.
   * A rendező függvény defaultja a defaultOrdering, ami 
   * a > operátort használja.
   */ 
  List(ListElem<T>*, int (*)(T&,T&));

  /**
   * Iterátor osztály
   */ 
  class iterator{
      ListElem<T>* next;
    public:
      iterator(ListElem<T>*);
      const T* operator*();
      void operator++();
      bool isAtEnd();
  };
  /**
   * Visszatér egy a lista elején álló iterátorral.
   */ 
  iterator getIterator();
  /**
   * Átállítja a rendezéshez használt összehasonlító függvényt.
   *
   * Pozitív számot adjon vissza ha az első paraméter hátrébb 
   * van a rendezésben mint a második, 0-t ha egyenlőek, egyébként negatívat.
   */ 
  void setOrdering(bool (*ord)(T&,T&));
  
  /**
   * rendezi a listát
   */ 
  void order();

  /**
   * Meghívja a kapott függvényt minden elemre a listában.
   */ 
  void foreach(void (*f)(T&));
  
  /**
   * Rendezetten beszúr egy új elemet.
   */ 
  void operator+=(T);

  /**
   * Kiveszi az első az adott elemmel az összehasonlító
   * függvény szerint egyenlő elemet.
   */ 
  void operator-=(T);
  
  /**
   * Kiírja a lista összes elemét a megadott ostreamre
   */ 
  void debugPrint(ostream&);

  /**
   * Felszabadítja a listát, és az összes adatot is.
   */ 
  ~List();
};

/**
 * Alapértelmezett összehasonlító függvény.
 * A > és a == operátorokat használja.
 */ 
template<class T>
int defaultOrdering(T& a,T& b){
  if(a>b) return 1;
  else if(a==b) return 0;
  return -1;
}

/**
 * Ez az osztály két statikus taggfügvényt tartalmaz 
 * a map és a flatMap funkciók megvalósítására.
 */ 
template <class T, class U>
class ListMapper{
  public:

  /**
   * Egy új listát hoz létre az eredeti lista elemeihez a függvény 
   * által hozzárendelt értékekből.
   */ 
  static List<U> map(List<T>, U* (*)(const T*));
  /**
   * Egy új listát hoz létre az eredeti lista elemeihez a függvény
   * által rendelt listák összefűzésével.
   */ 
  static List<U> flatMap(List<T>, List<U> (*)(const T*));
};


#endif
