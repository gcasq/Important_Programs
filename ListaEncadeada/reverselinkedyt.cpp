void reverselink(struct Node *p)
{
	struct Node *head;
	if(p->prox==NULL)
	{
		head=p;
		return ;
	}
	reverselink(p->next);
 	struct *r;	
	r=p->next;
	r->next=p;
	p->next=NULL;



}




