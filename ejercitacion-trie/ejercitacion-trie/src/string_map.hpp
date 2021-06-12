template <typename T>
string_map<T>::string_map() : _size(0) { raiz = new Nodo(); }

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for (string clave: claves) {
        erase(clave);
    }
    for (string clave: d.claves) {
        this->insert(make_pair(clave, at(clave)));
    }
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& value_type){
    Nodo* actual = raiz;
    pair<string, T> value = value_type;
    for (int i = 0; i < value.first.size()-1; i++) {
        int ascii = value.first[i];
        if (actual->siguientes[ascii]) { // entro a un nodo existente o creo uno
            actual = actual->siguientes[ascii];
        } else {
            actual->siguientes[ascii] = new Nodo();
            actual = actual->siguientes[ascii];
        }
    }
    int ult_c = value.first.back();
    T* def = new T(value.second);
    if (actual->siguientes[ult_c]){ // ultima letra
        if (actual->definicion) delete actual->definicion; // ya existe definicion
        delete actual->siguientes[ult_c];
        actual->siguientes[ult_c] = new Nodo(def);
    } else {
        actual->siguientes[ult_c] = new Nodo(def);
        _size++;
    }
    claves.insert(value.first);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    int res;
    Nodo* actual = raiz;
    for (char c: clave) {
        if (!actual->siguientes[int(c)]) return 0;
        actual = actual->siguientes[int(c)];
    }
    (actual->definicion)? res = 1 : res = 0;
    return res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = raiz;
    for (char c: clave) {
        actual = actual->siguientes[int(c)];
    }
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = raiz;
    for (char c: clave) {
        actual = actual->siguientes[int(c)];
    }
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = raiz;
    Nodo* ultimo = raiz;
    int itr = 0;
    for (int i = 0; i < clave.size(); i++) {
        if (actual->definicion) ultimo = actual, itr = i;
        actual = actual->siguientes[clave[i]];
    }
    delete actual->definicion;
    claves.erase(clave);
//    if (!actual->haySiguientes()) {
//        for (int j = clave.size()-1; j > itr; j--) {
//            ac
//        }
//    }

}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}