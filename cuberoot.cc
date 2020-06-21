extern "C" double cuberoot(int x);

double cuberoot(int x) {
    double cube, precision = 0.000001;
    if(x < 0) {
        x = x * -1;
    }

    for(cube=1; x >= cube*cube*cube; cube++);

    for(--cube; (cube*cube*cube) < x; cube += precision);

    return cube;
}