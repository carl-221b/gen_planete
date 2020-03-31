#ifndef SHAPE_REPOSITORY_H
#define SHAPE_REPOSITORY_H

#include "shape.h"

#define DEFAULT_SAVE_PATH "./planet"

/**
 * @brief interface to manage saves and loads of shapes
 */
class Shape_Repository {
public:

     static char *FILE_SAVE_OUTPUT;

    /**
     * @brief Saves the planet into a .obj format file, does not include the color yet
     *
     */
    static void saveOBJ(Shape* shape, const std::string& filename);

    /**
     * @brief Saves the planet into a .off format file, does not include the color yet
     *
     */
    static void saveOFF(Shape* shape, const std::string& filename);
};

#endif // SHAPE_REPOSITORY_H
