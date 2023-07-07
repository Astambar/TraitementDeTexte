#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* url;
    int end_position;
} URLInfo;

URLInfo trouverURLSuivante(const char* texte, int position) {
    regex_t regexURL;
    int reti;
    char msgbuf[100];

    // Pattern de l'URL
    char* patternURL = "(https?|ftp)://[^[:space:]/$.?#].[^[:space:]]*";

    // Compilation de l'expression régulière pour l'URL
    reti = regcomp(&regexURL, patternURL, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erreur lors de la compilation de l'expression régulière pour les URL\n");
        URLInfo info = {NULL, position};
        return info;
    }

    // Vérification si la position donnée correspond au début d'une URL
    char* texte_partiel = (char*)malloc((strlen(texte) - position + 1) * sizeof(char));
    strncpy(texte_partiel, texte + position, strlen(texte) - position);
    texte_partiel[strlen(texte) - position] = '\0';

    regmatch_t match;
    reti = regexec(&regexURL, texte_partiel, 1, &match, 0);
    if (!reti && match.rm_so == 0) {
        // Une correspondance a été trouvée au début du texte partiel
        int start = match.rm_so;
        int end = match.rm_eo;
        int length = end - start;
        char* url = (char*)malloc((length + 1) * sizeof(char));
        strncpy(url, texte_partiel + start, length);
        url[length] = '\0';

        // Libération de la mémoire utilisée par l'expression régulière et le texte partiel
        regfree(&regexURL);
        free(texte_partiel);

        URLInfo info = {url, position + end};
        return info;
    }

    // Libération de la mémoire utilisée par l'expression régulière et le texte partiel
    regfree(&regexURL);
    free(texte_partiel);

    // Aucune correspondance trouvée ou la correspondance n'est pas au début, retour d'une structure URLInfo avec "URL n'existe pas"
    URLInfo info = {NULL, position};
    return info;
}

int main() {
    const char* texte = "Voici un exemple de texte contenant une URL : https://www.example.com. ";

    int position = 46;
    URLInfo info = trouverURLSuivante(texte, position);

    if (info.url != NULL) {
        printf("URL : %s\n", info.url);
        printf("Position de fin : %d\n", info.end_position);
    } else {
        printf("URL n'existe pas à cette position.\n");
    }

    return 0;
}
