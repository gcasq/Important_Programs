#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include<iomanip>
using namespace std; 
  
typedef struct node{
    char letter;
    int freq;
    struct node *esq;
    struct node *dir;
    string cod;
}newnode;

vector<pair<char,int>> create_table(FILE *p, int &tamanho){
    char ch;
    tamanho = 0;
    int novo = 1;
    vector<pair<char,int>> table;
    ch = fgetc(p);
    while(ch!=EOF){
        if(tamanho == 0){
            table.push_back(make_pair(ch,1));
            tamanho = 1;
        }else{
            for(int i=0; i<tamanho; i++){
                if(ch == table[i].first){
                    table[i].second++;
                    novo = 0;
                }
            }
            if(novo == 1){
                table.push_back(make_pair(ch,1));
                tamanho++;
            }
        }
        novo = 1;
        ch = fgetc(p);
    }
    return table;
}

void printpre (newnode *raiz)
{   
    cout<<raiz->letter <<"("<<raiz->freq<<")"<<" ";
    if (raiz->esq != (newnode*)NULL){printpre (raiz->esq);}
    if (raiz->dir != (newnode*)NULL){printpre (raiz->dir);}
}

class Compare { 
public: 
    bool operator()(newnode* a, 
                    newnode* b) 
    { 
        // Defining priority on 
        // the basis of frequency 
        return a->freq > b->freq; 
    } 
}; 

void createcod(newnode *raiz,string p, vector<pair<string, int>> &coded_table){
    if(raiz->letter==NULL){
    string pesq = p+'0';
    string pdir = p+'1';
    createcod(raiz->dir,pdir,coded_table);
    createcod(raiz->esq,pesq,coded_table);
    }
    else{
        raiz->cod = p;
        coded_table.push_back(make_pair(raiz->cod, raiz->letter));

    }

}

void merge3(vector<pair<string,int>>& lista, int inicio, int meio, int fim){
    int size_left = meio-inicio+1;
    int size_right = fim-meio;
    int top_left=0,top_right=0;
    int k, i, j;
    vector<pair<string,int>> left(size_left);
    vector<pair<string,int>> right(size_right);

    for(i = 0; i < size_left; i++)
    {
        left[i] = lista[inicio+i];
    }
    for(j = 0; j < size_right; j++)
    {
        right[j]=lista[meio+j+1];
    }
    for(k = inicio; k <= fim; k++)
    {
        if(top_left >= size_left){
            lista[k] = right[top_right];
            top_right++;
        }else if(top_right >= size_right){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].second <= right[top_right].second){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].second > right[top_right].second){
            lista[k] = right[top_right];
            top_right++;
        }
    }
}

void merge_sort3(vector<pair<string,int>>& lista, int inicio, int fim){
    if(inicio < fim)
    {
        int meio = (inicio+fim)/2;
        merge_sort3(lista, inicio, meio);
        merge_sort3(lista, meio+1, fim);
        merge3(lista, inicio, meio, fim);
    }
}

int busca_binaria(vector<pair<string,int>>& lista, int inicio, int fim, int chave){
    //calcula-se a metade da lista
    int meio = (inicio + fim)/2;
    //compara chave com o valor medio da lista, se for maior
    if(chave > lista[meio].second){
        //condição de parada(verifica se eu cheguei numa lista unitaria)
        if(fim - meio <=1){
            //compara a chave com esse unico elemento da lista
            if(lista[meio].second == chave){
                return meio;
            }else{
                return -1;
            }
            //caso nao chegeui em lista unitaria, refaço a busca a partir da metade até o final
        }else{
            busca_binaria(lista, meio, fim, chave);
        }
        //tudo aqui é analogo ao de cima
    }else if(chave < lista[meio].second){
        if(meio - inicio <=0){
            if(lista[meio].second == chave){
                return meio;
            }else{
                return -1;
            }
        }else{
            busca_binaria(lista, inicio, meio, chave);
        }
        //achei a chave
    }else if(chave == lista[meio].second){
        return meio;
    }
}

void coded_txt(vector<pair<string, int>> &coded_table, char *nome){
    FILE *p;
    p = fopen(nome,"r");
    ofstream arq;
    arq.open("texto.hfm");
    char ch;
    int chave, pos;
    ch = fgetc(p);
    while(ch!=EOF){
        chave = (int)ch;
        pos = busca_binaria(coded_table, 0, coded_table.size(), chave);
        arq << coded_table[pos].first;
        ch = fgetc(p);
    }
    fclose(p);
    arq.close();
}

void putpre (newnode *raiz, vector<pair<int,int>> &pre)
{   
    pre.push_back(make_pair((int)raiz->letter,raiz->freq));

    if (raiz->esq != NULL){putpre (raiz->esq,pre);}
    if (raiz->dir != NULL){putpre (raiz->dir,pre);}
}

void putsim (newnode *raiz, vector<pair<int,int>> &sim)
{
    if (raiz->esq != NULL){putsim (raiz->esq,sim);}
    sim.push_back(make_pair((int)raiz->letter,raiz->freq));
    if (raiz->dir != NULL){putsim (raiz->dir,sim);}
}

void writepre(newnode *raiz){
    vector<pair<int,int>> preorder;
    vector<pair<int,int>> simorder;

    putpre(raiz,preorder);
    putsim(raiz,simorder);

    ofstream arq;
    arq.open("arvhuf.txt");

    for(int i=0;i<preorder.size();i++){
        arq << preorder[i].first <<" "<<preorder[i].second<<" "<<simorder[i].first <<" "<<simorder[i].second<<endl;
    }
    arq.close();
}

int main() 
{ 
    FILE *p;
    char nome[] = "input.txt";
    p = fopen(nome, "r");
    int tamanho, first;
    first = 0;
    vector<pair<string, int>> coded_table;
    vector<pair<char,int>> table;
    vector<newnode> huff;
    priority_queue<newnode*, vector<newnode*>,Compare> priorq;

    table = create_table(p, tamanho);
    fclose(p);

    newnode teste;
    priorq.push(&teste);
    newnode *testee;
    testee = new newnode;
    priorq.push(testee);

    testee = new newnode;
    priorq.push(testee);

    while(!priorq.empty()){
        cout<<priorq.top()<<" ";
        priorq.pop();
    }

    for(int i=0;i<table.size();i++){
        newnode *aux;
        aux = new newnode;
        aux->letter = table[i].first;
        aux->freq = table[i].second;
        aux->dir=(newnode*)NULL;
        aux->esq=(newnode*)NULL;
        priorq.push(aux);
    }
    int auxx;
    while(priorq.size()!=1){
        auxx=0;
        newnode *aux;
        aux = new newnode;
        aux->esq = priorq.top();auxx+=priorq.top()->freq;
        priorq.pop();
        aux->dir = priorq.top();auxx+=priorq.top()->freq;
        priorq.pop();
        aux->letter = (char)NULL;
        aux->freq = auxx;
        priorq.push(aux);
    }
    printpre(priorq.top());
    createcod(priorq.top(),"",coded_table);
    merge_sort3(coded_table, 0, coded_table.size()-1);
    coded_txt(coded_table,nome);
    writepre(priorq.top());
    fclose(p);
}