#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "GenMap.h"
#include "NoiseUtil.h"

void GenMap::_initMap() {
    _map.resize(_sizeX);

    for (int i = 0; i < _sizeX; i++) {
        _map[i].resize(_sizeY);
    }
}

int GenMap::_getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = min(x + 1, abs(x - _sizeX));
    int distanceY = min(y + 1, abs(y - _sizeY));
    return min(distanceX, distanceY);
}

void GenMap::_setMapFromPerlinNoise(float** noise) {
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            _map[i][j].setBiome(floor(noise[i][j] + 0.5));
        }
    }
}

int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

void GenMap::generate(int octaves, float lacunarity, float persistence) {
    float** noise = NoiseUtil::getWhiteNoise(_sizeX, _sizeY);

    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            if (_getDistanceFromOutOfBounds(i, j) <= max(min(_sizeX, _sizeY) / 20, 1)) {
                noise[i][j] = 0;
            }
        }
    }

    _setMapFromPerlinNoise(NoiseUtil::getPerlinNoise(octaves, lacunarity, persistence, _sizeX, _sizeY, noise));
}

void GenMap::printMap(bool useColor) {
    stringstream strstr;

    for (int i = _sizeY-1; i > -1; i--) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[j][i].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}
