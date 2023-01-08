#define bitcnt(a) (__builtin_popcountll(a))
#define bithigh(a) (63-__builtin_clzll(a))
#define lg bithigh

#define cd complex<double>
const double PI = acos(-1);

int rev(int x, int n){

    int r = 0;
    for (int i = 0; i < n; i++)
        r |= ((x>>i)&1) << (n-i-1);
    return r;
}

vector<cd> FFT(const vector<cd>& P, bool inv){

    int n = P.size();
    assert(bitcnt(n) == 1);
    vector<cd> y(n);
    for (int i = 0; i < n; i++){
        int j = rev(i, lg(n));
        y[j] = P[i];
    }
    for (int len = 2; len <= n; len <<= 1){
        double theta = 2 * PI / len * (inv ? -1 : 1);
        cd W(cos(theta), sin(theta));
        for (int i = 0; i < n; i += len){
            cd w(1);
            for (int j = 0; j < len/2; j++){
                cd u = y[i+j], v = w * y[i+j+len/2];
                y[i+j] = u+v;
                y[i+j+len/2] = u-v;
                w *= W;
            }
        }
    }
    if (inv) for (cd& z : y) z /= n;
    return y;
}
