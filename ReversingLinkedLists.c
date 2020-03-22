struct Node *Reverse(struct Node *head){
	struct Node *temp = NULL, *nextNode = NULL;
	while(head){
		nextNode = head->next;
		head->next = temp;
		temp = head;
		head = nextNode;
	}
	return head;
}

Time complexity = O(n), Space complexity = O(1)
