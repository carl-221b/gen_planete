#ifndef EDITOR_H
#define EDITOR_H

#include <stdlib.h>
#include <map>

#include <geometry.h>
#include <string>



class Editor
{
public:

    Editor();

    /**
     * @brief modifyGeometry, modify the geometry given.
     */
    void modifyGeometry(Geometry&);

    /**
     * @brief getColorsGenerated, get the colors used by the editor.
     * @return
     */
    std::map<std::string,int> getColorsGenerated();
};

#endif // EDITOR_H
