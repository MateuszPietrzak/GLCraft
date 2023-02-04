//
// Created by mateuszp on 2/2/23.
//

#include "../../include/TextRenderer.h"

TextRenderer::TextRenderer() {

}

void TextRenderer::init(int scr_width, int scr_height) {
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        std::cout << "Freetype init error\n";
        return;
    }

    FT_Face face;
    if(FT_New_Face(ft, "assets/fonts/font.ttf", 0, &face)) {
        std::cout << "Freetype could not load font\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "Freetype could not load glyph\n";
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned char i = 0; i < 128; ++i) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cout << "Freetype coud no load char " << i << '\n';
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
                );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (unsigned int)face->glyph->advance.x
        };

        characters.insert(std::pair<char, Character>(i, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    projection = glm::ortho(0.0f, (float)scr_width, 0.0f, (float)scr_height);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    shader = Shader("src/glsl/text.vert", "src/glsl/text.frag");

    shader.use();
    shader.setMat4("projection", projection);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void TextRenderer::render(std::string text, float x, float y, float scale, glm::vec3 color) {
    shader.use();
    shader.setVec3("text_color", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for(auto& c: text) {
        Character ch = characters[c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (float)(ch.advance >> 6) * scale;
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glBindVertexArray(0);
}

void TextRenderer::updateWindowSize(int new_width, int new_height) {
    projection = glm::ortho(0.0f, (float)new_width, 0.0f, (float)new_height);
}

