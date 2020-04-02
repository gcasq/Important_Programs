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
		aux->prox=p;
		aux->valor=b;
		return aux;			
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

node* deletes(node *p) 
{
	node *c,*ant;	
	c=p;
	if(p==NULL){cout << "lista vazia\n"; return NULL;}
	if(p->prox==NULL){free(p);return NULL;}
	while(p->prox!=NULL){		
					ant=p;
					p=p->prox;
				}
	ant->prox=NULL;
	free(p);
	return c;
}

int main()
{
	cout << "this is a linked list of a stack (pilha)! \n";
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
			head=deletes(head);break;
		
		case 3:
			print(head);break;
		
		case 4:
			printreverse(head);cout<<endl;break;		
	}
	}
}

