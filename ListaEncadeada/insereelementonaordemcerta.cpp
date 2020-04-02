#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct Node{
	int valor;
	struct Node *prox;

}node;

node* insert(node *p,int b)
{
	node *aux,*c,*q;
	c=p;
	aux=(node *)malloc(sizeof(node));
	if(p==NULL)//se n tiver lista ainda
	{
		aux->prox=NULL;
		aux->valor=b;
		return aux;
	}
	else{   
		if(b<=p->valor)//se for o primeiro da lista
		{
			aux->prox=p;
			aux->valor=b;
			return aux;
		}
		else{
			while(b>p->valor){
			q=p;
			p=p->prox;
			if(p==NULL){break;}
			}	

			if(p==NULL){	aux->valor=b;
					q->prox=aux;
					aux->prox=NULL;
					return c;
					}//insere no final
			else{
					if(p==c){
					aux->valor=b;
					aux->prox=p;
					return aux;
					}//insere no começo
				
					else{
					q->prox=aux;
                	                aux->prox=p;
        	                        aux->valor=b;
	                                return c;	
					}
			}
		    }
	    }	
}

void print(node *p)
{
	if(p==NULL){cout << "lista vazia\n";}
		else{
			cout<<endl;
			while(1)
			{
				cout << p->valor<<" ";
				if(p->prox==NULL){break;}
				p=p->prox;
			}
		    }
		cout << endl;
}

void printreverse(node *p)
{
	if(p==NULL){cout << "lista vazia\n";}
	else{
		if(p->prox==NULL){cout << endl<<p->valor <<" " ;}
		else
		{
		printreverse(p->prox);
		cout<< p->valor <<" ";
		}
	}
}

node* deletes(node *p, int x) 
{
	node *c,*q;	
	c=p;
	if(p==NULL){cout << "lista vazia\n"; return NULL;}
	
	if(x==1){c=p->prox;free(p);return c;}
	while(x!=1)
	{	
		q=p;
		p=p->prox;
		x--;	if(p->prox==NULL&&x!=1){cout << "posicao invalida\n";return c;}
}

	if(p->prox==NULL){q->prox=NULL;free(p);return c;}

	q->prox=p->prox;free(p);
	return c;
}

int main()
{
	cout << "this is a linked list which puts integers in order immediatly! \n";
	int x=1,a;
	node *head=NULL;

	while(x!=5)
	{
	cout<< "\nchoose your option: \n1)insert an element\n2)deletes an element\n3)print list\n4)prints list reversed\n5)ends program:   ";
	cin >> x;
	switch(x)
	{
		case 1:
			cout << "\ninsira o elemento: ";
			cin >>a;
			head=insert(head,a);break;
		
		case 2:
			cout << "\ndigite a posicao do elemento que quer retirar:  ";
			cin >>a;
			head=deletes(head,a);break;
		
		case 3:
			print(head);break;
		
		case 4:
			printreverse(head);cout<<endl;break;		
	}
	}
}
