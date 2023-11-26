#ifndef VECTOR__H
#define VECTOR__H

struct Vec
{
	int size;
	Element* first;
	Element* current;
	Element* last;
	
	void(*insert)(Vec* _vector, int iPos, Element _newElem);
	void(*erase)(Vec* _vector, int iPos);
	void(*clear)(Vec* _vector);
	void(*push_back)(Vec*, Element _newElem);
	void(*pop_back)(Vec* _vector);
	void(*create)(Vec* _vector);

	Element(*get_element)(Vec* _vector, int _iPos);
	void (*modify_element)(Vec* _vector, int iPos, int _choice, float _value);
};

void insert(Vec* _vector, int iPos, Element _newElem);
void erase(Vec* _vector, int iPos);
void clear(Vec* _vector);
void push_back(Vec*, Element _newElem);
void pop_back(Vec* _vector);
void create(Vec* _vector);
Element get_element(Vec* _vector, int _iPos);
void modify_element(Vec* _vector, int iPos, int _choice, float _value);

#endif 
