#include "list.h"
#include <stddef.h> // for NULL
#include <stdlib.h> // for malloc
#include <stdio.h> // for printf
#include <assert.h> // for assert

list list_create() {
	list lst=malloc(sizeof(node));
	(*lst)=NULL;
	return lst;
}

void list_insertStart(list lst, node insert) 
{
	assert(list_valid(lst)); 
	assert(node_getNext(insert) == NULL);
	node_setNext(insert, *lst);
	*lst = insert;
}

	
	
	// Make sure there is no endless loop
	// TODO: insert the "insert" node at the start of the list
	// Algorithm:
	//      Make sure that the insert node is a single node... not a list
	//			i.e. insert's next pointer is NULL.
	//      Make the next pointer of the insert node is the old head of the list
	//		Make the insert node the new head of the list


void list_insertEnd(list lst,node insert) {
	assert(list_valid(lst));
	assert(node_getNext(insert) == NULL); 
	 // Make sure there is no endless loop
	if ((*lst)==NULL) {
		// Special case for null lists
		(*lst)=insert;
		return;
	}
	node tail=list_getTail(lst); // Find the tail of the list
	assert(node_getNext(insert)==NULL); // Ensure you are only adding one node to the list
	node_setNext(tail,insert); // Add the current node at the tail
}



void list_insertOrder(list lst,node insert) {
	assert(list_valid(lst));
	assert(node_getNext(insert) == NULL);

	if (*lst == NULL)
	{
		 *lst = insert;
    } else if (node_comparePayload(*lst, insert) >= 0) {
        node_setNext(insert, *lst);
        *lst = insert;
    } else {
        node prev = NULL;
        node curr = *lst;
        while (curr != NULL && node_comparePayload(curr, insert) < 0) {
            prev = curr;
            curr = node_getNext(curr);
        }
        if (prev != NULL) {
            node_setNext(insert, curr);
            node_setNext(prev, insert);
        }
    }
}
	
	 // Make sure there is no endless loop
	// TODO: insert the "insert" node in payload order, from least at the head to greatest at the tail
	// Algorithm:
	//    Make sure that the insert node is a single node... not a list
	//    If the list is empty, 
	//        add the insert node to the start of the list and return
	//    If the payload of the insert node is less than the payload of the head of the list,
	//        then just insert the insert node at the beginning of the list 
	//        and you are done.
	//    Loop through the list; starting at the head node,
	//		 while the current node has a next node AND
	//          the payload of the next node is less than the payload of the insert node,
	//		 		increment the node by going to the next node in the list
	//    When this loop ends, there are two possible outcomes:
	//       1. You got to the tail of the list, 
	//           so the insert payload is bigger than all nodes in the list. 
	//           In this case, add the insert node to the end of the list
	//           and you are done.
	//       2. You got to a node whose payload is smaller than the insert payload,
	//           but whose next node has a payload which is greater than
	//           the insert payload. In this case, you need to put the
	//           insert node after this node, but before what is currently
	//           defined as this node's next node. (That means you have to
	//           update both this node's next pointer, and the insert node's
	//           next pointer.)


node list_getTail(list lst) {
	assert(list_valid(lst)); // Ensure no endless loop
	if ((*lst)==NULL) return NULL; // Null list has no tail
	node nde=(*lst);
	while(node_hasNext(nde)) {
		nde=node_getNext(nde);
	}
	return nde;
}

int list_size(list lst) {
	if ((*lst)==NULL) return 0; // Nothing in the list
	int size=1; // at least one node
	node nde=(*lst);
	while(node_hasNext(nde)) {
		size++;
		nde=node_getNext(nde);
		assert(size<1000); // In case there is an endless loop
	}
	return size;
}

bool list_valid(list lst) {
	node *visited=malloc(sizeof(node)*list_size(lst));
	int n=0;
	node nde=(*lst);
	while(nde!=NULL) {
		for(int i=0;i<n;i++) {
			if (visited[i]==nde) {
				free(visited);
				return false; // already visited this node!
			}
		}
		visited[n++]=nde;
		nde=node_getNext(nde);
	}
	free(visited);
	return true;
}

void list_print(char *prefix,list lst) {
	assert(list_valid(lst)); // Ensure no endless loop
	if ((*lst)==NULL) printf("%s<empty>\n",prefix);
	else {
		node nde=*lst;
		printf("%s",prefix);
		while(node_hasNext(nde)) {
			node_print(nde);
			nde=node_getNext(nde);
		}
		node_print(nde);
		putchar('\n');
	}
}

void list_free(list lst) {
	if (*lst) node_free(*lst); // Only free the nodes if the list is not empty
	free(lst);
}