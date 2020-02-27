#include "../include/noisyheight_editor.h"
#include "../include/mesh.h"

#include <gtest/gtest.h>

TEST(EditorTest, creation) {

    Shape* shape = new Mesh(DATA_DIR"/models/icosa.obj");
    Editor* ed = new NoisyHeight_Editor(shape);
    EXPECT_NE (ed,  nullptr);
    delete ed;
    delete shape;
}

TEST(EditorTest, edit) {

    Shape* shape = new Mesh(DATA_DIR"/models/icosa.obj");
    Editor* ed = new NoisyHeight_Editor(shape);
    ed->edit();
    EXPECT_NO_FATAL_FAILURE();
    delete ed;
    delete shape;
}
