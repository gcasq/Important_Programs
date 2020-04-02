
//https://practice.geeksforgeeks.org/problems/print-linked-list-elements/1

void display(struct Node *head)
{
    struct Node *p;
    p=head;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;

    }
}
