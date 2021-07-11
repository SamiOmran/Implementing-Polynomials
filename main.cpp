#include "string"
#include <iostream>

using namespace std;

class Term {
private:
    int coefficient;
    int exponent;
    Term *next;

public:

    Term(int coefficient, int exponent) {
        this->coefficient = coefficient;
        this->exponent = exponent;
        this->next = NULL;
    }

    int getCoefficient() {
        return coefficient;
    }

    void setCoefficient(int coefficient) {
        this->coefficient = coefficient;
    }

    int getExponent() {
        return exponent;
    }

    void setExponent(int exponent) {
        this->exponent = exponent;
    }

    Term *getNext() {
        return next;
    }

    void setNext(Term *next) {
        this->next = next;
    }
};

class Polynomial {
private:
    Term *polynomial;

public:
    Polynomial() {
        polynomial = NULL;
    }

    Term *getPolynomial() {
        return polynomial;
    }

    void setPolynomial(Term *poly) {
        this->polynomial = poly;
    }

    void insertTerm(int coeff, int expo) {
        cout<<"Inserted new term with coefficient "<<coeff<<", and exponent "<<expo<<endl;
        Term *newTerm = new Term(coeff, expo);

        if (!polynomial || polynomial->getExponent() >= expo) {
            newTerm->setNext(polynomial);
            polynomial = newTerm;
        } else {
            Term *temp = polynomial;
            while (temp->getNext() != NULL &&  expo > temp->getNext()->getExponent() ) {
                temp = temp->getNext();
            }
            newTerm->setNext(temp->getNext());
            temp->setNext(newTerm);
        }
    }

    void deleteTerm(int coeff, int expo) {
        if (!polynomial) {
            cout<<"Empty of terms"<<endl;
            return;
        }

        if (polynomial->getCoefficient() == coeff && polynomial->getExponent() == expo) {
            polynomial = polynomial->getNext();
        }

        else {
            Term *temp = polynomial;
            Term *prev;
            bool found = false;
            while (temp != NULL) {

                if (temp->getCoefficient() == coeff && temp->getExponent() == expo) {
                    prev->setNext(temp->getNext());
                    return;
                }

                prev = temp;
                temp = temp->getNext();
            }

            if (!found) {
                cout<<"The term ("<<coeff<<"x^"<<expo<<") not found"<<endl;
                return;
            }
        }

        cout<<"The term with coefficient "<<coeff<<", and exponent "<<expo<<" got deleted."<<endl;
    }

    void reversePolynomial() {
        if (!polynomial){
            return;
        }

        Term *current = polynomial;
        Term *prev = NULL, *next = NULL;

        while (current != NULL) {
            next = current->getNext();
            current->setNext(prev);
            prev = current;
            current = next;
        }

        polynomial = prev;
        cout<<"The polynomial got reversed"<<endl;
    }

    void computeDerivative() {
        if (!polynomial){
            cout<<"Cannot compute derivative, its empty"<<endl;
            return;
        }

        Term *temp = polynomial;
        int coeff = 0, expo = 0;

        while (temp != NULL) {
            coeff = temp->getCoefficient();
            expo = temp->getExponent();
            temp->setCoefficient(coeff * expo);
            temp->setExponent(expo - 1);

            if (temp->getExponent() == -1)
                deleteTerm(temp->getCoefficient(), temp->getExponent());

            temp = temp->getNext();
        }

    }

    string toString() {
        if (!polynomial) {
            return "Empty";
        }

        string thePolynomial = "";
        Term *temp = polynomial;

        while (temp != NULL) {
            if (temp->getExponent() == 1) {
                thePolynomial += to_string(temp->getCoefficient()) + "x";
            }

            else if (temp->getExponent() == 0) {
                thePolynomial += to_string(temp->getCoefficient());
            }

            else {
                thePolynomial += to_string(temp->getCoefficient()) + "x^" + to_string(temp->getExponent());
            }

            temp = temp->getNext();

            if (temp)
                thePolynomial += " + ";
        }
        return thePolynomial;
    }

};


class TestClass {
private:
    Polynomial *poly;

public:
    TestClass() {
        poly = new Polynomial();
    }

    Polynomial *getPoly() const {
        return poly;
    }

    void setPoly(Polynomial *poly) {
        this->poly = poly;
    }

    void insertTerm(int coeff, int expo) {
        cout<<"Insert new term function called: "<<endl;
        poly->insertTerm(coeff, expo);
        printPolynomial();
    }

    void deleteTerm(int coeff, int expo) {
        poly->deleteTerm(coeff, expo);
        printPolynomial();
    }

    void reversePolynomial() {
        poly->reversePolynomial();
        printPolynomial();
    }

    void computeDerivative() {
        cout<<"Called derivative function "<<endl;
        poly->computeDerivative();
        printPolynomial();
    }

    void printPolynomial() {
        cout<<"The polynomial till now is: ";
        cout<<poly->toString()<<endl;
    }
};

int main() {
    TestClass *t = new TestClass();

    int choice = 0;
    cout<<"Choose from this menu:\n1- Insert term.\n2- Delete Term.\n3- Compute derivative.\n4- Reverse the polynomial.\n5- Print.\n6- Exit."<<endl;

    cin>>choice;
    int coeff = 0, expo = 0;

    while (choice != 6) {
        if (choice == 1) {
            cout<<"Enter the Coefficient of the term"<<endl;
            cin>>coeff;
            cout<<"Enter the Exponent of the term"<<endl;
            cin>>expo;

            t->insertTerm(coeff, expo);
        } else if (choice == 2) {
            cout<<"Enter the Coefficient of the term you want to delete"<<endl;
            cin>>coeff;
            cout<<"Enter the Exponent of the term you want to delete"<<endl;
            cin>>expo;

            t->deleteTerm(coeff, expo);
        } else if (choice == 3) {
            t->computeDerivative();
        } else if (choice == 4) {
            t->reversePolynomial();
        } else if (choice == 5) {
            t->printPolynomial();
        }
        cout<<endl;
        cout<<"Choose from the menu again"<<endl;
        cin>>choice;
    }




    return 0;
}
