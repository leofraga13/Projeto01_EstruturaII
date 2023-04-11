//Leonardo Fraga TIA:32158841 -- Estrutura de Dados II Projeto01
#include <iostream>
#include <string>
using namespace std;

struct Registro {
  string nome;
  string cargo;
  float remuneracao_bruta;
  string unidade;

};

class No {
private:
    No* esquerda;
    No* direita;
    string chave;
    Registro valor;
    
public:
    No(string chave, Registro valor) {
        this->chave = chave;
        this->valor = valor;
        esquerda = nullptr;
        direita = nullptr;
    }

    // funções getters e setters
    string getChave() {
        return chave;
    }


    No* getEsquerda() {
        return esquerda;
    }

    No* getDireita() {
        return direita;
    }

    void setEsquerda(No* no) {
        esquerda = no;
    }

    void setDireita(No* no) {
        direita = no;
    }
    
    Registro getValor() {
        return valor;
    }

    void setChave(string k){
        chave = k;
    }
};

class ArvoreBST{
  private:
    No *raiz;

  public:
    ArvoreBST(){
      raiz = NULL;
    }
    
    void setRaiz(No* root){
      raiz = root;
    }

    No* getRaiz() {
      return raiz;
    }


  void inserir(string chave, Registro valor) {
    if (raiz == nullptr) {
        raiz = new No(chave, valor);
    } else {
        inserirAux(raiz, chave, valor);
    }
  }

  void inserirAux(No* no, string chave, Registro valor) {
    // se a chave a ser inserida é menor que a chave do nó atual, insere na sub-árvore esquerda
    if (chave < no->getChave()) {
        if (no->getEsquerda() == nullptr) {
            No* novo_no = new No(chave, valor);
            no->setEsquerda(novo_no);
        } else {
            inserirAux(no->getEsquerda(), chave, valor);
        }
    // se a chave a ser inserida é maior que a chave do nó atual, insere na sub-árvore direita
    } else if (chave > no->getChave()) {
        if (no->getDireita() == nullptr) {
            No* novo_no = new No(chave, valor);
            no->setDireita(novo_no);
        } else {
            inserirAux(no->getDireita(), chave, valor);
        }
    }
    // se a chave já existe na árvore, não faz nada (não é possível ter duas chaves iguais na BST)
}


  No* findMin(No* t){
        if(t == NULL)
            return NULL;
        else if(t->getEsquerda() == NULL)
            return t;
        else
            return findMin(t->getEsquerda());
    }



  No *excluir(No* t, string key){
      
    if (t == NULL) {
      cout << "Funcionario nao Encontrado!" << endl;
      return t;
    }   
    if (key < t->getChave())
      t->setEsquerda(excluir(t->getEsquerda(),key));
    else if (key > t->getChave())
      t->setDireita(excluir(t->getDireita(),key));
    else{ //encontramos o nó a ser removido
    //Caso1: o no a ser excluido nao tem filhos
      if (t->getEsquerda() == NULL and t->getDireita() == NULL){
        cout <<endl<< "Funcionario Removido!" << endl;
        delete(t);
        return NULL; //faz o pai apontar para NULL e o nó não faz mais parte da BST   
      }            
      else{ //Caso2: tem apenas um filho, a esquerda ou a direita
        if (t->getEsquerda() == NULL){
          No* temp = t->getDireita();
          cout <<endl<< "Funcionario Removido!" << endl;
          delete(t);
          return temp; //Faz o pai apontar para o único filho do nó
        }
        else if  (t->getDireita() == NULL){
          No* temp = t->getEsquerda();
          cout <<endl<< "Funcionario Removido!" << endl;
          delete(t);
          return temp; //Faz o pai apontar para o único filho do nó
        }
        else{ //Caso3: o no a ser excluido tem 2 filhos. Vamos escolher o menor dos maiores //para substituir o no que sera removido. Sucessor = menor no na sub-arvore da direita
          No* temp = findMin(t->getDireita()); 
          //Copia a chave do sucessor para o no que esta sendo removido
          t->setChave(temp->getChave());
            
          //Remove da arvore o sucessor!
          t->setDireita(excluir(t->getDireita(),temp->getChave()));
          
        }
      }
    }

    //retorna a raiz da arvore
    return t;
  }

};