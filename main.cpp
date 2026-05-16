#include <iostream>
using namespace std;

// Function prototype
int gcd(int, int);

class Rational
{
    friend ostream& operator<<(ostream&, const Rational&);
    friend istream& operator>>(istream&, Rational&);
    friend Rational operator+(const Rational&, const Rational&);
    friend Rational operator-(const Rational&, const Rational&);
    friend Rational operator*(const Rational&, const Rational&);
    friend Rational operator/(const Rational&, const Rational&);
    friend bool operator==(const Rational&, const Rational&);

private:
    int num;
    int den;

    void reduce();

public:
    Rational(int n = 0, int d = 1)
    {
        num = n;
        den = d;
        reduce();
    }

    double toDecimal() const
    {
        return static_cast<double>(num) / den;
    }
};

// Output operator
ostream& operator<<(ostream& out, const Rational& r)
{
    out << r.num << "/" << r.den;
    return out;
}

// Input operator
istream& operator>>(istream& in, Rational& r)
{
    char slash;

    in >> r.num >> slash >> r.den;

    r.reduce();

    return in;
}

// Addition
Rational operator+(const Rational& r1, const Rational& r2)
{
    return Rational(
        (r1.num * r2.den) + (r2.num * r1.den),
        r1.den * r2.den
    );
}

// Subtraction
Rational operator-(const Rational& r1, const Rational& r2)
{
    return Rational(
        (r1.num * r2.den) - (r2.num * r1.den),
        r1.den * r2.den
    );
}

// Multiplication
Rational operator*(const Rational& r1, const Rational& r2)
{
    return Rational(
        r1.num * r2.num,
        r1.den * r2.den
    );
}

// Division
Rational operator/(const Rational& r1, const Rational& r2)
{
    return Rational(
        r1.num * r2.den,
        r1.den * r2.num
    );
}

// Equality check
bool operator==(const Rational& r1, const Rational& r2)
{
    return (r1.num * r2.den) == (r2.num * r1.den);
}

// Reduce fraction
void Rational::reduce()
{
    // Prevent denominator from being 0
    if (den == 0)
    {
        den = 1;
    }

    // Keep denominator positive
    if (den < 0)
    {
        num = -num;
        den = -den;
    }

    int g = gcd(abs(num), den);

    num /= g;
    den /= g;
}

// Greatest Common Divisor
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

int main()
{
    Rational x, y;

    cout << "Enter two rational numbers (example: 1/2 3/4): ";
    cin >> x >> y;

    cout << "\nFirst Rational Number: " << x;
    cout << " = " << x.toDecimal() << endl;

    cout << "Second Rational Number: " << y;
    cout << " = " << y.toDecimal() << endl;

    cout << "\nArithmetic Operations\n";

    cout << x << " + " << y << " = " << x + y << endl;
    cout << x << " - " << y << " = " << x - y << endl;
    cout << x << " * " << y << " = " << x * y << endl;
    cout << x << " / " << y << " = " << x / y << endl;

    cout << "\nComparison\n";

    if (x == y)
    {
        cout << "The rational numbers are equal." << endl;
    }
    else
    {
        cout << "The rational numbers are not equal." << endl;
    }

    return 0;
}