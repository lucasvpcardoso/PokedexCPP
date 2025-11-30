#include "Pokemon.h"
#include <iostream>
#include <sstream>

// --- IMPLEMENTAÇÃO DA CLASSE BASE ---
Pokemon::Pokemon(string n, int lv, int dx)
    : nome(n), level(lv), dex(dx) {}

// Sobrecarga de Construtor (Requisito 8)
Pokemon::Pokemon(const Pokemon& outro)
    : nome(outro.nome), level(outro.level), dex(outro.dex) {}

string Pokemon::info() const {
    stringstream ss;
    ss << nome << " (Dex: " << dex << " | Lv " << level << ") | Tipo: " << getTipoPrincipal();
    return ss.str();
}

// --- IMPLEMENTAÇÃO DE POKEMON AGUA (NÍVEL 2) ---
void PokemonAgua::ataqueRapido() {
    cout << nome << " usou Jato d'Água (Ataque Rápido)!\n";
}
void PokemonAgua::ataqueCarregado() {
    cout << nome << " usou Hidro Bomba (Ataque Carregado)! É muito efetivo!\n";
}
// Sobrecarga de Método (Requisito 8)
void PokemonAgua::ataqueCarregado(int carga) {
    cout << nome << " carregou por " << carga << " turnos e usou Água Poderosa!\n";
}

// --- IMPLEMENTAÇÃO DE POKEMON FOGO (NÍVEL 2) ---
void PokemonFogo::ataqueRapido() {
    cout << nome << " usou Brasas (Ataque Rápido)!\n";
}
void PokemonFogo::ataqueCarregado() {
    cout << nome << " usou Lança-Chamas (Ataque Carregado)! O alvo está em chamas!\n";
}

// --- IMPLEMENTAÇÃO DE POKEMON GRAMA (NÍVEL 2) ---
void PokemonGrama::ataqueRapido() {
    cout << nome << " usou Folha Navalha (Ataque Rápido)!\n";
}
void PokemonGrama::ataqueCarregado() {
    cout << nome << " usou Chicote de Cipó (Ataque Carregado)! É muito efetivo!\n";
}


// --- IMPLEMENTAÇÃO DOS INICIAIS (NÍVEL 3) ---

// SQUIRTLE
string Squirtle::info() const {
    return PokemonAgua::info() + " - Herdeiro da linhagem de Kanto.";
}

// CHARMANDER
string Charmander::info() const {
    return PokemonFogo::info() + " - Pokemon de Fogo Puro, nível inicial.";
}

// BULBASAUR
string Bulbasaur::info() const {
    return PokemonGrama::info() + " - Pokemon Semente.";
}
// As classes restantes (Wartortle, Blastoise, Charmeleon, Charizard, Ivysaur, Venusaur)
// usam as implementações padrão no .h e as implementações polimórficas das classes Nível 2.