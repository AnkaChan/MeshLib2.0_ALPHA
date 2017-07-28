#include <algorithm>
#include <iostream>
#include <MeshLib/core/Mesh/BaseMesh.h>
#include <MeshLib/core/Mesh/Interface.h>
#include <MeshLib/core/Mesh/Vertex.h>
#include <MeshLib/core/Mesh/HalfEdge.h>
#include <MeshLib/core/Mesh/Edge.h>
#include <MeshLib/core/Mesh/Face.h>
#include <MeshLib/core/Mesh/iterators_new.h>

using namespace MeshLib;
class myVertex : public CVertex {
public:
	int num = 0;
};
class myHalfedge : public CHalfEdge {
public:
	int num = 10;
};
using std::cout;
using std::endl;
int main() {
	typedef CInterface<myVertex, CEdge, CFace, myHalfedge> Interface;
	typedef CIteratorsI<Interface> Iterators;
	typedef Interface::MeshType CMesh;

	std::vector<int> v(10);
	for (int& i : v) {
		i = 0;
	}

	CMesh mesh;
	mesh.read_m("D:/Data/Mesh/outputs/face125.m");
	Iterators::MEIterator meIter(&mesh);
	cout << "Iterating Edges." << endl;
	for (auto pE : meIter) {
		Interface::VertexPtr pV1, pV2;
		pV1 = Interface::edgeVertex1(pE);
		pV2 = Interface::edgeVertex2(pE);

		cout << "The edge's length:" << Interface::edgeLength(pE)
			<< "\nThe two vertice are: " << Interface::vertexId(pV1) << ", " << Interface::vertexId(pV2) << endl;

		cout << "Vertex 1: " << pV1->point() << endl;
		cout << "Vertex 2: " << pV2->point() << endl;

	}

	Iterators::MVIterator mvIter(&mesh);
	cout << "Iterating Edges." << endl;
	for (auto pV : mvIter) {
		cout << "Vertex id: " << Interface::vertexId(pV) << " Position: " << pV->point() << endl;
		Iterators::VOutHEIterator voutheIter(pV);
		for (auto pHE : voutheIter) {
			cout << "The halfedge: " << pHE << endl;
			Interface::VertexPtr pTargetV = Interface::halfedgeTarget(pHE);
			cout << "Target vertex id: " << Interface::vertexId(pTargetV) << endl;
		}
	}

	getchar();

	Interface::VertexPtr pV = mesh.idVertex(10);
	Iterators::VCcwOutHEIterator vheiter(pV);
	for (Interface::HalfEdgePtr pHE : vheiter) {
		std::cout << "This is the halfedge pointer:" << (int)pHE << std::endl;
	}
	  
	auto find_zero = [] (const int& a) {return a == 0; };
	auto zeros = std::find_if(v.begin(), v.end(), find_zero);

	/*Iterators::VCcwOutHEIterator vccwheiter(pV);
	for (Interface::HalfEdgePtr pHE : vccwheiter) {
		std::cout << "This is the halfedge pointer:" << (int)pHE << std::endl;
	}*/
	getchar();
}