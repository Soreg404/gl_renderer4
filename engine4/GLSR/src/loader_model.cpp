#include "glsr.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


glr::sMesh loadMesh(aiMesh *mesh) {
	
	glr::sMesh ret = glr::getRef<glr::Mesh>();
	unsigned offs = 0, offsNorm = 0, offsUv = 0;
	if(mesh->mVertices) { ret->vAttributes.push_back({ 0 }); offs += 3; }
	if(mesh->mNormals) { ret->vAttributes.push_back({ 1 }); offsNorm = offs * sizeof(float); offs += 3; }
	if(mesh->mTextureCoords[0]) { ret->vAttributes.push_back({ 2 }); offsUv = offs * sizeof(float); }

	unsigned strd = 0;
	for(int i = 0; i < ret->vAttributes.size(); i++) strd += ret->vAttributes.at(i).byteSize; // needsfix

	char *verts = new char[mesh->mNumVertices * strd];

	if(mesh->mVertices) {
		for(size_t i = 0; i < mesh->mNumVertices; i++)
			*reinterpret_cast<aiVector3D *>(verts + i * strd) = mesh->mVertices[i];
	}
	if(mesh->mNormals) {
		for(size_t i = 0; i < mesh->mNumVertices; i++)
			*reinterpret_cast<aiVector3D *>(verts + i * strd + offsNorm) = mesh->mNormals[i];
	}
	if(mesh->mTextureCoords[0]) {
		for(size_t i = 0; i < mesh->mNumVertices; i++)
			*reinterpret_cast<aiVector3D *>(verts + i * strd + offsUv) = mesh->mTextureCoords[0][i];
	}

	ret->setBuffer(GLR_VERTEX_BUFFER, glr::getUniq<glr::model::Buffer>(verts, mesh->mNumVertices *strd, mesh->mNumVertices, strd));

	if(mesh->mNumFaces) {
		unsigned *inds = new unsigned[mesh->mNumFaces * mesh->mFaces[0].mNumIndices];

		for(unsigned i = 0; i < mesh->mNumFaces; i++) {
			aiFace *curr = mesh->mFaces + i;
			for(size_t j = 0; j < curr->mNumIndices; j++) {
				inds[i * mesh->mFaces[0].mNumIndices + j] = curr->mIndices[j];
			}
		}

		unsigned iCount = mesh->mNumFaces * mesh->mFaces[0].mNumIndices;
		ret->setBuffer(GLR_INDEX_BUFFER, glr::getUniq<glr::model::Buffer>(inds, iCount * sizeof(unsigned), iCount));
	}

	return ret;

}

void processNodes(const aiScene *scene, aiNode *node, std::vector<glr::model::Object> *objs, unsigned *index = nullptr) {
	bool del = false;
	if(!index) {
		del = true;
		index = new unsigned{ 0 };
	} else {
		glr::model::Object o;

		for(unsigned int i = 0; i < node->mNumMeshes; i++) o.slots.push_back({ nullptr, loadMesh(scene->mMeshes[node->mMeshes[i]]) });
		objs->at(*index) = o;
		(*index)++;
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++) processNodes(scene, node->mChildren[i], objs, index);

	if(del) delete index;

}

unsigned countNodes(aiNode *root) {
	unsigned count = 1;
	for(unsigned i = 0; i < root->mNumChildren; i++) count += countNodes(root->mChildren[i]);
	return count;
}

glr::sModel glr::res::loadModel(const glr::Window *w, const char *path) {


	sModel ret = glr::getRef<glr::Model>();

	Assimp::Importer imp;
	const aiScene *scene = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode || !scene->mMeshes) {
		GLRLOG("ASSIMP ERROR: %s", imp.GetErrorString());
		return ret;
	}


	unsigned allNodes = countNodes(scene->mRootNode) - 1;
	if(!allNodes) { GLRLOG("%s; nothing to load", path); return ret; }

	ret->objects = std::vector<model::Object>(allNodes);

	processNodes(scene, scene->mRootNode, &ret->objects);

	if(w) {
		glfwMakeContextCurrent(w->getContext());
		ret->load();
	}

	return ret;

}