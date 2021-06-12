#include "Lista.h"

Lista::Lista() : longitud_(0), head(nullptr), last(nullptr) {}

Lista::Nodo::Nodo(const int &elem) : data(elem), next(nullptr), back(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    while (longitud_ > 0) {
        eliminar(0);
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    while (longitud_ > 0) {
        eliminar(0);
    }
    for (int i = 0; i < aCopiar.longitud(); ++i) {
        this->agregarAtras(aCopiar.iesimo(i));
    }
    this->longitud_ = aCopiar.longitud();
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* n = new Nodo(elem);
    if (longitud_ == 0){
        head = n;
        last = head;
    } else {
        n->next = head;
        head->back = n;
        head = n;
    }
    longitud_++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* n = new Nodo(elem);
    if (longitud_ == 0){
        last = n;
        head = last;
    } else {
        n->back = last;
        last->next = n;
        last = n;
    }
    longitud_++;
}

void Lista::eliminar(Nat i){
    Nodo* m = head;
    for (int n = 0; n < i; n++) {
        m = m->next;
    }
    if (m->back){
        (m->back)->next = m->next;
    } else {
        head = m->next;
    }
    if (m->next){
        (m->next)->back = m->back;
    } else {
        last = m->back;
    }
    longitud_--;
    delete m;
}

int Lista::longitud() const {
    return this->longitud_;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* m = head;
    for (int n = 0; n < i; n++) {
        m = m->next;
    }
    return m->data;
}

int& Lista::iesimo(Nat i) {
    Nodo* m = head;
    for (int n = 0; n < i; n++) {
        m = m->next;
    }
    return m->data;
}

void Lista::mostrar(ostream& o) {
    for (int i = 0; i < longitud_; ++i) {
        o << this->iesimo(i) << endl;
    }
}
