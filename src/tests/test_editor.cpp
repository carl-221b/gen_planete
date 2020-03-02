#include "../include/noisyheight_editor.h"
#include "../include/icosphere.h"

#include <gtest/gtest.h>

TEST(EditorTest, creation_noisyheight) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Editor* ed = new NoisyHeight_Editor(shape);
    EXPECT_NE (ed,  nullptr);
    delete ed;
    delete shape;
}

TEST(EditorTest, edit_noisyheight) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Editor* ed = new NoisyHeight_Editor(shape);
    ed->edit();
    EXPECT_NO_FATAL_FAILURE();
    delete ed;
    delete shape;
}
