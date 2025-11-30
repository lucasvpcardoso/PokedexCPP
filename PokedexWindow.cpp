#include "PokedexWindow.h"
#include "Pokemon.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QDir>
#include <fstream>      // Para persistência
#include <sstream>

PokedexWindow::PokedexWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Pokédex - OO Grau B");
    resize(800, 500);

    QWidget *central = new QWidget();
    setCentralWidget(central);

    lista = new QListWidget();
    lista->setFixedWidth(250);

    imagem = new QLabel("Selecione um Pokémon");
    imagem->setAlignment(Qt::AlignCenter);

    info = new QLabel("");
    info->setAlignment(Qt::AlignCenter);
    info->setStyleSheet("font-size: 18px; font-weight: bold;");

    btnRapido = new QPushButton("Ataque Rápido");
    btnCarregado = new QPushButton("Ataque Carregado");
    btnSalvar = new QPushButton("Salvar Pokémons (Persistence)");
    btnAdd = new QPushButton("Adicionar Novo Pokémon");

    // Layout
    QHBoxLayout *hl = new QHBoxLayout(central);
    QVBoxLayout *vlInfo = new QVBoxLayout();

    vlInfo->addWidget(imagem);
    vlInfo->addWidget(info);
    vlInfo->addWidget(btnRapido);
    vlInfo->addWidget(btnCarregado);
    vlInfo->addWidget(btnSalvar);
    vlInfo->addWidget(btnAdd);

    hl->addWidget(lista);
    hl->addLayout(vlInfo);

    carregarPokemons();

    for (Pokemon *p : pokemons)
        lista->addItem(QString::fromStdString(p->info()));

    // Conexões
    connect(lista, &QListWidget::currentRowChanged, this, &PokedexWindow::selecionarPokemon);
    connect(btnRapido, &QPushButton::clicked, this, &PokedexWindow::ataqueRapido);
    connect(btnCarregado, &QPushButton::clicked, this, &PokedexWindow::ataqueCarregado);
    connect(btnSalvar, &QPushButton::clicked, this, &PokedexWindow::salvarPokemons);
    connect(btnAdd, &QPushButton::clicked, this, &PokedexWindow::adicionarNovoPokemon);
}

// Destrutor para Alocação Dinâmica (Requisito 6)
PokedexWindow::~PokedexWindow() {
    for (Pokemon *p : pokemons) {
        delete p;
    }
}

// Persistência - Carregamento (Requisito 7)
void PokedexWindow::carregarPokemons() {
    ifstream file("pokemons.csv");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Erro de Persistência", "Arquivo pokemons.csv não encontrado. Carregando dados padrão.");
        // Alocação Dinâmica de exemplo
        pokemons.push_back(new Venusaur(45));
        pokemons.push_back(new Charizard(50));
        pokemons.push_back(new Blastoise(50));
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, level_str;
        int level;

        getline(ss, type, ',');
        getline(ss, level_str, ',');

        try {
            level = stoi(level_str);
        } catch (...) {
            continue;
        }

        // Criação polimórfica (Alocação Dinâmica)
        if (type == "Squirtle") {
            pokemons.push_back(new Squirtle(level));
        } else if (type == "Wartortle") {
            pokemons.push_back(new Wartortle(level));
        } else if (type == "Blastoise") {
            pokemons.push_back(new Blastoise(level));
        } else if (type == "Charmander") {
            pokemons.push_back(new Charmander(level));
        } else if (type == "Charmeleon") {
            pokemons.push_back(new Charmeleon(level));
        } else if (type == "Charizard") {
            pokemons.push_back(new Charizard(level));
        } else if (type == "Bulbasaur") {
            pokemons.push_back(new Bulbasaur(level));
        } else if (type == "Ivysaur") {
            pokemons.push_back(new Ivysaur(level));
        } else if (type == "Venusaur") {
            pokemons.push_back(new Venusaur(level));
        }
    }
    file.close();
}

// Persistência - Salvamento (Requisito 7)
void PokedexWindow::salvarPokemons() {
    ofstream file("pokemons.csv");
    if (!file.is_open()) {
        QMessageBox::critical(this, "Erro de Persistência", "Falha ao abrir o arquivo para salvar.");
        return;
    }

    for (Pokemon *p : pokemons) {
        file << p->nome << "," << p->level << "\n";
    }
    file.close();
    QMessageBox::information(this, "Persistência", "Pokémons salvos com sucesso em pokemons.csv!");
}

QString PokedexWindow::caminhoImagem(int dex) {
    // CORREÇÃO: Usando caminho de recurso para garantir que a imagem seja empacotada no EXE.
    QString prefixo_recurso = ":/imgs/";
    QString subpasta_nome = "Pokedex/";

    // Converte o número da dex para string formatada (ex: 7 -> "007")
    QString nome = QString("%1.png").arg(dex, 3, 10, QChar('0'));

    // Cria o caminho completo: ":/imgs/Pokedex/007.png"
    QString full = prefixo_recurso + subpasta_nome + nome;

    // A função QFileInfo::exists(full) ainda funciona para caminhos de recurso
    if (!QFileInfo::exists(full))
        return ":/erro.png"; // Se tiver uma imagem de erro no recurso (opcional)

    return full;
}

void PokedexWindow::selecionarPokemon() {
    int row = lista->currentRow();
    if (row < 0 || row >= pokemons.size()) return;

    atualizarUI(pokemons[row]); // Passa o ponteiro
}

void PokedexWindow::atualizarUI(const Pokemon *p) {
    if (!p) return;

    QPixmap img(caminhoImagem(p->dex));
    imagem->setPixmap(img.scaled(250, 250, Qt::KeepAspectRatio));

    // Uso de Polimorfismo: p->info() chama a versão correta
    info->setText(QString::fromStdString(p->info()));
}

void PokedexWindow::ataqueRapido() {
    int row = lista->currentRow();
    if (row < 0 || row >= pokemons.size()) return;

    Pokemon *p = pokemons[row];
    p->ataqueRapido(); // Polimorfismo (Requisito 5)
    QMessageBox::information(this, "Ataque Rápido", QString::fromStdString(p->nome + " usou Ataque Rápido!"));
}

void PokedexWindow::ataqueCarregado() {
    int row = lista->currentRow();
    if (row < 0 || row >= pokemons.size()) return;

    Pokemon *p = pokemons[row];
    p->ataqueCarregado(); // Polimorfismo (Requisito 5)

    // CORRIGIDO: Mensagem de ataque e FECHAMENTO CORRETO DA FUNÇÃO
    QMessageBox::information(this, "Ataque Carregado",
                             QString::fromStdString(p->nome + " usou Ataque Carregado!"));
} // <--- FIM CORRETO DA FUNÇÃO ataqueCarregado

// Cadastro via GUI
void PokedexWindow::adicionarNovoPokemon() {
    bool ok;
    // Lista de todas as 9 opções
    QStringList tiposDisponiveis = QStringList()
                                   << "Bulbasaur" << "Ivysaur" << "Venusaur"
                                   << "Charmander" << "Charmeleon" << "Charizard"
                                   << "Squirtle" << "Wartortle" << "Blastoise";

    QString item = QInputDialog::getItem(this, "Adicionar Pokémon",
                                         "Escolha o Pokémon:",
                                         tiposDisponiveis, 0, false, &ok);

    if (ok && !item.isEmpty()) {
        int level = QInputDialog::getInt(this, "Nível do Pokémon",
                                         "Digite o Nível (1-100):", 1, 1, 100, 1, &ok);

        if (ok) {
            Pokemon *novoP = nullptr;

            // Alocação Dinâmica (new)
            if (item == "Squirtle") {
                novoP = new Squirtle(level);
            } else if (item == "Wartortle") {
                novoP = new Wartortle(level);
            } else if (item == "Blastoise") {
                novoP = new Blastoise(level);
            } else if (item == "Charmander") {
                novoP = new Charmander(level);
            } else if (item == "Charmeleon") {
                novoP = new Charmeleon(level);
            } else if (item == "Charizard") {
                novoP = new Charizard(level);
            } else if (item == "Bulbasaur") {
                novoP = new Bulbasaur(level);
            } else if (item == "Ivysaur") {
                novoP = new Ivysaur(level);
            } else if (item == "Venusaur") {
                novoP = new Venusaur(level);
            }

            if (novoP) {
                pokemons.push_back(novoP);
                lista->addItem(QString::fromStdString(novoP->info()));

                QMessageBox::information(this, "Sucesso",
                                         QString("Novo %1 (Lv %2) adicionado! Clique em Salvar para persistir os dados.").arg(item).arg(level));
            }
        }
    }
} // <--- FIM CORRETO DA FUNÇÃO adicionarNovoPokemon
