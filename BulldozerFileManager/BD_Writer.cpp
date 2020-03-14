#include "pch.h"
#include "BD_Writer.h"

BD_Writer::BD_Writer() {

}

BD_Writer::~BD_Writer() {

}

void BD_Writer::AppendVertex(vec3d vertex) {
	m_vertices.push_back(vertex);
}

void BD_Writer::AppendIndices(int indice) {
	m_indices.push_back(indice);
}

void BD_Writer::AppendNormal(vec3d normal) {
	m_normals.push_back(normal);
}

void BD_Writer::AppendUVcoord(vec2d uv) {
	m_uv_coord.push_back(uv);
}

void BD_Writer::ToBinary(std::string filepath, std::string filename) {
	std::string ddir = filepath + filename + ".msh";

	std::ofstream bFile;
	bFile.open(ddir.c_str(), std::ios::binary);

	if (!bFile) {
		dispErrorMessageBox(TEXT("Cannot create bin file. See console for details."));
		std::cerr << "Cannot create bin file : " << ddir;

		return;
	}

	int nbrVertices = m_vertices.size();
	int nbrIndice = m_indices.size();
	int nbrNormal = m_normals.size();
	int nbrUVcoord = m_uv_coord.size();

	bFile.write(reinterpret_cast<const char*>(&nbrVertices), sizeof(int));

	for (int i = 0; i < nbrVertices; i++) {
		bFile.write(reinterpret_cast<const char*>(&m_vertices[i]), sizeof(vec3d));
	}

	bFile.write(reinterpret_cast<const char*>(&nbrIndice), sizeof(int));

	for (int i = 0; i < nbrIndice; i++) {
		bFile.write(reinterpret_cast<const char*>(&m_indices[i]), sizeof(int));
	}

	bFile.write(reinterpret_cast<const char*>(&nbrNormal), sizeof(int));

	for (int i = 0; i < nbrNormal; i++) {
		bFile.write(reinterpret_cast<const char*>(&m_normals[i]), sizeof(vec3d));
	}

	bFile.write(reinterpret_cast<const char*>(&nbrUVcoord), sizeof(int));

	for (int i = 0; i < nbrUVcoord; i++) {
		bFile.write(reinterpret_cast<const char*>(&m_uv_coord[i]), sizeof(vec2d));
	}

	bFile.close();
}

void BD_Writer::ClearWriter() {
	m_indices.clear();
	m_vertices.clear();
	m_normals.clear();
	m_uv_coord.clear();
}