#include "definitions.h"
#include "Vector.h"

// function pointers association
void create(Vec* _vector)
{
	_vector->size = 0;
	_vector->push_back = push_back;
	_vector->pop_back = pop_back;
	_vector->insert = insert;
	_vector->erase = erase;
	_vector->clear = clear;
	_vector->get_element = get_element;
	_vector->modify_element = modify_element;
}

void push_back(Vec* _vector, Element _newElem)
{
	Element* element, * nouvel_element;

	// CASE 1: Insert in an empty List
	if (_vector->size == 0)
	{
		_vector->first = new Element;
		*_vector->first = _newElem;
		_vector->first->ptrSuivant = nullptr;
	}
	else
		// CASE 2: Insert at the end of an already pop2ulated List
	{
		// => creation of the new element to insert
		nouvel_element = new Element;
		*nouvel_element = _newElem;

		// => go to the end of the list
		for (element = _vector->first; element->ptrSuivant != nullptr; element = element->ptrSuivant)// arr�t au dernier �l�ment
		{
		}//=> at the end of this loop, element points to the end of the list

		element->ptrSuivant = nouvel_element;
		nouvel_element->ptrSuivant = nullptr;
	}
	_vector->size++;
}

void insert(Vec* _vector, int _pos, Element _newElem)
{
	if (_pos >= 0 && _pos <= _vector->size)
	{
		Element* element, * nouvel_element;
		if (_vector->size == 0)// Insertion dans une liste vide
		{
			_vector->first = new Element;
			_vector->first->x = _newElem.x;
			_vector->first->y = _newElem.y;
			_vector->first->timer = _newElem.timer;

			_vector->first->ptrSuivant = nullptr;

		}
		else
		{
			element = _vector->first; // on se replace en d�but de liste

			// Cr�ation de l'�l�ment � ins�rer : nouveau iPos i�me �lt
			nouvel_element = new Element;
			_vector->first = new Element;
			_vector->first->x = _newElem.x;
			_vector->first->y = _newElem.y;
			_vector->first->timer = _newElem.timer;

			// INSERTION DU NOUVEL Element :
			if (_pos != _vector->size) // si position interm�diaire (pas � la fin)
			{
				if (_pos == 0)
				{

					nouvel_element->ptrSuivant = _vector->first->ptrSuivant;
					_vector->first = nouvel_element;

				}
				else
				{

					for (int i = 1; i < _pos - 1; i++)// lecture des premiers �l�ments
					{
						element = element->ptrSuivant;
					}//=> � la fin, element pointe sur "le iPos i�me �l�ment" 

					nouvel_element->ptrSuivant = element->ptrSuivant;//on fait pointer le nouvel_element sur l'ancien 5�me qui devient donc le 6�me de la liste
					element->ptrSuivant = nouvel_element; // on fait pointer element (4�me) sur le nouvel_element � ins�rer, qui devient donc le 5�me �l�ment

				}
			}
			else // insertion � la fin de la Liste
			{
				for (element = _vector->first; element->ptrSuivant != NULL; element = element->ptrSuivant)// arr�t au dernier �l�ment
				{
				}//=> � la fin, element pointe sur dernier �l�ment" 
				element->ptrSuivant = nouvel_element;
				nouvel_element->ptrSuivant = NULL;

			}
		}
		_vector->size++;
	}
}

//removes a single element from the vector
void erase(Vec* _vector, int iPos)
{
	if (iPos >= 1 && iPos <= _vector->size)
	{
		Element* element;


		Element* temp;
		Element* Lecture;

		if (iPos == 1)
		{

			temp = _vector->first;
			_vector->first = (_vector)->first->ptrSuivant;
			delete(temp);
			temp = NULL;

		}
		else if (iPos != _vector->size)
		{
			element = _vector->first; // on se replace en d�but de liste

			temp = _vector->first;
			Lecture = _vector->first;

			for (int i = 1; i < iPos - 1; i++)
			{
				temp = temp->ptrSuivant;
			}
			for (int i = 1; i < iPos; i++)
			{
				Lecture = Lecture->ptrSuivant;
			}
			temp->ptrSuivant = temp->ptrSuivant->ptrSuivant;
			delete(Lecture);
			Lecture = NULL;


		}
		else // suppression dernier �l�ment
		{

			// Pas utile on a la fonction pop_back 
		}
		_vector->size--;
	}
}

// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
void clear(Vec* _vector)
{
	while (_vector->first != nullptr)
	{
		_vector->first = _vector->first->ptrSuivant;
	}
	delete _vector->first;
}


//Delete last element
//Removes the last element in the vector, effectively reducing the container size by one.
//This destroys the removed element.
void pop_back(Vec* _vector)
{
	Element* element = nullptr;
	for (element = _vector->first; element->ptrSuivant->ptrSuivant != nullptr; element = element->ptrSuivant)// lecture de toute la liste
	{
	}//=> � la fin, element pointe sur l'avant-dernier �l�ment
	delete element->ptrSuivant;
	element->ptrSuivant = nullptr;
	_vector->size--;
}

Element get_element(Vec* _vector, int iPos)
{
	_vector->current = _vector->first;

	for (int i = 0; i < iPos; i++)
	{
		if (i == iPos - 1)
		{
			return *_vector->current;
		}
		else
		{
			_vector->current = _vector->current->ptrSuivant;
		}
	}
}

void modify_element(Vec* _vector, int iPos, int _choice, float _value)
{
	_vector->current = _vector->first;

	for (int i = 0; i < iPos; i++)
	{
		if (i == iPos - 1)
		{
			switch (_choice)
			{
			case 0:
				_vector->current->x -= _value;
				break;
			case 1:
				_vector->current->y -= _value;
				break;
			case 2:
				_vector->current->timer -= _value;
				break;
			}
		}
		else
		{
			_vector->current = _vector->current->ptrSuivant;
		}
	}
}