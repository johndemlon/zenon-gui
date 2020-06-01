// Lizenz: public domain

typedef void (*constructor)();

// Im Linkerskript definiert
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void initialiseConstructors();

// Ruft die Konstruktoren für globale/statische Objekte auf
void initialiseConstructors()
{
    for (constructor* i = &start_ctors; i != &end_ctors; ++i)
        (*i)();
}
