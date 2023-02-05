#version 330 core

in vec2 tex_coords;

uniform sampler2D tex;

out vec4 frag_col;

void main() {
    vec4 col = texture(tex, tex_coords);
    frag_col = col;
}
