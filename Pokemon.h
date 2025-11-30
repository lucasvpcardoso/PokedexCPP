#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// NÍVEL 1: CLASSE ABSTRATA (Requisito 4)
class Pokemon {
public:
    string nome;
    int level;
    int dex;

    Pokemon(string n, int lv, int dx);          // Sobrecarga 1
    Pokemon(const Pokemon& outro);              // Sobrecarga 2 (Requisito 8)

    // Métodos Virtuais Puros (Polimorfismo/Interface)
    virtual string getTipoPrincipal() const = 0;
    virtual string info() const;
    virtual void ataqueRapido() = 0;
    virtual void ataqueCarregado() = 0;
    
    // Destrutor virtual essencial para Alocação Dinâmica (Requisito 6)
    virtual ~Pokemon() = default; 
};

// --- CLASSES INTERMEDIÁRIAS (NÍVEL 2 - Herança Simples - Requisito 2) ---

class PokemonAgua : public Pokemon {
public:
    PokemonAgua(string n, int lv, int dx) : Pokemon(n, lv, dx) {}
    string getTipoPrincipal() const override { return "Água"; }
    void ataqueRapido() override;
    void ataqueCarregado() override;
    void ataqueCarregado(int carga); // Sobrecarga de Método (Requisito 8)
};

class PokemonFogo : public Pokemon {
public:
    PokemonFogo(string n, int lv, int dx) : Pokemon(n, lv, dx) {}
    string getTipoPrincipal() const override { return "Fogo"; }
    void ataqueRapido() override;
    void ataqueCarregado() override;
};

class PokemonGrama : public Pokemon {
public:
    PokemonGrama(string n, int lv, int dx) : Pokemon(n, lv, dx) {}
    string getTipoPrincipal() const override { return "Grama"; }
    void ataqueRapido() override;
    void ataqueCarregado() override;
};

// --- CLASSES CONCRETAS (NÍVEL 3 - Herança Multinível - Requisito 3) ---

// ÁGUA
class Squirtle : public PokemonAgua {
public:
    Squirtle(int lv) : PokemonAgua("Squirtle", lv, 7) {}
    string info() const override; 
};
class Wartortle : public PokemonAgua {
public:
    Wartortle(int lv) : PokemonAgua("Wartortle", lv, 8) {}
    string info() const override { return PokemonAgua::info() + " - Tartaruga Marinha."; }
};
class Blastoise : public PokemonAgua {
public:
    Blastoise(int lv) : PokemonAgua("Blastoise", lv, 9) {}
    string info() const override { return PokemonAgua::info() + " - Canhões de Água Pesados."; }
};

// FOGO
class Charmander : public PokemonFogo {
public:
    Charmander(int lv) : PokemonFogo("Charmander", lv, 4) {}
    string info() const override; 
};
class Charmeleon : public PokemonFogo {
public:
    Charmeleon(int lv) : PokemonFogo("Charmeleon", lv, 5) {}
    string info() const override { return PokemonFogo::info() + " - Lagarto Chama, temperamental."; }
};
class Charizard : public PokemonFogo {
public:
    Charizard(int lv) : PokemonFogo("Charizard", lv, 6) {}
    string info() const override { return PokemonFogo::info() + " - Dragão de Fogo."; }
};

// GRAMA
class Bulbasaur : public PokemonGrama {
public:
    Bulbasaur(int lv) : PokemonGrama("Bulbasaur", lv, 1) {}
    string info() const override;
};
class Ivysaur : public PokemonGrama {
public:
    Ivysaur(int lv) : PokemonGrama("Ivysaur", lv, 2) {}
    string info() const override { return PokemonGrama::info() + " - Broto em desenvolvimento."; }
};
class Venusaur : public PokemonGrama {
public:
    Venusaur(int lv) : PokemonGrama("Venusaur", lv, 3) {}
    string info() const override { return PokemonGrama::info() + " - Flor Tóxica gigante."; }
};