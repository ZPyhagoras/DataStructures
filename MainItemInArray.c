#include <stdio.h>

int MainItem(int nums[], int length) {
    int count, item;
    count = 0;
    item = -1;
    for (int i = 0; i < length; i++) {
        if (count == 0) {
            item = nums[i];
            ++count;
        }
        else {
            if (nums[i] == item) {
                ++count;
            }
            else {
                --count;
            }
        }
    }
    count = 0;
    for (int i = 0; i < length; i++) {
        if (nums[i] == item) {
            ++count;
        }
    }
    if (count > length / 2) {
        return item;
    }
    else {
        return -1;
    }
}

int main() {
    int nums[11] = {1, 2, 1, 1, 1, 1, 1, 8, 9, 7, 6};
    int numsMainItem = MainItem(nums, 11);
    printf("Nums\' main item: %d\n", numsMainItem);
    return 0;
}