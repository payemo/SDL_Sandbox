#pragma once

#include <vector>
#include "Layer.h"
#include "Vector2D.h"

struct Tileset;

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, const std::vector<Tileset>& tilesets);

    virtual void Update() override;
    virtual void Render() override;

    inline void SetTileIds(const std::vector<std::vector<int>>& data) { m_tileIds = data; }
    inline void SetTileSize(int tileSize) { m_tileSize = tileSize; }

private:
    const std::vector<Tileset>& m_tilesets;

private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    Vector2D m_position;
    Vector2D m_velocity;

    std::vector<std::vector<int>> m_tileIds;

private:
    const Tileset& GetTilesetById(int tileId);
};