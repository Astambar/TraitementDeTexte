#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traitement_de_texte.h"

WordInfo getWordAtPosition(const char* text, int position, const char* separators)
{
    int start = -1;
    int end = -1;
    int separators_length = strlen(separators);

    int i = 0;
    while (text[i] != '\0') {
        bool is_separator = false;
        for (int j = 0; j < separators_length; j++) {
            if (text[i] == separators[j]) {
                is_separator = true;
                break;
            }
        }

        if (!is_separator) {
            if (start == -1) {
                start = i;
            }
            end = i;
        } else {
            if (start != -1 && end != -1) {
                if (position >= start && position <= end) {
                    int length = end - start + 1;
                    char* word = (char*)malloc((length + 1) * sizeof(char));
                    strncpy(word, text + start, length);
                    word[length] = '\0';

                    WordInfo info = {word, end};
                    return info;
                }
                start = -1;
                end = -1;
            }
        }
        i++;
    }

    if (start != -1 && end != -1 && position >= start && position <= end) {
        int length = end - start + 1;
        char* word = (char*)malloc((length + 1) * sizeof(char));
        strncpy(word, text + start, length);
        word[length] = '\0';
        WordInfo info = {word, end};
        return info;
    }

    WordInfo info = {NULL, -1};
    return info;
}

void printWordAndLink(const char* text)
{
    int i = 0;
    int countUrl = 0;
    int countWord = 0;
    int lengthText = countLengthText(text);
    const char* separators = " ;,?;.:/!\n\t\r";
    URLInfo info;
    WordInfo wordInfo;

    while (i <= lengthText) {
        info = is_url_at_position(text, i);
        if (info.url != NULL) {
            printf("URL numéro[%d] Trouver la voici : %s\n", countUrl, info.url);
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
            free(info.url);
        } else {
            wordInfo = getWordAtPosition(text, i, separators);
            if (wordInfo.word != NULL) {
                printf("Mot numéro[%d] Trouver la voici : %s\n", countWord, wordInfo.word);
                printf("Mot Trouver à la position: %d\n", i);
                printf("Fin du mot à la position: %d\n", wordInfo.end_position);
                countWord++;
                i = wordInfo.end_position;
                free(wordInfo.word);
            } else {
                printf("Ce n'est ni un mot ni une URL : %c\n", text[i]);
            }
        }
        i++;
    }
}
