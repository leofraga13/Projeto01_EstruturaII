//Leonardo Fraga TIA:32158841 -- Estrutura de Dados II Projeto01

#include "Arvore.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;


void destruirArvore(No* no) {
    if (no == NULL) {
        return;
    }
    destruirArvore(no->getEsquerda());
    destruirArvore(no->getDireita());
    delete no;
}

Registro BuscarMaiorSalario(No* no) {
    Registro maior = no->getValor();

    stack<No*> pilha;
    pilha.push(no);

    while (!pilha.empty()) {
        No* atual = pilha.top();
        pilha.pop();

        if (atual->getValor().remuneracao_bruta > maior.remuneracao_bruta) {
            maior = atual->getValor();
        }

        if (atual->getDireita() != nullptr) {
            pilha.push(atual->getDireita());
        }
        if (atual->getEsquerda() != nullptr) {
            pilha.push(atual->getEsquerda());
        }
    }

    return maior;
}

Registro BuscarMenorSalario(No* no) {
    Registro menor = no->getValor();
    stack<No*> pilha;
    pilha.push(no);

    while (!pilha.empty()) {
      No* atual = pilha.top();
      pilha.pop();

      if(atual->getValor().remuneracao_bruta != 0){
        if (atual->getValor().remuneracao_bruta < menor.remuneracao_bruta) {
          menor = atual->getValor();
        }
      }
      
      if (atual->getDireita() != nullptr) {
        pilha.push(atual->getDireita());
      }
      if (atual->getEsquerda() != nullptr) {
        pilha.push(atual->getEsquerda());
      }
    }
    return menor;
  }

float montanteGasto(No* no){
  float total = 0;
  stack<No*> pilha;
  
    pilha.push(no);
    while (!pilha.empty()) {
      No* atual = pilha.top();
      pilha.pop();

      if (atual->getValor().cargo == "PROCURADOR DO MUNICIPIO II") {
        total = total + atual->getValor().remuneracao_bruta;
      }

      if (atual->getDireita() != nullptr) {
        pilha.push(atual->getDireita());
      }
      if (atual->getEsquerda() != nullptr) {
        pilha.push(atual->getEsquerda());
      }
    }

  return total;
}

float mediaAssessores(No* no, string tipo){
  float media;
  float total = 0;
  float num_funcionarios = 0;

  stack<No*> pilha;
  
    pilha.push(no);
    while (!pilha.empty()) {
      No* atual = pilha.top();
      pilha.pop();

      if (atual->getValor().cargo == tipo) {
        num_funcionarios++;
        total = total + atual->getValor().remuneracao_bruta;
      }

      if (atual->getDireita() != nullptr) {
        pilha.push(atual->getDireita());
      }
      if (atual->getEsquerda() != nullptr) {
        pilha.push(atual->getEsquerda());
      }
    }

  media = total/num_funcionarios;
  return media;
}

float gastoGabinetePrefeito(No* no){
  float total = 0;
  stack<No*> pilha;
  
    pilha.push(no);
    while (!pilha.empty()) {
      No* atual = pilha.top();
      pilha.pop();

      if (atual->getValor().unidade == "GABINETE DO PREFEITO") {
        total = total + atual->getValor().remuneracao_bruta;
      }

      if (atual->getDireita() != nullptr) {
        pilha.push(atual->getDireita());
      }
      if (atual->getEsquerda() != nullptr) {
        pilha.push(atual->getEsquerda());
      }
    }

  return total;
}

float mediaGabinetePrefeito(No* no){
  float media;
  float total = 0;
  float num_funcionarios = 0;

  stack<No*> pilha;
  
    pilha.push(no);
    while (!pilha.empty()) {
      No* atual = pilha.top();
      pilha.pop();

      if (atual->getValor().unidade == "GABINETE DO PREFEITO") {
        num_funcionarios++;
        total = total + atual->getValor().remuneracao_bruta;
      }

      if (atual->getDireita() != nullptr) {
        pilha.push(atual->getDireita());
      }
      if (atual->getEsquerda() != nullptr) {
        pilha.push(atual->getEsquerda());
      }
    }

  media = total/num_funcionarios;
  return media;
}

int totalFuncGabinete(No* no){

  float total = 0;

  stack<No*> pilha;
  
    pilha.push(no);
    while (!pilha.empty()) {
      No* atual = pilha.top();
      pilha.pop();

      if (atual->getValor().unidade == "GABINETE DO PREFEITO") {
        total++;
      }

      if (atual->getDireita() != nullptr) {
        pilha.push(atual->getDireita());
      }
      if (atual->getEsquerda() != nullptr) {
        pilha.push(atual->getEsquerda());
      }
    }

  return total;
}


int main() {
  ArvoreBST arv;
  int i;
  int cont = 0;
  int verifica = 0;
  string linha;
  Registro registro;
  int opcao = -1;

  while (opcao != 5) {
    cout << endl << "MENU:" << endl;
    cout << "1-Leitura de Dados" << endl;
    cout << "2-Analises de Dados" << endl;
    cout << "3-Remove Funcionario" << endl;
    cout << "4-Salvar Dados" << endl;
    cout << "5-Encerrar Aplicacao" << endl;
    cout << endl << "Digite a opcao:";
    cin >> opcao;

    if(opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5){
      cout<<"Opcao Invalida!!!";
    }
    else if (opcao == 1) {
      string arquivo;
      cout << "Digite o nome do arquivo que deseja ler: ";
      cin >> arquivo;

      ifstream fin(arquivo);

      if (!fin.is_open()) {
        cout << endl << "Nao foi possivel abrir o arquivo: " << arquivo << endl;
        return 1;
      }

      while (!fin.eof()) {
        getline(fin, linha);
        if (verifica != 0) {
          istringstream iss(linha);
          string data;
          while (getline(iss, data, ';')) {
            if (cont == 0) {
              cont++;
            } else if (cont == 1) {
              registro.nome = data;
              cont++;
            } else if (cont == 2) {
              if (data != "") {
                registro.cargo = data;
              }
              cont++;
            } else if (cont == 3) {
              if (data != "") {
                registro.cargo = data;
              }
              cont++;
            } else if (cont == 4) {
              cont++;
            } else if (cont == 5) {
              cont++;
            } else if (cont == 6) {
              if(data.empty()) {
                 data = "0,00";
              }
              if(data == "              "){
                data = "0,00";
              }
    
              size_t pos = data.find('.');
              if (pos != string::npos) {
                data.erase(pos, 1);
              }
              
              size_t pos2 = data.find('.');
              if (pos2 != string::npos) {
                data.erase(pos2, 1);
              }
              data.replace(data.find(','), 1, ".");
              float saida = stof(data);
              registro.remuneracao_bruta = saida;
              cont++;
            }
            else if(cont == 7){
              registro.unidade = data;
              cont++;
            }
          }
          string chave = registro.nome;
          arv.inserir(chave, registro);
        }
        verifica = 1;
        cont = 0;
      }
      fin.close();
      cout << endl << endl << "Leitura bem Sucedida!!!" << endl << endl;
    } 
    else if (opcao == 2) {
      if(arv.getRaiz() == NULL){
        cout<<endl<<"Estrutura Vazia! Faca a Leitura de Dados!"<<endl;
      }
      else{
        cout<<endl<<endl<<"Analise de Dados"<<endl;
        // Analise de Dados 1:
        Registro maior_salario = BuscarMaiorSalario(arv.getRaiz());
        Registro menor_salario = BuscarMenorSalario(arv.getRaiz());
        cout<<endl<<"1-) Maior e Menor remuneracao bruta de todos os funcionarios"<<endl;
        cout<<endl<<"__________Maior Remuneracao Bruta__________"<<endl;
        cout<<"Nome: "<<maior_salario.nome<<endl<<"Remuneracao Bruta: R$"<<maior_salario.remuneracao_bruta<<endl<<"Cargo: "<<maior_salario.cargo<<endl<<"Unidade: "<<maior_salario.unidade;
        
        cout<<endl<<endl<<"__________Menor Remuneracao Bruta__________"<<endl;
        cout<<"Nome: "<<menor_salario.nome<<endl<<"Remuneracao Bruta: R$"<<menor_salario.remuneracao_bruta<<endl<<"Cargo: "<<menor_salario.cargo<<endl<<"Unidade: "<<menor_salario.unidade<<endl<<endl;

        // Analise de Dados 2:
        float montante_total = montanteGasto(arv.getRaiz());
        cout<<endl<<"2-) Montante Gasto com os Salarios do Cargo: PROCURADOR DO MUNICIPIO II"<<endl;
        cout<<endl<<endl<<"Total Gasto: R$"<<montante_total<<endl<<endl;

        // Analise de Dados 3:
        string assessor1 = "ASSESSOR I";
        float media_assessor1 = mediaAssessores(arv.getRaiz(),assessor1);
        cout<<endl<<"3-) Media Salarial do Cargo: ASSESSOR I"<<endl;
        cout<<endl<<endl<<"Media Salarial : R$"<<media_assessor1<<endl<<endl;

   
        // Analise de Dados 4:
        int func_gabinete = totalFuncGabinete(arv.getRaiz());
        float montante_gabinete = gastoGabinetePrefeito(arv.getRaiz());
        float media_gabinete = mediaGabinetePrefeito(arv.getRaiz());
        cout<<endl<<"4-) Montante Gasto e Media Salarial na Unidade do GABINETE DO PREFEITO"<<endl;
        cout<<endl<<"Total Gasto: R$"<<montante_gabinete<<endl<<endl;
        cout<<"Total Funcionarios: "<<func_gabinete<<endl<<endl;
        cout<<"Media Salarial : R$"<<media_gabinete<<endl<<endl;

        // Analise de Dados 5:
        string assessor2 = "ASSESSOR II";
        string assessor3 = "ASSESSOR III";
        string assessor4 = "ASSESSOR IV";
        string assessor5 = "ASSESSOR V";
        
        float media_assessor2 = mediaAssessores(arv.getRaiz(),assessor2);
        float media_assessor3 = mediaAssessores(arv.getRaiz(),assessor3);
        float media_assessor4 = mediaAssessores(arv.getRaiz(),assessor4);
        float media_assessor5 = mediaAssessores(arv.getRaiz(),assessor5);

        
        cout<<endl<<"5-) Diferenca na media Salarial entre os 5 tipos de CARGO de ASSESSOR"<<endl;
        cout<<endl<<endl<<"Media Salarial ASSESSOR I: R$"<<media_assessor1<<endl;
        cout<<"Media Salarial ASSESSOR II: R$"<<media_assessor2<<endl;
        cout<<"Media Salarial ASSESSOR III: R$"<<media_assessor3<<endl;
        cout<<"Media Salarial ASSESSOR IV: R$"<<media_assessor4<<endl;
        cout<<"Media Salarial ASSESSOR V: R$"<<media_assessor5<<endl<<endl<<endl;
      }
      
    }
    else if(opcao == 3){
      if(arv.getRaiz() == NULL){
        cout<<endl<<"Estrutura Vazia! Faca a Leitura de Dados!"<<endl;
      }
      else{
        string x;
        
        cout<<endl<<endl<<"Remove Funcionario"<<endl;
        cout <<endl<<"Digite o nome do funcionario que sera excluido: ";
        cin.ignore();
        getline(cin, x);
        No* resp = arv.excluir(arv.getRaiz(),x);
        arv.setRaiz(resp);
        
      }
    }
    else if(opcao == 4){
      
    }
    else if(opcao == 5){
      destruirArvore(arv.getRaiz());
      cout<<endl<<endl<<"Programa Encerrado e Dados Alocados Liberados";
    }
  }

  return 0;
}
