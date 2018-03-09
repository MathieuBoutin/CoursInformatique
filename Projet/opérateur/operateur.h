#ifndef DEF_OPERATEUR
#define DEF_OPERATEUR

class Objet
{
    public:


    Objet();
    bool Objet::estInf(Objet const &b) const;
    bool estEgal(Objet const &b) const;
    

};

// en dehors de la classe

bool operator==(Objet const &a, Objet const &b);
bool operator!=(Objet const &a, Objet const &b);
bool operator<(Objet const &a , Objet const &b);
bool operator>(Objet const &a , Objet const &b);
bool operator<=(Objet const &a , Objet const &b);
bool operator>=(Objet const &a , Objet const &b);
#endif