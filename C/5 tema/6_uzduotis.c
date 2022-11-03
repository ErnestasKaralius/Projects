#include <stdio.h>

void print_sums(int array[], int length, int sum)
{
    int temp_sum = 0;
    for(int i = 0; i < length; ++i)
        temp_sum += array[i];

    if(temp_sum == sum)
    {
        for(int i = 0; i < length; ++i)
            printf("%d %c ", array[i], i == length - 1 ? '=' : '+');

        printf("%d\n", sum);
    }
}

void find_combinations(int numbers[], int temp_array[], int sum, int size, int position, int length)
{
    if(length != 1)
        print_sums(temp_array, length, sum);

    for(int j = position; j < size; ++j)
    {
        temp_array[length] = numbers[j];
        find_combinations(numbers, temp_array, sum, size, j + 1, length + 1);
    }
}

int main()
{

    int x, size;
    printf("Iveskite, kokia turetu buti sekos skaiciu suma: ");
    scanf("%d", &x);

    printf("Iveskite masyvo dydi: ");
    scanf("%d", &size);

    if(size < 1)
    {
        printf("Masyvo dydis turi buti teigiamas skaicius!");
        return 0;
    }

    int numbers[size];

    for(int i = 0; i < size; ++i)
        scanf("%d", &numbers[i]);

    int temp_array[size]; // To store combinations
    for(int i = 0; i < size - 1; ++i)
    {
        temp_array[0] = numbers[i];
        find_combinations(numbers, temp_array, x, size, i + 1, 1);
    }

    return 0;
}
