#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include "traitement_de_texte.h"

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

char* extract_partial_text(const char* text, int position)
{
    int length = strlen(text) - position;
    char* partial_text = (char*)malloc((length + 1) * sizeof(char));
    strncpy(partial_text, text + position, length);
    partial_text[length] = '\0';
    return partial_text;
}

int is_url_start(const char* text, int position, regex_t* url_regex)
{
    char* partial_text = extract_partial_text(text, position);

    regmatch_t match;
    int reti = regexec(url_regex, partial_text, 1, &match, 0);
    if (!reti && match.rm_so == 0) {
        free(partial_text);
        return 1;
    }

    free(partial_text);
    return 0;
}

URLInfo get_url_info(const char* text, int position, regex_t* url_regex)
{
    char* partial_text = extract_partial_text(text, position);

    regmatch_t match;
    int reti = regexec(url_regex, partial_text, 1, &match, 0);
    if (!reti && match.rm_so == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        int length = end - start + 1;
        char* url = strndup(partial_text + start, length);

        free(partial_text);

        URLInfo info = {url, position + end};
        return info;
    }

    free(partial_text);

    URLInfo info = {NULL, position};
    return info;
}

URLInfo is_url_at_position(const char* text, int position)
{
    char* url_pattern = "(https?|ftp)://[^[:space:]/$.?#].[^[:space:]]*";

    regex_t url_regex = compile_regex(url_pattern);

    if (is_url_start(text, position, &url_regex)) {
        URLInfo info = get_url_info(text, position, &url_regex);
        regfree(&url_regex);
        return info;
    }

    regfree(&url_regex);
    URLInfo info = {NULL, position};
    return info;
}

int countUrl(const char* text)
{
    int i = 0;
    int countUrl = 0;
    int lengthText = countLengthText(text);
    URLInfo info;

    while (i <= lengthText) {
        info = is_url_at_position(text, i);
        if (info.url != NULL) {
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
            free(info.url);
        }
        i++;
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

    while (i <= lengthText) {
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
