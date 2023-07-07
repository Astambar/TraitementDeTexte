#include "traitement_de_texte.h"

/**
 * is_url_at_position - Vérifie si une URL débute à la position donnée
 * @text: Le texte source
 * @position: La position de départ
 *
 * Retourne une structure URLInfo contenant l'URL trouvée et la position de fin si une URL débute à la position donnée.
 * Sinon, retourne une structure URLInfo avec NULL et la position d'origine.
 */
URLInfo is_url_at_position(const char* text, int position)
{
    // Pattern de l'URL
    char* url_pattern = "(https?|ftp)://[^[:space:]/$.?#].[^[:space:]]*";

    regex_t url_regex = compile_regex(url_pattern);

    // Vérification si la position donnée correspond au début d'une URL
    char* partial_text = extract_partial_text(text, position);

    regmatch_t match;
    int reti = regexec(&url_regex, partial_text, 1, &match, 0);
    if (!reti && match.rm_so == 0) {
        // Une correspondance a été trouvée au début du texte partiel
        int start = match.rm_so;
        int end = match.rm_eo;
        int length = end - start + 1;
        char* url = strndup(partial_text + start, length);

        // Libération de la mémoire utilisée par l'expression régulière et le texte partiel
        regfree(&url_regex);
        free(partial_text);

        URLInfo info = {url, position + end};
        return info;
    }

    // Libération de la mémoire utilisée par l'expression régulière et le texte partiel
    regfree(&url_regex);
    free(partial_text);

    // Aucune correspondance trouvée ou la correspondance n'est pas au début, retour d'une structure URLInfo avec "URL n'existe pas"
    URLInfo info = {NULL, position};
    return info;
}

int countUrl(const char* text)
{
    int i = 0;
    int countUrl = 0;
    char current_character;
    URLInfo info;

    while ((current_character = text[i]) != '\0') {
        info = is_url_at_position(text, i);
        if (info.url != NULL) {
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
        } else {
            i++;
        }
		if (info.url != NULL) {
			free(info.url);
		}
    }
    return countUrl;
}

void printAllUrlInText(const char* text)
{
    int i = 0;
    int countUrl = 0;
	int lengthText = countLengthText(text);
    char current_character;
    URLInfo info;

    while ((i <= lengthText)) {
        info = is_url_at_position(text, i);
        if (info.url != NULL) {
            printf("URL numéro[%d] Trouver la voici : %s\n", countUrl, info.url);
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
			free(info.url);
        }
        i++;
    }
}
