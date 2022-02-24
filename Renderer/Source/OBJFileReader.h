#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct OBJvertexcoords {
	float X;
	float Y;
	float Z;
};

struct OBJtexturecoords {
	float V;
	float U;
};

struct OBJnormalcoords {
	float X;
	float Y;
	float Z;
};

struct OBJface {
	int vertexcoord;
	int texturecoord;
	int normalcoord;
};

struct OBJfaceLines {
	std::string faceline;
};

struct OBJpolygon {
	int edge;
	std::vector<float> buffer;
};

class OBJFileReader {

private:
	const std::string& obj_filepath;
	static unsigned int total_obj_number;
	unsigned int obj_id = 0;

public:
	OBJFileReader(const std::string& filepath);
	~OBJFileReader();

	std::vector<OBJpolygon> getPolygonBuffer() const;

private:
	std::vector<OBJvertexcoords> vertexcoords;
	std::vector<OBJtexturecoords> texturecoords;
	std::vector<OBJnormalcoords> normalcoords;
	std::vector<OBJfaceLines> facelines;
	std::vector<OBJpolygon> polygons;
	std::vector<float> vertexbuffer;

	void OBJfileReader(const std::string& filepath);
	void PolygonReader();
};