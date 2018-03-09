#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE

#include <string>


class Personnage
{
    public:
    Personnage();
    void recevoirDegats(int nbDegats);
    void attaquer(Personnage &cible);
    void boirePotionDeVie(int quantitePotion);
    void changerArme(std::string nomNouvelleArme, int degatsNouvelleArme);
    bool estVivant();
    void afficherEtat() ;
    private:

    int m_vie;
    int m_mana;
    std::string m_nomArme; 
    int m_degatsArme;
};

#endif