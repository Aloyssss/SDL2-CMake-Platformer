#include "Tilemap.h"

Tilemap::Tilemap(const std::string& jsonFile, const std::string& tilesetFile, SDL_Renderer* renderer, Camera* camera)
    : _renderer(renderer), _camera(camera), _tileSize(0), _mapWidth(0), _mapHeight(0)
{
    loadTilemap(jsonFile);
    loadTileset(tilesetFile);
}

Tilemap::~Tilemap()
{
    if (_tilesetTexture)
    {
        SDL_DestroyTexture(_tilesetTexture);
    }
}

void Tilemap::render(SDL_Renderer* renderer)
{
    for (const auto& layer : _layers)
    {
        for (const auto& tile : layer.tiles)
        {
            SDL_Rect srcRect
            {
                (tile.id % _tilesetCols) * _tileSize,
                (tile.id / _tilesetCols) * _tileSize,
                _tileSize,
                _tileSize
            };

            SDL_Rect destRect
            {
                tile.x * _tileSize * scale - _camera->getView().x,
                tile.y * _tileSize * scale - _camera->getView().y,
                _tileSize * scale,
                _tileSize * scale
            };

            SDL_RenderCopy(renderer, _tilesetTexture, &srcRect, &destRect);
        }
    }
}

void Tilemap::loadTilemap(const std::string& jsonFile)
{
    std::ifstream file(jsonFile);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open tilemap file.");
    }

    json data;
    file >> data;

    _tileSize = data["tileSize"].get<int>();
    _mapWidth = data["mapWidth"].get<int>();
    _mapHeight = data["mapHeight"].get<int>();

    for (const auto& layerData : data["layers"])
    {
        Layer layer;
        layer.name = layerData["name"].get<std::string>();
        layer.collider = layerData["collider"].get<bool>();

        for (const auto& tileData : layerData["tiles"])
        {
            Tile tile;
            tile.id = std::stoi(tileData["id"].get<std::string>());
            tile.x = tileData["x"].get<int>();
            tile.y = tileData["y"].get<int>();
            layer.tiles.push_back(tile);
        }

        _layers.push_back(layer);
    }
}

void Tilemap::loadTileset(const std::string& tilesetFile)
{
    SDL_Surface* surface = IMG_Load(tilesetFile.c_str());
    if (!surface)
    {
        throw std::runtime_error("Failed to load tileset image.");
    }

    _tilesetTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    if (!_tilesetTexture)
    {
        throw std::runtime_error("Failed to create texture from tileset.");
    }

    int textureWidth, textureHeight;
    SDL_QueryTexture(_tilesetTexture, nullptr, nullptr, &textureWidth, &textureHeight);
    _tilesetCols = textureWidth / _tileSize;
    _tilesetRows = textureHeight / _tileSize;
}



