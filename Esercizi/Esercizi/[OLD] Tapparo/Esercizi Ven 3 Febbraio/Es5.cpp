class C{
public:
    int x;
    C(int k = 5): x(k) {}
    C *m (C&c) {
        if ((c.x != 5) && (x == 5))
            return &c;
        else
            return this;
    }
};

int main()
{
    C a, b(2), c(a);
    cout << (b.m(b))->x << " " <<
            (a.m(a))->x << " " << c.m(a) <<
            " " << c.m(c);
}
