#ifndef BASIC_EDITOR_H
#define BASIC_EDITOR_H

#include "editor.h"

class Basic_Editor : public Editor
{
public:
    Basic_Editor() {}
    ~Basic_Editor();
    surface_mesh::Surface_mesh modifyShape(surface_mesh::Surface_mesh surface_mesh);

private:

};

#endif // BASIC_EDITOR_H
