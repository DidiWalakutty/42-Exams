#include "ft_list.h"

void sort_int_tab(int *tab, unsigned int size) {
    unsigned int i = 0;
    int temp;

    while (i < (size - 1)) {
        if (tab[i] > tab[i + 1]) {
            // Swap the elements
            temp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = temp;
            // Reset `i` to 0 to restart the comparison from the beginning
            i = 0;
        } else {
            // Move to the next index
            i++;
        }
    }
}
