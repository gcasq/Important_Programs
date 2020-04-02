//add element at begining or ending
//   https://practice.geeksforgeeks.org/problems/linked-list-insertion/1/


Node *insertAtBegining(Node *head, int newData) {

   struct Node *aux=(struct Node*)malloc(sizeof(struct Node));
 if(head==NULL)
 {
    aux->data=newData;
    aux->next=NULL;
    return aux;
 }

 else{
   aux->data=newData;
   aux->next=head;
   return aux;}

}
// function appends the data at the end of the list
Node *insertAtEnd(Node *head, int newData)  {
   struct Node *p;
   p=head;
   struct Node *aux2=(struct Node*)malloc(sizeof(struct Node));

   if(head==NULL)
 {
    aux2->data=newData;
    aux2->next=NULL;
    return aux2;
 }
  else{
   while(1)
   {
       if(p->next==NULL){p->next=aux2;break;}
       p=p->next;
   }
   aux2->data=newData;
   aux2->next=NULL;
   return head;
}}

