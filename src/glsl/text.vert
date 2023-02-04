#version 330 core
layout(location = 0) in vec2 input_pos;
layout(location = 1) in vec2 input_tex_coords;

out vec2 tex_coords;
uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(input_pos, 0.0, 1.0);
    tex_coords = input_tex_coords;
}