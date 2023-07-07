echo "gcc -g testURL.c -o testURL"
gcc -g testURL.c -o testURL
echo "valgrind --leak-check=full --show-leak-kinds=all ./testURL"
valgrind --leak-check=full --show-leak-kinds=all ./testURL
