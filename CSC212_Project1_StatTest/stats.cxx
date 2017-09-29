// FILE: newpoint.cxx
// CLASS IMPLEMENTED: point (See newpoint.h for documentation.)

#include <iostream>
#include <math.h>
#include "stats.h"
#include <assert.h>
using namespace std;

namespace main_savitch_2C
{
	//This function initialize all prviate members to 0.
	statistician::statistician()
	{
		count = 0;
		total = 0.0;
		tinyest = 0.0;
		largest = 0.0;
	}

	//This function compute: 1. Sum of all numbers in the sequence; 2.Total numbers in the 
	//sequence; 3. Min and Max of the sequence;
	void statistician::next(double r)
	{

		//Sum up all numbers in the sequence.
		total = r + total;  

	    //The r set to min and max when count equal to zero.
		if (count == 0) 
		{	
			largest = r;
			tinyest = r;
		}

		// Increment count by 1.
		++count; 

		//1. After count is greater than zero, r starts to compare with min and max;
		//2. r will set to be the largest if r is greater than the current largest.
		//Otherwise, r will set to tinyest if r is less than the current tinyest.
	    if(count>0) 
		{
			if (largest < r)
				largest = r;

			else if (tinyest > r)
				tinyest = r;
		}
	
     }

	//The function reset all private member variables to 0.
	void statistician::reset()
	{
		   count = 0;
		   total = 0.0;
		   tinyest = 0.0;
		   largest = 0.0;

	}

	//This function return the total numbers in the sequence, which is the length of the sequence.
	int statistician::length() const
	{
		   return count;

	}
	
	//This function return the sum of all numbers in the sequence;
	double statistician::sum() const
	{
		   return total;
	}

	//The function return the mean of all numbers in the sequence only if the length of the sequence
	//is greater than zero;
	double statistician::mean() const
	{
		 assert(length() > 0);
		    return total / count;
	}

	//The function return the minimum of the sequence if the length of the sequence is equal
	//or greater than zero.
	double statistician::minimum() const
	{
		 assert(count >= 0);
		 	return tinyest;
	}

	//The function return the maximum of the sequence if the length of the sequence is equal
	//or greater than zero.
	double statistician::maximum() const
	{
		assert(count >=0);
			return largest;
	}

	//The function returns all the numbers that s1 and s2 contain.
	statistician operator +(const statistician& s1, const statistician& s2)
	{

		//Initialize an object call combine from the class.
		statistician combine; 

		//s2 is returned if the length of s1 is zero.
		if (s1.length() == 0)
			return s2;

		//s1 is returned if the length of s2 is zero.
		if (s2.length() == 0)
			return s1;
		
		//The length of combine is the total length of s1 + s2 in the sequence.
		combine.count = s1.length() + s2.length();

		//The sum of the combine is the total sum of s1 + s2 in the sequence.
		combine.total = s1.sum() + s2.sum();

		//If the min in s2 is greater than s1's, then the min in s1 is set to the min is combine.
		if (s2.minimum() > s1.minimum())
			combine.tinyest = s1.minimum();
		
		//Otherwise, the the min in s2 is set to the min is combine.
		else
			combine.tinyest = s2.minimum();

		//If the max in s2 is greater than s1's, the max in s2 is set to the max is combine.
		if (s2.maximum() > s1.maximum())
			combine.largest = s2.maximum();

		//Otherwise, the max in s1 is set to the max is combine.
		else
			combine.largest = s1.maximum();

		return combine;


	}

	//The function is returned the same number that s does, but each number has been multiplied by the scale number.
	statistician operator *(double scale, const statistician& s)
	{
		//Initialize an object called combine from the class.
		statistician combine;

		//The sum of combine is multiply by the sum of s and the scale to get the sum of combine.
		combine.total = scale * s.sum();

		//The length of combine remain the same.
		combine.count = s.length();

		//If the scale is less than 0(negative), the largest in s now is the smallest by multiplying the scale 
		//so set that number to the smallest number in combine.
		if (scale < 0)
			combine.tinyest = scale * s.maximum();

		//Otherwise, set the smallest number in s to the smallest in combine.
		else
			combine.tinyest = scale * s.minimum();

		//If the scale is greater than zero, the largest in s is still the largest by multiplying the scale
		//so set that number to the largest number in combine. 
		if (scale > 0)
			combine.largest = scale * s.maximum();

		//Otherwise, this mean the scale is negative, so the smallest number in s is the largest by multiplying 
		// the scale. Set that to the largest to combine.
		else
			combine.largest = scale * s.minimum();

		return combine;

	}

	//This function returns true if s1 is equal to s2. This mean s1 and s2 has same length and same sum.
	bool operator ==(const statistician& s1, const statistician& s2)
	{
		//Simply return true if the length of s1 and s2 is zero.
		if (s1.length() == 0 && s2.length() == 0)
			return true;

		//Otherwise, return true if they has same length and same sum. 
		else
			return ((s1.length() == s2.length()) && (s1.sum() == s2.sum()));


	}

}