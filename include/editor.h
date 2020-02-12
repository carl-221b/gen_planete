#ifndef EDITOR_H
#define EDITOR_H

#include <stdlib.h>
#include <map>

#include <geometry.h>
#include <string>



class Editor
{
    using namespace std;

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
    map<string,int> getColorsGenerated();
};

#endif // EDITOR_H
