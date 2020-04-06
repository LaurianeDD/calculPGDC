#include <iostream>

//Prototypes
int obtenirPGCD(int* fraction);
void simplifierFraction(int* fraction);
int obtenirFractions(int** adresseFractions);
void lireFraction(int* fraction);
bool fractionValide(int* fraction);
void afficherFractions(int* fractions, int quantite);

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

void lireFraction(int* fraction) {
    /*
     * Obtient un numerateur et denominateur de l'utilisateur
     * et enregistre les valeurs aux index appropries du tableau de fractions
     */

    std::string numerateur;
    std::string denominateur;

    bool valide;
    do {
        std::cout << "Veuillez saisir une fraction(0/0): ";
        //Lis jusqu'au caractere '/'
        std::getline(std::cin, numerateur, '/');
        //Lis le reste des caracteres jusqu'au saut de ligne
        std::cin >> denominateur;

        //Conversion du numerateur en entier
        //Et assignation a l'index recu en parametre
        //Si erreur, assigne 0
        try {
            *(fraction) = std::stoi(numerateur);
        } catch (std::invalid_argument const& e) {
            std::cout << "Entree invalide: le numerateur doit etre un nombre entier" << std::endl;
            *(fraction) = 0;
        } catch (std::out_of_range const& e) {
            std::cout << "Entree invalide: le numerateur est trop grand" << std::endl;
            *(fraction) = 0;
        }

        //Conversion du denominateur en entier
        //Et assignation a l'index suivant celui recu en parametre (index impair)
        //Si erreur, assigne 0
        try {
            *(fraction + 1) = std::stoi(denominateur);
        } catch (std::invalid_argument const& e) {
            std::cout << "Entree invalide: le denominateur doit etre un nombre entier" << std::endl;
            *(fraction + 1) = 0;
        } catch (std::out_of_range const& e) {
            std::cout << "Entree invalide: le denominateur est trop grand" << std::endl;
            *(fraction + 1) = 0;
        }

        //Verifie que le numerateur et le denominateur sont plus grand que 0
        if (!fractionValide(fraction)) {
            valide = false;
            std::cout << "Fraction invalide: les operandes doivent etre des entiers positifs." << std::endl;
        } else {
            valide = true;
        }
    } while (!valide);
}

bool fractionValide(int* fraction) {
    /*
     * Verifie la validite de la fraction entree par l'utilisateur
     */
    //Recoit l'adresse d'un numerareur en parametre (index pair)
    int numerateur = *(fraction);
    int denominateur = *(fraction + 1);

    return (numerateur > 0) && (denominateur > 0);
}

void afficherFractions(int* fractions, int quantite) {
    /*
     *Affiche les fractions sous leur forme originale (entree par l'utilisateur)
     *et la version simplifiee de chacune
     */

    //Copie le tableau fractions
    int* fractionsSimplifiees = new int[quantite];
    for (int i = 0; i < (quantite * 2); i++) {
        fractionsSimplifiees[i] = fractions[i];
    }

    //Pour chaque fraction
    for (int fraction = 0; fraction < quantite; fraction++) {
        //Calcul sa valeur simplifiee
        simplifierFraction((fractionsSimplifiees + (fraction * 2)));
    }

    int numerateur;
    int denominateur;
    int numerateurSimplifie;
    int denominateurSimplifie;

    for (int fraction = 0; fraction < quantite; fraction++) {
        //Assignation des valeurs a des variables pour alleger la lecture
        //Assignation des operandes de la fraction originale
        numerateur = fractions[fraction * 2];
        denominateur = fractions[(fraction * 2) + 1];
        //Assignation des operandes de la fraction simplifiee
        numerateurSimplifie = fractionsSimplifiees[fraction * 2];
        denominateurSimplifie = fractionsSimplifiees[(fraction * 2) +1];

        //Affiche la fraction originale
        std::cout << numerateur << "/" << denominateur;
        std::cout << "  >>>   ";
        //Affiche la fraction simplifiee
        std::cout << numerateurSimplifie << "/" << denominateurSimplifie;
        std::cout << std::endl;
    }

    delete[] fractionsSimplifiees;
}