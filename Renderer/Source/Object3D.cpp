#include "Object3D.h"

Object3D::Object3D()
{
}

Object3D::Object3D(const std::vector<OBJpolygon>& coords_mesh, unsigned int shader_program_id) :
	obj_coords_mesh(coords_mesh), program_id(shader_program_id)
{
	obj_mesh_length = obj_coords_mesh.size();
	obj_mesh = new VertexArrayObject[obj_mesh_length];
	is_there_tex = false;
}

Object3D::Object3D(const std::vector<OBJpolygon>& coords_mesh, unsigned int shader_program_id, Texture* texture) :
	obj_coords_mesh(coords_mesh), program_id(shader_program_id), obj_tex(texture)
{
	obj_mesh_length = obj_coords_mesh.size();
	obj_mesh = new VertexArrayObject[obj_mesh_length];
	is_there_tex = true;
}

Object3D::~Object3D()
{
	delete[] obj_mesh;
}


void Object3D::bindVertexArrayObjectToMesh()
{
	VertexBuffer* vb;
	IndexBuffer* ib;

	for (int i = 0; i < obj_coords_mesh.size(); i++)
	{
		vb = new VertexBuffer(obj_coords_mesh[i]);

		vb->evaluatePosAttribFromShader("position", program_id);
		vb->evaluateTexAttribFromShader("texcoord", program_id);
		vb->evaluateNormalAttribFromShader("normal", program_id);
		vb->setPosAttribs(3, 8, 0);
		vb->setTexAttribs(2, 8, 3);
		vb->setNormalAttribs(3, 8, 5);

		ib = new IndexBuffer(obj_coords_mesh[i].edge);

		if (!is_there_tex) {
			one_polygon_of_mesh = new VertexArrayObject(vb, ib);
			one_polygon_of_mesh->addBuffer();
		}
		else {
			one_polygon_of_mesh = new VertexArrayObject(vb, ib, obj_tex);
			one_polygon_of_mesh->addBuffer();
		}

		obj_mesh[i] = *one_polygon_of_mesh;
	}


}

void Object3D::changeTextureOfOneMesh(Texture* tex, unsigned int mesh_index)
{
	obj_mesh[mesh_index].changeTexture(tex);
}

void Object3D::deleteObject()
{

}
