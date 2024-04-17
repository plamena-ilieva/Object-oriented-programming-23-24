#include <iostream>
#include "Set.h"

int main()
{
	Set s1(5);
	s1.add(1);
	s1.add(3);
	Set s2(7);
	s2.add(1);
	s2.add(7);

	s1.print();
	s2.print();

	Set unionSet = unionOfSets(s1, s2);
	unionSet.print();

	Set intersectionSet = intersectionOfSets(s1, s2);
	intersectionSet.print();
}
