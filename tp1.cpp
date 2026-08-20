#include "tp1.h"

/* ---------------------------------------------------------------
 * Parte 1: funciones libres (no operan sobre un arreglo).
 * --------------------------------------------------------------- */

bool is_prime(int x) {
    // TODO: determinar si x es primo.
    for (int i = x-1; i > 1; i-=1) {
        if (x % i == 0) {return false;}
    }
    return true;
}

int storage_capacity(float d, float v) {
    // TODO: calcular cuántos productos de volumen v entran en el depósito d.
    if (d>=0 && v > 0) {return (int)(d/v);}
    return 0;
}

void swap(int *x, int *y) {
    // TODO: intercambiar los valores de x e y.
    if (x != nullptr && y != nullptr) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
}

/* ---------------------------------------------------------------
 * Parte 2: CustomVector. Administra su propia memoria con
 * new/delete. Recordá la regla de los tres: destructor,
 * constructor de copia y operator=.
 * --------------------------------------------------------------- */

CustomVector::CustomVector(int length) {
    // TODO: reservar memoria para 'length' enteros y setear capacity.
    this->capacity = length;
    this->length = length;
    this->data = new int[length];
}

CustomVector::CustomVector(const int *array, int length) {
    // TODO: reservar memoria, copiar 'length' enteros desde 'array' y
    // setear capacity.
    this->length = length;
    this->capacity = length;
    this->data = new int[length];

    for (int i = 0; i < length; i++) {
        this->data[i] = array[i];
    }   
}

CustomVector::CustomVector(const CustomVector &other) {
    // TODO: copia profunda del contenido de 'other' (incluida capacity).
    this->length = other.length;
    this->capacity = other.capacity;
    for (int i = 0; i < length; i++) {
        this->data[i] = other.data[i];
    }   
}

CustomVector &CustomVector::operator=(const CustomVector &other) {
    // TODO: liberar lo anterior y hacer una copia profunda de 'other'
    // (incluida capacity).
    delete[] this->data;

    this->capacity = other.capacity;
    this->length = other.length;
    for (int i = 0; i < length; i++) {
        this->data[i] = other.data[i];
    }   
    return *this;
}

CustomVector::~CustomVector() {
    // TODO: liberar la memoria del vector.
    delete[] this->data;
}

int CustomVector::get_length() const {
    return this->length;
}

int &CustomVector::operator[](int i) {
    // TODO: devolver el elemento en la posición i.
    return this->data[i];
}

const int &CustomVector::operator[](int i) const {
    // TODO: devolver el elemento en la posición i.
    return this->data[i];
}

int CustomVector::max() const {
    // TODO: devolver el máximo del vector.
    int maximo = this->data[0];

    for (int i = 0; i < this->length; i++) {
        if (maximo < this->data[i]) {maximo = data[i];}
    }
    return maximo;
}

void CustomVector::map(int (*f)(int)) {
    // TODO: aplicar f a cada elemento. Si f es NULL, no hacer nada.
    if (f != nullptr) {
        for (int i = 0; i < length; i++) {
            data[i] = f(data[i]);
        }
    }
}

void CustomVector::bubble_sort() {
    // TODO: ordenar el vector ascendentemente con bubble sort.
    for (int i = 0; i < this->length; i++){
        for (int j = 0; j < this->length - (i + 1); j++){
            if (data[j] > data[j+1]){
                int temp = data[j];
                this->data[j] = data[j+1];
                this->data[j+1] = temp;
            }

        }
    }
}

bool CustomVector::equal(const CustomVector &other) const {
    // TODO: determinar si los dos vectores son idénticamente iguales.
    if (length == other.length) {
        for (int i = 0; i < length; i++){
            if (data[i] != other.data[i]) {return false;}
        }
        return true;
    };
    return false;
}

bool CustomVector::is_anagram(const CustomVector &other) const {
    // TODO: determinar si los dos vectores son anagramas.
    if (length == other.length) {
        for (int i = 0; i < length; i++) {
            bool esta = false;
            for (int j = 0; j < length; j++){
                if (data[i] == other.data[j]) {esta = true; break;}
            }
            if (!esta) {return false;}
        }
        return true;
    }
    return false;
}

int CustomVector::get_capacity() const {
    return this->capacity;
}

void CustomVector::push_back(int value) {
    // TODO: agregar 'value' al final del vector, creciendo la capacity
    // si hace falta.
    this->length+=1;
    this->capacity += 1;
    int* temp = new int[length];

    for (int i=0; i < length -1; i++) {
        temp[i] = data[i];
    }

    data[length] = value;

    delete[] data;
    data = temp;
}

void CustomVector::remove() {
    // TODO: quitar el último elemento del vector. Si está vacío, no
    // hacer nada.
}

/* ---------------------------------------------------------------
 * Parte 3: reserva de UN solo objeto (new / delete escalar).
 * --------------------------------------------------------------- */

CustomVector *war_winner(const CustomVector &a, const CustomVector &b) {
    // TODO: devolver un CustomVector nuevo con el ganador de cada
    // ronda (el máximo entre a[i] y b[i]).
    return nullptr;
}

void destroy_vector(CustomVector *vector) {
    // TODO: liberar vector con delete (versión escalar, sin []).
}

CustomVector *tournament_champion(CustomVector **decks, int num_decks) {
    // TODO: enfrentar decks[0] contra cada mazo siguiente con
    // war_winner, liberando el campeón anterior y el mazo que
    // perdió en cada pelea, y devolver el campeón final.
    return nullptr;
}
