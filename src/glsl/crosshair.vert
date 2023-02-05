#version 330 core

layout (location = 0) in vec2 input_coords;

uniform mat4 projection;
uniform int width;
uniform int height;

out vec2 tex_coords;

void main() {
    gl_Position = projection * vec4((input_coords.x * 16) + (width/2) - 8, (input_coords.y * 16) + (height/2) - 8, 0.0, 1.0);
    tex_coords = input_coords;
}
