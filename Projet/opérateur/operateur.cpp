#include <iostream>

using namespace std;

// Fonctions permettant de coder les operateurs.


bool Objet::estEgal(Objet const &b) const
{
    return (m_heures == b.m_heures && m_minutes == b.m_minutes && m_secondes == b.m_secondes);     //Teste si a.m_heure == b.m_heure etc.  
}



bool Objet::estInf(Objet const &b) const
{
    if (m_heures < b.m_heures)
    {
        return true;
    }
    else if (m_heures == b.m_heures && m_minutes < b.m_minutes)
    {
        return true;
    }
    else if (m_heures == b.m_heures && m_minutes == b.m_minutes && m_secondes < b.m_secondes)
    {
        return true;
    }
    else 
    {
        return false;
    }
    
}



// Les operateurs !!!!!!

bool operator==(Objet const &a, Objet const &b)
{
    return a.estEgal(b) ;
   
}

bool operator!= (Objet const &a , Objet const &b)
{
    return !(a==b);
}

bool operator<(Objet const &a , Objet const &b)
{
    return (a.estInf(b) && !(a==b));
}

bool operator>(Objet const &a , Objet const &b)
{
    return (!(a.estInf(b)) && !(a.estEgal(b)));
}

bool operator<=(Objet const &a , Objet const &b)
{
    return a.estInf(b);
}

bool operator>(Objet const &a , Objet const &b)
{
    return !(a.estInf(b));
}