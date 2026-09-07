# TP2 - Lista doblemente enlazada e iterador en C++

En este trabajo práctico hay que implementar una **lista doblemente enlazada**
(clase `List`) y un **iterador externo** (clase `ListIter`) sobre ella. El
objetivo es practicar estructuras enlazadas y el manejo de memoria dinámica con
`new` / `delete` en C++, usando clases dueñas de su propia memoria (RAII), al
igual que en el TP1.

La clase `List` define un tipo paramétrico mediante un template de C++.
Por esta razón, se obtiene un tipo de datos distinto dependiendo del
tipo de datos que se desee utilizar para los valores que guarda la lista:
`List<int>`, `List<string>`, `List<List<string>>`, etc, todo con la misma
implementación genérica `List<T>`.

Se tiene que completar el archivo `tp2.h`. Las declaraciones ya están dadas en el mismo
`tp2.h`: **no cambies las firmas**, solo hay que implementar el cuerpo. Todos los
tests de `tests.cpp` tienen que pasar, sin warnings de compilación y sin pérdidas
de memoria (leaks).

Notar que por cómo funcionan los templates de C++, al ser List una clase
template es necesario colocar la implementación en el mismo `tp2.h` en
lugar de un `tp2.cpp` separado.

## Reglas generales

- Para reservar y liberar memoria dinámica usá `new` / `delete`. **No** usar
  `malloc` ni `free`.
- La clase `List` es dueña de sus nodos: los reserva (con `new`) al insertar y
  los libera (con `delete`) al sacarlos o al destruirse. Los **valores**
  (de tipo genérico `T`) los provee el usuario y se copian al crear los nodos de la lista,
  a través del único constructor de `List<T>::Node`.
- El código tiene que compilar sin warnings con los flags de la cátedra
  (`-Wall -Wconversion -Werror`, ver más abajo).

## Parte 1: La clase `List`

`List` representa una lista doblemente enlazada valores genéricos de tipo `T`. Internamente
tiene un nodo (`struct Node` privado) con `value`, `next` y `prev`, más `head`,
`tail` y `size`. Hay que implementar:

### Constructor y destructor

- `List()`
  Crea una lista vacía.

- `~List()`
  Destructor: libera todos los nodos que queden con `delete`.

### Constructor por copia y operador de asignación

- `List(const List<T> &other)`
Inicializa la lista a una copia de other

- `List &operator=(const List<T> &other)`
Actualiza la lista para que sea una copia de other

### Consultas

- `bool is_empty() const` — devuelve si la lista está vacía.
- `size_t length() const` — devuelve la cantidad de elementos.
- `const T &peek_head() const` / `const T &peek_tail() const` — devuelven el valor del
  principio / final sin sacarlo.

### Inserción y borrado

- `void insert_head(const T& value)` / `void insert_tail(const T& value)`
  Insertan un valor al principio / final.

- `T pop_head()` / `T pop_tail()`
  Sacan el primer / último nodo y devuelven su valor.

## Parte 2: La clase `ListIter` (iterador externo)

`ListIter` recorre una `List`. Es una clase definida dentro de `List` para poder moverse por sus
nodos. Se crea con las fábricas `create_head` / `create_tail`.

- `ListIter create_head()` / `ListIter create_tail()`
  Crean un iterador parado en el primer / último elemento.

- `bool forward()` / `bool backward()`
  Avanzan / retroceden una posición. Devuelven `false` si no se puede.

- `const T& peek_current() const` — valor en la posición actual.

- `bool at_first() const` / `bool at_last() const`
  Indican si el iterador está en el primer / último elemento.

- `bool insert_after(const T&value)` / `bool insert_before(const T&value)`
  Insertan un valor detrás / delante del actual sin mover el iterador.

- `T remove()`
  Saca el elemento actual, reposiciona el iterador en el siguiente (o en el
  anterior si no había siguiente) y devuelve una copia del valor.

## Cómo compilar y correr los tests

### Con make (igual que la corrección de la cátedra)

```sh
make local
```

Compila todos los `.cpp` y corre los tests bajo `valgrind` con
`--leak-check=full`. Falla si hay warnings, tests en rojo o pérdidas de memoria.

### Con Docker (si no tenés g++ / valgrind instalados)

```sh
make docker
```

Levanta una imagen de Ubuntu con las herramientas necesarias y corre `make local`
adentro.

### A mano (para desarrollar más rápido, sin valgrind)

```sh
g++ -g -std=c++11 -Wall -Wconversion -Wno-sign-conversion -Werror -o tp2 *.cpp
./tp2
```

Al correr `./tp2` se imprime cada test (`OK` / `FAILED`) y `Todo ok!` si pasan
todos. El código de salida es 0 cuando está todo bien. Si definís la variable de
entorno `TESTING_SILENT`, solo se muestran los tests que fallan.

## Archivos

- `tp2.h`: declaraciones e implementaciones de `List` y `ListIter`.
   **NO modificar las firmas.**, únicamente la **SECCION DE IMPLEMENTACION!!!**
- `testing.h` / `testing.cpp`: infraestructura de tests. No hace falta tocarlos.
- `makefile`, `Dockerfile`: para compilar y correr.

## Entrega

Entregar **solamente** el archivo `tp2.h` completo. Verificar que `make local`
pase sin errores, sin warnings y sin leaks. Una entrega que no cumple con esas
condiciones no se considera aprobada y se va a reentrega. Tampoco se puede
modificar en nada las firmas y declaraciones de las clases provistas, solamente
se debe completar la SECCION DE IMPLEMENTACION.
