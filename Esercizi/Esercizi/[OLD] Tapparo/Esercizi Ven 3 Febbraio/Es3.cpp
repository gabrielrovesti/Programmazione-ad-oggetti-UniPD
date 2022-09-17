class C{
public:
    int *const p;
    c(int A=0) : p(new int(A)) {}
};

int main()
{
    C x(3);
    C y;
    x = y;  // ERRORE, non abbiamo ridefinito l'assegnazione, quindi viene invocata l'assegnazione standard.
            // Perciò eliminiamo questa riga.
    C z(y);
}
