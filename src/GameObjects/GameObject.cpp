#include "GameObject.h"
//
//GameObject::GameObject(std::string filename_, float x_, float y_ )
//	: posx{x_}
//	, posy{ y_ }
//{
//	bboxMap.clear();
//	bboxMap.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<BBox>>>{"Invariant", std::unordered_map<std::string, std::vector<BBox>>{}});
//	bboxMap.at("Invariant").clear();
//	bboxMap.at("Invariant").emplace(std::pair<std::string, std::vector<BBox>>{ std::pair<std::string, std::vector<BBox>>{"Invariant", std::vector<BBox>{}}});
//	bboxMap.at("Invariant").at("Invariant").clear();
//	bboxMap.at("Invariant").at("Invariant").emplace_back(BBox{this});
//
//}
GameObject::GameObject(sf::Vector2f size, sf::Vector2f texRectSize)
{
	pos_.x = 0.f;
	pos_.y = 0.f;
	numFrames_.clear();
	numFrames_.push_back(1);
	texFrames_.clear();
	sizes_.clear();
	sizes_.push_back({ size.x, size.y });
	texFrames_.push_back(std::unordered_map<std::string, std::vector<sf::IntRect>>{});
	texFrames_[0].clear();
	offsets_.push_back(std::unordered_map<std::string, std::vector<sf::Vector2f>>{});
	offsets_[0].clear();


	if (texRectSize.x == 0 || texRectSize.y == 0)
	{
		texFrames_[0]["Uni"] = std::vector<sf::IntRect>{};
		texFrames_[0]["Uni"].clear();
		texFrames_[0]["Uni"].push_back(sf::IntRect{ {0, 0}, {(int)size.x, (int)size.y} });
		
	}
	else
	{
		texFrames_[0]["Uni"] = std::vector<sf::IntRect>{};
		texFrames_[0]["Uni"].clear();
		texFrames_[0]["Uni"].push_back({{0, 0}, {(int)texRectSize.x, (int)texRectSize.y}});
	}

	offsets_[0]["Uni"] = std::vector<sf::Vector2f>{};
	offsets_[0]["Uni"].clear();
	offsets_[0]["Uni"].push_back(sf::Vector2f{ 0.f,0.f });
	animIDs_.clear();
	animIDs_.push_back("Invariant");
	currID_ = "Invariant";
	isUniDirectional_.push_back(true);
	currDir_ = "Uni";
	currFrame_ = (size_t)0;
	numAnimations_ = 0;
	texIDs_.clear();
	texIDs_.push_back(Cfg::Textures::Invariant);
}



size_t GameObject::getIndex()
{
	// add one for the invariante
	for (int i = 0; i < numAnimations_ + 1; i++)
	{
		if (currID_ == animIDs_[i])
		{
			return i;
		}
	}
	return (size_t)0;
}


size_t GameObject::getIndex(const std::string& id_)
{
	// add one for the invariante
	for (int i = 0; i < numAnimations_ + 1; i++)
	{
		if (id_ == animIDs_[i])
		{
			return i;
		}
	}

	return (size_t)0;
}



GameObject::~GameObject()
{

}

//void GameObject::addBBox(std::string id_, std::string dir_, sf::FloatRect bbox_)
//{
//	if (bboxMap.find(id_) == bboxMap.end())
//	{
//		bboxMap[id_] = std::unordered_map<std::string, std::vector<BBox>>{};
//		bboxMap[id_].clear();
//	}
//	if (bboxMap.at(id_).find(dir_) == bboxMap.at(id_).end())
//	{
//		bboxMap[id_].emplace(std::pair<std::string, std::vector<BBox>>{dir_, std::vector<BBox>{}});
//		bboxMap[id_].at(dir_).clear();
//	}
//
//	bboxMap[id_].at(dir_).emplace_back(this, bbox_.left, bbox_.top, bbox_.width, bbox_.height);
//
//}
//
//BBox& GameObject::getBBox()
//{
//	// TODO: insert return statement herereturn bboxMap.at(id_).at(dir_).at(index_);
//
//	return bboxMap.at("Invariant").at("Invariant").at(0);
//}
//
//BBox& GameObject::getBBox(std::string id_, std::string dir_, int index_)
//{
//	return bboxMap.at(id_).at(dir_).at(index_);
//}

std::unique_ptr<sf::Sprite> GameObject::sprite()
{
	std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>(Cfg::textures.get((int)texIDs_[getIndex()]));
	tmp->setTextureRect(texFrames_[getIndex()][currDir_][currFrame_]);
	tmp->setPosition({ pos_.x - offsets_[getIndex()][currDir_][currFrame_].x, pos_.y - offsets_[getIndex()].at(currDir_).at(currFrame_).y });
	return std::move(tmp);
}

void GameObject::Render(sf::RenderWindow& wnd_)
{
	wnd_.draw(*sprite());
}

std::string GameObject::CurrID()
{
	return currID_;
}

std::string GameObject::CurrDir()
{
	return currDir_;
}

sf::Vector2f GameObject::getPos()
{
	return pos_;
}

void GameObject::setPos(sf::Vector2f pos)
{
	pos_.x = pos.x;
	pos_.y = pos.y;
}

void GameObject::move(sf::Vector2f amt)
{
	pos_.x += amt.x;
	pos_.y += amt.y;
}

