#ifndef SCORES__H
#define SCORES__H

class Scores
{
private:

public:

	std::string m_name;
	int m_score;

	Scores();
	static void InputScore(sf::Event _event, int _id);
	static void LoadScoreFile();
	static void SaveScoreFile();
	static void Display();
	~Scores();

};

#endif