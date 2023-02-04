#version 330 core

uniform sampler2D tex;

in vec2 tex_coords;
in float sel;

out vec4 frag_col;

void main() {
    if(sel == 0.0) {
        frag_col = texture(tex, tex_coords);
    }
    else {
        frag_col = vec4(texture(tex, tex_coords).xyz * 0.8, 1.0);
    }
}