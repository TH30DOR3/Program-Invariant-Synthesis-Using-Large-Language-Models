#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void display(int *arr, int n)
{
    assert(arr != NULL);
    assert(n >= 0);
    for (int i = 0; i < n; i++)
    {
        assert(i >= 0 && i < n);  // bounds check for arr[i]
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *first, int *second)
{
    assert(first != NULL && second != NULL);
    int temp = *first;
    *first = *second;
    *second = temp;
}

void cycleSort(int *arr, int n)
{
    assert(arr != NULL);
    assert(n >= 0);

    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
    {
        assert(cycle_start >= 0 && cycle_start < n); // valid index
        int item = arr[cycle_start];
        int pos = cycle_start;

        // Invariant before inner loop: item == arr[cycle_start]
        assert(pos == cycle_start);

        for (int i = cycle_start + 1; i < n; i++)
        {
            assert(i >= 0 && i < n);
            if (arr[i] < item)
                pos++;
        }

        // pos in range [cycle_start, n)
        assert(pos >= cycle_start && pos < n);

        if (pos == cycle_start)
            continue;

        // Skip duplicates
        while (item == arr[pos])
        {
            pos += 1;
            assert(pos < n);  // prevent out-of-bounds
        }

        if (pos != cycle_start)
        {
            assert(pos >= 0 && pos < n);
            swap(&item, &arr[pos]);
            writes++;
        }

        while (pos != cycle_start)
        {
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++)
            {
                assert(i >= 0 && i < n);
                if (arr[i] < item)
                    pos++;
            }

            assert(pos >= cycle_start && pos < n);

            while (item == arr[pos])
            {
                pos += 1;
                assert(pos < n); // avoid out-of-bounds
            }

            if (item != arr[pos])
            {
                assert(pos >= 0 && pos < n);
                swap(&item, &arr[pos]);
                writes++;
            }
        }
    }

    // Optional post-condition: number of writes must be less than n
    assert(writes >= 0 && writes < n);
}

int main()
{
    int arr[] = {20, 40, 50, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    assert(n > 0);

    printf("Original array: ");
    display(arr, n);

    cycleSort(arr, n);

    // After sorting: arr must be sorted in ascending order
    for (int i = 0; i < n - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }

    printf("Sorted array: ");
    display(arr, n);

    return 0;
}
