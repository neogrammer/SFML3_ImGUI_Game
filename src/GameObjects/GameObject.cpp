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

GameObject::GameObject(const sf::Vector2f& pos, const sf::Vector2f& size)
	: pos_{pos}
{
	numFrames_.clear();
	numFrames_.push_back(1);
	texFrames_.clear();
	sizes_.clear();
	sizes_.push_back({ 50.f,50.f });
	texFrames_.push_back(std::vector<sf::IntRect>{});
	texFrames_[texFrames_.size() - (size_t)1].clear();
	texFrames_[texFrames_.size() - (size_t)1].push_back({ { 0, 0 }, { 50,50 } });
	offsets_.push_back(std::vector<sf::Vector2f>{});
	offsets_[offsets_.size() - (size_t)1].clear();
	offsets_[offsets_.size() - (size_t)1].push_back({ 0.f, 0.f  });
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
//	tmp->setTexture(Cfg::textures.get((int)texIDs_[getIndex()]));
	tmp->setTextureRect(texFrames_[getIndex()][currFrame_]);
	tmp->setPosition({ pos_.x - offsets_[getIndex()][currFrame_].x, pos_.y - offsets_[getIndex()][currFrame_].y });
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

