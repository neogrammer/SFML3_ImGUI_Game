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
	texIDs_.push_back(texID);
	numFrames_.push_back(numFrames);
	sizes_.push_back(size);
	texFrames_.push_back(std::unordered_map<std::string, std::vector<sf::IntRect>>{});
	texFrames_[texFrames_.size() - (size_t)1].clear();
	offsets_.push_back(std::unordered_map<std::string, std::vector<sf::Vector2f>>{});
	offsets_[offsets_.size() - (size_t)1].clear();

	if (offsets.empty())
	{ 

		offsets_[offsets_.size() - (size_t)1]["Uni"] = std::vector<sf::Vector2f>{};
		offsets_[offsets_.size() - (size_t)1]["Uni"].clear();
		offsets_[offsets_.size() - (size_t)1]["Uni"].reserve(numFrames);
		for (int i = 0; i < numFrames; i++)
		{
			offsets_[offsets_.size() - (size_t)1]["Uni"].push_back({0.f,0.f});
		}
		currDir_ = "Uni";
		isUniDirectional_.push_back(true);

		texFrames_[texFrames_.size() - (size_t)1]["Uni"] = std::vector<sf::IntRect>{};
	}
	else
	{
		offsets_[offsets_.size() - (size_t)1][dir] = std::vector<sf::Vector2f>{};
		offsets_[offsets_.size() - (size_t)1][dir].clear();
		offsets_[offsets_.size() - (size_t)1][dir].reserve(numFrames);
		for (int i = 0; i < offsets.size(); i++)
		{
			offsets_[offsets_.size() - (size_t)1][dir].push_back(offsets[i]);
		}
		if (dir == "Uni")
			isUniDirectional_.push_back(true);
		else
			isUniDirectional_.push_back(false);

		texFrames_[texFrames_.size() - (size_t)1][dir] = std::vector<sf::IntRect>{};
	}
		// cols on first line
		int frameX = (int)(startPos.x / texRectSize.x);


		// only do the one frameset
		for (int i = frameX; i < (int)std::min((numFrames + frameX), pitch); i++)
		{
			texFrames_[texFrames_.size() - (size_t)1][dir].emplace_back(sf::IntRect{ {(int)startPos.x + (int)(i * texRectSize.x),(int)startPos.y},(sf::Vector2i)texRectSize });
		}

		int numDone = pitch - frameX;

		if (numFrames - numDone < pitch && numFrames - numDone > 0)
		{
			for (int i = 0; i < numFrames - numDone; i++)
			{
				texFrames_[texFrames_.size() - (size_t)1][dir].emplace_back(sf::IntRect{ { i * (int)texRectSize.x, (int)startPos.y + (int)texRectSize.y},(sf::Vector2i)texRectSize });
			}
		}
	numAnimations_ += 1;
}


void VisibleObject::Render(sf::RenderWindow& wnd_)
{
	wnd_.draw(*sprite());
}