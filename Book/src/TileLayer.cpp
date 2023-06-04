#include "TileLayer.h"
#include "Level.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets)
    : m_tileSize(tileSize), 
    m_tilesets(tilesets),
    m_position(0, 0),
    m_velocity(0, 0)
{
    m_numColumns = TheGame::Instance()->GetWidth() / m_tileSize;
    m_numRows = TheGame::Instance()->GetHeight() / m_tileSize;
}

void TileLayer::Update()
{
    m_position += m_velocity;
}

void TileLayer::Render()
{
    int x, y, x2, y2 = 0;

    x = m_position.GetX() / m_tileSize;
    y = m_position.GetY() / m_tileSize;

    x2 = int(m_position.GetX()) % m_tileSize;
    x2 = int(m_position.GetY()) % m_tileSize;

    for (int i = 0; i < m_numRows; ++i) {
        for (int j = 0; j < m_numColumns; ++j) {
            int id = m_tileIds[i][j + x];

            if (id == 0)
                continue;

            const Tileset& tileset = GetTilesetById(id);
            --id;

            TheTextureManager::Instance()->DrawTile(
                tileset.name,
                tileset.margin,
                tileset.spacing,
                (j * m_tileSize) - x2,
                (i * m_tileSize) - y2,
                m_tileSize,
                m_tileSize,
                (id - (tileset.firstGridId - 1)) / tileset.numColumns,
                (id - (tileset.firstGridId - 1)) % tileset.numColumns,
                TheGame::Instance()->GetRenderer());
        }
    }
}

const Tileset& TileLayer::GetTilesetById(int tileId)
{
    for (int i = 0; i < m_tilesets.size(); ++i) {
        if (i + 1 <= m_tilesets.size() - 1) {
            if (tileId >= m_tilesets[i].firstGridId && tileId < m_tilesets[i + 1].firstGridId) {
                return m_tilesets[i];
            }
        }
        else {
            return m_tilesets[i];
        }
    }

    std::cout << "Tiset was not found" << std::endl;
    Tileset t;
    return t;
}