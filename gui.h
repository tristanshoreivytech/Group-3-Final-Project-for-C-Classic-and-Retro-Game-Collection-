#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL.h>

#include "board.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 1200;

const int TILE_SIZE = 150;

namespace GUI {
    void initSDL();
    void cleanupSDL(SDL_Renderer* renderer, SDL_Window* window);

    SDL_Window* createSDLWindow();
    SDL_Renderer* createSDLRenderer(SDL_Window* window);

    void drawChessboard(SDL_Renderer* renderer, Board* board);
    int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);

    void handleMouseClicked(SDL_MouseButtonEvent event, Board* board);
    void handleKeyPressed(SDL_KeyboardEvent event, Board* board);

    std::pair<int, int> getBoardIndices(int x, int y);

}  // namespace GUI

#endif 