#include "matrice.h"
#include <cstdlib>

// retourne true si mat est bien gardee, et false sinon
bool est_gardee(Matrice<bool> &mat) {

  //**** à remplir ****
}

// quelques fonctions utilitaires pour la création de matrices (vous n'avez pas
// de travail demandé dans ces fonctions) construit et retourne une matrice
// booléenne aléatoire
Matrice<bool> get_bool_matrice_random(size_t rows, size_t cols) {
  Matrice<bool> mat(rows, cols);
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c) {
      mat(r, c) = rand() % 2; // façon discutable d'allouer un bool aléatoire
    }
  }

  return mat;
}

// construit et retourne une matrice booléenne vide
Matrice<bool> get_bool_matrice_vide(size_t rows, size_t cols) {
  Matrice<bool> mat(rows, cols);
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c) {
      mat(r, c) = false; // façon discutable d'allouer un bool aléatoire
    }
  }

  return mat;
}

// affecte la valeur val à chaque cellule de la rangée r
template <typename TYPE>
void remplir_rangee(Matrice<TYPE> &mat, size_t r, TYPE val) {
  size_t nbcol = mat.get_dimensions().second;
  for (size_t c = 0; c < nbcol; ++c) {
    mat(r, c) = val; // notez que ceci fait une copie
  }
}

// affecte la valeur val à chaque colonne de la rangée r
template <typename TYPE>
void remplir_colonne(Matrice<TYPE> &mat, size_t c, TYPE &val) {
  size_t nbrangee = mat.get_dimensions().first;
  for (size_t r = 0; r < nbrangee; ++r) {
    mat(r, c) = val; // notez que ceci fait une copie
  }
}

int main() {

  // ce main presente quelques cas d'utilisation, mais ne teste pas tout!

  size_t rows = 3;
  size_t cols = 4;
  Matrice<int> mat(rows, cols, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

  cout << "Matrice initiale" << endl;
  mat.afficher();

  cout << "mat(1, 1) = 13" << endl;
  mat(1, 1) = 13;
  mat.afficher();

  cout << "Swap rangees 1-2" << endl;
  mat.swap_rangees(1, 2);
  mat.afficher();

  cout << "Swap colonnes 1-2" << endl;
  mat.swap_colonnes(1, 2);
  mat.afficher();

  // todo: tests de redimension

  // ceci est pour voir si des matrices à portée limitée survit au destructeur
  {
    Matrice<int> mat_locale(5000, 10000);
    mat_locale(500, 1000) = 2;
    cout << "mat_locale(500, 1000) = " << mat_locale(500, 1000) << endl;

    cout << endl;
    cout << "Copie de mat_locale par constructeur" << endl;
    Matrice<int> mat_copy(mat_locale);

    cout << "Copie de mat_locale par affectation" << endl;
    Matrice<int> mat_assign(1, 1);
    mat_assign = mat_locale;

    cout << "mat_copy(500, 1000) = " << mat_copy(500, 1000) << endl;
    cout << "mat_assign(500, 1000) = " << mat_assign(500, 1000) << endl;

    cout << endl;
    cout << "Modif de mat_copy et mat_assign" << endl;
    mat_copy(100, 200) = 3;
    mat_assign(100, 200) = 4;
    cout << "mat_locale(100, 200) = " << mat_locale(100, 200)
         << "     (non-initialisee)" << endl;
    cout << "mat_copy(100, 200) = " << mat_copy(100, 200) << endl;
    cout << "mat_assign(100, 200) = " << mat_assign(100, 200) << endl;
  }
  cout << "La destruction de mat_locale et de ses copies n'a pas fait de crash "
          ":)"
       << endl;

  cout << endl;
  cout << "Tests de garde" << endl;
  size_t dim = 100;

  Matrice<bool> mat_rand = get_bool_matrice_random(dim, dim);
  bool gardee = est_gardee(mat_rand);
  cout << "mat_rand gardee=" << gardee << endl;

  Matrice<bool> mat_vide = get_bool_matrice_vide(dim, dim);
  gardee = est_gardee(mat_vide);
  cout << "mat_vide gardee=" << gardee << endl;

  bool var_true =
      true; // je dois faire ça car remplir_rangee demande la valeur par
            // référence, et faire remplir_rangee(mat_r1, 0, true); n'est pas
            // valide (passer "true" en référence = impossible)
  Matrice<bool> mat_r1 = get_bool_matrice_vide(dim, dim);
  remplir_rangee(mat_r1, 0, var_true);
  gardee = est_gardee(mat_r1);
  cout << "mat_r1 gardee=" << gardee << endl;

  Matrice<bool> mat_rn = get_bool_matrice_vide(dim, dim);
  remplir_rangee(mat_rn, dim - 1, var_true);
  gardee = est_gardee(mat_rn);
  cout << "mat_rn gardee=" << gardee << endl;

  Matrice<bool> mat_c1 = get_bool_matrice_vide(dim, dim);
  remplir_colonne(mat_c1, 0, var_true);
  gardee = est_gardee(mat_c1);
  cout << "mat_c1 gardee=" << gardee << endl;

  Matrice<bool> mat_cn = get_bool_matrice_vide(dim, dim);
  remplir_colonne(mat_cn, dim - 1, var_true);
  gardee = est_gardee(mat_cn);
  cout << "mat_cn gardee=" << gardee << endl;

  Matrice<bool> mat_diag = get_bool_matrice_vide(dim, dim);
  for (size_t i = 0; i < dim; ++i) {
    mat_diag(i, i) = true;
  }
  gardee = est_gardee(mat_diag);
  cout << "mat_diag gardee=" << gardee << endl;

  mat_diag(dim / 2, dim / 2) = false;
  gardee = est_gardee(mat_diag);
  cout << "mat_diag modifiee gardee=" << gardee << endl;

  return 0;
}
