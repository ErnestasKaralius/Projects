#include <stdio.h>
#include <stdlib.h>

void get_sums(int num[], int size, int* sum1, int* sum2)
{
    for(int i = 0; i < size / 2; ++i)
    {
        *sum1 += num[i];
        *sum2 += num[size - i - 1];
    }
}

int main()
{
    int size;
    int sum1 , sum2;

    printf("Iveskite masyvo dydi: ");
    scanf("%d", &size);
    if(size < 2)
    {
        printf("Masyvo dydis turi buti didesnis uz 1!");
        return 0;
    }

    int nums[size], closest_array[size];
    int closest_difference;

    printf("Iveskite %d masyvo elementus: ", size);

    for(int i = 0; i < size; ++i)
        scanf("%d", &nums[i]);

    for(int i = 1; i <= size; ++i)
        for(int j = 0; j < size - 1; ++j)
        {
            sum1 = 0, sum2 = 0;

            int temp = nums[j];
            nums[j] = nums[j + 1];
            nums[j + 1] = temp;

            get_sums(nums, size, &sum1, &sum2);
            int difference = abs(sum2 - sum1);

            if(i == 1 && j == 0)
            {
                closest_difference = difference;
                for(int k = 0; k < size; ++k)
                    closest_array[k] = nums[k];
            }

            else if(difference < closest_difference)
            {
                closest_difference = difference;
                for(int k = 0; k < size; ++k)
                    closest_array[k] = nums[k];
            }
        }

    // Print the array
    for(int i = 0; i < size; ++i)
        printf("%d ", closest_array[i]);

    return 0;
}
