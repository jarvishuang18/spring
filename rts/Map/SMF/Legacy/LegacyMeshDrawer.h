/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef _LEGACY_MESH_DRAWER_H_
#define _LEGACY_MESH_DRAWER_H_

#include "Map/SMF/IMeshDrawer.h"
#include "System/float3.h"


class CVertexArray;
class CCamera;
class CSMFReadMap;
class CSMFGroundDrawer;


/**
 * Map drawer implementation
 */
class CLegacyMeshDrawer : public IMeshDrawer
{
public:
	CLegacyMeshDrawer(CSMFReadMap* rm, CSMFGroundDrawer* gd);
	~CLegacyMeshDrawer();

	void Update() {}

	void DrawMesh(const DrawPass::e& drawPass);
	void DrawShadowMesh();

private:
	void FindRange(const CCamera* cam, int& xs, int& xe, int y, int lod);

	void DrawVertexAQ(CVertexArray* ma, int x, int y);
	void DrawVertexAQ(CVertexArray* ma, int x, int y, float height);
	void EndStripQ(CVertexArray* ma);
	void DrawGroundVertexArrayQ(CVertexArray*& ma);

	void DoDrawGroundRow(const CCamera* cam, int bty);
	void DoDrawGroundShadowLOD(int nlod);

#ifdef USE_GML
	static void DoDrawGroundRowMT(void* c, int bty);
	static void DoDrawGroundShadowLODMT(void* c, int nlod);
#endif

	bool BigTexSquareRowVisible(const CCamera* cam, int) const;

private:
	CSMFReadMap* smfReadMap;
	CSMFGroundDrawer* smfGroundDrawer;

	float3 lastCamPos;
	float maxCamDeltaDistSq;
	int numBigTexX;
	int numBigTexY;

	int viewRadius;
	int neededLod;

	bool waterDrawn;
};

#endif // _LEGACY_MESH_DRAWER_H_
