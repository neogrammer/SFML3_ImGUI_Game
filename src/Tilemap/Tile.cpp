#include "Tile.h"

Tile::Tile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, bool visible, int type)
	: VisibleObject(texRectSize, texRectSize, texID, startPos, pitch, 1, "Uni", "Tileset", std::vector<sf::Vector2f>{})
	, pitch_{pitch}
	, visible_{visible}
	, type_{type}
{

}

Tile::Tile(const Tile& o)
	: VisibleObject{ (sf::Vector2f)o.sizes_[o.getIndex()], (sf::Vector2f)o.sizes_[o.getIndex()], o.textureID_, (sf::Vector2f)o.texFrames_[o.getIndex()].at("Uni")[0].position, o.pitch_, (int)o.texFrames_.at(o.getIndex()).at("Uni").size(), "Uni", "Tileset", std::vector<sf::Vector2f>{}}
{
	type_ = o.type_;
	pitch_ = o.pitch_;
	visible_ = o.visible_;



}

Tile& Tile::operator=(const Tile& o)
{
	/*auto* other = dynamic_cast<VisibleObject*>(const_cast<Tile*>(&o));
	Tile aTile{ (sf::Vector2f)other->getFrameSize(), o.textureID_, (sf::Vector2f)other->getTexFrame(o.currID_, o.currDir_, (size_t)0).position, o.pitch_, o.visible_, o.type_ };*/

	this->currID_ = o.currID_;
	this->currFrame_ = o.currFrame_;
	this->currDir_ = o.currDir_;


	this->textureID_ = o.textureID_;

	this->numAnimations_ = o.numAnimations_;
	this->type_ = o.type_;
	this->vel_ = o.vel_;
	this->visible_ = o.visible_;
	this->pos_ = o.pos_;
	this->pitch_ = o.pitch_;
	//this->animIDs_.clear();
	//this->isUniDirectional_.clear();
	//this->sizes_.clear();
	//this->numFrames_.clear(); 
	/*for (int i = 0; i < o.animIDs_.size(); i++)
	{
		this->animIDs_.push_back(o.animIDs_[i]);
		this->isUniDirectional_.push_back(o.isUniDirectional_[i]);
		this->sizes_.push_back(o.sizes_[i]);
		this->numFrames_.push_back(o.numFrames_[i]);*/

	//}

	//this->texFrames_.clear();
	//this->offsets_.clear();

	/*for (int i = 0; i < texFrames_.size(); i++)
	{
		this->texFrames_.push_back(o.texFrames_[i]);
		this->texFrames_[this->getIndex()]["Uni"] = std::vector<sf::IntRect>{};
		this->texFrames_[this->getIndex()]["Uni"].clear();
		for (int j = 0; j < o.texFrames_.at(i).at("Uni").size(); j++)
			this->texFrames_[this->getIndex()]["Uni"].push_back(o.texFrames_.at(i).at("Uni").at(j));

		this->offsets_.push_back(o.offsets_[i]);
		this->offsets_[this->getIndex()]["Uni"] = std::vector<sf::Vector2f>{};
		this->offsets_[this->getIndex()]["Uni"].clear();
		for (int j = 0; j < o.offsets_.at(i).at("Uni").size(); j++)
			this->offsets_[this->getIndex()]["Uni"].push_back(o.offsets_.at(i).at("Uni").at(j));
	}*/

	return *this;


	// TODO: insert return statement here
}

Tile::Tile(Tile&& o)
	: VisibleObject(std::move(*(VisibleObject*)&o))
{
	type_ = o.type_;
	pitch_ = o.pitch_;
	visible_ = o.visible_;
}

Tile& Tile::operator=(Tile&& o)
{
	
	/*auto* other = dynamic_cast<VisibleObject*>(const_cast<Tile*>(&o));
	Tile aTile{ (sf::Vector2f)other->getFrameSize(), o.textureID_, (sf::Vector2f)other->getTexFrame(o.currID_, o.currDir_, (size_t)0).position, o.pitch_, o.visible_, o.type_ };*/

	this->currID_ = o.currID_;
	this->currFrame_ = o.currFrame_;
	this->currDir_ = o.currDir_;


	this->textureID_ = o.textureID_;

	this->numAnimations_ = o.numAnimations_;
	this->type_ = o.type_;
	this->vel_ = o.vel_;
	this->visible_ = o.visible_;
	this->pos_ = o.pos_;
	this->pitch_ = o.pitch_;
	//this->animIDs_.clear();
	//this->isUniDirectional_.clear();
	//this->sizes_.clear();
	//this->numFrames_.clear();
	/*for (int i = 0; i <= o.animIDs_.size(); i++)
	{
		this->animIDs_.push_back(o.animIDs_[i]);
		this->isUniDirectional_.push_back(o.isUniDirectional_[i]);
		this->sizes_.push_back(o.sizes_[i]);
		this->numFrames_.push_back(o.numFrames_[i]);

	}

	this->texFrames_.clear();
	this->offsets_.clear();

	for (int i = 0; i <= texFrames_.size(); i++)
	{
		this->texFrames_.push_back(o.texFrames_[i]);
		this->texFrames_[this->getIndex()]["Uni"] = std::vector<sf::IntRect>{};
		this->texFrames_[this->getIndex()]["Uni"].clear();
		for (int j = 0; j < o.texFrames_.at(i).at("Uni").size(); j++)
			this->texFrames_[this->getIndex()]["Uni"].push_back(o.texFrames_.at(i).at("Uni").at(j));

		this->offsets_.push_back(o.offsets_[i]);
		this->offsets_[this->getIndex()]["Uni"] = std::vector<sf::Vector2f>{};
		this->offsets_[this->getIndex()]["Uni"].clear();
		for (int j = 0; j < o.offsets_.at(i).at("Uni").size(); j++)
			this->offsets_[this->getIndex()]["Uni"].push_back(o.offsets_.at(i).at("Uni").at(j));
	}*/

	return *this;
}

void Tile::Render(sf::RenderWindow& wnd_)
{
	if (type_ != 0 && type_ != 3)
		wnd_.draw(*sprite());
}

sf::Vector2f Tile::getSize()
{
	return this->sizes_.at(getIndex());
}

sf::Vector2i Tile::getTexRectSize()
{
	return texFrames_.at(getIndex()).at(currDir_).at(currFrame_).size;
}

sf::Vector2f Tile::getPos()
{
	return pos_;
}

sf::Vector2i Tile::getTexPos()
{
	return texFrames_.at(getIndex()).at(currDir_).at(currFrame_).position;
}

int Tile::getPitch()
{
	return pitch_;
}

Cfg::Textures Tile::getTextureID()
{
	return textureID_;
}

void Tile::setVisible(bool cond)
{
	visible_ = cond;
}

bool Tile::isVisible()
{
	return visible_;
}

bool Tile::isEmpty() { return (type_ == 0); }

size_t Tile::getIndex() const
{
	return VisibleObject::getIndex();
}

size_t Tile::getIndex(const std::string& id_)
{
	return VisibleObject::getIndex(id_);
}
