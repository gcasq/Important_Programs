//obs: este e o jeito burro que eu fiz
Node* reverseList(Node *head)
{
    if(head==NULL){return NULL;}
else
{   
    if(head->next==NULL){return head;}
    else{
    struct Node *p,*q,*r;
    p=head->next;
    q=head;
    head->next=NULL;
    
    while(1)
    {
        r=p->next;
        p->next=q;
        q=p;
        p=r;
        if(p==NULL){break;}
    }
    return q;
    }
}

}

//obs: este e o jeito inteligente que usa recursão  

Node *reverseLol(Node *head, Node *prev){
if(head == NULL)
return prev;
Node* actualHead = reverseLol(head->next, head);
head -> next = prev;
return actualHead;

}
Node* reverseList(Node *head)
{
return(reverseLol(head, NULL));

}
