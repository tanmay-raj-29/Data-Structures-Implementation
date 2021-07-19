int gcd(int a,int b) {
    while(b>0) {
        a %= b;
        swap(a, b);
    }
    return a;
}
//gcd(a,b)=gcd(a,a-b)
//gcd(a,b)=gcd(a,b%a)