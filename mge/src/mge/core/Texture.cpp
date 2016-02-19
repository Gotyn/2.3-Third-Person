#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "mge/core/Texture.hpp"

std::map<std::string, Texture*> Texture::_textures; // for static texturs var

Texture::Texture() {
    glGenTextures (1, &_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

GLuint Texture::getId() {
	return _id;
}

// importer for textures
Texture* Texture::load(std::string pName, GLenum internalFormat, GLenum format, bool shadow)
{
    Texture* texture = 0;

    //try to locate texture
   	std::map<std::string, Texture*>::iterator textureIterator = _textures.find(pName);

   	if (textureIterator == _textures.end()) {
        if(!shadow) {
            texture = _loadFromFile(pName);
            std::cout << "Texture " << pName << " with id " << texture->getId() << " loaded." << std::endl;
            std::cout << "Caching texture." << std::endl;
            _textures[pName] = texture;
        } else {
            texture = _createTextureForShadow(&internalFormat, &format);
            std::cout << "Shadow map texture " << pName << " with id " << texture->getId() << " loaded." << std::endl;
            std::cout << "Caching texture." << std::endl;
            _textures[pName] = texture;
        }
    } else {
        std::cout << "Returning cached texture " << pName << std::endl;
        texture = textureIterator->second;
    }

    return texture;
}

Texture* Texture::_loadFromFile(std::string pName) {
    // load from file and store in cache
    sf::Image image;
    if (image.loadFromFile(pName)) {
        //normal image 0,0 is top left, but opengl uv 0,0 is bottom left, so we flip the image internally
        image.flipVertically();
        //create a wrapper for the id (texture is nothing more than that) and
        //load corresponding data into opengl using this id
        Texture * texture = new Texture();
        glBindTexture (GL_TEXTURE_2D, texture->getId());
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //here don't really know what index should be supplied to internalFormat/format
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glBindTexture(GL_TEXTURE_2D, 0);
        return texture;
    } else {
        return 0;
    }
}

Texture* Texture::_createTextureForShadow(GLenum* internalFormat, GLenum* format)
{
    Texture * texture = new Texture();
    glBindTexture (GL_TEXTURE_2D, texture->getId());
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D (GL_TEXTURE_2D, 0, internalFormat[0], 1024, 1024, 0, format[0], GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}








