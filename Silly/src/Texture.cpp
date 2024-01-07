#include "Texture.h"

Texture::Texture(){

}

void Texture::init() {

}

vector<s_Texture> Texture::getTextures() {
	return m_textures;
}

void Texture::assignTexture(s_Texture texture) {
	m_textures.push_back(texture);
}

void Texture::draw() {

}