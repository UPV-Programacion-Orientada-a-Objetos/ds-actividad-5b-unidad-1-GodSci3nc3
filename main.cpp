#include <iostream>

template <typename T>
class MatrizBase {
public:
    virtual void cargarValores() = 0;
    virtual void imprimir() const = 0;
    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otraMatriz) const = 0;

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
    
    virtual ~MatrizDinamica() {
        for (int i = 0; i < this->_filas; i++) {
            delete[] _datos[i];
        }
        delete[] _datos;
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
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otraMatriz) const override {
        return nullptr;
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
    
    MatrizBase<T>* sumar(const MatrizBase<T>& otraMatriz) const override {
        return nullptr;
    }
};

int main() {
    return 0;
}