#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton {
protected:
    // Constructor protegido para que solo las clases hijas (como GearLever) puedan usarlo
    Singleton() {}
    virtual ~Singleton() {}

private:
    // Deshabilitar la copia y asignación
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);

public:
    // Método estático para obtener la única instancia
    static T& getInstance() {
        // Al ser static, se inicializa solo la primera vez que se llama a la función
        static T instance;
        return instance;
    }
};

#endif
