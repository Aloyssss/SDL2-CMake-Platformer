
#include "Header.h"
#include "Camera.h"
#include <fstream>

// scale factor TO BE REMOVED
const float scale = 2.f;

using json = nlohmann::json;

/* Tilemap class definition */
class Tilemap 
{
public:
    // Constructeur / Destructeur
    Tilemap(const std::string& jsonFile, const std::string& tilesetFile, SDL_Renderer* renderer, Camera* camera);
    ~Tilemap();

    // Tilemap rendering
    void render(SDL_Renderer* renderer);

    // Getters / <setters
    Vector2i getWorldBounds(void) const { return Vector2i(_mapWidth * _tileSize * scale, _mapHeight * _tileSize * scale); }

private:
    struct Tile 
    {
        int id;
        int x;
        int y;
    };

    struct Layer 
    {
        std::string name;
        std::vector<Tile> tiles;
        bool collider;
    };

    SDL_Renderer* _renderer;
    Camera* _camera;
    SDL_Texture* _tilesetTexture;
    int _tileSize;
    int _mapWidth, _mapHeight;
    int _tilesetCols, _tilesetRows;
    std::vector<Layer> _layers;

    // Load files
    void loadTilemap(const std::string& jsonFile);
    void loadTileset(const std::string& tilesetFile);
};
