#pragma once

#include <vector>
#include <utility>

class TabHashEncadeamento {
private:
    int m; // tamanho da tabela
    int n; // número de elementos na tabela
    // limiar para redimensionamento. quando n/m > limiar, redimensionar
    int limiar; 
    int redims; // número de redimensionamentos realizados

    std::vector<std::pair<int,int>> *tabela; // tabela hash
    // função hash
    int hash(int chave){
        int pos = chave % m;
        return pos;
    } 

    // redimensiona a tabela para o novo tamanho (novo_m)
      void redimensionar(int novo_m) {
        std::vector<std::pair<int,int>>*nova_tabela = new std::vector<std::pair<int,int>>[novo_m];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < tabela[i].size(); j++)
            {
                int pos = hash(tabela[i][j].first);
                nova_tabela[pos].push_back(tabela[i][j]);
            }
            
        }
        delete[] tabela;
        redims++;
        m = novo_m;        
        }
public:
    //Construtor: inicializa uma nova tabela com tamanho m
    TabHashEncadeamento(int tamanho, int limiar = 5){
        this->m = tamanho;
        this->limiar = limiar;
        this->redims = 0;
        this->n = 0;
    }

    //Destrutor: libera todos os recursos alocados para a tabela
    ~TabHashEncadeamento(){
        delete[] tabela;
    }
    
    //Insere um novo par (chave, valor) na tabela
    void inserir(int chave, int valor){
        if((n/m) > limiar);
        {
        redimensionar((2*m));
        }

        int pos = hash(chave);
        tabela[pos].push_back({chave,valor});
    }
    
    //Remove o par com a chave da tabela
    void remover(int chave){
        int pos =  hash(chave);
        for(int i = 0 ;i < tabela[pos].size();i++){
            if(tabela[pos][i].first == chave){
                tabela[pos].erase(tabela[pos].begin() + i);
                this->n--;
                return;
            }
        }
    }
    
    //Busca o valor associado a chave na tabela
    std::pair<int,int>& buscar(int chave){
        int pos = hash(chave);
        for(int i = 0;i < tabela[pos].size();i++){
            if(tabela[pos][i].first == chave){
                return tabela[pos][i];
            }
        }
        return invalido;
    }
    
    //Imprime a tabela
    void imprimir(){
        std::pair<int,int>temp;
        for(int i = 0; i < m;i++){
            std::cout<<"índice"<<i<<":"<< std::endl;
            for(int j = 0; j < tabela[i].size();j++){
                temp = tabela[i][j];
                std::cout<<"("<<temp<<","<<")"<< std::endl;
            }
        }
    }

    //Imprime informações sobre a tabela (m, n e fator de carga)
    void imprimir_info(){
        std::cout<<"informações da tabela :"<< std::endl;
        std::cout<<"tamanho :"<<m<<std::endl;
        std::cout<<"numero de elementos na tabela :"<<n<<std::endl;
        std::cout<<"limar :"<<limiar<<std::endl;
        std::cout<<"numero de redimensionamentos :"<<redims<<std::endl;
    }

    //par chave-valor inválido para indicar que a chave não foi encontrada
    std::pair<int,int> invalido;

    // retorna as chaves da tabela
    std::vector<int> chaves(){
        std::vector<int>vetor_chaves;
        for(int i = 0;i < m;i++){
            for(int j = 0;j < tabela[i].size();j++){
                vetor_chaves.push_back(tabela[i][j].first);
            }
        }
        return vetor_chaves;
    }

    // retorna todos os pares (chave, valor) da tabela
    std::vector<std::pair<int,int>> itens(){
        std::vector<std::pair<int,int>>vetor;
        for(int i = 0;i < m;i++){
            for(int j = 0;tabela[i].size();j++){
                vetor.push_back(tabela[i][j]);
            }
        }
        return vetor;
    }


};