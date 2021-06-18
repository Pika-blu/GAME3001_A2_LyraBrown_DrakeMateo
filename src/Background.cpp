#include "Background.h"
#include "TextureManager.h"
#include <fstream>
#include<cstring>
#include <sstream>
#include<cstdlib>

using namespace std;
Background::Background()
{
	TextureManager::Instance().load("../Assets/textures/tileMap.png", "background");

	auto size = TextureManager::Instance().getTextureSize("background");
	setWidth(size.x);
	setHeight(size.y);

	getRigidBody()->isColliding = false;
	setType(BACKGROUND);
    
	//Tile build
	string filename = "../Assets/data/desertMap.txt";
	ifstream input;
	input.open(filename.c_str());
    if (input.is_open()) 
    {
        string line;
        getline(input, line);
        stringstream ss(line);
        ss >> m_maxRows;
        ss >> m_maxCols;
        //cout << m_maxRows << " " << m_maxCols << endl;
        //create the 2 dimensional array of size maxRows and maxCols
        m_mapData = new int* [m_maxRows];
        for (int x = 0; x < m_maxRows; x++) {
            m_mapData[x] = new int[m_maxCols];
        }
        // load the array
        for (int r = 0; r < m_maxRows; r++) {
            getline(input, line);
            stringstream ss(line);
            for (int c = 0; c < m_maxCols; c++) {
                ss >> m_mapData[r][c];
            }
        }

        input.close();
    }
   
}

string Background::printMap() const
{
    stringstream s;
    for (int row = 0; row < m_maxRows; row++)
    {
        for (int col = 0; col < m_maxCols; col++) 
        {
            
           if (m_mapData[row][col] == 0) {
                    s << "0";
           }
           if (m_mapData[row][col] == 1) {
                    s << "1";
           }
            
        }
        s << "\n";
    }
    return s.str();
}

Background::~Background()
= default;

void Background::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance().draw("background", 0, 0, 0, 255, false);
}

void Background::update()
{
}

void Background::clean()
{
}

