class C{
private:
    int d;
public:
    C(string s = ""): d(s.size()) {}
    explicit C(int m): d(m) {}
    operator int() {return d;}
    C operator+(C x) { return C(d+x.d);}
};

int main()
{
    C a, b("pippo"), c(3);
    cout << a << " " << 1+b << " " << c+4 << " " << c+b;
}
