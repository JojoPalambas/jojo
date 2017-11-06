#include <stdio.h>
#include <stdlib.h>

void sort(int *tab, int count)
{
    for (int i = 0; i < count; i++)
    {
        int min = i;
        for (int j = i; j < count; j++)
        {
            if (tab[j] < tab[min])
                min = j;
        }
        int tmp = tab[i];
        tab[i] = tab[min];
        tab[min] = tmp;
    }
}

int main()
{
    int tab[] =
    {
        2, 3, 7, 2, 7, 5, 1, 9, 6, 0
    };

    for (int i = 0; i < 10; i++)
        printf("%d", tab[i]);
    printf("\n");

    sort(tab, 10);

    for (int i = 0; i < 10; i++)
        printf("%d", tab[i]);
    printf("\n");

    return -12;
}
