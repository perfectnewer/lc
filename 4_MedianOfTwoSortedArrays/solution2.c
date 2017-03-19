double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double median = 0.0;
    int total = nums1Size + nums2Size;
    int flag =  total & 1, stop = 0;
    int i=0, j = 0, x = 0;

    if(flag) {
        stop = total/2;
    } else {
        stop = total/2 - 1;
    }
    stop = stop > total ? total : stop;

    for(x=0; x < stop && i < nums1Size && j < nums2Size; ++x) {
        if(nums1[i] < nums2[j]) {
            ++i;
        } else {
            ++j;
        }
    }

    if(i < nums1Size && j < nums2Size) {
        if(flag) {
            return nums1[i] < nums2[j] ? nums1[i] : nums2[j];
        }

        if(nums1[i] < nums2[j]) {
            median += nums1[i];
            ++i;
        } else {
            median += nums2[j];
            ++j;
        }

        if(i >= nums1Size) {
            return (median + nums2[j]) / 2;
        }

        if(j >= nums2Size) {
            return (median + nums1[i]) / 2;
        }

        median += nums1[i] < nums2[j] ? nums1[i] : nums2[j];
        return median / 2;
    }

    int *p_t = NULL;
    int tmp = 0;
    if(i < nums1Size) {
        p_t = nums1;
        tmp = i;
    } else {
        p_t = nums2;
        tmp = j;
    }

    for(; x < stop; ++x) {
        ++tmp ;
    }

    if(flag) {
        return p_t[tmp];
    }

    median = p_t[tmp] + p_t[tmp+1];
    return median / 2;
}
