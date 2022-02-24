#include "OBJFileReader.h"

unsigned int OBJFileReader::total_obj_number = 0;

OBJFileReader::OBJFileReader(const std::string& filepath) : obj_filepath(filepath), obj_id(total_obj_number++)
{
	OBJfileReader(obj_filepath);
}

OBJFileReader::~OBJFileReader()
{
	vertexcoords.clear();
	texturecoords.clear();
	normalcoords.clear();
	facelines.clear();
	polygons.clear();

	total_obj_number -= 1;
}

void OBJFileReader::OBJfileReader(const std::string& filepath)
{
	std::ifstream stream(filepath, std::ios::binary);

	if (!stream.is_open()) {
		std::cout << "couldnt load a file" << std::endl;
		return;
	}

	std::string line;

	int i = 0;
	int t = 0;

	std::string token;

	OBJvertexcoords v_coord;
	OBJtexturecoords t_coord;
	OBJnormalcoords n_coord;
	OBJfaceLines faceline;

	while (getline(stream, line)) {
		if (i++ < 2) continue;
		if (line[0] == 'v' && line[1] == ' ') {
			t = 0;
			for (int pos = 0; pos < line.length(); pos++)
			{
				if (line[pos] == ' ') {
					i = pos + 1;
					while (line[i] != ' ' && i < line.length()) {
						token += line[i++];
					}
					t++;
					if (t == 1) {
						v_coord.X = std::stof(token);
					}
					else if (t == 2) {
						v_coord.Y = std::stof(token);
					}
					else if (t == 3) {
						v_coord.Z = std::stof(token);
						vertexcoords.push_back(v_coord);
						t = 0;
					}
					//std::cout << std::stof(token) << std::endl;
					token.clear();
				}
			}
		}
		else if (line[0] == 'v' && line[1] == 't') {
			t = 0;
			for (int pos = 0; pos < line.length(); pos++)
			{
				if (line[pos] == ' ') {
					i = pos + 1;
					while (line[i] != ' ' && i < line.length()) {
						token += line[i++];
					}
					t++;
					if (t == 1) {
						t_coord.U = std::stof(token);
					}
					else if (t == 2) {
						t_coord.V = std::stof(token);
						texturecoords.push_back(t_coord);
						t = 0;
					}
					//std::cout << std::stof(token) << std::endl;
					token.clear();
				}
			}
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			t = 0;
			for (int pos = 0; pos < line.length(); pos++)
			{
				if (line[pos] == ' ') {
					i = pos + 1;
					while (line[i] != ' ' && i < line.length()) {
						token += line[i++];
					}
					t++;
					if (t == 1) {
						n_coord.X = std::stof(token);
					}
					else if (t == 2) {
						n_coord.Y = std::stof(token);
					}
					else if (t == 3) {
						n_coord.Z = std::stof(token);
						normalcoords.push_back(n_coord);
						t = 0;
					}
					//std::cout << std::stof(token) << std::endl;
					token.clear();
				}
			}
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			faceline.faceline = line;
			facelines.push_back(faceline);
		}
	}

	stream.close();
	
	PolygonReader();

	return;
}

void OBJFileReader::PolygonReader()
{
	int i = 0;
	int t = 0;
	int slash = 0;

	std::string token;
	int a = 0;

	std::vector<OBJface> faces;

	int vertexnum = 0;

	OBJpolygon polygon;

	for (int k = 0; k < facelines.size(); k++)
	{
		t = 0;
		OBJface face;
		for (int pos = 0; pos < facelines[k].faceline.length(); pos++)
		{
			if (facelines[k].faceline[pos] == '/') slash += 1;

			if (slash == 6) vertexnum = 3;
			if (slash == 8) vertexnum = 4;
		}
		slash = 0;
		for (int pos = 0; pos < facelines[k].faceline.length(); pos++)
		{
			if (facelines[k].faceline[pos] == ' ' || facelines[k].faceline[pos] == '/') {
				i = pos + 1;
				while (facelines[k].faceline[i] != '/' && facelines[k].faceline[i] != '/' && i < facelines[k].faceline.length()) {
					token += facelines[k].faceline[i++];
				}
				t++;
				i++;
				if (token.length() < 2)
				{
					if (t == 1) {
						face.vertexcoord = (int)*token.c_str() - (int)'0';
					}
					else if (t == 2) {
						face.texturecoord = (int)*token.c_str() - (int)'0';
					}
					else if (t == 3) {
						face.normalcoord = (int)*token.c_str() - (int)'0';
						faces.push_back(face);
						t = 0;
					}
				}
				else
				{
					if (t == 1) {
						face.vertexcoord = std::stoi(token);
					}
					else if (t == 2) {
						face.texturecoord = std::stoi(token);
					}
					else if (t == 3) {
						face.normalcoord = std::stoi(token);
						faces.push_back(face);
						t = 0;
					}
				}

				token.clear();
			}
		}

		a = faces.size();

		for (int c = a - vertexnum; c < a; c++)
		{
			vertexbuffer.push_back(vertexcoords[faces[c].vertexcoord - 1].X);
			vertexbuffer.push_back(vertexcoords[faces[c].vertexcoord - 1].Y);
			vertexbuffer.push_back(vertexcoords[faces[c].vertexcoord - 1].Z);
			vertexbuffer.push_back(texturecoords[faces[c].texturecoord - 1].U);
			vertexbuffer.push_back(texturecoords[faces[c].texturecoord - 1].V);
			vertexbuffer.push_back(normalcoords[faces[c].normalcoord - 1].X);
			vertexbuffer.push_back(normalcoords[faces[c].normalcoord - 1].Y);
			vertexbuffer.push_back(normalcoords[faces[c].normalcoord - 1].Z);
		}

		polygon.edge = vertexnum;
		polygon.buffer = vertexbuffer;

		polygons.push_back(polygon);

		vertexbuffer.clear();
	}
}

std::vector<OBJpolygon> OBJFileReader::getPolygonBuffer() const
{
	return polygons;
}
