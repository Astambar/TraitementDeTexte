#ifndef TRAITEMENT_DE_TEXTE_H
#define TRAITEMENT_DE_TEXTE_H

#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "url_utils.h"
#include "word_utils.h"

typedef struct {
    char* url;
    int end_position;
} URLInfo;

typedef struct {
    char* word;
    int end_position;
} WordInfo;

URLInfo is_url_at_position(const char* text, int position);
WordInfo getWordAtPosition(const char* text, int position, const char* separators);
int countLengthText(const char* text);
int countUrl(const char* text);
void printAllUrlInText(const char* text);
void printWordAndLink(const char* text);
/**
 * General Fonction
 * 
 */
 regex_t compile_regex(const char* pattern);
 char* extract_partial_text(const char* text, int position);

#endif /* TRAITEMENT_DE_TEXTE_H */
