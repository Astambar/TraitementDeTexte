echo "gcc -g *.c *.h -o TraitementDeTexte"
gcc -g *.c *.h -o TraitementDeTexte
echo "valgrind --leak-check=full --show-leak-kinds=all ./TraitementDeTexte"
valgrind --leak-check=full --show-leak-kinds=all ./TraitementDeTexte
