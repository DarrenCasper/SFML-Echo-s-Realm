#include "Game.h"
#include "constants.h"

int main ()
{
    Game g { "Echo's Realm", screen_width, screen_height };
    g.start ();
}
