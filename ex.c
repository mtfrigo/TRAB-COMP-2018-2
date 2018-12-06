char s = 's';
char ss[2];
char sss[2] = { 'c', 'g'};

int x = 2;
int xx[2];
int xxx[2] = {2, 3};

int g = 3;
char gg = 'c';

int main () {

    s = 'c';
    ss[1] = 'h';
    ss[2] = 'k';

    s = gg;
    ss[1] = gg;
    ss[2] = gg;

    x = 3;
    xx[1] = 5;
    xxx[5] = 7;

    x = g;
    xx[1] = g;
    xxx[5] = g;

}