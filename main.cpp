#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include <math.h>

using namespace std;

/* TMAB 2019/2 - Estudo Dirigido 4 / Aprendizes de C/C++

Integrantes do Grupo:

Nome:                      DRE:

Alexandre Cordeiro        118037282
Bernardo Mendonca         118038733
Caue Caviglioni           118058458
Claudio Teixeira          118049815
Marcos Godinho            118058864

*/

struct Estabelecimentos {
    int ID;
    char CATEGORIA;
    string NOME;
    string ENDERECO;
    int TEL1;
    int TEL2;
    int TEL3;
    int posX;
    int posY;

};

Estabelecimentos tabela[1000];
int numeroDeLidos = 0;
int listaID[1000];
string listaCategoria[1000];
string listaNome[1000];
string listaEndereco[1000];
int listaTel1[1000];
int listaTel2[1000];
int listaTel3[1000];
int listaPosX[1000];
int listaPosY[1000];

// Gera um numero aleatorio para servir de ID para os estabelecimentos
int geradorID() {
    return rand();

}

// Gera uma categoria aleatoria para cada estabelecimento
char geradorCategoria() {
    char caracteres[] = {'C','F','B','R','L'};
    char tipo = caracteres[rand() % sizeof(caracteres)];
    return tipo;
}

// Funcao que gera um nome aleatorio para cada estabelecimento       ** Coloquei como tamanho maximo para a string de 30 caractereres para nao poluir tanto o arquivo de texto
string geradorNomes() {
    int tamanho = 30;
    stringstream ss;
    string caracteres = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < tamanho; i++) {
        ss << caracteres[rand() % sizeof(caracteres)/sizeof(caracteres[0])];
    }

    string nome = ss.str();

    return nome;
}

//Gera um endereco aleatorio do tipo: (Rua ou Avenida)_nome_numero_bairro                ** Assim como no geradorNomes() o nome da rua ou avenida é limitado a 15 caracteres e o bairro a 5
string geradorEndereco() {
    int tamanho = 15;
    stringstream nomeRua;
    stringstream nomeBairro;
    stringstream ss;
    string palavrasChave[] = {"Rua", "Avenida"};
    string caracteres = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < tamanho; i++) {
        nomeRua << caracteres[rand() % sizeof(caracteres)/sizeof(caracteres[0])];
    }

    int numeroRua = rand();

    for (int i = 0; i < 5; i++) {
        nomeBairro << caracteres[rand() % sizeof(caracteres)/sizeof(caracteres[0])];
    }

    ss << palavrasChave[rand() % 2] << "_" << nomeRua.str() << "_" << numeroRua % 200 << "_" << nomeBairro.str();
    string endereco = ss.str();

    return endereco;

}

// Gera 3 telefones aleatorios para cada estabelecimento
vector<int> geradorTelefones() {
    int telefone;
    vector<int> telefones;
    for(int i = 0; i < 3; i++) {
    telefone = rand() % 1500000 + 80000000;
    telefones.push_back(telefone);

    }

    return telefones;

}

// Gera uma posicao (X,Y) para cada estabelecimentos
vector<int> geradorPosXY() {
    int x = rand() % 2000;
    int y = rand() % 2000;

    vector<int> pos;
    pos.push_back(x);
    pos.push_back(y);

    return pos;

}

//Utiliza as funcoes anteriores para criar um estabelecimento aleatorio no arquivo de texto. No caso, toda vez que essa funcao for rodada, 11 novos estabelecimentos serao criados no arquivo de texto
void geradorLinhasTabela(){
    ofstream arq("estabelecimentos.txt", ios::app);
    for(int i = 0; i <= 10; i++) {
        arq << geradorID() << " " << geradorCategoria() << " " << geradorNomes() << " " << geradorEndereco() << " " << geradorTelefones()[0] << " " << geradorTelefones()[1] << " " << geradorTelefones()[2] << " " << geradorPosXY()[0] << " " << geradorPosXY()[1] << endl;

    }

}

// Transfere os dados do arquivo de texto para o C++
void carregaTabela() {
    ifstream arq("estabelecimentos.txt");

    do{
       arq >> tabela[numeroDeLidos].ID >> tabela[numeroDeLidos].CATEGORIA >> tabela[numeroDeLidos].NOME >> tabela[numeroDeLidos].ENDERECO >> tabela[numeroDeLidos].TEL1 >> tabela[numeroDeLidos].TEL2 >> tabela[numeroDeLidos].TEL3 >> tabela[numeroDeLidos].posX >> tabela[++numeroDeLidos].posY;
               listaID[numeroDeLidos] = tabela[numeroDeLidos].ID;
               listaCategoria[numeroDeLidos] = tabela[numeroDeLidos].CATEGORIA;
               listaNome[numeroDeLidos] = tabela[numeroDeLidos].NOME;
               listaEndereco[numeroDeLidos] = tabela[numeroDeLidos].ENDERECO;
               listaTel1[numeroDeLidos] = tabela[numeroDeLidos].TEL1;
               listaTel2[numeroDeLidos] = tabela[numeroDeLidos].TEL2;
               listaTel3[numeroDeLidos] = tabela[numeroDeLidos].TEL3;
               listaPosX[numeroDeLidos] = tabela[numeroDeLidos].posX;
               listaPosY[numeroDeLidos] = tabela[numeroDeLidos].posY;


    }while(arq.good());
}

//Funcao que calcula a distancia entre 2 pontos
int distancia(int x, int x0, int y, int y0) {
    return sqrt(pow((x-x0),2) + pow((y-y0),2));
}

int main() {
    // Exemplo de input:   SELECT B FROM LOJAS   *ENTER*
    //                     WHERE 400 500 > 1000  *ENTER*


    // Necessario para a utilizacao correta da funcao rand()
    srand(time(NULL));
    // Gera aleatoriamente mais estabelecimentos no arquivo de texto toda vez que o programa for rodado
    geradorLinhasTabela();
    // Transfere informacao acerca dos estabelecimentos do arquivo de texto para o C++
    carregaTabela();

    string input;
    cout << "Lista de Categorias: C(comercio), F(farmacia), B(banco), R(restaurante), L(lanchonete)" << endl;
    cout << "Lista de Comandos: SELECT, FROM, WHERE, EXIT" << endl;

    cout << "Digite o comando: ";
    getline(cin, input);

    // Repete o ciclo ate o usuario digitar EXIT no prompt de comando
    while(input != "EXIT") {
        // Analisa se o campo é de comércio
        if(input == "SELECT C FROM LOJAS") {
            cout << "WHERE ";
            string condicao;
            getline(cin, condicao);

            // Quebra a string dada como condicao em cada palavra que a compoe
            stringstream splitCondicao(condicao);
            string palavra;
            vector<string> listaTermosCondicao;
            while(splitCondicao >> palavra) listaTermosCondicao.push_back(palavra);

            // Utiliza a funcao stoi para converter a string de um numero para um inteiro
            // Foi considerado que o usuario escreva uma condicao do tipo: posX posY >,<,= tolerancia       Ex: 200 300 > 1000 ou 400 400 < 1500
            int X = std::stoi(listaTermosCondicao[0]);
            int Y = std::stoi(listaTermosCondicao[1]);
            int tolerancia = std::stoi(listaTermosCondicao[3]);

                for(int i = 1; i < (sizeof(listaPosX)/sizeof(listaPosX[0])); i++) {
                    if(condicao.find("<") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "C") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) < tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                }

            }else if(condicao.find(">") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "C") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) > tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;

                        }

            }else if(condicao.find("=") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "C") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) == tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                        }
                    }
                }

        listaTermosCondicao.clear();
        cout << "Digite o comando: ";
        getline(cin,input);

        //Analisa se o campo é de farmácia
        }else if(input == "SELECT F FROM LOJAS") {
            cout << "WHERE ";
            string condicao;
            getline(cin, condicao);

            stringstream splitCondicao(condicao);
            string palavra;
            vector<string> listaTermosCondicao;
            while(splitCondicao >> palavra) listaTermosCondicao.push_back(palavra);

            int X = std::stoi(listaTermosCondicao[0]);
            int Y = std::stoi(listaTermosCondicao[1]);
            int tolerancia = std::stoi(listaTermosCondicao[3]);

                for(int i = 1; i < (sizeof(listaPosX)/sizeof(listaPosX[0])); i++) {
                    if(condicao.find("<") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "F") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) < tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                }

            }else if(condicao.find(">") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "F") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) > tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;

                        }

            }else if(condicao.find("=") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "F") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) == tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                        }
                    }
                }

        listaTermosCondicao.clear();
        cout << "Digite o comando: ";
        getline(cin,input);

        //Analisa se o campo é de banco
        }else if(input == "SELECT B FROM LOJAS") {
            cout << "WHERE ";
            string condicao;
            getline(cin, condicao);

            stringstream splitCondicao(condicao);
            string palavra;
            vector<string> listaTermosCondicao;
            while(splitCondicao >> palavra) listaTermosCondicao.push_back(palavra);

            int X = std::stoi(listaTermosCondicao[0]);
            int Y = std::stoi(listaTermosCondicao[1]);
            int tolerancia = std::stoi(listaTermosCondicao[3]);

                for(int i = 1; i < (sizeof(listaPosX)/sizeof(listaPosX[0])); i++) {
                    if(condicao.find("<") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "B") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) < tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                }

            }else if(condicao.find(">") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "B") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) > tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;

                        }

            }else if(condicao.find("=") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "B") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) == tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                        }
                    }
                }

        listaTermosCondicao.clear();
        cout << "Digite o comando: ";
        getline(cin,input);

        //Analisa se o campo é de restaurante
        }else if(input == "SELECT R FROM LOJAS") {
            cout << "WHERE ";
            string condicao;
            getline(cin, condicao);

            stringstream splitCondicao(condicao);
            string palavra;
            vector<string> listaTermosCondicao;
            while(splitCondicao >> palavra) listaTermosCondicao.push_back(palavra);

            int X = std::stoi(listaTermosCondicao[0]);
            int Y = std::stoi(listaTermosCondicao[1]);
            int tolerancia = std::stoi(listaTermosCondicao[3]);

                for(int i = 1; i < (sizeof(listaPosX)/sizeof(listaPosX[0])); i++) {
                    if(condicao.find("<") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "R") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) < tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                }

            }else if(condicao.find(">") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "R") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) > tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;

                        }

            }else if(condicao.find("=") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "R") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) == tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                        }
                    }
                }

        listaTermosCondicao.clear();
        cout << "Digite o comando: ";
        getline(cin,input);

        //Analisa se o campo é de lanchonete
        }else if(input == "SELECT L FROM LOJAS") {
            cout << "WHERE ";
            string condicao;
            getline(cin, condicao);

            stringstream splitCondicao(condicao);
            string palavra;
            vector<string> listaTermosCondicao;
            while(splitCondicao >> palavra) listaTermosCondicao.push_back(palavra);

            int X = std::stoi(listaTermosCondicao[0]);
            int Y = std::stoi(listaTermosCondicao[1]);
            int tolerancia = std::stoi(listaTermosCondicao[3]);

                for(int i = 1; i < (sizeof(listaPosX)/sizeof(listaPosX[0])); i++) {
                    if(condicao.find("<") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "L") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) < tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                }

            }else if(condicao.find(">") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "L") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) > tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;

                        }

            }else if(condicao.find("=") != std::string::npos && listaPosX[i] != 0 && listaCategoria[i] == "L") {
                        if(distancia(X,listaPosX[i],Y,listaPosY[i]) == tolerancia) {
                        stringstream ss;
                        ss << "ID: " << listaID[i] << " | Categoria: " << listaCategoria[i] << " | Nome: " << listaNome[i] << " | Endereco: " << listaEndereco[i] << " | Tel 1: " << listaTel1[i] << " | Tel 2: " << listaTel2[i] << " | Tel 3: " << listaTel3[i] << " | Distancia ate voce: " << distancia(X,listaPosX[i],Y,listaPosY[i]);
                        string nome = ss.str();
                        cout << nome << endl;
                        }
                    }
                }

        listaTermosCondicao.clear();
        cout << "Digite o comando: ";
        getline(cin,input);

        }else
        getline(cin,input);
    }

    return 0;
}










