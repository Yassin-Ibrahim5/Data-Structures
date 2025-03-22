#include <iostream>
#include <cmath>
using namespace std;

class Polynomial{
private:
    int degree;
    int* coefficients;
    int constant = 0;

public:
    Polynomial(int d);
    Polynomial(int deg, int c, const int* coeffs);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    void setCoefficients();
    void display() const;

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
};

Polynomial::Polynomial(int d) : degree(d){
    coefficients = new int[degree + 1]();
}

Polynomial::Polynomial(int deg, int c, const int* coeffs) : degree(deg), constant(c){
    coefficients = new int[degree + 1];
    for (int i = 0; i <= degree; ++i)
    {
        coefficients[i] = coeffs[i];
    }
}

Polynomial::Polynomial(const Polynomial& other) : degree(other.degree), constant(other.constant){
    coefficients = new int[degree + 1]();
    for (int i = 0; i <= other.degree; ++i)
    {
        coefficients[i] = other.coefficients[i];
    }
}

Polynomial::~Polynomial(){
    delete[] coefficients;
    coefficients = nullptr;
}

void Polynomial::setCoefficients(){
    cout << "Enter polynomial:";
    cin >> constant;
    for (int i = 0; i <= degree; ++i)
    {
        cin >> coefficients[i];
    }
}

void Polynomial::display() const{
    if (coefficients == nullptr)
    {
        return;
    }
    string expression;
    bool first = true;
    for (int i = this->degree; i >= 0; i--)
    {
        int c = coefficients[i];
        if (c == 0){
            continue;
        }
        string sign;
        if (first){
            sign = (c < 0) ? "-" : "";
            first = false;
        }
        else{
            sign = (c < 0) ? " - " : " + ";
        }
        c = abs(c);

        string term;
        if (i == 0){
            term = to_string(c);
        }
        else{
            term = (c == 1 ? "x" : to_string(c) + "x");
            if (i > 1){
                term += ("^" + to_string(i));
            }
        }

        expression += sign + term;
    }

    if (expression.empty()){
        expression = "0";
    }
    cout << expression << " = " << constant << endl;
}

Polynomial Polynomial::operator+(const Polynomial& other) const{
    int maxDegree = max(this->degree, other.degree);
    auto* resultCoeffs = new int[maxDegree + 1]();

    for (int i = 0; i <= this->degree; ++i)
    {
        resultCoeffs[i] += this->coefficients[i];
    }
    for (int i = 0; i <= other.degree; ++i)
    {
        resultCoeffs[i] += other.coefficients[i];
    }

    Polynomial result(maxDegree, this->constant + other.constant,resultCoeffs);
    delete[] resultCoeffs;
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const{
    int maxDegree = max(this->degree, other.degree);
    auto* resultCoeffs = new int[maxDegree + 1]();

    for (int i = 0; i <= other.degree; ++i)
    {
        resultCoeffs[i] += other.coefficients[i];
    }
    for (int i = 0; i <= this->degree; ++i)
    {
        resultCoeffs[i] -= this->coefficients[i];
    }

    Polynomial result(maxDegree, this->constant + other.constant,resultCoeffs);
    delete[] resultCoeffs;
    return result;
}

int getDegree(const string& prompt) noexcept(false){
    int degree;
    while(true){
        try
        {
            cout << prompt;
            cin >> degree;
            if (cin.fail() || degree < 0)
            {
                throw invalid_argument("Invalid input. Degree must be a non-negative integer.");
            }
            return degree;
        }catch (const invalid_argument& e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

//int main(){
//    int degree1 = getDegree("Order of first polynomial: ");
//
//    Polynomial p1(degree1);
//    p1.setCoefficients();
//
//    int degree2 = getDegree("Order of second polynomial: ");
//    Polynomial p2(degree2);
//    p2.setCoefficients();
//
//    cout << "First polynomial: ";
//    p1.display();
//
//    cout << "Second polynomial: ";
//    p2.display();
//
//    Polynomial sum = p1 + p2;
//    cout << "\nSum of polynomials: ";
//    sum.display();
//
//    Polynomial diff = p1 - p2;
//    cout << "\nDifference (P1 - P2): ";
//    diff.display();
//
//    return 0;
//}
