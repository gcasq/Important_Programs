#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class newnode{
    private:
        pair<char,int> content;
        newnode *right;
        newnode *left;
        string cod;
    public:
        newnode(){right = NULL;
            left = NULL;}
        newnode(pair<char,int> content){
            this->content = content;
            right = NULL;
            left = NULL;
        }
        void copy(newnode& node){
            content = node.content;
            left = node.left;
            right = node.right;
        }
        void set_content(pair<char,int> content){
            this->content = content;
        }
        void set_left(newnode *left){
            this->left = left;
        }
        void set_right(newnode *right){
            this->right = right;
        }
        pair<char,int> get_pair(){
            return content;
        }
        newnode* get_left(){
		    return left;
	    }
        newnode* get_right(){
		    return right;
	    }
        void set_cod(string codigo){
            cod = cod + codigo;
        }
        string get_cod(){
            return cod;
        }
};

void decode_txt(newnode *raiz){
    newnode *aux = raiz;
    FILE *p;
    p = fopen("texto.hfm", "r");
    ofstream arq;
    arq.open("saída.txt");
    char ch;
    ch = fgetc(p);

    while(ch!=EOF){
        if(ch=='0'){
            aux=aux->get_left();
        }
        if(ch=='1'){
            aux=aux->get_right();
        }
        if(aux->get_pair().first != (int)NULL){
            arq << aux->get_pair().first;
            aux=raiz;
        }
        ch = fgetc(p);
    }
    fclose(p);
    arq.close();
}

void getorders(vector<pair<char,int>> &pre,vector<pair<char,int>> &sim){
    ifstream preord;
    int asciinumbpre,freqpre,asciinumbsim,freqsim;
    char chpre,chsim;
    preord.open("arvhuf.txt");
    if(!preord.is_open()){cout<<"Error"<<endl;return ;}//verifica se o arquivo abriu bem

     while(!preord.eof()){
        preord >> asciinumbpre >> freqpre >> asciinumbsim >> freqsim;
        chpre = asciinumbpre;
        chsim = asciinumbsim;
       if(preord.good()){
        pre.push_back(make_pair(chpre,freqpre));
        sim.push_back(make_pair(chsim,freqsim));
        }
    }
    preord.close();
}

void printpre (newnode *raiz)
{   
    cout<<raiz->get_pair().second<<"("<<raiz->get_pair().first<<")"<<" ";
    if (raiz->get_left() != NULL){printpre(raiz->get_left());}
    if (raiz->get_right() != NULL){printpre(raiz->get_right());}
} 

int search(vector<pair<char,int>> &arr, int strt, int end, pair<char,int> value)  
{  
    int i;  
    for (i = strt; i <= end; i++)  
    {  
        if (arr[i].second == value.second && (int)arr[i].first == (int)value.first)  
            return i;  
    }  
}  

newnode* buildTree(vector<pair<char,int>> &in, vector<pair<char,int>> &pre, int inStrt, int inEnd)  
{  
    static int preIndex = 0;  
  
    if (inStrt > inEnd)  
        return NULL;  
  
    newnode *tNode;
    tNode = new newnode(pre[preIndex++]);
  
    if (inStrt == inEnd)  
        return tNode;  
  
    int inIndex = search(in, inStrt, inEnd, tNode->get_pair());  
  
    
    tNode->set_left(buildTree(in, pre, inStrt, inIndex - 1));  
    tNode->set_right(buildTree(in, pre, inIndex + 1, inEnd));  
  
    return tNode;  
}  

int main(){
    vector<pair<char,int>> preorder;
    vector<pair<char,int>> inorder;

    getorders(preorder,inorder);//recupera a pre-ordem e ordem simétrica do arvhuf.txt

    int len = preorder.size();  
    
    newnode* raiz = buildTree(inorder, preorder, 0, len - 1);  

    decode_txt(raiz);

    return 0;
}