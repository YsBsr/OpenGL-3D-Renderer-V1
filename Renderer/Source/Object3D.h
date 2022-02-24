#pragma once

#include <iostream>
#include <vector>

#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "OBJFileReader.h"


class Object3D {

public:
	std::vector<OBJpolygon> obj_coords_mesh;
	unsigned int program_id;
	Texture* obj_tex;
	VertexArrayObject* obj_mesh;
	unsigned int obj_mesh_length;

private:
	unsigned int object3d_id = 0;
	VertexArrayObject* one_polygon_of_mesh;

	bool is_there_tex;

	VertexBuffer vb;
	IndexBuffer ib;

public:
	Object3D();
	Object3D(const std::vector<OBJpolygon>& coords_mesh, unsigned int shader_program_id);
	Object3D(const std::vector<OBJpolygon>& coords_mesh, unsigned int shader_program_id, Texture* texture);
	~Object3D();

	void bindVertexArrayObjectToMesh();

	void changeTextureOfOneMesh(Texture* tex, unsigned int mesh_index);

	void deleteObject();
};