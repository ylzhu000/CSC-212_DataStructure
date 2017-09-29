//Yanlin Zhu
//Email: yzhu000@citymail.cuny.edu
//CSC212 KL - 34592

#include <iostream>
#include <math.h>
#include "sequence2.h"
#include <assert.h>
#include <algorithm>
#include <iterator>
using namespace std;

namespace main_savitch_4
{
	const sequence::size_type sequence::DEFAULT_CAPACITY;


	sequence::sequence(size_type initial_capacity)
	{
		data = new value_type[initial_capacity]; //Allocate dynamice memory from heap using the size of the default capacity.
		capacity = initial_capacity; //initialize and set the default capacity to member variable, capacity.
		used = 0; //initialize used to 0;
		current_index = 0; //initialize current_index to 0;

	}


	sequence::sequence(const sequence& source)
	{
		data = new value_type[source.capacity]; // Pointer, Data allocates memories, where its size is the source'capacity.
		capacity = source.capacity; // obtain the source's capacity
		used = source.used; //obtain the total number of items from the source's sequence.
		current_index = source.current_index; //obtain the current_index from the source's sequence.
	    copy(source.data, source.data+used, data); //obtain the source's data within the size of data+used.


	}

	sequence::~sequence()
	{

		delete [] data; // Release the dynamice memory that Data used.

	}

	void sequence::resize(size_type new_capacity)
	{
		value_type *larger_array;  // define pointer, larger_array.

		//check if capacity is equal to the new_capacitr, return nothing if it's true.
		if (new_capacity == capacity) 
			return; 
		
		//check if new_capacity is less than used, set new_capacity to used if it's true.
		if (new_capacity < used)
			new_capacity = used;
		
		//As a result, new_capacity ! = capacity, used < capacity
		//So need to resize of the size of the capacity. 

		  larger_array = new value_type[new_capacity]; //allocate dynamic memory, where the size is the new_capacity size.

		  copy(data, data + used, larger_array); // copy eveything from data to larger_array.
		  delete [] data; //free the dynamice memory that data used. 
	      
          data = larger_array; // make data points to larger_arrary to obtain the stuffs that larger_array obtain from the old data.
		  capacity = new_capacity; //update new_capacity to capacity.


	}

	//The first item on the sequence becomes the current item.
    //but if the sequence is empty, then there is no current item.
	void sequence::start()
	{

		current_index = 0; 
	}

	//Pre-C: is_item() must be true.
	//Post-C: If the current item was already the last item in the
	//sequence, then there is no longer any current item. Otherwise, the new
	//current item is the item immediately after the original current item.
	void sequence::advance()
	{
		assert(is_item());
		++current_index;

	}


	void sequence::insert(const value_type& entry)
	{
		// check if capacity is full, call resize function if yes.
		if (used == capacity)
			resize(used + 1);

		//cset current_index to 0 if there's no current item.
		if (!is_item())
			current_index = 0;
		
		// a for loop to shift eveything one position to the right from current_index.
	    for (size_type i = used; i > current_index; i--)
		    data[i] = data[i - 1];

		
		data[current_index] = entry; // set the new item to current_index.
			 
		++used; // increment used by 1 since one new entry has been added.

	}


	void sequence::attach(const value_type& entry)
	{
		//check if the capacity is full, call resize function if yes.
		if (used == capacity)
			resize(used + 1);
		
		//check if there's a current item, if yes, set used -1 to current_index.
		if (!is_item())
			current_index = used - 1;

		// a for loop to shift everything one position to the right after current_index.
	   for (size_type i = used; i > current_index; --i)
		{		
				data[i] = data[i - 1];
		}
	    
		data[++current_index] = entry; //update current_index by 1 first to achieve inserting after current_index, then set new item to current_index.
		
		used++; // increment used by 1 since one new item has been added.
			
	}


	void sequence::remove_current()
	{
		// there must be a current item in order to remove.
		assert(is_item()); 

		// a for loop to move everything from current_index to the left.
		for (size_type i = current_index + 1; i < used; i++)
				data[i - 1] = data[i];
			
		used--; //decrement used by 1 since removed an item.
		
	}


	void sequence::operator =(const sequence& source)
	{

		value_type* new_data; // initialize a pointer call new_data.

		// check self-assignment, if yes, return nothing.
		if (this == &source)
			return;

		// if souce's capacity is not equal to capacity
		if (capacity != source.capacity)
		{
			new_data = new value_type[source.capacity]; //allocate dynamice memory where its size is the

		    delete[] data; // free data's dynamice memory
			data = new_data; // make data points to new_data, where its size is source's capacity
			capacity = source.capacity; // update capacity to source's capacity
		}

		used = source.used; // update used to source's used.
		current_index = source.current_index; // update current_index to source's current_index.
	    copy(source.data, source.data + source.used, data); // copy eveything from source's data to data.
	}

	// reutrn the total number of items are currently in the sequence bag.
	sequence::size_type sequence::size() const
	{

		return used;
	}

	// A true return value indicates that there is a valid
    // "current" item that may be retrieved by activating the current
    // member function (listed below). A false return value indicates that
    // there is no valid current item.
	bool sequence::is_item() const
	{

		return (current_index < used);
	}

	// Precondition: is_item( ) returns true.
	// Postcondition: The item returned is the current item in the sequence.
	sequence::value_type sequence::current() const
	{
		assert(is_item());
            return data[current_index];

	}




}