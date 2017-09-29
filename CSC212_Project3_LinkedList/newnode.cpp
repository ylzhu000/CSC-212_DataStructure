// FILE: node1.cxx
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field, and the link in link_field.

#include "newnode.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
using namespace std;

namespace main_savitch_5
{
	size_t list_length(const node* head_ptr)
		// Library facilities used: cstdlib
	{
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			++answer;

		return answer;
	}

	void list_head_insert(node*& head_ptr, const node::value_type& entry)
	{
		head_ptr = new node(entry, head_ptr);
	}

	void list_insert(node* previous_ptr, const node::value_type& entry)
	{
		node *insert_ptr;

		insert_ptr = new node(entry, previous_ptr->link());
		previous_ptr->set_link(insert_ptr);
	}

	node* list_search(node* head_ptr, const node::value_type& target)
		// Library facilities used: cstdlib
	{
		node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				return cursor;
		return NULL;
	}

	const node* list_search(const node* head_ptr, const node::value_type& target)
		// Library facilities used: cstdlib
	{
		const node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				return cursor;
		return NULL;
	}

	node* list_locate(node* head_ptr, size_t position)
		// Library facilities used: cassert, cstdlib
	{
		node *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link();
		return cursor;
	}

	const node* list_locate(const node* head_ptr, size_t position)
		// Library facilities used: cassert, cstdlib
	{
		const node *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link();
		return cursor;
	}

	void list_head_remove(node*& head_ptr)
	{
		node *remove_ptr;

		remove_ptr = head_ptr;
		head_ptr = head_ptr->link();
		delete remove_ptr;
	}

	void list_remove(node* previous_ptr)
	{
		node *remove_ptr;

		remove_ptr = previous_ptr->link();
		previous_ptr->set_link(remove_ptr->link());
		delete remove_ptr;
	}

	void list_clear(node*& head_ptr)
		// Library facilities used: cstdlib
	{
		while (head_ptr != NULL)
			list_head_remove(head_ptr);
	}

	void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
		// Library facilities used: cstdlib
	{
		head_ptr = NULL;
		tail_ptr = NULL;

		// Handle the case of the empty list.
		if (source_ptr == NULL)
			return;

		// Make the head node for the newly created list, and put data in it.
		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;

		// Copy the rest of the nodes one at a time, adding at the tail of new list.
		source_ptr = source_ptr->link();
		while (source_ptr != NULL)
		{
			list_insert(tail_ptr, source_ptr->data());
			tail_ptr = tail_ptr->link();
			source_ptr = source_ptr->link();
		}
	}

	//The time complexity for this function is O(n) since a for loop is created to search the target in each node.
	//Since this function is to return the total # of target in the linklist, a for loop is necessary.
	//If there are n nodes, all the nodes would be going through to look for the target until there is a null link field.
	size_t list_occurrences(const node* head_ptr, const node::value_type& target)
	{
		const node *cursor; //Create a pointer called cursor to keep track of the link field.
		size_t cout_target = 0; //Initilize a counter called cout_target to cout the target items.

		//1. Set the head_ptr to cursor so it points to first node.
		//2. Search for the target until the pointer, cursor points to a null link field, which means that's the last node.
	    //If a target exist in the node list, increment the cout_target by 1.
		//Return count_target until the pointer, cursor point to a null link filed.
		//If the list is empty, return 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				cout_target++;

		return cout_target;

	}

	
	//The time complexity for this function is O(1) since it's just insert the entry at the tail.
	//Even there's a while loop to go through all the node's link, but the entry simply attach to the linklist
	//after reach the end of the tail of the linklist. In addition, this function use insert function, which its 
	//time complexity is O(1). Thus, insert function is being used after reach the tial node.
	void list_tail_attach(node*& head_ptr, const node::value_type& entry)
	{
		node * attach_ptr= new node; //Create a new node for tail node.
		
		attach_ptr = head_ptr; //Initialize the attach_ptr by setting attach_ptr equals to head_ptr;

		//If head_ptr points to null(0) node, then head = tail. Thus, Call list_head_insert function to insert the entry at the head.
		if (head_ptr == NULL)
		{
			list_head_insert(head_ptr, entry);
		}

		//If head_ptr points to not null node, attach the entry to the tail.
		else
		{
			while (attach_ptr->link() != 0) // If attact_ptr didn't to last node yet
			{
				attach_ptr = attach_ptr->link(); //keep point to next node.
			}
	        
			list_insert(attach_ptr, entry); //If this is the last node, use insert function to add the entry to the tail.
		}

    }
	
	//The time complexity for this function is O(1) since the function just simply delete the item at the tail.
	//Even though it needs to get the total length first, then call the list_locate to get the last entry 
	//then call the list _remove to remove the tail, but the time it takes to delete a node is just O(1).
	
	void list_tail_remove(node*& head_ptr)
	{

		size_t node_length = list_length(head_ptr); //Get the total length of the linklist.

		//If there's only one node, the tail is the same as the head. Then just remove the node that 
		//head_ptr points to by calling the list_head_remove. Finally, set head_ptr to null.
		if (node_length == 1)
		{
			list_head_remove(head_ptr);
			head_ptr = NULL;
		}

		//If there are more nodes, get the last node's position by calling list_locate then call
		//list_remove function to remove that node, which is the tail node.
		else
		{
			node * Get_Tail_PTR = list_locate(head_ptr, node_length - 1);

			list_remove(Get_Tail_PTR);
		}

	}


	//The time complexity for this function is O(n) since it needs to copy n front node through the for loop.
	//In order to copy the data from n front nodes, a for loop is necessary. Thus, if there are n nodes, the 
	//function needs to go thoguh n nodes. 
	node* list_copy_front(const node* source_ptr, std::size_t n)
	{
		node * new_head_ptr = new node; // create a new node for head_ptr
		 

		const node* cursor = source_ptr; //Initialize a pointer called cursor points to the source_ptr's link field.

		cursor = source_ptr->link();
		//Set up a for loop to copy the front (n - 1) items in the linklist.
		for (size_t count = 0; count < n; count++)
		{
			list_tail_attach(new_head_ptr, cursor->data()); //call list_tail_attach to get the front item.
			cursor = cursor->link(); //make the cursor points to next node's link field after get an item.
		}

		//Return the items in the new_head_ptr.
		return new_head_ptr;

	}


}