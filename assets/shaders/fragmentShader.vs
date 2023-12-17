#version 330 core
out vec4 FragColor;

// in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D sTexture;
uniform sampler2D sTexture2;

void main() {
    FragColor = mix(texture(sTexture, TexCoord), texture(sTexture2, TexCoord), 0.5);
}