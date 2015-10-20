//============================================================================
// Name        : 
// Author      : 
// Version     :
// Copyright   : 
// Description : 
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


typedef vector<int> IntList;

void print (IntList const& listA, string const& prefix="", string const& suffix="")
{
	cout << prefix;
	copy(listA.begin(), listA.end(), std::ostream_iterator<IntList::value_type>(cout, " "));
	cout << suffix;
	cout << endl;
}

unsigned merge_and_count_split_inversions(IntList const& listA,
										  IntList const& listB,
										  IntList& output)
{
	IntList::const_iterator itrA = listA.begin();
	IntList::const_iterator itrB = listB.begin();
	unsigned count=0;

	while (itrA != listA.end() && itrB != listB.end())
	{
		if (*itrA <= *itrB)
		{
			output.push_back(*itrA++);
		}
		else{
			output.push_back(*itrB++);
			count+= (listA.end() - itrA);
		}
	}

	while (itrA != listA.end())
	{
		output.push_back(*itrA++);
	}
	while (itrB != listB.end())
	{
		output.push_back(*itrB++);
	}

	return count;
}

unsigned sort(IntList const& aList,
		  	  IntList& output)
{
	/**
	 * Base case
	 */
	if (aList.size() == 0)
	{
		return 0;
	}
	else if (aList.size() == 1)
	{
		copy(aList.begin(), aList.end(), back_inserter(output));
		return 0;
	}

	/**
	 * Split into equal lists [ O(n) ]
	 */
	IntList left(aList.begin(), aList.begin() + aList.size()/2);
	IntList	right(aList.begin() + aList.size()/2, aList.end());


	unsigned count = 0;

	/**
	 * Recursive split call [ O(n log(n)) ]
	 */
	IntList newLeft, newRight;
	count += sort(left, newLeft);
	count += sort(right, newRight);

	/**
	 * Call merge + count [ O(n) ]
	 */
	return count + merge_and_count_split_inversions(newLeft, newRight, output);
}

int main() {

	IntList values;
	IntList sorted;

	int x;
	while (cin >> x)
	{
		values.push_back(x);
	}

	cout << "Inversions: " << sort(values, sorted)<<endl;

	//print(sorted, "\nSorted: ");

	return 0;
}
