#include "CPURasterizerLocal.h"

// Local defines
#define PUT3(V) buf[carr] = V.x; buf[carr + 1] = V.y; buf[carr + 2] = V.z; carr += 3;
#define PUT2(V) buf[carr] = V.x; buf[carr + 1] = V.y; carr += 2;

// GLOBAL FUNCTIONS
float* LoadModel(char *fileName, int * total, int * mask) {
	printf("[LOADER] Loading %s\n", fileName);
	const struct aiScene *scene = aiImportFile(fileName,
			aiProcess_CalcTangentSpace | aiProcess_Triangulate
					| aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (!scene) {
		printf("[LOADER] Scene not created!\n");
		return NULL;
	}

	int numMeshes = 0;

	printf("[LOADER] There is %d mesh in total\n", (numMeshes = scene->mNumMeshes));

	int totalVertices = 0;

	for (int i = 0; i < numMeshes; i++) {
		struct aiMesh * mesh = scene->mMeshes[i];
		totalVertices += 3 * mesh->mNumFaces;

		int totalFaces = mesh->mNumFaces;
		int totalVertices = mesh->mNumVertices;
		printf("[LOADER][MESH:%d] Total faces: %d, Total vertices: %d\n", (i + 1), totalFaces, totalVertices);

		if (mesh->mVertices != NULL) {
			*mask |= VERTEX_COORDS;
			printf("[LOADER][MESH:%d] Mesh has vertices\n", (i + 1));
		}
		if (mesh->mTextureCoords[0] != NULL) {
			*mask |= TEXTURE_COORDS;
			printf("[LOADER][MESH:%d] Mesh has texture coords\n", (i + 1));
		}
		if (mesh->mNormals != NULL) {
			*mask |= NORMAL;
			printf("[LOADER][MESH:%d] Mesh has normals\n", (i + 1));
		}
	}

	*total = totalVertices;

	printf("[LOADER] There is %d vertices in total\n", totalVertices);

	float * buf = calloc(totalVertices * CalcVertexSizeByMask(*mask), sizeof(float));
	int carr = 0;

	printf("[LOADER] One vertex costs %d bytes\n", CalcVertexSizeByMask(*mask));

	if (buf == NULL) {
		printf("[LOADER] Cad calloc!\n");
		return NULL;
	}

	for (int i = 0; i < numMeshes; i++) {
		struct aiMesh * mesh = scene->mMeshes[i];

		for (int j = 0; j < mesh->mNumFaces; j++) {
			struct aiFace face = mesh->mFaces[j];
			int totalInd = face.mNumIndices;
			for (int k = 0; k < totalInd; k++) {
				int ind = face.mIndices[k];
				if (mesh->mVertices != NULL) {
					PUT3(mesh->mVertices[ind]);
				}
				if (mesh->mTextureCoords[0] != NULL) {
					PUT2(mesh->mTextureCoords[0][ind]);
				}
				if (mesh->mNormals != NULL) {
					PUT3(mesh->mNormals[ind]);
				}
			}
		}

	}

	aiReleaseImport(scene);

	printf("[LOADER] Model loading is OK\n");

	return buf;
}
