#include "BlockRenderer.hpp"

BlockRenderer::BlockRenderer(Texture* texture,
                             Shader* shader,
                             Camera* camera) :
                             ModelRenderer(
                                {
                                    // far side
                                    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

                                    // side closer to the camera
                                    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,

                                    // left side
                                    0.0f, 1.0f, 1.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

                                    // right side
                                    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
                                    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

                                    // top side
                                    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f,   0.0f, 0.0f,

                                    // bottom side
                                    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                                    0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,   0.0f, 0.0f
                                },
                                {
                                    0, 1, 2,
                                    1, 2, 3,

                                    4, 5, 6,
                                    5, 6, 7,

                                    8, 9, 10,
                                    9, 10, 11,

                                    12, 13, 14,
                                    13, 14, 15,

                                    16, 17, 18,
                                    17, 18, 19,

                                    20, 21, 22,
                                    21, 22, 23
                                },
                                texture, shader, camera
                             )
{ }
