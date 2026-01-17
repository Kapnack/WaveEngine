TileMap::TileMap(const string& mapFilePath, const string& texturePath, const Vector2& textureSize)
{
    TextureImporter textureImporter;
    textureImporter.LoadTexture(texturePath);
    texture = textureImporter.GetLoadedTexture();

    this->textureSize = textureSize;

    ImportTileMap(mapFilePath);
}
