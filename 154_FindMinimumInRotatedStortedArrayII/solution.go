package main

import (
    "fmt"
)

func findMin(nums []int) int {
    length := len(nums)

    if nums[length - 1] > nums[0] {
        return nums[0]
    }

    st := 0
    for st < length - 1 {
        if nums[st] > nums[st + 1] {
            return nums[st + 1]
        }
        st += 1
    }
    return nums[st]
}

func main() {
    fmt.Println(findMin([]int{3, 1, 3, 3}))
}
