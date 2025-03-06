#include "Tilemap.h"

void Tilemap::Initialize(LevelName level)
{
	TSET ts = getTilesetData(level);
	this->SetupTileset(ts.tileDataType, { (float)ts.tw,(float)ts.th }, ts.texID, ts.cols * ts.rows, ts.cols, ts.cols * ts.rows - 1);
	TMAP tmapData = getLevelData(level);
	this->SetupTilemap(tmapData.level, (int)tmapData.cols, (int)tmapData.rows, { (float)tmapData.tw, (float)tmapData.th });
}

void Tilemap::SetupTileset(int* tilesetDataType, sf::Vector2f texRectSize, Cfg::Textures texID, int numFrames, int pitch, int emptyTileNum)
{
	if (tilesetDataType == nullptr)
		return;

	for (int y = 0; y < numFrames / pitch; y++)
	{
		for (int x = 0; x < pitch; x++)
		{
			int num = y * pitch + x;
			int theType = tilesetDataType[num];
			tset_.AddTile(texRectSize, texID, { x * texRectSize.x, y * texRectSize.y }, pitch, ((theType == 2 || theType == 3) ? true : false), theType);
			tset_.getTiles().at(tset_.getTiles().size() - (size_t)1)->setPos({ x * texRectSize.x, y * texRectSize.y });
			if (y * pitch + x == emptyTileNum)
				tset_.getTiles().at(tset_.getTiles().size() - (size_t)1)->setVisible(false);
		}
	}
}

void Tilemap::SetupTilemap(int* tilesetTileNums, int cols, int rows, sf::Vector2f size_)
{
	cols_ = cols;
	rows_ = rows;
	tw_ = (int)size_.x;
	th_ = (int)size_.y;

	if (tset_.getTiles().empty())
		return;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int num = tilesetTileNums[y * cols + x];
			if (num >= tset_.getTiles().size())
			{
				continue;
			}
			std::unique_ptr<Tile> aTile = std::move(tset_.copyTile(num));
			auto& t = tiles_.emplace_back((sf::Vector2f)aTile->getTexRectSize(), aTile->getTextureID(), (sf::Vector2f)aTile->getTexPos(), aTile->getPitch(), aTile->isVisible(), aTile->getType());
			tiles_.at(tiles_.size() - (size_t)1).setPos({ (float)x * (float)tset_.getTiles().at(num)->getTexRectSize().x, (float)y * (float)tset_.getTiles().at(num)->getTexRectSize().y });
		}
	}
}

std::vector<Tile> Tilemap::getTiles()
{
	return tiles_;
}

void Tilemap::Render(sf::RenderWindow& wnd_, float dt_)
{
	sf::View vw = wnd_.getView();

	auto center = vw.getCenter();
	auto left = center.x - (vw.getSize().x / 2.f);
	left /= tiles_.at(0).getTexRectSize().x;
	left = std::max(left, 0.f);
	auto top = center.y - (vw.getSize().y / 2.f);
	top /= tiles_.at(0).getTexRectSize().y;
	top = std::max(top, 0.f);

	int numTilesX = (int)vw.getSize().x / tiles_.at(0).getTexRectSize().x;
	int numTilesY = (int)vw.getSize().y / tiles_.at(0).getTexRectSize().y;

	int right = (int)(left + numTilesX);
	int bottom = (int)(top + numTilesY);

	right = (int)std::max((float)std::min(right + 1, cols_), 0.f);
	bottom = (int)std::max((float)std::min(bottom + 1, rows_), 0.f);
	

	for (int y = (int)top; y < bottom; y++)
	{
		for (int x  = (int)left; x < right; x++)
		{ 
			int i = y * cols_ + x;
			if (i >= tiles_.size())
				continue;
			if (tiles_[i].getType() != 0 && tiles_[i].getType() != 3)
					wnd_.draw(*tiles_[i].sprite());
		}
	}
}
