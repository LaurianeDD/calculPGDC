#include <iostream>

//Prototypes
int obtenirPGCD(int* fraction);
void simplifierFraction(int* fraction);
int obtenirFractions(int** adresseFractions);

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

int obtenirFractions(int** adresseFractions) {
    /*
     * Initialisation d'un tableau de dimension specifies par l'utilisateur
     * et remplissage du tableau avec des valeurs entrees par l'utilisateur
     */
    int nbFractions;
    std::cout << "Veuillez entrer le nombre de fractions a analyser: ";
    std::cin >> nbFractions;

    if (nbFractions <= 0) return -1;

    //Recoit l'adresse d'un pointeur en parametre
    //Allocation d'un espace memoire sur le 'tas'
    //Assigne une adresse sur le 'tas' comme valeur du pointeur
    *adresseFractions = new int[nbFractions * 2];

    //Verifie qu'une adresse a bien ete assignee au pointeur
    if (*adresseFractions == NULL) return -1;

    //Utilisation d'un tableau unidimensionnel pour stockes les fractions
    //Les index pairs contiennent les numerateurs
    for (int fraction = 0; fraction < nbFractions; fraction++) {
        lireFraction( (*adresseFractions + (fraction * 2)) );
    }

    //Valeur utilise par le main() et les autres fonctions
    return nbFractions;
}