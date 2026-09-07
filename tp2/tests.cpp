#include "testing.h"
#include "tp2.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>

class TipoDummy
{
private:
    bool destroyed;
public:
    TipoDummy(const TipoDummy &otro) { destroyed = false;}
    TipoDummy &operator=(const TipoDummy &otro) { assert(!destroyed); }
    ~TipoDummy() {assert(!destroyed); destroyed = true; }
};

class TipoDummyConDefault
{
private:
    bool destroyed;
public:
    TipoDummyConDefault() { destroyed = false;}
    TipoDummyConDefault(const TipoDummyConDefault &otro) { destroyed = false;}
    TipoDummyConDefault &operator=(const TipoDummy &otro) { assert(!destroyed); }
    ~TipoDummyConDefault() {assert(!destroyed); destroyed = true; }
};

template<typename T>
bool test_create_and_destroy_list() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  delete list;
  return tests_result;
}

template<typename T>
bool test_empty_size_and_length() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  tests_result &= test_assert("La lista está vacia", list->is_empty());
  delete list;
  return tests_result;
}

template<typename T>
bool test_insert_head_successfully() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  tests_result &= test_assert("La lista está vacia", list->is_empty());
  list->insert_head(T());
  tests_result &=
      test_assert("El largo de la lista es 1", list->length() == 1);
  tests_result &= test_assert("La lista no está vacia", !list->is_empty());
  delete list;
  return tests_result;
}

template<typename T>
bool test_destroy_value() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  for (int i = 0; i < 100; i++) {
    list->insert_head(T());
  }
  delete list;
  test_assert("Se destruyo la lista", true);
  return tests_result;
}

template<typename T>
bool test_insert_tail_successfully() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  tests_result &= test_assert("La lista está vacia", list->is_empty());
  list->insert_tail(T());
  tests_result &=
      test_assert("El largo de la lista es 1", list->length() == 1);
  tests_result &= test_assert("La lista no está vacia", !list->is_empty());
  delete list;
  return tests_result;
}

bool test_peek_head() {
  bool tests_result = true;
  List<int> *list = new List<int>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 10; i++) {
    list->insert_head(i);
    tests_result &= test_assert("El valor de head es correcto",
                                list->peek_head() == i);
  }
  delete list;
  return tests_result;
}

bool test_peek_tail() {
  bool tests_result = true;
  List<int> *list = new List<int>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 10; i++) {
    list->insert_tail(i);
    tests_result &= test_assert("El valor de tail es correcto",
                                list->peek_tail() == i);
  }
  delete list;
  return tests_result;
}

template<typename T>
bool test_simple_pop_head(const T&valueA, const T&valueB) {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->insert_head(valueA);
  tests_result &=
      test_assert("El largo de la lista es 1", list->length() == 1);
  tests_result &= test_assert("Al eliminar el head el valor es correcto",
                              list->pop_head() == valueA);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  list->insert_tail(valueB);
  tests_result &=
      test_assert("El largo de la lista es 1", list->length() == 1);
  tests_result &= test_assert("Al eliminar el head el valor es correcto",
                              list->pop_head() == valueB);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  delete list;
  return tests_result;
}

template<typename T>
bool test_simple_pop_tail(const T&valueA, const T&valueB) {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->insert_tail(valueA);
  tests_result &=
      test_assert("El largo de la lista es 1", list->length() == 1);
  tests_result &= test_assert("Al eliminar el tail el valor es correcto",
                              list->pop_tail() == valueA);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  list->insert_head(valueB);
  tests_result &=
      test_assert("El largo de la lista es 1", list->length() == 1);
  tests_result &= test_assert("Al eliminar el tail el valor es correcto",
                              list->pop_tail() == valueB);
  tests_result &=
      test_assert("El largo de la lista es 0", list->length() == 0);
  delete list;
  return tests_result;
}

bool test_multiple_peek() {
  bool tests_result = true;
  List<int> *list = new List<int>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      list->insert_head(i);
      tests_result &= test_assert("El valor de head es el insertado",
                                  list->peek_head() == i);
      if (list->length() > 1) {
        tests_result &= test_assert("El valor de tail es correcto",
                                    list->peek_tail() == (i - 1));
      } else {
        tests_result &= test_assert("El valor de tail es correcto",
                                    list->peek_tail() == i);
      }
    } else {
      list->insert_tail(i);
      tests_result &= test_assert("El valor de head es correcto",
                                  list->peek_head() == i - 1);
      tests_result &= test_assert("El valor de tail es el insertado",
                                  list->peek_tail() == i);
    }
  }
  delete list;
  return tests_result;
}

bool test_multiple_pop() {
  bool tests_result = true;
  List<int> *list = new List<int>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 0; i < 100; i++) {
    list->insert_head(i);
    list->insert_tail(i);
  }

  tests_result &=
      test_assert("El largo de la lista es 200", list->length() == 200);

  for (int i = 99; i >= 0; i--) {
    tests_result &=
        test_assert("Eliminar el primer elemento funciona correctamente",
                    list->pop_head() == i);
    tests_result &=
        test_assert("Eliminar el último elemento funciona correctamente",
                    list->pop_tail() == i);
  }

  tests_result &= test_assert("La lista está vacia", list->is_empty());

  delete list;
  return tests_result;
}

bool test_multiple_pop_random_patterns() {
  bool tests_result = true;
  List<int> list;
  for (int i = 0; i < 100; i++) {
    list.insert_head(i);
    list.insert_tail(i+811);
    switch (((i*37)%97) % 4) {
    case 0:
      list.insert_head(i);
      list.insert_tail(i+811);
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      list.pop_head() == i);
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      list.pop_tail() == i+811);
      break;

    case 1:
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      list.pop_head() == i);
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      list.pop_tail() == i+811);
      list.insert_head(i);
      list.insert_tail(i+811);
      break;

    case 2:
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      list.pop_tail() == i+811);
      list.insert_head(i);
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      list.pop_head() == i);
      list.insert_tail(i+811);
      break;

    case 3:
      tests_result &=
          test_assert("Eliminar el primer elemento funciona correctamente",
                      list.pop_head() == i);
      list.insert_head(i);
      tests_result &=
          test_assert("Eliminar el último elemento funciona correctamente",
                      list.pop_tail() == i+811);
      list.insert_tail(i+811);
      break;
    }
  }

  tests_result &=
      test_assert("El largo de la lista es 200", list.length() == 200);

  for (int i = 99; i >= 0; i--) {
    tests_result &=
        test_assert("Eliminar el primer elemento funciona correctamente",
                    list.pop_head() == i);
    tests_result &=
        test_assert("Eliminar el último elemento funciona correctamente",
                    list.pop_tail() == i+811);
  }

  tests_result &= test_assert("La lista está vacia", list.is_empty());

  return tests_result;
}

template<typename T>
bool test_iter_create_and_destroy() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->create_head();
  list->create_tail();
  delete list;
  return tests_result;
}

template<typename T>
bool test_iter_empty_list_move_fails() {
  bool tests_result = true;
  List<T> *list = new List<T>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  typename List<T>::ListIter iter = list->create_head();
  typename List<T>::ListIter iter2 = list->create_tail();
  tests_result &= test_assert("El iterador en head no puede avanzar",
                              !iter.forward());
  tests_result &= test_assert("El iterador en head no puede retroceder",
                              !iter.backward());
  tests_result &= test_assert("El iterador en tail no puede avanzar",
                              !iter2.forward());
  tests_result &= test_assert("El iterador en tail no puede retroceder",
                              !iter2.backward());
  delete list;
  return tests_result;
}

template<typename T>
bool test_iter_one_element_list_move_fails() {
  bool tests_result = true;
  List<List<T>> *list = new List<List<T>>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->insert_tail(List<T>());
  typename List<List<T>>::ListIter iter = list->create_head();
  typename List<List<T>>::ListIter iter2 = list->create_tail();
  tests_result &= test_assert("El iterador en head no puede avanzar",
                              !iter.forward());
  tests_result &= test_assert("El iterador en head no puede retroceder",
                              !iter.backward());
  tests_result &= test_assert("El iterador en tail no puede avanzar",
                              !iter2.forward());
  tests_result &= test_assert("El iterador en tail no puede retroceder",
                              !iter2.backward());
  delete list;
  return tests_result;
}

bool test_iter_simple_move() {
  bool tests_result = true;
  List<int> *list = new List<int>;
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->insert_tail(1);
  list->insert_tail(2);
  typename List<int>::ListIter iter = list->create_head();
  tests_result &=
      test_assert("El iterador en head avanzo", iter.forward());
  tests_result &= test_assert("El iterador en head no puede volver a avanzar",
                              !iter.forward());
  tests_result &=
      test_assert("El iterador en head retrocedio", iter.backward());
  tests_result &=
      test_assert("El iterador en head no puede volver a retroceder",
                  !iter.backward());
  delete list;
  return tests_result;
}

bool test_iter_move_and_peek() {
  bool tests_result = true;
  List<int > *list = new List<int>;
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->insert_tail(1);
  list->insert_tail(2);
  typename List<int>::ListIter iter = list->create_head();
  tests_result &= test_assert("El valor del actual del iterador es 1",
                              iter.peek_current() == 1);
  tests_result &=
      test_assert("El iterador en head avanzo", iter.forward());
  tests_result &= test_assert("El valor del actual del iterador es 2",
                              iter.peek_current() == 2);
  tests_result &=
      test_assert("El iterador en head retrocedio", iter.backward());
  tests_result &= test_assert("El valor del actual del iterador es 1",
                              iter.peek_current() == 1);
  delete list;
  return tests_result;
}

bool test_iter_move_at_start_and_end() {
  bool tests_result = true;
  List<int> *list = new List<int>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  list->insert_tail(1);
  list->insert_tail(2);
  typename List<int>::ListIter iter = list->create_head();
  tests_result &=
      test_assert("El iterador esta al principio", iter.at_first());
  tests_result &=
      test_assert("El iterador no esta al final", !iter.at_last());
  tests_result &=
      test_assert("El iterador en head avanzo", iter.forward());
  tests_result &= test_assert("El iterador no esta al principio",
                              !iter.at_first());
  tests_result &=
      test_assert("El iterador esta al final", iter.at_last());
  tests_result &=
      test_assert("El iterador en head retrocedio", iter.backward());
  tests_result &=
      test_assert("El iterador esta al principio", iter.at_first());
  tests_result &=
      test_assert("El iterador no esta al final", !iter.at_last());
  delete list;
  return tests_result;
}

bool test_iter_full_list_read_only() {
  bool tests_result = true;
  List<int> *list = new List<int>;
  tests_result &= test_assert("La lista fue creada", list != NULL);
  for (int i = 1; i <= 100; i++) {
    list->insert_tail(i);
  }
  typename List<int>::ListIter iter = list->create_head();
  tests_result &=
      test_assert("El iterador esta al principio", iter.at_first());
  tests_result &=
      test_assert("El iterador no esta al final", !iter.at_last());
  int i = 1;
  tests_result &= test_assert("El valor del actual del iterador es correcto",
                              iter.peek_current() == i);
  while (iter.forward()) {
    i++;
    tests_result &= test_assert(
        "Se avanzo una posicion y el valor del actual del iterador es correcto",
        iter.peek_current() == i);
  }
  tests_result &= test_assert("El iterador no esta al principio",
                              !iter.at_first());
  tests_result &=
      test_assert("El iterador esta al final", iter.at_last());
  i = 100;
  tests_result &= test_assert("El valor del actual del iterador es correcto",
                              iter.peek_current() == i);
  while (iter.backward()) {
    i--;
    tests_result &= test_assert(
        "Se avanzo una posicion y el valor del actual del iterador es correcto",
        iter.peek_current() == i);
  }
  tests_result &=
      test_assert("El iterador esta al principio", iter.at_first());
  tests_result &=
      test_assert("El iterador no esta al final", !iter.at_last());
  delete list;
  return tests_result;
}

bool test_iter_move_on_random_list() {
  bool tests_result = true;
  List<int> list;
  for (int i = 0; i < 300; i++) {
    switch (((i*79) % 107) % 6) {
    case 0: // insert head exitoso
      list.insert_head(i);
    case 1: // insert tail exitoso
      list.insert_tail(i);
    case 2: // pop head
      list.pop_head();
    case 3: // pop tail
      list.pop_tail();
    default:
      list.insert_head(i);
    }
  }
  typename List<int>::ListIter iter = list.create_tail();
  tests_result &= test_assert("El iterador no esta al principio",
                              !iter.at_first());
  tests_result &=
      test_assert("El iterador esta al final", iter.at_last());
  size_t cant = 1;
  while (iter.backward()) {
    cant++;
  }
  tests_result &=
      test_assert("El largo de la lista es consistente con la cantidad iterada",
                  list.length() == cant);
  tests_result &=
      test_assert("El iterador esta al principio", iter.at_first());
  tests_result &=
      test_assert("El iterador no esta al final", !iter.at_last());
  return tests_result;
}

bool test_iter_insert_after_at_start() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  typename List<int*>::ListIter iter = list->create_head();
  aux = new int;
  *aux = 2;
  tests_result &= test_assert("Se inserto un elemento delante de head",
                              iter.insert_after(aux));
  tests_result &=
      test_assert("El iterador sigue en el primero", iter.at_first());

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  delete list;
  return tests_result;
}

bool test_iter_insert_after_at_middle() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 2;
  list->insert_tail(aux);
  aux = new int;
  *aux = 4;
  list->insert_tail(aux);
  typename List<int*>::ListIter iter = list->create_head();
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  aux = new int;
  *aux = 3;
  tests_result &= test_assert("Se inserto un elemento delante",
                              iter.insert_after(aux));

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 4",
                              *((int *)iter.peek_current()) == 4);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
  delete aux;
  delete list;
  return tests_result;
}

bool test_iter_insert_after_at_tail() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 2;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  typename List<int*>::ListIter iter = list->create_head();
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  aux = new int;
  *aux = 4;
  tests_result &= test_assert("Se inserto un elemento delante",
                              iter.insert_after(aux));

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 4",
                              *((int *)iter.peek_current()) == 4);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el ultimo elemento y es un 4", *aux == 4);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el ultimo elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el ultimo elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el ultimo elemento y es un 1", *aux == 1);
  delete aux;
  delete list;
  return tests_result;
}

bool test_iter_insert_before_at_end() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);

  typename List<int*>::ListIter iter = list->create_tail();
  aux = new int;
  *aux = 2;
  tests_result &= test_assert("Se inserto un elemento atras del final",
                              iter.insert_before(aux));
  tests_result &=
      test_assert("El iterador sigue en el final", iter.at_last());

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  delete list;
  return tests_result;
}

bool test_iter_insert_before_at_middle() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  aux = new int;
  *aux = 4;
  list->insert_tail(aux);
  typename List<int*>::ListIter iter = list->create_tail();
  tests_result &=
      test_assert("El iterador retrocedio", iter.backward());
  aux = new int;
  *aux = 2;
  tests_result &= test_assert("Se inserto un elemento detras",
                              iter.insert_before(aux));

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 4",
                              *((int *)iter.peek_current()) == 4);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
  delete aux;
  delete list;
  return tests_result;
}

bool test_iter_insert_before_at_head() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 2;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  aux = new int;
  *aux = 4;
  list->insert_tail(aux);
  typename List<int*>::ListIter iter = list->create_tail();
  tests_result &=
      test_assert("El iterador retrocedio", iter.backward());
  tests_result &=
      test_assert("El iterador retrocedio", iter.backward());
  aux = new int;
  *aux = 1;
  tests_result &= test_assert("Se inserto un elemento detras de head",
                              iter.insert_before(aux));

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 4",
                              *((int *)iter.peek_current()) == 4);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
  delete aux;
  delete list;
  return tests_result;
}

template<typename T>
bool test_iter_insert_empty_lists() {
  bool tests_result = true;
  List<List<List<T>>> *list = new List<List<List<T>>>();
  
  typename List<List<List<T>>>::ListIter iter = list->create_head();
  List<List<T>> aux;
  aux.insert_tail(List<T>());
  aux.insert_tail(List<T>());
  aux.insert_tail(List<T>());
  aux.insert_tail(List<T>());
  tests_result &=
      test_assert("Se inserto una lista de 4 elementos", iter.insert_after(aux));
  tests_result &=
      test_assert("El iterador está en el primero", iter.at_first());
  List<List<T>> aux2 = list->pop_head();
  aux = aux2;
  tests_result &=
      test_assert("Se remueve el primer elemento y es de 4 elementos", aux.length() == 4);

  iter = list->create_head();
  aux = List<List<T>>();
  aux.insert_tail(List<T>());
  aux.insert_tail(List<T>());
  tests_result &=
      test_assert("Se inserto una lista de 2 elementos", iter.insert_after(aux));
  tests_result &=
      test_assert("El iterador está en el primero", iter.at_first());
  aux = list->pop_tail();
  tests_result &=
      test_assert("Se remueve el ultimo elemento y es de 2 elementos", aux.length() == 2);

  iter = list->create_tail();
  aux.insert_tail(List<T>());
  tests_result &=
      test_assert("Se inserto una lista de 3 elementos", iter.insert_after(aux));
  aux = List<List<T>>();
  tests_result &=
      test_assert("El iterador está en el ultimo", iter.at_last());
  aux = list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es de 3 elementos", aux.length() == 3);

  iter = list->create_tail();
  aux.insert_tail(List<T>());
  tests_result &=
      test_assert("Se inserto una lista de 4 elementos", iter.insert_after(aux));
  tests_result &=
      test_assert("El iterador está en el ultimo", iter.at_last());
  List<List<T>> finalAux = list->pop_tail();
  tests_result &=
      test_assert("Se remueve el ultimo elemento y es una lista de 4", finalAux.length() == 4);

  delete list;
  return tests_result;
}

bool test_iter_delete_one_element_list() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);

  typename List<int*>::ListIter iter = list->create_head();
  aux = (int *)iter.remove();
  tests_result &= test_assert("Se elimina un 1 de la lista", *aux == 1);
  delete aux;

  tests_result &= test_assert("La lista esta vacia", list->is_empty());

  delete list;
  return tests_result;
}

bool test_iter_delete_head() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 2;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  aux = new int;
  *aux = 4;
  list->insert_tail(aux);

  typename List<int*>::ListIter iter = list->create_head();
  aux = (int *)iter.remove();
  tests_result &= test_assert("Se elimina un 1 de la lista", *aux == 1);
  delete aux;
  tests_result &= test_assert("El elemento actual es un 2",
                              *((int *)iter.peek_current()) == 2);

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 4",
                              *((int *)iter.peek_current()) == 4);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_head();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
  delete aux;

  delete list;
  return tests_result;
}

bool test_iter_delete_tail() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 2;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  aux = new int;
  *aux = 4;
  list->insert_tail(aux);

  typename List<int*>::ListIter iter = list->create_tail();
  aux = (int *)iter.remove();
  tests_result &= test_assert("Se elimina un 4 de la lista", *aux == 4);
  tests_result &= test_assert("El elemento actual es un 3",
                              *((int *)iter.peek_current()) == 3);
  delete aux;

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;

  delete list;
  return tests_result;
}

bool test_iter_delete_middle() {
  bool tests_result = true;
  List<int*> *list = new List<int*>();
  tests_result &= test_assert("La lista fue creada", list != NULL);
  int *aux = new int;
  *aux = 1;
  list->insert_tail(aux);
  aux = new int;
  *aux = 2;
  list->insert_tail(aux);
  aux = new int;
  *aux = 3;
  list->insert_tail(aux);
  aux = new int;
  *aux = 8;
  list->insert_tail(aux);
  aux = new int;
  *aux = 4;
  list->insert_tail(aux);

  typename List<int*>::ListIter iter = list->create_tail();
  tests_result &=
      test_assert("Se retrocede el iterador", iter.backward());
  aux = (int *)iter.remove();
  tests_result &= test_assert("Se elimina un 8 de la lista", *aux == 8);
  tests_result &= test_assert("El elemento actual es un 4",
                              *((int *)iter.peek_current()) == 4);
  delete aux;

  iter = list->create_head();
  tests_result &= test_assert("El elemento actual es 1",
                              *((int *)iter.peek_current()) == 1);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 2",
                              *((int *)iter.peek_current()) == 2);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 3",
                              *((int *)iter.peek_current()) == 3);
  tests_result &= test_assert("El iterador avanzo", iter.forward());
  tests_result &= test_assert("El elemento actual es 4",
                              *((int *)iter.peek_current()) == 4);
  tests_result &=
      test_assert("El iterador no puede avanzar", !iter.forward());

  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
  delete aux;
  aux = (int *)list->pop_tail();
  tests_result &=
      test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
  delete aux;

  delete list;
  return tests_result;
}

template<typename T>
int minimal_generic_type_tests() {
  int return_code = 0;
  return_code += !test_create_and_destroy_list<T>();
  return_code += !test_empty_size_and_length<T>();
  return_code += !test_iter_create_and_destroy<T>();
  return_code += !test_iter_empty_list_move_fails<T>();
  return_code += !test_iter_one_element_list_move_fails<T>();
  return_code += !test_iter_insert_empty_lists<T>();
  return return_code;
}

template<typename T>
int generic_type_tests() {
  int return_code = 0;
  return_code += minimal_generic_type_tests<T>();
  return_code += !test_destroy_value<T>();
  return_code += !test_insert_head_successfully<T>();
  return_code += !test_insert_tail_successfully<T>();
  return return_code;
}

template<typename T>
int generic_type_tests(const T& valueA, const T& valueB) {
  int return_code = 0;
  return_code += generic_type_tests<T>();
  return_code += !test_simple_pop_head<T>(valueA, valueB);
  return_code += !test_simple_pop_tail<T>(valueA, valueB);
  return return_code;
}

int main(void) {
  int return_code = 0;
  return_code += generic_type_tests<int>(37, 155);
  return_code += generic_type_tests<std::string>("hola", "chau");
  return_code += generic_type_tests<List<int>>();
  return_code += generic_type_tests<List<List<int>>>();
  return_code += generic_type_tests<List<List<std::string>>>();
  return_code += generic_type_tests<TipoDummyConDefault>();
  return_code += minimal_generic_type_tests<TipoDummy>();
  return_code += !test_multiple_peek();
  return_code += !test_multiple_pop();
  return_code += !test_peek_head();
  return_code += !test_peek_tail();
  return_code += !test_multiple_pop_random_patterns();
  return_code += !test_iter_delete_one_element_list();
  return_code += !test_iter_delete_head();
  return_code += !test_iter_delete_tail();
  return_code += !test_iter_delete_middle();
  return_code += !test_iter_simple_move();
  return_code += !test_iter_move_and_peek();
  return_code += !test_iter_move_at_start_and_end();
  return_code += !test_iter_full_list_read_only();
  return_code += !test_iter_move_on_random_list();
  return_code += !test_iter_insert_after_at_start();
  return_code += !test_iter_insert_after_at_middle();
  return_code += !test_iter_insert_after_at_tail();
  return_code += !test_iter_insert_before_at_end();
  return_code += !test_iter_insert_before_at_middle();
  return_code += !test_iter_insert_before_at_head();
  // Copy and assignment test
  List<int> a;
  a.insert_tail(1);
  a.insert_tail(2);
  a.insert_tail(3);
  List<int> b(a);
  List<int> c;
  c.insert_tail(33);
  c.insert_tail(38);
  c = a;
  bool ok = true;
  ok &= b.length() == 3;
  ok &= c.length() == 3;
  if (ok) {
      #define TEST(l) do { \
           List<int>::ListIter iter = l.create_head(); \
           ok &= iter.peek_current() == 1; \
           iter.forward(); \
           ok &= iter.peek_current() == 2; \
           iter.forward(); \
           ok &= iter.peek_current() == 3; \
          } while (false)
      TEST(b);
      TEST(c);
      // Self assignment test
      a = a;
      b = b;
      c = c;
      ok &= a.length() == 3;
      ok &= b.length() == 3;
      ok &= c.length() == 3;
      if (ok) {
          TEST(a);
          TEST(b);
          TEST(c);
      }
  }
  return_code += !test_assert("Todo igualdad", ok);
  if (return_code == 0) {
    printf("Todo ok!\n");
  } else {
    printf("Error code is %d\n", return_code);
  }
  return return_code;
}
