#include "testing.h"
#include "tp1.h"
#include <cstdio>

bool test_is_prime() {
  bool tests_result = true;
  tests_result &= test_assert("Prueba el número 2 es primo", is_prime(2));
  tests_result &= test_assert("Prueba el número 7 es primo", is_prime(7));
  tests_result &= test_assert("Prueba el número 6 no es primo", !is_prime(6));
  tests_result &=
      test_assert("Prueba el número 9409 no es primo", !is_prime(9409));
  return tests_result;
}

bool test_storage_capacity() {
  bool tests_result = true;
  tests_result &=
      test_assert("Prueba de capacidad 0", storage_capacity(1.0, 2.0) == 0);
  tests_result &= test_assert("Prueba de capacidad exactamente 1",
                              storage_capacity(1.0, 1.0) == 1);
  tests_result &= test_assert("Prueba de capacidad 2 con sobrante",
                              storage_capacity(2.0, 0.9f) == 2);
  tests_result &=
      test_assert("Prueba de capacidad 22", storage_capacity(20.0, 0.9f) == 22);
  return tests_result;
}

bool test_swap() {
  bool tests_result = true;
  int x = 4;
  int y = 5;

  swap(&x, &y);
  tests_result &=
      test_assert("Prueba swap enteros positivos", (x == 5 && y == 4));

  x = -1;
  y = 1;
  swap(&x, &y);
  tests_result &=
      test_assert("Prueba swap enteros con signo", (x == 1 && y == -1));

  x = 1;
  y = 1;
  swap(&x, &y);
  tests_result &=
      test_assert("Prueba swap enteros iguales", (x == 1 && y == 1));
  return tests_result;
}

bool test_array_max() {
  bool tests_result = true;
  CustomVector v(5);

  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }
  v[3] = 20;
  tests_result &= test_assert("Prueba máximo de arreglo", v.max() == 20);

  for (int i = 0; i < 5; i++) {
    v[i] = 10 - i;
  }
  tests_result &=
      test_assert("Prueba máximo de arreglo al principio", v.max() == 10);

  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }
  tests_result &= test_assert("Prueba máximo de arreglo al final", v.max() == 4);

  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }
  v[2] = 20;
  v[3] = 20;
  tests_result &=
      test_assert("Prueba máximo de arreglo dos veces", v.max() == 20);

  CustomVector single(1);
  single[0] = 10;
  tests_result &=
      test_assert("Prueba máximo de arreglo de un elemento", single.max() == 10);
  return tests_result;
}

int double_int(int a) { return a * 2; }

bool test_array_map() {
  bool tests_result = true;
  bool test_result = true;
  CustomVector v(5);

  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }
  v.map(double_int);
  for (int i = 0; i < 5; i++) {
    test_result &= v[i] == i * 2;
  }
  tests_result &=
      test_assert("Prueba map de arreglo duplicando entero", test_result);

  test_result = true;
  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }
  v.map(NULL);
  for (int i = 0; i < 5; i++) {
    test_result &= v[i] == i;
  }
  tests_result &= test_assert("Prueba map de arreglo sin función", test_result);
  return tests_result;
}

bool test_array_copy() {
  bool tests_result = true;
  bool test_result = true;
  CustomVector v(5);

  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }
  CustomVector copy(v); // constructor de copia

  for (int i = 0; i < 5; i++) {
    test_result &= copy[i] == v[i];
    copy[i] = copy[i] * 2;
    // el original no cambia -> la copia es profunda
    test_result &= copy[i] == v[i] * 2;
  }
  tests_result &= test_assert("Prueba copiar arreglo", test_result);
  return tests_result;
}

bool test_bubble_sort() {
  bool tests_result = true;
  bool test_result = true;
  CustomVector v(100);
  for (int i = 0; i < 100; i++) {
    v[i] = 99 - i;
  }

  v.bubble_sort();
  for (int i = 0; i < 100; i++) {
    test_result &= v[i] == i;
  }
  tests_result &= test_assert("Prueba bubble sort simple", test_result);

  test_result = true;
  for (int i = 0; i < 100; i++) {
    v[i] = -v[i];
  }
  v.bubble_sort();
  for (int i = 0; i < 100; i++) {
    test_result &= v[i] == -(99 - i);
  }
  tests_result &= test_assert("Prueba bubble sort negativos", test_result);

  return tests_result;
}

bool test_array_equal() {
  bool tests_result = true;
  CustomVector v1(5);
  CustomVector v2(5);
  for (int i = 0; i < 5; i++) {
    v1[i] = i;
    v2[i] = i;
  }

  CustomVector v1_short(2);
  CustomVector v2_short(3);
  tests_result &= test_assert("Prueba igualdad de arreglos largo distinto",
                              !v1_short.equal(v2_short));
  tests_result &=
      test_assert("Prueba igualdad de arreglos iguales", v1.equal(v2));
  v1[3] = 7;
  tests_result &=
      test_assert("Prueba igualdad de arreglos distintos por un elemento",
                  !v1.equal(v2));
  return tests_result;
}

bool test_integer_anagrams() {
  bool tests_result = true;
  CustomVector v1(10);
  CustomVector v2(10);
  for (int i = 0; i < 10; i++) {
    v1[i] = i;
    v2[i] = i;
  }

  CustomVector v1_short(2);
  CustomVector v2_short(3);
  tests_result &= test_assert("Prueba anagramas de arreglos largo distinto",
                              !v1_short.is_anagram(v2_short));
  tests_result &= test_assert("Prueba anagramas de arreglos iguales",
                              v1.is_anagram(v2));

  for (int i = 0; i < 10; i++) {
    v2[i] = 9 - i;
  }
  tests_result &= test_assert("Prueba anagramas de arreglos invertidos",
                              v1.is_anagram(v2));

  swap(&v1[2], &v1[7]);
  swap(&v2[0], &v2[5]);
  tests_result &=
      test_assert("Prueba anagramas con swap", v1.is_anagram(v2));

  v2[4] = 1;
  tests_result &=
      test_assert("Prueba anagramas cuando son distintos por un elemento",
                  !v1.is_anagram(v2));
  return tests_result;
}

bool test_push_back_and_remove() {
  bool tests_result = true;
  CustomVector v(0);

  tests_result &=
      test_assert("Prueba largo inicial 0", v.get_length() == 0);
  tests_result &=
      test_assert("Prueba capacity inicial >= length",
                  v.get_capacity() >= v.get_length());

  for (int i = 0; i < 5; i++) {
    v.push_back(i * i);
  }
  tests_result &= test_assert("Prueba largo tras push_back", v.get_length() == 5);
  tests_result &=
      test_assert("Prueba capacity crece con push_back",
                  v.get_capacity() >= v.get_length());

  bool values_ok = true;
  for (int i = 0; i < 5; i++) {
    values_ok &= v[i] == i * i;
  }
  tests_result &= test_assert("Prueba valores tras push_back", values_ok);

  v.remove();
  tests_result &= test_assert("Prueba largo tras remove", v.get_length() == 4);
  tests_result &=
      test_assert("Prueba último valor tras remove", v[3] == 9);

  while (v.get_length() > 0) {
    v.remove();
  }
  tests_result &=
      test_assert("Prueba vector vacío tras remover todo", v.get_length() == 0);

  v.remove(); // no debe hacer nada ni romper nada
  tests_result &=
      test_assert("Prueba remove sobre vector vacío", v.get_length() == 0);

  v.push_back(42);
  tests_result &=
      test_assert("Prueba push_back tras vaciar el vector",
                  v.get_length() == 1 && v[0] == 42);

  return tests_result;
}

bool test_war_winner() {
  bool tests_result = true;
  int arr_a[4] = {3, 8, 1, 9};
  int arr_b[4] = {5, 2, 1, 10};
  CustomVector a(arr_a, 4);
  CustomVector b(arr_b, 4);

  CustomVector *result = war_winner(a, b);
  tests_result &= test_assert("Prueba war_winner no es NULL", result != NULL);
  tests_result &=
      test_assert("Prueba largo de war_winner", result->get_length() == 4);

  bool values_ok = true;
  int expected[4] = {5, 8, 1, 10};
  for (int i = 0; i < 4; i++) {
    values_ok &= (*result)[i] == expected[i];
  }
  tests_result &= test_assert("Prueba ganador de cada ronda", values_ok);
  destroy_vector(result);

  int arr_c[2] = {1, 2};
  CustomVector c(arr_c, 2);
  CustomVector *result2 = war_winner(a, c);
  tests_result &= test_assert("Prueba war_winner con mazos de largo distinto",
                              result2->get_length() == 2);
  destroy_vector(result2);

  return tests_result;
}

bool test_tournament_champion() {
  bool tests_result = true;

  int arr0[2] = {3, 1};
  int arr1[2] = {5, 9};
  int arr2[2] = {2, 8};
  int arr3[2] = {4, 7};
  CustomVector **decks = new CustomVector *[4];
  decks[0] = new CustomVector(arr0, 2);
  decks[1] = new CustomVector(arr1, 2);
  decks[2] = new CustomVector(arr2, 2);
  decks[3] = new CustomVector(arr3, 2);

  CustomVector *champion = tournament_champion(decks, 4);
  tests_result &=
      test_assert("Prueba campeón no es NULL", champion != NULL);
  tests_result &= test_assert("Prueba largo del campeón",
                              champion->get_length() == 2);
  tests_result &= test_assert(
      "Prueba valores del campeón",
      (*champion)[0] == 5 && (*champion)[1] == 9);
  destroy_vector(champion);

  int arr4[3] = {6, 6, 6};
  CustomVector **single = new CustomVector *[1];
  single[0] = new CustomVector(arr4, 3);
  CustomVector *lone_champion = tournament_champion(single, 1);
  tests_result &= test_assert(
      "Prueba torneo con un solo mazo",
      (*lone_champion)[0] == 6 && (*lone_champion)[1] == 6 &&
          (*lone_champion)[2] == 6);
  destroy_vector(lone_champion);

  return tests_result;
}

int main(void) {
  int return_code = 0;
  return_code += !test_is_prime();
  return_code += !test_storage_capacity();
  return_code += !test_swap();
  return_code += !test_array_max();
  return_code += !test_array_map();
  return_code += !test_bubble_sort();
  return_code += !test_array_equal();
  return_code += !test_integer_anagrams();
  return_code += !test_array_copy();
  return_code += !test_push_back_and_remove();
  return_code += !test_war_winner();
  return_code += !test_tournament_champion();
  if (return_code == 0) {
    printf("Todo ok!\n");
  } else {
    printf("Error code is %d\n", return_code);
  }

  return return_code;
}
