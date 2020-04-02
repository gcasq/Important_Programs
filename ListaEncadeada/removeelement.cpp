//remove the element in position x in a linked list
//  https://practice.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1/

Node* deleteNode(Node *head,int x)
{
    int i=1;
    struct Node *p,*q,*aux;
    p=head;q=head;
    if(x>1){
            while(i<x)
            {
                p=p->next;
                i++;
            }
            aux=p->next;
            i=1;
            while(i<x-1)
            {
                q=q->next;
                i++;
            }
            q->next=aux;
            
            free(p);
          return head; }
           
    else
    {
        
        head=head->next;
        free(p);
        
    return head;
    }
    
}
