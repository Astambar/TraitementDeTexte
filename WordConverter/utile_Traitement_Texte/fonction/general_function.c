#include <stdio.h>
#include "traitement_de_texte.h"

int countLengthText(const char* text)
{
    int length = 0;
    for (; text[length] != '\0'; length++)
        ;
    return length;
}

int isSeparator(char character, const char* separators)
{
    int i = 0;
    while (separators[i] != '\0') {
        if (character == separators[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

void runExamples()
{
    const char* text = "Voici un exemple de texte contenant une URL : https://www.example.com. toto https://chat.openai.com/c/6269c834-6230-4273-93ed-86994296e3ca";

    int position = 46;
    const char* separators = " ;,?;.:/!\n\t\r";
    URLInfo info = is_url_at_position(text, position);
    WordInfo wordInfo = getWordAtPosition(text, 0, separators);
    if (info.url != NULL) {
        printf("URL : %s\n", info.url);
        printf("Position de fin : %d\n", info.end_position);
        printf("Caractère au début de l'URL : %c\n", text[position]);
        printf("Caractère à la fin -1 : %c\n", text[info.end_position - 1]);
        printf("Caractère à la fin neutre : %c\n", text[info.end_position]);
        printf("Caractère à la fin +1 : %c\n", text[info.end_position + 1]);

        free(info.url);
    } else {
        printf("Aucune URL ne commence à cette position.\n");
    }

    printf("Url Count: %d\n", countUrl(text));
    printAllUrlInText(text);
    printf("Test Trouve le premier mot : %s\n", wordInfo.word);
    free(wordInfo.word);
    printf("===========================================================================\n");
    printWordAndLink(text);

    int length = countLengthText(text);
    printf("Longueur du texte : %d\n", length);
}
