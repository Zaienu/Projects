#ifndef BUTTONMANAGER__H
#define BUTTONMANAGER__H

class ButtonManager
{
private: 

	std::vector <Button*> buttonVec;
	std::vector <void(*)()> pointerVec;

public:

	ButtonManager(ButtonList _bL);
	void SetIdle();
	std::vector <Button*> GetVector();
	void MousePressed();
	void MouseMoved();
	void Update();
	void Display();
	~ButtonManager();

};

#endif