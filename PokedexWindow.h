#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "Pokemon.h" 

class PokedexWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit PokedexWindow(QWidget *parent = nullptr);
    ~PokedexWindow(); // Requisito: Destrutor (Alocação Dinâmica)

private slots:
    void selecionarPokemon();
    void ataqueRapido();
    void ataqueCarregado();
    void salvarPokemons();          
    void adicionarNovoPokemon();    

private:
    QListWidget *lista;
    QLabel *imagem;
    QLabel *info;
    QPushButton *btnRapido;
    QPushButton *btnCarregado;
    QPushButton *btnSalvar;
    QPushButton *btnAdd;

    // Requisito 6: Alocação Dinâmica e Polimorfismo
    std::vector<Pokemon*> pokemons; 

    void carregarPokemons();        // Persistência (Requisito 7)
    void atualizarUI(const Pokemon *p); // Usa ponteiro
    QString caminhoImagem(int dex);
};