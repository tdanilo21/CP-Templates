#define bitcnt(a) (__builtin_popcountll(a))
#define bithigh(a) (63-__builtin_clzll(a))
#define lg bithigh
#define highpow(a) (1LL << (ll)lg(a))

namespace FFT{

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

    vector<ll> Multiply(const vector<ll>& A, const vector<ll>& B){

        int n = max(A.size(), B.size())*2;
        if (bitcnt(n) > 1) n = highpow(n)*2;
        vector<cd> a(n, 0), b(n, 0);
        for (int i = 0; i < n; i++){
            if (i < A.size()) a[i] = A[i];
            if (i < B.size()) b[i] = B[i];
        }
        a = FFT(a, 0);
        b = FFT(b, 0);
        for (int i = 0; i < n; i++)
            a[i] *= b[i];
        a = FFT(a, 1);
        vector<ll> C;
        for (int i = 0; i < n; i++)
            C.pb(llround(a[i].real()));
        while (C.size() && !C.back()) C.pop_back();
        return C;
    }
}
