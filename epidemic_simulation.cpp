#include<iostream>
#include<string>
#include<time.h>
#include<vector>

#define maxcomercio 10

using namespace std;

class gosminha{
private:
    int estado; //0 - saudável, 1 - doente, 2 - recuperado, 3 - morto
    int diasinfectado;
    int numerodacasa;
public:
    gosminha(int estado){this->estado=estado;diasinfectado=0;numerodacasa=-1;}
    int getestado(){return estado;}
    int getdias(){return diasinfectado;}
    void changeestado(int estado){this->estado=estado;}
    void aumentadia(){diasinfectado++;}
    int getcasa(){return numerodacasa;}
    void putcasa(int numerodacasa){this->numerodacasa = numerodacasa;}
};

class disease{
private:
    const float taxacontam;           //todas as taxas, um número entre 0 e 1, com duas casas decimais
    const float duracaoemdias;
    const float taxamort;
    float tc,tm;
public:
    disease(float taxacontam,float duracaoemdias,float taxamort):taxacontam(taxacontam),duracaoemdias(duracaoemdias),taxamort(taxamort){
        tc = taxacontam * 10000;
        tm = taxamort * 10000;
    }
    float gettc(){return tc;}
    float getded(){return duracaoemdias;}
    float gettm(){return tm;}
    float gettaxacontam(){return taxacontam;}
    float gettaxamort(){return taxamort;}
};

class place{
private:
    const int capacidade;
    gosminha **nolocal;
    int qtdenolocal;

public:
    place(int capacidade):capacidade(capacidade){
        nolocal = new gosminha*[capacidade];
        qtdenolocal=0;
    }
    int getqtdenolocal(){return qtdenolocal;}
    int getcapacidade(){return capacidade;}
    void aumentaqtdenolocal(){qtdenolocal++;}
    void inserenolocal(gosminha* g){nolocal[qtdenolocal]=g;}
    gosminha* getpessoa(int k){return nolocal[k];}
    void reseta(){
        delete[] nolocal;
        nolocal = new gosminha*[capacidade];
        qtdenolocal=0;
    }
};

class casa:public place{
public:
    casa():place(3){}
};

class comercio:public place{

public:
    comercio():place(maxcomercio){}
};

class simulation{
private:
    int numcobaias,diassimu,diaatual,contaminadanoinicio,qtdecasas,qtdecomercio;
    int numsaudavel,numcont,numrec;
    vector<gosminha> cobaias;
    casa *c;
    comercio *com;
public:
    simulation(disease &d,int numcobaias,int diassimu,int contaminadanoinicio):numcobaias(numcobaias),diassimu(diassimu){
        this->contaminadanoinicio = contaminadanoinicio;
        numsaudavel = numcobaias - contaminadanoinicio;
        numcont = contaminadanoinicio;
        numrec = 0;
        diaatual=0;
        for(int i=0;i<numcobaias;i++){//gera o determinado numero de cobaias pro experimento
            gosminha *aux;
            aux=new gosminha(0);
            cobaias.push_back(*aux);
        }
        for(int i=0;i<contaminadanoinicio;i++){//determina aleatoriamente quais são as cobaias que começam contaminadas
            int x=rand()%numcobaias; //numero aleatorio entre 0 e numcobaias-1
            if(cobaias[x].getestado()==1){i--;}
            else{cobaias[x].changeestado(1);}
        }
        putcasas(d);
        generatecomercio(d);
        runsimu(d);
    }
    void putcasas(disease &d){
        if(numcobaias%3==0){qtdecasas = numcobaias/3;}
        else{qtdecasas = numcobaias/3+1;}
            c = new casa[qtdecasas];
            
        int j=0;
        while(cobaias[numcobaias-1].getcasa()==-1){
            int x = rand()%qtdecasas;
            if(c[x].getqtdenolocal()==c[x].getcapacidade()){continue;}
            else{
                cobaias[j].putcasa(x);
                c[x].inserenolocal(&cobaias[j]);
                c[x].aumentaqtdenolocal();
                j++;
            }
        }
    }
    void generatecomercio(disease &d){
        qtdecomercio =  (numcobaias / maxcomercio)+3;
        com = new comercio[qtdecomercio];
    }

    void runsimu(disease &d){
        for(diaatual=0;diaatual<diassimu;diaatual++){
            saemdecasa(d);
            contaminanocomercio(d);
            resetacomercio(d);

            saemdecasa(d);
            contaminanocomercio(d);
            resetacomercio(d);

            saemdecasa(d);
            contaminanocomercio(d);
            contaminaemcasa(d);
            atualizaereseta(d);
            relatorioparcial(d);
        }
        relatoriofinal(d);
    }

    void saemdecasa(disease &d){
        int x;
        for(int k=0;k<numcobaias;k++){
            x = rand()%qtdecomercio;
            while(com[x].getqtdenolocal()==maxcomercio){
                x = rand()%qtdecomercio;
            }
            com[x].inserenolocal(&cobaias[k]);
            com[x].aumentaqtdenolocal();
        }
    }

    void resetacomercio(disease &d){
        for(int k = 0;k<qtdecomercio;k++){
            com[k].reseta();
        }
    }

    void contaminanocomercio(disease &d){
        int aux,cont;
        for(int k=0;k<qtdecomercio;k++){
            cont=0;
            for(int l=0;l<com[k].getqtdenolocal();l++){
                if(com[k].getpessoa(l)->getestado()==1){
                    cont++;
                }
            }//conta qtos, no estabelecimento, estão contaminados
            for(int p=0;p<cont;p++){
                for(int l=0;l<com[k].getqtdenolocal();l++)
                {

                    if(com[k].getpessoa(l)->getestado()==1||com[k].getpessoa(l)->getestado()==2){continue;}
                    else{
                        aux = rand()%10000 +1; //numero entre 1 e 10000
                        if(aux<=d.gettc()){
                            com[k].getpessoa(l)->changeestado(1);
                            numcont++;numsaudavel--;
                        }   //contaminou
                    }
                }
            }
        }
    }

    void contaminaemcasa(disease &d){
        int aux,cont;
        for(int k=0;k<qtdecasas;k++){
            cont=0;
            for(int l = 0;l < c[k].getqtdenolocal();l++){
                if(c[k].getpessoa(l)->getestado()==1){
                    cont++;
                }
            }//conta qtos, na casa, estão contaminados

            for(int p=0;p<cont;p++){
                for(int l=0;l<c[k].getqtdenolocal();l++)
                    {

                        if(c[k].getpessoa(l)->getestado()==1||c[k].getpessoa(l)->getestado()==2){continue;}
                        aux = rand()%10000 +1; //numero entre 1 e 10000
                        if(aux<=d.gettc()){
                            c[k].getpessoa(l)->changeestado(1);
                            numcont++;numsaudavel--;
                        }//contaminou
                    }
            }
        }
    }

    void atualizaereseta(disease &d){
        for(int k = 0;k<qtdecomercio;k++){
            com[k].reseta();
        }
        for(int k=0;k<numcobaias;k++){
            if(cobaias[k].getestado()==1){
                cobaias[k].aumentadia();
                if(cobaias[k].getdias()==d.getded()){
                    cobaias[k].changeestado(2);numcont--;numrec++;
                }
            }
        }
    }

    void relatoriofinal(disease &d){
        cout << "Doença: \n\tTaxa de infecção: "<<d.gettaxacontam()*100<<"%\n\tTaxa de mortalidade: "<<d.gettaxamort()*100<<"%"<<endl<<endl;
        cout << "Quantidade de habitantes: " << numcobaias<<endl<<endl;
        cout << "Numero dos que permaneceram saudáveis o tempo inteiro: "<< numsaudavel<<endl;
        cout << "Numero dos que permaneceram contaminados no final: "<< numcont<<endl;
        cout << "Numero dos que se recuperaram: "<< numrec<<endl;
    }

    void relatorioparcial(disease &d){
        cout <<diaatual;
        cout << " "<< numsaudavel;
        cout << " "<< numcont;
        cout << " "<< numrec<<endl;
    }
};

int main(){

    srand((unsigned)time(NULL));
    //x=rand()%10000+1; numero aleatorio entre 1 e 10000

    disease coronavirus(0.02,10,0);
    simulation s1(coronavirus,500000,100,10);

    return 0;
}