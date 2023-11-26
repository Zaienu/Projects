#include "GameData.h"
#include "definitions.h"
#include "Scores.h"
#include "TextManager.h"

Scores::Scores()
{

}

void Scores::InputScore(sf::Event _event, int _id)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.key.code == sf::Keyboard::Key::Enter)
	{
		if (!GD->m_InputBoxes[_id]->currentWord.empty() && GD->m_InputBoxes[_id]->edit)
		{
			Scores* score = new Scores();
			score->m_name = GD->m_InputBoxes[_id]->currentWord;
			score->m_score = GD->m_scores[_id];
			GD->m_scoreList.push_back(score);
		}
		GD->m_InputBoxes[_id]->edit = false;
		GD->m_InputBoxes[_id]->currentWord = "INPUT NAME..";
	}
}

void Scores::LoadScoreFile()
{
	GameData* GD = GameData::Get_Instance();
	std::string fileName = "../Assets/Files/HighScore.txt";
	std::fstream file(fileName, std::ios::beg | std::ios::in);

	if (file.is_open())
	{
		GD->m_scoreList.clear();
		while (!file.eof())
		{
			Scores* score = new Scores();
			file >> score->m_score;
			file >> score->m_name;
			GD->m_scoreList.push_back(score);
		}
	}
	else
	{
		std::cout << "error" << std::endl;
	}
}

void Scores::SaveScoreFile()
{
	GameData* GD = GameData::Get_Instance();
	if (GD->m_scoreList.size() > 10)
	{
		GD->m_scoreList.resize(10);
	}
	std::string fileName = "../Assets/Files/HighScore.txt";
	std::fstream file(fileName, std::ios::beg | std::ios::out);
	if (file.is_open())
	{
		for (int i = 0; i < GD->m_scoreList.size(); i++)
		{
			file << GD->m_scoreList[i]->m_score;
			file << "   ";
			file << GD->m_scoreList[i]->m_name;
			if (i + 1 != GD->m_scoreList.size())
			{
				file << "\r";
			}
		}
	}
	else
	{
		std::cout << "error" << std::endl;
	}
}

void Scores::Display()
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();
	std::sort(GD->m_scoreList.begin(),
		GD->m_scoreList.end(), [](const Scores* hs1, const Scores* hs2)
		{
			return hs1->m_score > hs2->m_score;
		});
	if (GD->m_scoreList.size() > 10)
	{
		GD->m_scoreList.resize(10);
	}
	for (int i = 0; i < GD->m_scoreList.size(); i++)
	{
		TextSettings textSettings =
		{
			"Poggers-Bold",
			"Score" + std::to_string(i),
			sf::Color::White,
			40
		};
		Text->FillVectors(textSettings);
		Text->SetString(textSettings.name, std::to_string(GD->m_scoreList[i]->m_score) + "   " + GD->m_scoreList[i]->m_name);
		TextDrawParameters drawText = 
		{
			textSettings.name,
			0,
			{ 250, (float)(100 + 55 * i) },
			&GD->m_window
		};
		Text->BlitText(drawText);
	}
}

Scores::~Scores()
{

}