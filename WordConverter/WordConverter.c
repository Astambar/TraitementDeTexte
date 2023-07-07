#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct MotNode {
    char mot[100];
    struct MotNode* suivant;
} MotNode;

MotNode* creerMotNode(const char* mot) {
    MotNode* node = (MotNode*)malloc(sizeof(MotNode));
    strcpy(node->mot, mot);
    node->suivant = NULL;
    return node;
}

void ajouterMot(MotNode** tete, const char* mot) {
    MotNode* node = creerMotNode(mot);
    if (*tete == NULL) {
        *tete = node;
    } else {
        MotNode* courant = *tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = node;
    }
}

bool motExiste(MotNode* tete, const char* mot) {
    MotNode* courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->mot, mot) == 0) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}

void libererListeMots(MotNode* tete) {
    MotNode* courant = tete;
    while (courant != NULL) {
        MotNode* suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

void ajouterMotsInexistants(const char* nom_fichierSource, const char* nom_fichierDestination) {
    FILE* fichierSource = fopen(nom_fichierSource, "r");

    if (fichierSource == NULL) {
        printf("Erreur lors de l'ouverture du fichier source.\n");
        return;
    }

    FILE* fichierDestination = fopen(nom_fichierDestination, "a");

    if (fichierDestination == NULL) {
        fichierDestination = fopen(nom_fichierDestination, "w");
        if (fichierDestination == NULL) {
            printf("Erreur lors de la création du fichier destination.\n");
            fclose(fichierSource);
            return;
        }
    }

    MotNode* motsExistant = NULL;

    char ligne[100];
    char* mot;
	const char* delimiteurs = " \t\r\n.,;:!?";

    while (fgets(ligne, sizeof(ligne), fichierSource) != NULL) {
        mot = strtok(ligne, delimiteurs); // Utilisation de strtok() pour découper la ligne en mots
        while (mot != NULL) {
            if (!motExiste(motsExistant, mot)) {
                fprintf(fichierDestination, "%s\n", mot);
                ajouterMot(&motsExistant, mot);
            }
            mot = strtok(NULL, delimiteurs); // Appel ultérieur à strtok() pour obtenir les mots suivants
        }
    }

    fclose(fichierSource);
    fclose(fichierDestination);

    libererListeMots(motsExistant);
}

void ecrireDansFichier(const char* nom_fichier, const char* texte) {
    FILE* fichier = fopen(nom_fichier, "a");

    if (fichier == NULL) {
        fichier = fopen(nom_fichier, "w");
        if (fichier == NULL) {
            printf("Erreur lors de la création du fichier.\n");
            return;
        }
    }

    fprintf(fichier, "%s\n", texte);

    fclose(fichier);
}

void releverMotsFichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[100];
    char* mot;

    printf("Mots trouvés dans le fichier :\n");

	// Chaîne de délimiteurs incluant les espaces, les tabulations, les retours chariot, les sauts de ligne et la ponctuation
    const char* delimiteurs = " \t\r\n.,;:!?";

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        mot = strtok(ligne, delimiteurs); // Utilisation de strtok() pour découper la ligne en mots
        while (mot != NULL) {
            printf("%s\n", mot);
            mot = strtok(NULL, delimiteurs); // Appel ultérieur à strtok() pour obtenir les mots suivants
        }
    }

    fclose(fichier);
}

int main() {

    releverMotsFichier("wordlist.txt");

    ajouterMotsInexistants("wordlist.txt", "listemots.txt");

    printf("Mots ajoutés à 'listemots.txt' :\n");
    releverMotsFichier("listemots.txt");

    return 0;
}
