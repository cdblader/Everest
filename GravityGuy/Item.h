/**********************************************************************************
// Item (Arquivo de Cabe�alho)
//
// Cria��o:     14 Mai 2012
// Atualiza��o: 31 Ago 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define um item de menu
//
**********************************************************************************/

#ifndef _GRAVITYGUY_ITEM_H_
#define _GRAVITYGUY_ITEM_H_

// ---------------------------------------------------------------------------------

#include "Object.h"
#include "Animation.h"
#include "TileSet.h"
#include "Types.h"

// ---------------------------------------------------------------------------------

enum MenuState { SELECTED, NOTSELECTED };

// ---------------------------------------------------------------------------------

class Item : public Object
{
private:
    TileSet* tileset;                // folha de sprites da anima��o
    Animation* animation;              // anima��o do menu

public:
    Item(float posX, float posY, uint menuId, string imgFile);
    ~Item();

    void Select();                      // seleciona menu
    void UnSelect();                    // desmarca sele��o
    bool Tutorial();

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif