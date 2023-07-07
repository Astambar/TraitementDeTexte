#include "traitement_de_texte.h"

/**
 * compile_regex - Compile l'expression régulière
 * @pattern: Le pattern de l'expression régulière
 *
 * Retourne la structure regex_t compilée.
 */
regex_t compile_regex(const char* pattern)
{
    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erreur lors de la compilation de l'expression régulière\n");
        exit(1);
    }
    return regex;
}

/**
 * extract_partial_text - Extrait le texte partiel à partir d'une position donnée
 * @text: Le texte source
 * @position: La position de départ
 *
 * Retourne le texte partiel extrait à partir de la position donnée.
 */
char* extract_partial_text(const char* text, int position)
{
    int length = strlen(text) - position;
    char* partial_text = (char*)malloc((length + 1) * sizeof(char));
    strncpy(partial_text, text + position, length);
    partial_text[length] = '\0';
    return partial_text;
}
