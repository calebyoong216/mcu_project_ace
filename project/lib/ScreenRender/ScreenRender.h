#include <Arduino.h>

static constexpr size_t kMaxObjects { 10 };
static constexpr size_t kSpriteMaxPixels { 20 };

struct Pixel {
    size_t row;
    size_t col;
    char character = '\0';
};

struct ScreenObject {
    Pixel sprite[kSpriteMaxPixels];
    bool display = false;
};

class ScreenRender {
public:
    explicit ScreenRender(size_t height, size_t width);
    void UpdateScreen();
    int AddObject();
    ScreenObject objects[kMaxObjects];
};
