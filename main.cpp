#include <iostream>

//Prototypes
int obtenirPGCD(int* fraction);
void simplifierFraction(int* fraction);

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

int obtenirPGCD(int* fraction) {
    /*
     * Calcule le plus grand diviseur commun entre deux valeurs
     * representant une fraction
     */

    int PGCD = 1;

    //Recoit l'adresse d'un numerareur en parametre (index pair)
    int numerateur = *fraction;
    int denominateur = *(fraction + 1);
    //Trouver le plus petit entre le numerateur et denominateur
    int minimum = (numerateur <= denominateur) ? numerateur : denominateur;

    for (int diviseur = 2; diviseur <= minimum; diviseur++) {
        if ((numerateur % diviseur) == 0 && (denominateur % diviseur) == 0)
            PGCD = diviseur;
    }

    //Retourne le dernier diviseur commun trouve; i.e. le plus grand diviseur commun
    return PGCD;
}

void simplifierFraction(int* fraction) {
    /*
     * Calcul la fraction simplifiee par le plus grand diviseur commun
     */
    int PGCD = obtenirPGCD(fraction);

    //Recoit l'adresse d'un numerareur en parametre (index pair)
    //Calcul du numerateur simplifie
    *fraction = *fraction / PGCD;

    //Calcul du denominateur simplifie
    *(fraction + 1) = *(fraction + 1) / PGCD;
}