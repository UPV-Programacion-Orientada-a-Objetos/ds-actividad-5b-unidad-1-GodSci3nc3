#include <iostream>

template <typename T>
class MatrizBase {
public:
    virtual ~MatrizBase() {}
    virtual void cargarValores() = 0;
    virtual void imprimir() const = 0;
    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otraMatriz) const = 0;
    virtual T obtenerValor(int i, int j) const = 0;

    int filas() const { return _filas; }
    int columnas() const { return _columnas; }

protected: 
    int _filas;
    int _columnas;
};

template <typename T>
class MatrizDinamica : public MatrizBase<T> {
private:
    T** _datos;

public:
    MatrizDinamica(int filas, int columnas) {
        this->_filas = filas;
        this->_columnas = columnas;
        
        _datos = new T*[filas];
        for (int i = 0; i < filas; i++) {
            _datos[i] = new T[columnas];
        }
    }
    
    MatrizDinamica(const MatrizDinamica<T>& other) {
        this->_filas = other._filas;
        this->_columnas = other._columnas;
        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; i++) {
            _datos[i] = new T[this->_columnas];
            for (int j = 0; j < this->_columnas; j++) {
                _datos[i][j] = other._datos[i][j];
            }
        }
    }

    MatrizDinamica& operator=(const MatrizDinamica<T>& other) {
        if (this == &other) return *this;
        if (_datos) {
            for (int i = 0; i < this->_filas; i++) delete[] _datos[i];
            delete[] _datos;
        }
        this->_filas = other._filas;
        this->_columnas = other._columnas;
        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; i++) {
            _datos[i] = new T[this->_columnas];
            for (int j = 0; j < this->_columnas; j++) _datos[i][j] = other._datos[i][j];
        }
        return *this;
    }

    MatrizDinamica(MatrizDinamica<T>&& other) noexcept {
        this->_filas = other._filas;
        this->_columnas = other._columnas;
        _datos = other._datos;
        other._datos = nullptr;
        other._filas = 0;
        other._columnas = 0;
    }

    MatrizDinamica& operator=(MatrizDinamica<T>&& other) noexcept {
        if (this == &other) return *this;
        if (_datos) {
            for (int i = 0; i < this->_filas; i++) delete[] _datos[i];
            delete[] _datos;
        }
        this->_filas = other._filas;
        this->_columnas = other._columnas;
        _datos = other._datos;
        other._datos = nullptr;
        other._filas = 0;
        other._columnas = 0;
        return *this;
    }

    virtual ~MatrizDinamica() {
        if (_datos) {
            for (int i = 0; i < this->_filas; i++) delete[] _datos[i];
            delete[] _datos;
        }
    }
    
    void cargarValores() override {
        std::cout << "Ingrese valores para matriz dinamica " << this->_filas << "x" << this->_columnas << ":\n";
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                std::cout << "Posicion [" << i << "][" << j << "]: ";
                std::cin >> _datos[i][j];
            }
        }
    }
    
    void imprimir() const override {
        for (int i = 0; i < this->_filas; i++) {
            std::cout << "| ";
            for (int j = 0; j < this->_columnas; j++) {
                std::cout << _datos[i][j] << " | ";
            }
            std::cout << "\n";
        }
    }
    
    T obtenerValor(int i, int j) const override {
        return _datos[i][j];
    }
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otraMatriz) const override {
    if (this->filas() != otraMatriz.filas() || this->columnas() != otraMatriz.columnas()) {
            return nullptr;
        }
        
        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(this->_filas, this->_columnas);
        
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                resultado->_datos[i][j] = this->_datos[i][j] + otraMatriz.obtenerValor(i, j);
            }
        }
        
        return resultado;
    }
};

template <typename T, int M, int N>
class MatrizEstatica : public MatrizBase<T> {
private:
    T _datos[M][N];

public:
    MatrizEstatica() {
        this->_filas = M;
        this->_columnas = N;
    }
    
    void cargarValores() override {
        std::cout << "Ingrese valores para matriz estatica " << this->_filas << "x" << this->_columnas << ":\n";
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                std::cout << "Posicion [" << i << "][" << j << "]: ";
                std::cin >> _datos[i][j];
            }
        }
    }
    
    void imprimir() const override {
        for (int i = 0; i < this->_filas; i++) {
            std::cout << "| ";
            for (int j = 0; j < this->_columnas; j++) {
                std::cout << _datos[i][j] << " | ";
            }
            std::cout << "\n";
        }
    }
    
    T obtenerValor(int i, int j) const override {
        return _datos[i][j];
    }
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otraMatriz) const override {
    if (this->filas() != otraMatriz.filas() || this->columnas() != otraMatriz.columnas()) {
            return nullptr;
        }
        
        MatrizEstatica<T, M, N>* resultado = new MatrizEstatica<T, M, N>();
        
        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                resultado->_datos[i][j] = this->_datos[i][j] + otraMatriz.obtenerValor(i, j);
            }
        }
        
        return resultado;
    }
};

int main() {
    MatrizDinamica<float> a(2,2);
    MatrizEstatica<float,2,2> b;

    a.cargarValores();
    b.cargarValores();

    MatrizBase<float>* c = a.sumar(b);
    if (c) {
        c->imprimir();
        delete c;
    }

    return 0;
}

template <typename T>
MatrizBase<T>* operator+(const MatrizBase<T>& left, const MatrizBase<T>& right) {
    return left.sumar(right);
}