#ifndef MINHA_BIBLIOTECA_HPP  // Evita inclusão múltipla do arquivo, se nio foi definido 
#define MINHA_BIBLIOTECA_HPP  // Define a macro de controle

#include <string>   // biblioteca para usarmos strings
#include <iostream> // iostream para cout e cin

class Autor {  // Classe que representa um autor

private:  // Área acessível apenas dentro da classe

    std::string nome;              // Nome do autor
    std::string* livros;           // Ponteiro para vetor dinâmico de livros
    int qtdLivros;                 // Quantidade atual de livros
    const int limiteLivros = 10;   // Máximo de livros permitidos

public:  // Métodos acessíveis externamente

    Autor();                       // Construtor inicializa atributos
    ~Autor();                      // Destrutor para liberar memória do vetor

    void definirNome(const std::string& nomeAutor);  // Define o nome do autor
    bool adicionarLivro(const std::string& titulo);  // Adiciona livro se houver espaço
    bool removerLivro(const std::string& titulo);    // Remove livro pelo título
    bool contemLivro(const std::string& titulo) const;  // Verifica se possui o livro
    void listarLivros() const;     // Lista todos os livros do autor
    const std::string& obterNome() const;  // Retorna o nome do autor
    bool estaVazio() const;  // Retorna true se não tiver livros
    int obterQtdLivros() const;  //usaremos para mostrar todos os livros cadastrados no sistema
};


class Biblioteca {  // Classe que vai representar a biblioteca

private:  // Atributos internos da biblioteca

    Autor* autores[10];        // Vetor fixo de 10 ponteiros para Autor
    int qtdAutores;            // Quantidade atual de autores cadastrados
    const int limiteAutores = 10;  // numero Máximo de autores permitidos

public:  // Métodos públicos da biblioteca

    Biblioteca();              // Construtor (inicializa estrutura)
    ~Biblioteca();             // Destrutor (libera autores criados)

    void mostrarMenu();        // Exibe menu principal
    void cadastrarLivro();     // Cadastra livro em um autor
    void listarAutoresELivros() const;  // Lista autores e seus livros
    void removerLivroOuAutor();  // Remove livro ou autor
    void buscarLivro() const;  // Procura livro na biblioteca
    void removerAutor(); //usaremos para remover autores diretamente
    void mostrarTotalLivros() const; //fução para mostrarmos o total de livros da biblioteca, e como é apenas pra mostrar usamos o const

private:  // Métodos auxiliares internos

    Autor* buscarAutor(const std::string& nome) const;  // Busca autor pelo nome
};

#endif  // Finaliza proteção contra inclusão múltipla