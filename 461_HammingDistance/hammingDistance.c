int hammingDistance(int x, int y) {
    int i = 0, dis = 0;
    for(i = 0; i < 31 ; ++i) {
        dis += (x >> i & 0x1) ^ (y >> i & 0x1);
    }
    return dis;
}
