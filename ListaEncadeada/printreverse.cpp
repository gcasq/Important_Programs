struct Node* head;

void printfreverse(struct Node* head)
{
	struct Node *p;
	p=head;
	if(p == NULL)
	{
		return;
	}	
	p=p->next;
	printfreverse(p);
	printf("%d ",p->data);
		
}




