echo "gcc -g main.c fonction/*.c fonction/*.h -o TraitementDeTexte"
gcc -g main.c fonction/*.c fonction/*.h -o TraitementDeTexte
echo "valgrind --leak-check=full --show-leak-kinds=all ./TraitementDeTexte"
valgrind --leak-check=full --show-leak-kinds=all ./TraitementDeTexte
