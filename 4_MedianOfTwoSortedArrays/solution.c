double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double median = 0.0;
    int total = nums1Size + nums2Size;
    int i = 0, j = 0, x = 0, stop = 0;
    int flag =  total & 1;

    stop = total/2;
    int *merge_arr = (int *)malloc((stop+1)*sizeof(int));

    for(x=0; x < stop + 1 && i < nums1Size && j < nums2Size; ++x) {
        if(nums1[i] < nums2[j]) {
            merge_arr[x] = nums1[i++];
        } else {
            merge_arr[x] = nums2[j++];
        }
    }

    if(x < stop+1) {
        int *p_tmp = NULL;
        int tmp = 0;
        if(i < nums1Size) {
            tmp = i;
            p_tmp = nums1;
        } else {
            tmp = j;
            p_tmp = nums2;
        }

        for(; x < stop + 1; ++x) {
            merge_arr[x] = p_tmp[tmp];
            ++tmp;
        }

    }

    if(flag) {
        return merge_arr[stop];
    }

    return (merge_arr[stop] + merge_arr[stop-1]) / 2.0;
}
