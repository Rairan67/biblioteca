#include "MinhaBiblioteca.hpp"   // Inclui as declarações das classes para permitir a implementação dos métodos

using namespace std;   // namespace para não precisarmos usar std::

//metodos da classe autor
Autor::Autor() {   // Construtor responsável por inicializar o objeto Autor
    nome = "";   // Inicializa o nome com string vazia para evitar lixo de memória
    qtdLivros = 0;   // Define inicialmente que o autor não possui livros cadastrados
    livros = new string[limiteLivros];   // Aloca dinamicamente um vetor de strings para armazenar os livros
}

Autor::~Autor() {   // Destrutor chamado automaticamente quando o objeto é destruído
    delete[] livros;   // Libera a memória previamente alocada com new[] evitando
}

void Autor::definirNome(const string& nomeAutor) {   // Método para atribuir nome ao autor
    nome = nomeAutor;   // Copia o valor recebido para o atributo interno
}

const string& Autor::obterNome() const {   // Retorna o nome do autor sem permitir modificação pelo const
    return nome;   // Retorna por referência constante para evitar cópia desnecessária
}

bool Autor::adicionarLivro(const string& titulo) {   // Adiciona um novo livro ao autor
    if (qtdLivros >= limiteLivros)   // Verifica se já atingiu a capacidade máxima do vetor
        return false;   // Impede inserção além do limite físico do array

    livros[qtdLivros++] = titulo;   // Insere o título na próxima posição livre e incrementa o contador
    return true;   // Indica que a inserção foi realizada com sucesso
}

bool Autor::removerLivro(const string& titulo) {   // Remove um livro específico do autor
    for (int i = 0; i < qtdLivros; i++) {   // Percorre apenas as posições válidas do vetor
        if (livros[i] == titulo) {   // Verifica se encontrou o livro desejado

            for (int j = i; j < qtdLivros - 1; j++)   // Percorre os elementos após o removido
                livros[j] = livros[j + 1];   // Desloca os livros para manter o vetor compacto

            qtdLivros--;   // Reduz a quantidade lógica de livros armazenados
            return true;   // Indica que a remoção foi realizada
        }
    }
    return false;   // Retorna falso caso o livro não seja encontrado
}

bool Autor::contemLivro(const string& titulo) const {   // Verifica se determinado livro pertence ao autor
    for (int i = 0; i < qtdLivros; i++)   // Percorre apenas livros válidos
        if (livros[i] == titulo)   // Compara título atual com o procurado
            return true;   // Retorna verdadeiro se encontrar correspondência

    return false;   // Retorna falso se nenhum livro corresponder
}

bool Autor::estaVazio() const {   // Verifica se o autor não possui livros cadastrados
    return qtdLivros == 0;   // Retorna verdadeiro quando a quantidade lógica for zero
}

void Autor::listarLivros() const {   // Exibe todos os livros do autor
    if (qtdLivros == 0) {   // Verifica se não há livros cadastrados
        cout << "  Nenhum livro.\n";   // Informa ausência de livros
        return;   // Encerra a função
    }

    for (int i = 0; i < qtdLivros; i++)   // Percorre todos os livros válidos
        cout << "  - " << livros[i] << endl;   // Imprime cada título armazenado
}

int Autor::obterQtdLivros() const {   // Permite consultar quantos livros o autor possui
    return qtdLivros;   // Retorna o contador interno mantendo encapsulamento
}

//metodos da classe biblioteca
Biblioteca::Biblioteca() {   // Construtor da classe Biblioteca
    qtdAutores = 0;   // Inicializa a biblioteca sem autores cadastrados

    for (int i = 0; i < limiteAutores; i++)   // Percorre todo o vetor de ponteiros
        autores[i] = nullptr;   // Inicializa cada posição como vazia evitando ponteiros inválidos
}

Biblioteca::~Biblioteca() {   // Destrutor responsável por liberar memória da biblioteca
    for (int i = 0; i < qtdAutores; i++)   // Percorre apenas autores realmente criados
        delete autores[i];   // Libera cada objeto Autor criado dinamicamente
}

Autor* Biblioteca::buscarAutor(const string& nome) const {   // Busca um autor pelo nome
    for (int i = 0; i < qtdAutores; i++)   // Percorre autores cadastrados
        if (autores[i]->obterNome() == nome)   // Compara nomes utilizando método encapsulado
            return autores[i];   // Retorna o ponteiro armazenado no vetor

    return nullptr;   // Retorna nulo caso o autor não exista
}

void Biblioteca::cadastrarLivro() {   // Permite cadastrar livro e autor se necessário

    string nomeAutor, nomeLivro;   // Variáveis temporárias para entrada

    cout << "Autor: ";
    getline(cin, nomeAutor);   // Lê nome do autor digitado

    cout << "Livro: ";
    getline(cin, nomeLivro);   // Lê nome do livro digitado

    Autor* autor = buscarAutor(nomeAutor);   // Verifica se autor já existe

    if (autor == nullptr) {   // Caso o autor não esteja cadastrado

        if (qtdAutores >= limiteAutores) {   // Verifica limite máximo de autores
            cout << "Limite de autores atingido.\n";
            return;
        }

        autores[qtdAutores] = new Autor();   // Cria novo objeto dinamicamente na heap
        autores[qtdAutores]->definirNome(nomeAutor);   // Define nome do novo autor
        autores[qtdAutores]->adicionarLivro(nomeLivro);   // Adiciona primeiro livro

        qtdAutores++;   // Atualiza contador lógico de autores

    } else {   // Caso o autor já exista

        if (!autor->adicionarLivro(nomeLivro))   // Tenta adicionar livro ao autor existente
            cout << "Limite de livros atingido.\n";
    }
}

void Biblioteca::removerLivroOuAutor() {   // Remove livro e possivelmente o autor

    string titulo;
    cout << "Digite o livro para remover: ";
    getline(cin, titulo);   // Lê título a ser removido

    for (int i = 0; i < qtdAutores; i++) {   // Percorre autores cadastrados

        if (autores[i]->removerLivro(titulo)) {   // Tenta remover livro do autor atual

            cout << "Livro removido.\n";

            if (autores[i]->estaVazio()) {   // Verifica se autor ficou sem livros

                delete autores[i];   // Libera memória do autor removido

                for (int j = i; j < qtdAutores - 1; j++)   // Desloca ponteiros
                    autores[j] = autores[j + 1];   // Mantém vetor compacto

                autores[qtdAutores - 1] = nullptr;   // Evita ponteiro pendente na última posição

                qtdAutores--;   // Atualiza quantidade lógica

                cout << "Autor removido por nao possuir mais livros.\n";
            }

            return;
        }
    }

    cout << "Livro nao encontrado.\n";
}

void Biblioteca::removerAutor() {   // Remove autor independentemente dos livros

    string nome;
    cout << "Digite o nome do autor para remover: ";
    getline(cin, nome);   // Lê nome digitado

    for (int i = 0; i < qtdAutores; i++) {   // Percorre autores

        if (autores[i]->obterNome() == nome) {   // Verifica correspondência

            delete autores[i];   // Libera memória do autor

            for (int j = i; j < qtdAutores - 1; j++)   // Desloca ponteiros subsequentes
                autores[j] = autores[j + 1];

            autores[qtdAutores - 1] = nullptr;   // Limpa última posição

            qtdAutores--;   // Atualiza contador

            cout << "Autor removido com sucesso.\n";
            return;
        }
    }

    cout << "Autor nao encontrado.\n";
}

void Biblioteca::buscarLivro() const {   // Busca livro em toda biblioteca

    string titulo;
    cout << "Digite o livro: ";
    getline(cin, titulo);   // Lê título a procurar

    for (int i = 0; i < qtdAutores; i++)   // Percorre autores
        if (autores[i]->contemLivro(titulo)) {   // Verifica presença do livro
            cout << "Autor: " << autores[i]->obterNome() << endl;
            return;
        }

    cout << "Livro nao encontrado.\n";
}

void Biblioteca::listarAutoresELivros() const {   // Lista todos os autores e seus livros

    if (qtdAutores == 0) {   // Verifica se biblioteca está vazia
        cout << "Nenhum autor cadastrado.\n";
        return;
    }

    for (int i = 0; i < qtdAutores; i++) {   // Percorre autores cadastrados
        cout << "\nAutor: " << autores[i]->obterNome() << endl;
        autores[i]->listarLivros();   // Exibe livros de cada autor
    }
}

void Biblioteca::mostrarTotalLivros() const {   // Calcula total geral de livros

    int total = 0;   // Inicializa acumulador

    for (int i = 0; i < qtdAutores; i++)   // Percorre autores
        total += autores[i]->obterQtdLivros();   // Soma quantidade individual

    cout << "\nTotal de livros cadastrados: " << total << endl;
}

void Biblioteca::mostrarMenu() {   // Controla interação principal com usuário

    int opcao = -1;   // Inicializa variável de controle

    while (opcao != 0) {   // Mantém menu ativo até escolher sair

        cout << "\n1 - Cadastrar Livro\n";
        cout << "2 - Remover Livro\n";
        cout << "3 - Buscar Livro\n";
        cout << "4 - Listar Autores e Livros\n";
        cout << "5 - Remover Autor\n";
        cout << "6 - Mostrar total de livros\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";

        cin >> opcao;   // Recebe opção do usuário
        cin.ignore();   // Limpa buffer para permitir uso correto de getline

        switch (opcao) {   // Direciona execução conforme opção escolhida
            case 1: cadastrarLivro(); break;
            case 2: removerLivroOuAutor(); break;
            case 3: buscarLivro(); break;
            case 4: listarAutoresELivros(); break;
            case 5: removerAutor(); break;
            case 6: mostrarTotalLivros(); break;
            case 0: cout << "Finalizando programa.\n"; break;
            default: cout << "Opcao invalida!\n"; break;
        }
    }
}