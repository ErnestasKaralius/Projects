#include <stdio.h>

#define ARRAY_SIZE 1000

void swap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int get_median_of_three(int array[], int low, int mid, int high)
{
    int a = array[low], b = array[mid], c = array[high];

    if(b > a && a > c || c > a && a > b)
        return low;

    if(a > b && b > c || c > b && b > a)
        return mid;

    return high;
}

void recursive_quicksort(int array[], int low, int high)
{
    if(low < high)
    {
        int pivot = get_median_of_three(array, low, (low + high) / 2, high);
        int i = low, j = high;

        while(i < j)
        {
            while(array[i] <= array[pivot] && i <= high)
                ++i;

            while(array[j] > array[pivot] && j >= low)
                --j;

            if(i < j)
                swap(array, i, j);
        }

        swap(array, j, pivot);

        recursive_quicksort(array, low, j - 1);
        recursive_quicksort(array, j + 1, high);
    }
}

void quicksort(int array[], int length)
{
    int low[ARRAY_SIZE], high[ARRAY_SIZE];
    int i = 0;

    low[0] = 0;
    high[0] = length;

    while(i >= 0)
    {
        int left = low[i];
        int right = high[i] - 1;

        if(left < right)
        {
            int pivot = array[left];

            while(left < right)
            {
                while(array[right] >= pivot && left < right)
                    --right;

                if(left < right)
                {
                    array[left] = array[right];
                    ++left;
                }

                while(array[left] <= pivot && left < right)
                    ++left;

                if(left < right)
                {
                    array[right] = array[left];
                    --right;
                }
            }

            ++i;
            array[left] = pivot;
            low[i] = left + 1;

            high[i] = high[i - 1];
            high[i - 1] = left;

            if(high[i] - low[i] > high[i - 1] - low[i - 1])
            {
                swap(low, i, i - 1);
                swap(high, i, i - 1);
            }
        }
        else
            --i;
    }
}

int main()
{
    int array[ARRAY_SIZE];
    int length;

    scanf("%d", &length);
    for(int i = 0; i < length; ++i)
        scanf("%d", &array[i]);

    // recursive_quicksort(array, 0, length - 1);
    // quicksort(array, length);

    for(int i = 0; i < length; ++i)
        printf("%d ", array[i]);

    return 0;
}
