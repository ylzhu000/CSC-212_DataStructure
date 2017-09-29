// FILE: pqueue2.cxx
// IMPLEMENTS: PriorityQueue (See pqueue2.h for documentation.)
//-- IMPLEMENTED BY: (name and email address)
//
// NOTE: You will need -lm at the end of your compile line to pick up
// the math library!

// INVARIANT for the PriorityQueue Class:
//   1. The member variable many_items is the number of items in the
//      PriorityQueue.
//   2. The items themselves are stored in the member variable heap,
//      which is a partially filled array organized to follow the usual
//      heap storage rules from Chapter 11 of the class notes.
// NOTE: Private helper functions are implemented at the bottom of this
// file along with their precondition/postcondition contracts.

#include <assert.h>    // Provides assert function
#include <iomanip>   // Provides setw
#include <iostream>  // Provides cin, cout
#include <math.h>      // Provides log2
#include "pqueue2.h"

using namespace std;

PriorityQueue::PriorityQueue()
{
	many_items = 0; //Initialize many_item to 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	heap[many_items].data = entry; // Store the entry to the heap array.
	heap[many_items].priority = priority; // Store the priority to the heap's priority.

	// Check if there's no items.
	if (many_items == 0)
	{
		many_items++; // Simplily increment many_items by 1 if there just the new entry.
	}

	// If there are more items other than the new entry,
	else
	{
		unsigned int total_items = many_items; // Create a temporary variable to hold the current number of items.
		many_items++; // Increment many_items by 1. 

		// Use a while loop to adjust the priority with parent node.
		while (parent_priority(total_items) < priority)
		{
			swap_with_parent(total_items); // Call swap function if new current priority is greater than the parent node. 
			total_items = parent_index(total_items); // Update total_items so can keep compare until the current priority finish adjusting.
		}	
	}
}

// note: treat it as the combination of top() and pop()
PriorityQueue::Item PriorityQueue::get_front()
{
	assert(many_items > 0); 

	// Check if many_item is just 1.
	if (many_items == 1)
	{
		Item front = heap[0].data; // Create a temporary variable to store the first item of heap.
		many_items--; // Decrement many_items.
		return front; // Return the first item.
	}

	// If there's more than one item,
	else
	{
		
		Item front = heap[0].data; // Create a temporary variable to store the first item of heap.
		heap[0] = heap[many_items - 1]; // Then, move the last item to first position. 
		unsigned int priority = heap[many_items - 1].priority; // Set the last item's priority to current priority to start adjust the heap.
		unsigned int i = 0; // Initialize i to 0.

		// Use a while loop to adjust the priority if last item is less than parents or children.
		while ((i < many_items) && !is_leaf(i) && big_child_priority(i) > priority)
		{

			unsigned int big_index_child = big_child_index(i); // First, determine which left or right child has greater priority.
			swap_with_parent(big_child_index(i)); // Then, Call the swap_with_parent to determine if the value of child is greater than the parent(swap if it is).
			i = big_index_child; // Update i to keep compare.
		}

        many_items--; // Decrement many_items by one. 
		return front; // Return the value of the first item.
	}
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function
// returns true. Otherwise the function returns false.
{
	if ((2 * i + 1) >= many_items) // Check if left child is greater or equal to the total numbers of items. 
		return true; // Return true if it is, which means no left children.

	else
		return false; // Otherwise, return false, which means there's leaf.
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
	assert(i > 0 && (i < many_items)); // size_t i has to be greater than 0 and less than many_items.
	return (i - 1) / 2; // Reutrn the index of the parent of heap[i] using parent's formula.
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
	return heap[(i - 1) / 2].priority; // Return the priority of the parent of heap[i] using parent's formula.
}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children.
// This is the child with the larger priority.
{
	assert(!is_leaf(i)); 

	// Check if right child is less than many_items.
	if ((2 * i + 2) < many_items)
	{
		// Check if the left child's priority is greater than right's.
		if (heap[(2 * i) + 1].priority > heap[(2 * i) + 2].priority)
		{
			// Return left child's index if yes.
			return (2 * i) + 1;
		}

		else
		{
			// Return right child's index otherwise.
			return (2 * i) + 2;
		}
	}

	// If there's no right child, just return the left child, no need to compare.
	else
	{
		return(2 * i) + 1;
	}
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
	assert(!is_leaf(i)); 
	return heap[big_child_index(i)].priority; // Return the value heap[big_child_index(i)].priority.
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
	assert(i > 0 && i < many_items); // size_t i has to be greater than 0 and less than many_items.
	OneItemInfo temp_parent_value = heap[parent_index(i)]; // Create a temporary variable to hold parent value of heap[i].
	OneItemInfo temp_child_value = heap[i]; // Create a temporary variable to hold the value of heap[i].
	
    // Swap Process
	heap[i] = temp_parent_value; // Set the value of temp_parent_value to heap[i].                            
	heap[parent_index(i)] = temp_child_value; // Set the value of temp_child_value to heap[parent_index(i)].  
}

void PriorityQueue::print_tree(const char message[], size_t i) const
// Postcondition: If the message is non-empty, then that has been written
// to cout. After the message, the portion of the heap with root at node
// node i has been written to the screen. Each node's data is indented
// 4*d, where d is the depth of the node.
// NOTE: The default argument for message is the empty string, and the
// default argument for i is zero. For example, to print the entire
// tree of a PriorityQueue p, with a message of "The tree:", you can call:
//     p.print_tree("The tree:");
// This call uses the default argument i=0, which prints the whole tree.
{
	const char NO_MESSAGE[] = "";
	size_t depth;

	if (message[0] != '\0')
		cout << message << endl;

	if (i >= many_items)
		cout << "NO NODES." << endl;
	else
	{
		depth = int(log(double(i + 1)) / log(2.0));
		cout << setw(depth * 4) << "";
		cout << heap[i].data;
		cout << " (priority " << heap[i].priority << ")" << endl;
		if (2 * i + 1 < many_items)
			print_tree(NO_MESSAGE, 2 * i + 1);
		if (2 * i + 2 < many_items)
			print_tree(NO_MESSAGE, 2 * i + 2);
	}

}