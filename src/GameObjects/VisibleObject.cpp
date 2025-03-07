#include "VisibleObject.h"
#include <unordered_map>

VisibleObject::VisibleObject(sf::Vector2f size, sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, int numFrames, const std::string& dir, const std::string& animID, std::vector<sf::Vector2f> offsets)
	: GameObject{ size, texRectSize }
{
	// basically do this on an animation add, gotta do each direction in an animation
	currFrame_ = 0;
	currID_ = animID;
	currDir_ = dir;
	textureID_ = texID;
	animIDs_.push_back(animID);
	numFrames_.push_back(numFrames);
	sizes_.push_back(size); 
	texFrames_.push_back(std::unordered_map<std::string, std::vector<sf::IntRect>>{});
	texFrames_[1].clear();
	offsets_.push_back(std::unordered_map<std::string, std::vector<sf::Vector2f>>{});
	offsets_[1].clear();
	//texFrames_.back().clear();
	//offsets_.back().clear();
	

	if (dir == "Uni")
	{ 

		offsets_[1]["Uni"] = std::vector<sf::Vector2f>{};
		offsets_[1]["Uni"].clear();
		offsets_[1]["Uni"].reserve(numFrames);
		for (int i = 0; i < numFrames; i++)
		{
			offsets_[1]["Uni"].push_back({0.f,0.f});
		}
		currDir_ = "Uni";
		isUniDirectional_.push_back(true);

		texFrames_[1]["Uni"] = std::vector<sf::IntRect>{};
		texFrames_[1]["Uni"].clear();
		for (int i = 0; i < numFrames; i++)
			texFrames_[1]["Uni"].emplace_back(sf::IntRect{sf::Vector2i(startPos.x + i * texRectSize.x, startPos.y), sf::Vector2i(texRectSize.x, texRectSize.y)});
	}
	else
	{
		offsets_[1][dir] = std::vector<sf::Vector2f>{};
		offsets_[1][dir].clear();
		offsets_[1][dir].reserve(numFrames);
		for (int i = 0; i < offsets.size(); i++)
		{
			offsets_[1][dir].push_back(offsets[i]);
		}
		if (dir == "Uni")
			isUniDirectional_.push_back(true);
		else
			isUniDirectional_.push_back(false);

		texFrames_[1][dir] = std::vector<sf::IntRect>{};
		texFrames_[1][dir].clear();
		for (int i = 0; i < numFrames; i++)
			texFrames_[1][dir].emplace_back(sf::IntRect{ sf::Vector2i(startPos.x + i * texRectSize.x, startPos.y), sf::Vector2i(texRectSize.x, texRectSize.y) });

	}


		//// cols on first line
		//int frameX = (int)(startPos.x / texRectSize.x);

		//int numDone = 0;
		//// only do the one frameset
		//for (int i = frameX; i < pitch; i++)
		//{
		//	if (frameX >= numFrames)
		//		break;
		//	texFrames_[getIndex()][dir].emplace_back(sf::IntRect{{(int)startPos.x + (int)(i * texRectSize.x),(int)startPos.y},(sf::Vector2i)texRectSize});
		//	numDone++;
		//}
		//int totalDone = numDone;
		//int rowsDone = 1;

	
		//while (numDone < numFrames)
		//{
		//	for (int i = 0; i < numFrames - numDone; i++)
		//	{
		//		if (i + totalDone >= numFrames || i >= pitch)
		//			break;
		//		else
		//		{
		//			texFrames_[getIndex()][dir].emplace_back(sf::IntRect{ {i * (int)texRectSize.x, (int)startPos.y + rowsDone * (int)texRectSize.y},(sf::Vector2i)texRectSize });
		//			numDone++;
		//		}
		//	}
		//	rowsDone++;
		//}

		numAnimations_ += 1;
}


void VisibleObject::Render(sf::RenderWindow& wnd_)
{
	wnd_.draw(*sprite());
}

size_t VisibleObject::getIndex() const
{
	return GameObject::getIndex();
}

size_t VisibleObject::getIndex(const std::string& id_)
{
	return GameObject::getIndex(id_);
}

sf::IntRect VisibleObject::getTexFrame(const std::string& animID, const std::string& dir, size_t frameNum)
{
	return texFrames_[getIndex(animID)].at(dir).at(frameNum);
}

sf::Vector2i VisibleObject::getFrameSize()
{
	return getTexFrame(currID_, currDir_, currFrame_).size;
}

sf::Vector2i VisibleObject::getFrameSize(const std::string& animID)
{
	return getTexFrame(animID, currDir_, currFrame_).size;
}
