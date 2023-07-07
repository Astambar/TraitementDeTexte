#include "traitement_de_texte.h"


int main()
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

        // Libération de la mémoire allouée pour l'URL
        free(info.url);
    } else {
        printf("Aucune URL ne commence à cette position.\n");
    }
	printf("Url Count: %d\n", countUrl(text));
	printAllUrlInText(text);
	printf("Test Trouve le premier mots : %s\n", wordInfo.word);
	free(wordInfo.word);
	printf("===========================================================================\n");
	printWordAndLink(text);

    return 0;
}
