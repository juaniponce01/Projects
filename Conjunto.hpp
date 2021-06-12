#include <stack>

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _longitud(0) {};

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if (!_raiz){
        return false;
    } else {
        Nodo* n = _raiz;
        while(n){
            if (clave < n->valor) {
                n = n->izq;
            } else if (clave > n->valor) {
                n = n->der;
            } else {
                return true;
            }
        }
        return n;
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (_longitud == 0){
        _raiz = new Nodo(clave);
        _longitud++;
    } else {
        Nodo* n = _raiz;
        while(n){
            if (clave < n->valor) {
                if (!n->izq) {
                    n->izq = new Nodo(clave);
                    n->izq->padre = n;
                    _longitud++;
                } else {
                    n = n->izq;
                }
            } else if (clave > n->valor) {
                if (!n->der) {
                    n->der = new Nodo(clave);
                    n->der->padre = n;
                    _longitud++;
                } else {
                    n = n->der;
                }
            } else {
                break;
            }
        }
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo* n = _raiz;
    while (n->valor != clave) {
        (n->valor < clave)? n = n->der : n = n->izq;
    }
    if (n->esHoja()) {
        if (n->padre) {
            (n->padre->der == n)? n->padre->der = NULL : n->padre->izq = NULL;
        } else {
            _raiz = NULL;
        }
    } else if (n->der && n->izq) {
        Nodo* suc = n->der;
        while (suc->izq){
            suc = suc->izq;
        }
        n->valor = suc->valor;
        if (suc->padre == n){
            (suc->der)? suc->padre->der = suc->der : suc->padre->der = NULL;
        } else {
            (suc->der)? suc->padre->izq = suc->der : suc->padre->izq = NULL;
        }
        n = suc;
    } else {
        if (n->padre) {
            if (n->der) {
                if (n->valor < n->padre->valor) {
                    n->padre->izq = n->der;
                } else {
                    n->padre->der = n->der;
                }
                n->der->padre = n->padre;
            } else {
                if (n->valor < n->padre->valor) {
                    n->padre->izq = n->izq;
                } else {
                    n->padre->der = n->izq;
                }
                n->izq->padre = n->padre;
            }
        } else {
            if (n->der){
                n->der->padre = NULL;
                _raiz = n->der;
            } else {
                n->izq->padre = NULL;
                _raiz = n->izq;
            }
        }
    }
    delete n;
    _longitud--;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* n = _raiz;
    while (n->valor != clave) {
        (n->valor < clave)? n = n->der : n = n->izq;
    }
    if (n->der){
        n = n->der;
        while (n->izq){
            n = n->izq;
        }
    } else {
        n = n->padre;
    }
    return n->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* min = _raiz;
    while (min->izq){
        min = min->izq;
    }
    return min->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* max = _raiz;
    while (max->der){
        max = max->der;
    }
    return max->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _longitud;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
    Nodo* n = _raiz;
    stack<Nodo*> s;
    while (n || s.empty() == false) {
        while (n) {
            s.p(n);
            n = n->izq;
        }
        n = s.top();
        s.pop();
        os << n->data << " ";
        n = n->der;
    }
}

