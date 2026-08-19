# TP1 - Funciones y clase CustomVector en C++

En este trabajo práctico hay que implementar un conjunto de funciones básicas y
una clase `CustomVector` que representa un arreglo dinamico de enteros. El objetivo es
practicar la separación entre funciones libres y métodos de una clase, y el
manejo de memoria dinámica con `new` / `delete`.

Se tiene que completar el archivo `tp1.cpp`. Las declaraciones ya están dadas en
`tp1.h`: **no cambies las firmas**, solo hay que implementar el cuerpo. Todos los tests
de `tests.cpp` tienen que pasar, sin warnings de compilación y sin pérdidas de
memoria (leaks).

## Reglas generales

- Para reservar y liberar memoria dinámica usá `new` / `new[]` y
  `delete` / `delete[]`. **No** usar `malloc` ni `free`.
- La clase `CustomVector` es dueña de su memoria: la reserva cuando se crea el
  objeto y la libera cuando el objeto se destruye. No debe haber leaks.
- El código tiene que compilar sin warnings con los flags de la cátedra
  (`-Wall -Wconversion -Werror`, ver más abajo).

## Parte 1: Funciones libres

Estas funciones no operan sobre un arreglo, así que son funciones sueltas (no
métodos).

- `bool is_prime(int x)`
  Determina si un número es primo.

- `int storage_capacity(float d, float v)`
  Dado el volumen de un depósito `d` y el volumen de un producto `v`, calcula
  cuántos productos enteros entran en el depósito.

- `void swap(int *x, int *y)`
  Intercambia los valores de dos enteros.

## Parte 2: La clase CustomVector

`CustomVector` representa un arreglo dinamico de enteros y es responsable de su propia
memoria. Hay que implementar los siguientes metodos (ya declarados en
`tp1.h`):

### Constructores, asignación y destructor

- `CustomVector(int length)`
  Crear un vector de `length` enteros (reservados dinámicamente, sin un valor
  inicial definido).

- `CustomVector(const int *array, int length)`
  Crear un vector copiando `length` enteros desde `array`.

- `CustomVector(const CustomVector &other)`
  Constructor de copia: crea un vector nuevo con un **deep copy** del
  contenido de `other` (modificar la copia no debe afectar al original).

- `CustomVector &operator=(const CustomVector &other)`
  Asignación por copia: reemplaza el contenido actual por un deep copy
  de `other`, liberando la memoria que tenía antes.

- `~CustomVector()`
  Destructor: liberar la memoria del vector.

> Nota: al administrar memoria propia, estos tres metodos (destructor,
> constructor de copia y `operator=`) van siempre juntos. Si falta alguno,
> vas a tener copias superficiales o double frees.

### Acceso

- `int get_length() const`
  Devuelve la cantidad de elementos.

- `int &operator[](int i)` y `const int &operator[](int i) const`
  Permiten acceder al elemento en la posición `i` para leer y escribir.

### Operaciones sobre el arreglo

- `int max() const`
  Devuelve el máximo del vector.

- `void map(int (*f)(int))`
  Aplica la función `f` a cada elemento del vector. Si `f` es `NULL`, no hace
  nada.

- `void bubble_sort()`
  Ordena el vector ascendentemente usando el algoritmo bubble sort.

- `bool equal(const CustomVector &other) const`
  Determina si dos vectores son iguales (mismo largo y mismos
  elementos en el mismo orden).

- `bool is_anagram(const CustomVector &other) const`
  Determina si dos vectores son anagramas: en algún orden, contienen los
  mismos elementos.

### Capacity, push_back y remove

Hasta acá el tamaño del vector quedaba fijo al crearlo. Ahora `CustomVector`
tiene que poder crecer y achicarse, distinguiendo entre `length` (cantidad de
elementos usados) y `capacity` (cantidad de enteros para los que ya hay
memoria reservada, siempre `>= length`).

- `int get_capacity() const`
  Devuelve la capacity actual del vector.

- `void push_back(int value)`
  Agrega `value` al final del vector, creciendo la capacity si hace falta.

- `void remove()`
  Quita el último elemento del vector. Si el vector está vacío, no hace nada.

## Parte 3: reservar un solo objeto (new / delete escalar)

Hasta acá toda la memoria que se reservo fue para *arrays* (con `new[]`,
liberados con `delete[]`). Hay que reservar, en cambio, **un solo
objeto**: un `CustomVector` nuevo en el heap. Para eso se usa la versión
escalar de `new` / `delete` (sin corchetes). Regla: lo que se pide con `new`
se libera con `delete`; lo que se pide con `new[]` se libera con `delete[]`.

`a` y `b` son dos mazos de cartas representados como `CustomVector`. Se
juega una guerra de cartas: en cada ronda se enfrenta la carta en la
posición `i` de cada mazo y gana la más alta.

- `CustomVector *war_winner(const CustomVector &a, const CustomVector &b)`
  Reserva dinámicamente un `CustomVector` nuevo con el ganador de cada
  ronda. Si los mazos tienen largos distintos, se juegan tantas rondas como
  el mazo más corto y las cartas sobrantes no participan.

- `void destroy_vector(CustomVector *vector)`
  Libera el `CustomVector` reservado por `war_winner`.

Con `war_winner` ya se puede resolver una guerra entre dos mazos. Esta función
arma un torneo entre `num_decks` mazos: enfrenta a `decks[0]` contra
`decks[1]`, al ganador contra `decks[2]`, y así hasta `decks[num_decks -
1]`. El mazo que sobrevive al final es el campeón del torneo.

La función se queda con toda la memoria de `decks`: ni el array ni los
mazos que van perdiendo hacen falta después de jugar. Lo único que hay que
liberar aparte, con `destroy_vector`, es el campeón que devuelve.

- `CustomVector *tournament_champion(CustomVector **decks, int num_decks)`
  Juega el torneo completo y devuelve el campeón final.

## Cómo compilar y correr los tests

### Con make (igual que la corrección de la cátedra)

```sh
make local
```

Compila todos los `.cpp` y corre los tests bajo `valgrind` con
`--leak-check=full`. Falla si hay warnings, tests en rojo o pérdidas de
memoria.

### Con Docker (si no tenés g++ / valgrind instalados)

```sh
make docker
```

Levanta una imagen de Ubuntu con las herramientas necesarias y corre
`make local` adentro.

### A mano (para desarrollar más rápido, sin valgrind)

```sh
g++ -g -std=c++11 -Wall -Wconversion -Wno-sign-conversion -Werror -o tp1 *.cpp -lm
./tp1
```

Al correr `./tp1` se imprime cada test (`OK` / `FAILED`) y `Todo ok!` si pasan
todos. El código de salida es 0 cuando está todo bien. Si definís la variable
de entorno `TESTING_SILENT`, solo se muestran los tests que fallan.

## Archivos

- `tp1.h`: declaraciones. **No lo modifiques.**
- `tp1.cpp`: implementación. **Este es el archivo que tenés que completar.**
- `tests.cpp`: tests. Podés leerlos para entender qué se espera de cada función.
- `testing.h` / `testing.cpp`: infraestructura de tests. No hace falta tocarlos.
- `makefile`, `Dockerfile`: para compilar y correr.

## Entrega

Entregar **solamente** el archivo `tp1.cpp` completo. Verificar que
`make local` pase sin errores, sin warnings y sin leaks. Una entrega que no cumple con esas condiciones, no se considerara aprobada y se ira a reentrega.
