
#include "Header.h"
#include "Camera.h"
#include <fstream>

using json = nlohmann::json;

class Tilemap {
public:
    Tilemap(const std::string& jsonFile, const std::string& tilesetFile, SDL_Renderer* renderer, Camera* camera)
        : renderer(renderer), camera(camera), tileSize(0), mapWidth(0), mapHeight(0) {
        loadTilemap(jsonFile);
        loadTileset(tilesetFile);
    }

    ~Tilemap() {
        if (tilesetTexture) {
            SDL_DestroyTexture(tilesetTexture);
        }
    }

    void render() {
        for (const auto& layer : layers) {
            for (const auto& tile : layer.tiles) {
                SDL_Rect srcRect{
                    (tile.id % tilesetCols) * tileSize,
                    (tile.id / tilesetCols) * tileSize,
                    tileSize,
                    tileSize
                };

                SDL_Rect destRect{
                    tile.x * tileSize - camera->getView().x,
                    tile.y * tileSize - camera->getView().y,
                    tileSize,
                    tileSize
                };

                SDL_RenderCopy(renderer, tilesetTexture, &srcRect, &destRect);
            }
        }
    }

private:
    struct Tile {
        int id;
        int x;
        int y;
    };

    struct Layer {
        std::string name;
        std::vector<Tile> tiles;
        bool collider;
    };

    SDL_Renderer* renderer;
    Camera* camera;
    SDL_Texture* tilesetTexture;
    int tileSize;
    int mapWidth;
    int mapHeight;
    int tilesetCols;
    std::vector<Layer> layers;

    void loadTilemap(const std::string& jsonFile) {
        std::ifstream file(jsonFile);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open tilemap file.");
        }

        json data;
        file >> data;

        tileSize = data["tileSize"].get<int>();
        mapWidth = data["mapWidth"].get<int>();
        mapHeight = data["mapHeight"].get<int>();

        for (const auto& layerData : data["layers"]) {
            Layer layer;
            layer.name = layerData["name"].get<std::string>();
            layer.collider = layerData["collider"].get<bool>();

            for (const auto& tileData : layerData["tiles"]) {
                Tile tile;
                tile.id = std::stoi(tileData["id"].get<std::string>());
                tile.x = tileData["x"].get<int>();
                tile.y = tileData["y"].get<int>();
                layer.tiles.push_back(tile);
            }

            layers.push_back(layer);
        }
    }

    void loadTileset(const std::string& tilesetFile) {
        SDL_Surface* surface = IMG_Load(tilesetFile.c_str());
        if (!surface) {
            throw std::runtime_error("Failed to load tileset image.");
        }

        tilesetTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!tilesetTexture) {
            throw std::runtime_error("Failed to create texture from tileset.");
        }

        int textureWidth, textureHeight;
        SDL_QueryTexture(tilesetTexture, nullptr, nullptr, &textureWidth, &textureHeight);
        tilesetCols = textureWidth / tileSize;
    }
};
