#include <iostream>
#include "Personnage.h"

using namespace std;


Personnage::Personnage()
{
    m_vie        = 100;
    m_mana       = 100;
    m_nomArme    = "épée rouillée";
    m_degatsArme = 10;
}
void Personnage::recevoirDegats(int nbDegats)
{
    m_vie -= nbDegats;
    if (m_vie < 0)
    {
        m_vie=0;
    }
}

bool Personnage::estVivant()
{
    return (m_vie > 0);
}

void Personnage::attaquer(Personnage &cible)
{
    cible.recevoirDegats(m_degatsArme);
}

void Personnage::changerArme(string nomNouvelleArme, int degatsNouvelleArme)
{
    m_nomArme    = nomNouvelleArme;
    m_degatsArme = degatsNouvelleArme;
}

void Personnage::boirePotionDeVie(int quantitePotion)
{
    m_vie += quantitePotion;

    if (m_vie > 100)
    {
        m_vie = 100;
    }
}

void Personnage::afficherEtat() 
{
    cout << "vie :" << m_vie << endl;
    cout << "mana :" << m_mana << endl;

}