#ifndef TP1_TP1_H
#define TP1_TP1_H

#include <utility>

/*
 * ============================================================
 *  Funciones que NO operan sobre un arreglo -> siguen siendo
 *  funciones libres.
 * ============================================================
 */

/*
 * Determina si un número es primo.
 * P (Pre):  x >= 2.
 * Q (Post): devuelve true <-> x es primo.
 *           No modifica ningún estado (función pura).
 */
bool is_prime(int x);

/*
 * Dado el volumen de un depósito D y el volumen de un producto V
 * la función calcula cuántos productos entran en el depósito.
 * P (Pre):  d >= 0 && v > 0 (son volúmenes: d puede ser 0, v debe ser positivo).
 * Q (Post): devuelve floor(d / v), es decir la parte entera de d/v.
 *           No modifica ningún estado (función pura).
 */
int storage_capacity(float d, float v);

/*
 * Intercambia dos valores de enteros.
 * Opera sobre dos enteros sueltos, no sobre un arreglo, por eso
 * se mantiene como función libre.
 * P (Pre):  x != nullptr && y != nullptr (apuntan a enteros válidos).
 *           Sean x0 = *x, y0 = *y sus valores iniciales.
 * Q (Post): *x == y0 && *y == x0 (los valores quedan intercambiados).
 */
void swap(int *x, int *y);

/*
 * ============================================================
 *  Arreglo de enteros -> clase CustomVector.
 *
 *  La clase es dueña de su memoria (RAII): la reserva en el
 *  constructor con new[] y la libera en el destructor con
 *  delete[]. Por eso no hace falta ninguna función para liberar
 *  a mano.
 * ============================================================
 */
class CustomVector {
private:
    int *data;
    int length;
    int capacity;

public:
    /*
     * Crea un vector de 'length' enteros sin inicializar.
     * P (Pre):  length >= 0.
     * Q (Post): get_length() == length && get_capacity() == length &&
     *           hay memoria reservada para 'length' enteros
     *           (cuyo contenido queda indefinido).
     */
    explicit CustomVector(int length);

    /*
     * Crea un vector copiando 'length' enteros desde 'array'.
     * P (Pre):  length >= 0 && array apunta a un arreglo con al menos
     *           'length' enteros válidos.
     * Q (Post): get_length() == length && get_capacity() == length &&
     *           para todo i en [0, length): (*this)[i] == array[i]
     *           (copia propia e independiente de 'array').
     */
    CustomVector(const int *array, int length);

    /*
     * Constructor de copia: hace una copia profunda.
     * (Reemplaza a la vieja función copy_array.)
     * P (Pre):  'other' es un CustomVector válido.
     * Q (Post): get_length() == other.get_length() &&
     *           para todo i: (*this)[i] == other[i], con memoria propia
     *           (modificar uno no afecta al otro).
     */
    CustomVector(const CustomVector &other);

    /*
     * Asignación por copia: copia profunda liberando lo anterior.
     * (Necesario junto al constructor de copia y al destructor:
     *  "regla de los tres".)
     * P (Pre):  '*this' y 'other' son CustomVector válidos.
     * Q (Post): la memoria previa de '*this' fue liberada;
     *           get_length() == other.get_length() &&
     *           para todo i: (*this)[i] == other[i], con memoria propia;
     *           devuelve *this. Si this == &other, no hay cambios.
     */
    CustomVector &operator=(const CustomVector &other);

    /*
     * Destructor: libera la memoria con delete[].
     * P (Pre):  '*this' es un CustomVector válido, no destruido antes.
     * Q (Post): la memoria de 'data' quedó liberada; usar el objeto
     *           luego es comportamiento indefinido.
     */
    ~CustomVector();

    /*
     * Cantidad de elementos del vector.
     * P (Pre):  '*this' es un CustomVector válido.
     * Q (Post): devuelve la cantidad de elementos (>= 0);
     *           no modifica el vector (const).
     */
    int get_length() const;

    /*
     * Acceso a un elemento por índice (lectura/escritura y solo lectura).
     * P (Pre):  0 <= i < get_length().
     * Q (Post): devuelve una referencia al elemento i-ésimo. La versión
     *           no-const permite leer y escribir; la const, solo leer.
     *           No cambia la longitud ni la capacidad.
     */
    int &operator[](int i);
    const int &operator[](int i) const;

    /*
     * Devuelve el máximo del vector. (ex array_max)
     * P (Pre):  get_length() >= 1 (el vector no está vacío).
     * Q (Post): devuelve max{ (*this)[i] : 0 <= i < get_length() };
     *           no modifica el vector (const).
     */
    int max() const;

    /*
     * Aplica la función a cada elemento del vector.
     * Si f es NULL no hace nada. (ex array_map)
     * P (Pre):  '*this' es válido; f es nullptr o un puntero a función
     *           aplicable a un int.
     * Q (Post): si f == nullptr, el vector queda igual;
     *           si f != nullptr, para todo i: (*this)[i] == f(i).
     *           La longitud y la capacidad no cambian.
     */
    void map(int (*f)(int));

    /*
     * Ordena el vector ascendentemente con bubble sort. (ex bubble_sort)
     * P (Pre):  '*this' es un CustomVector válido.
     * Q (Post): el vector queda ordenado de menor a mayor
     *           (para todo i < j: (*this)[i] <= (*this)[j]) y es una
     *           permutación de los elementos originales; misma longitud.
     */
    void bubble_sort();

    /*
     * Determina si dos vectores son idénticamente iguales. (ex array_equal)
     * P (Pre):  '*this' y 'other' son CustomVector válidos.
     * Q (Post): devuelve true <-> tienen la misma longitud y, para todo i,
     *           (*this)[i] == other[i]. No modifica ninguno (const).
     */
    bool equal(const CustomVector &other) const;

    /*
     * Determina si dos vectores son anagramas: en algún orden,
     * son el mismo arreglo. (ex integer_anagrams)
     * P (Pre):  '*this' y 'other' son CustomVector válidos.
     * Q (Post): devuelve true <-> tienen la misma longitud y uno es
     *           permutación del otro (mismos elementos con igual
     *           multiplicidad). No modifica ninguno de los dos (const).
     */
    bool is_anagram(const CustomVector &other) const;

    /*
     * Cantidad de enteros para los que hay memoria reservada
     * actualmente (siempre >= get_length()).
     * P (Pre):  '*this' es un CustomVector válido.
     * Q (Post): devuelve la capacidad reservada, con
     *           get_capacity() >= get_length(); no modifica el vector.
     */
    int get_capacity() const;

    /*
     * Agrega 'value' al final del vector, creciendo la capacity
     * si hace falta.
     * P (Pre):  '*this' es un CustomVector válido.
     *           Sea n0 = get_length() antes de la llamada.
     * Q (Post): get_length() == n0 + 1 && (*this)[n0] == value;
     *           los elementos [0, n0) no cambian; get_capacity() >=
     *           get_length().
     */
    void push_back(int value);

    /*
     * Quita el último elemento del vector.
     * Si el vector está vacío, no hace nada.
     * P (Pre):  '*this' es un CustomVector válido.
     *           Sea n0 = get_length() antes de la llamada.
     * Q (Post): si n0 == 0, el vector queda igual;
     *           si n0 > 0, get_length() == n0 - 1 y los elementos
     *           [0, n0-1) no cambian. La capacidad no se reduce.
     */
    void remove();
};

/*
 * Juego de guerra de cartas: 'a' y 'b' son dos mazos. Por cada
 * ronda (posición) gana la carta más alta. Devuelve un
 * CustomVector nuevo con el ganador de cada ronda; las cartas
 * sobrantes del mazo más largo no juegan. Se libera con
 * destroy_vector.
 * P (Pre):  'a' y 'b' son CustomVector válidos.
 * Q (Post): devuelve un CustomVector nuevo de longitud
 *           rounds == min(a.get_length(), b.get_length()),
 *           donde para todo i: (*res)[i] == max(a[i], b[i]).
 *           'a' y 'b' no se modifican. El llamador es dueño del
 *           resultado y debe liberarlo con destroy_vector.
 */
CustomVector *war_winner(const CustomVector &a, const CustomVector &b);

/*
 * Libera un CustomVector reservado con war_winner.
 * P (Pre):  vector es nullptr o un puntero devuelto por war_winner /
 *           tournament_champion aún no liberado.
 * Q (Post): la memoria de 'vector' quedó liberada (si era nullptr no
 *           hace nada); 'vector' pasa a ser un puntero colgante.
 */
void destroy_vector(CustomVector *vector);

/*
 * Torneo de eliminación: 'decks' tiene 'num_decks' mazos. Arranca
 * con decks[0] como campeón y lo va enfrentando, uno por uno,
 * contra cada mazo siguiente con war_winner. En cada pelea se
 * liberan el campeón anterior y el mazo que perdió, y el ganador
 * de war_winner pasa a ser el nuevo campeón.
 * La función toma posesión de 'decks' (el array y los mazos se
 * liberan durante el torneo) y devuelve el campeón final, que hay
 * que liberar aparte con destroy_vector.
 * P (Pre):  num_decks >= 1 && decks != nullptr && cada decks[i]
 *           (0 <= i < num_decks) es un CustomVector* válido, reservado
 *           con new, y 'decks' fue reservado con new[].
 * Q (Post): devuelve el CustomVector* campeón final (resultado de
 *           encadenar war_winner). Todos los mazos intermedios y el
 *           arreglo 'decks' quedan liberados (la función toma posesión).
 *           El llamador debe liberar el resultado con destroy_vector.
 */
CustomVector *tournament_champion(CustomVector **decks, int num_decks);

#endif // TP1_TP1_H
