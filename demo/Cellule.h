#ifndef CELLULE_H_INCLUDED
#define CELLULE_H_INCLUDED
#include <SDL2/SDL.h>


class Cellule
{
public :
    Cellule();
    ~Cellule();

private :
    bool m_vie;
    int m_line;
    int m_column;
    SDL_Rect m_positionCellule;

};
#endif // CELLULE_H_INCLUDED
