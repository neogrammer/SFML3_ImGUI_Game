#include "Tilemap.h"

void Tilemap::Initialize(LevelName level)
{
	TSET ts = NEWgetTilesetData(level);
	this->SetupTileset(ts.tileDataType, { (float)ts.tw,(float)ts.th }, ts.texID, ts.cols * ts.rows, ts.cols);
	TMAP tmapData = NEWgetLevelData(level);
	this->SetupTilemap(tmapData.level, (int)tmapData.cols, (int)tmapData.rows, { (float)tmapData.tw, (float)tmapData.th });
}

void Tilemap::SetupTileset(std::vector<int> tilesetDataType, sf::Vector2f texRectSize, Cfg::Textures texID, int numFrames, int pitch)
{
	if (tilesetDataType.empty())
		return;

	

	for (int y = 0; y < numFrames / pitch; y++)
	{
		for (int x = 0; x < pitch; x++)
		{
			int num = y * pitch + x;
			int theType = tilesetDataType[num];
			tset_.AddTile(texID, sf::IntRect{ sf::Vector2i{ (int)(x * (int)texRectSize.x), (int)(y * (int)texRectSize.y) }, sf::Vector2i(texRectSize) }, pitch, (TileType)theType, (theType == 0), { (float)x * texRectSize.x, (float)y * texRectSize.y });
		}
	}
}

void Tilemap::SetupTilemap(std::vector<int> tilesetTileNums, int cols, int rows, sf::Vector2f size_)
{
	cols_ = cols;
	rows_ = rows;
	tw_ = (int)size_.x;
	th_ = (int)size_.y;

	if (tset_.getTiles().empty())
		return;

	
		std::vector<std::unique_ptr<TileObj>>& tileset = tset_.getTiles();
		tiles_.clear();
		tiles_.reserve(cols * rows);
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				int num = tilesetTileNums[y * cols + x];
				if (num >= tset_.getTiles().size())
				{
					continue;
				}
				//std::unique_ptr<Tile> aTile = std::move(tset_.copyTile(num));
//				std::unique_ptr<TileObj> aTile = std::move(tset_.copyTile(num));

				Cfg::Textures tex = tileset.at(num)->getTextureID();
				sf::IntRect texRect = sf::IntRect{ (sf::Vector2i)tileset.at(num)->getTexRectPos(), (sf::Vector2i)tileset.at(num)->getTexRectSize() };
				int pitch = tileset.at(num)->getPitch();
				TileType type = tileset.at(num)->getType();
				bool empty = tileset.at(num)->isEmpty();
				
				tiles_.push_back(TileObj{ tex, texRect, pitch, type, empty, sf::Vector2f{(float)(x * texRect.size.x),(float)(y * texRect.size.y)} });
				//(sf::Vector2f)aTile->getTexRectSize(), aTile->getTextureID(), (sf::Vector2f)aTile->getTexPos(), aTile->getPitch(), aTile->isVisible(), aTile->getType());
			}
		}
		/*for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				tiles_[y * cols + x].SetPosition({ (float)x * size_.x, (float)y * size_.y });

			}
		}*/
	
}

std::vector<TileObj> Tilemap::getTiles()
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
		for (int x = (int)left; x < right; x++)
		{
			int i = y * cols_ + x;
			if (i >= tiles_.size())
				continue;
			tiles_[i].render(wnd_);
		}
	}
}
