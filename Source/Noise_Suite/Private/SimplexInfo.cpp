// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplexInfo.h"

typedef struct LatticePoint2D LatticePoint2D;
typedef struct LatticePoint4D LarricePoint4D;
LatticePoint2D POINTS_2D[32];
LatticePoint3D *POINTS_3D[8];
LatticePoint4D POINTS_4D[256][256];
LatticePoint2D create2DPoint(int x, int y);
LatticePoint4D create4DPoint(int x, int y, int z, int w);

SimplexInfo::SimplexInfo()
{
	/*
		Setting up 2D lattice points
	*/
	for (int i = 0; i < 8; i++)
	{
		int i1, j1, i2, j2;
		if ((i & 1) == 0)
		{
			if ((i & 2) == 0) { i1 = -1; j1 = 0; }
			else { i1 = 1; j1 = 0; }
			if ((i & 4) == 0) { i2 = 0; j2 = -1; }
			else { i2 = 0; j2 = 1; }
		}
		else
		{
			if ((i & 2) != 0) { i1 = 2; j1 = 1; }
			else { i1 = 0; j1 = 1; }
			if ((i & 4) != 0) { i2 = 1; j2 = 2; }
			else { i2 = 1; j2 = 0; }
		}
		POINTS_2D[i * 4 + 0] = create2DPoint(0, 0);
		POINTS_2D[i * 4 + 1] = create2DPoint(1, 1);
		POINTS_2D[i * 4 + 2] = create2DPoint(i1, j1);
		POINTS_2D[i * 4 + 3] = create2DPoint(i2, j2);
	}

	/*
		Setting up 3D lattice points
	*/
	for (int i = 0; i < 8; i++)
	{
		int i1, j1, k1, i2, j2, k2;
		i1 = (i >> 0) & 1; j1 = (i >> 1) & 1; k1 = (i >> 2) & 1;
		i2 = i1 ^ 1; j2 = j1 ^ 1; k2 = k1 ^ 1;

		// The two points within this octant, one from each of the two cubic half-lattices.
		LatticePoint3D *c0 = new LatticePoint3D(i1, j1, k1, 0);
		LatticePoint3D *c1 = new LatticePoint3D(i1 + i2, j1 + j2, k1 + k2, 1);

		// (1, 0, 0) vs (0, 1, 1) away from octant.
		LatticePoint3D *c2 = new LatticePoint3D(i1 ^ 1, j1, k1, 0);
		LatticePoint3D *c3 = new LatticePoint3D(i1, j1 ^ 1, k1 ^ 1, 0);

		// (1, 0, 0) vs (0, 1, 1) away from octant, on second half-lattice.
		LatticePoint3D *c4 = new LatticePoint3D(i1 + (i2 ^ 1), j1 + j2, k1 + k2, 1);
		LatticePoint3D *c5 = new LatticePoint3D(i1 + i2, j1 + (j2 ^ 1), k1 + (k2 ^ 1), 1);

		// (0, 1, 0) vs (1, 0, 1) away from octant.
		LatticePoint3D *c6 = new LatticePoint3D(i1, j1 ^ 1, k1, 0);
		LatticePoint3D *c7 = new LatticePoint3D(i1 ^ 1, j1, k1 ^ 1, 0);

		// (0, 1, 0) vs (1, 0, 1) away from octant, on second half-lattice.
		LatticePoint3D *c8 = new LatticePoint3D(i1 + i2, j1 + (j2 ^ 1), k1 + k2, 1);
		LatticePoint3D *c9 = new LatticePoint3D(i1 + (i2 ^ 1), j1 + j2, k1 + (k2 ^ 1), 1);

		// (0, 0, 1) vs (1, 1, 0) away from octant.
		LatticePoint3D *cA = new LatticePoint3D(i1, j1, k1 ^ 1, 0);
		LatticePoint3D *cB = new LatticePoint3D(i1 ^ 1, j1 ^ 1, k1, 0);

		// (0, 0, 1) vs (1, 1, 0) away from octant, on second half-lattice.
		LatticePoint3D *cC = new LatticePoint3D(i1 + i2, j1 + j2, k1 + (k2 ^ 1), 1);
		LatticePoint3D *cD = new LatticePoint3D(i1 + (i2 ^ 1), j1 + (j2 ^ 1), k1 + k2, 1);

		// First two points are guaranteed.
		c0->NextOnFailure = c0->NextOnSuccess = c1;
		c1->NextOnFailure = c1->NextOnSuccess = c2;

		// If c2 is in range, then we know c3 and c4 are not.
		c2->NextOnFailure = c3; c2->NextOnSuccess = c5;
		c3->NextOnFailure = c4; c3->NextOnSuccess = c4;

		// If c4 is in range, then we know c5 is not.
		c4->NextOnFailure = c5; c4->NextOnSuccess = c6;
		c5->NextOnFailure = c5->NextOnSuccess = c6;

		// If c6 is in range, then we know c7 and c8 are not.
		c6->NextOnFailure = c7; c6->NextOnSuccess = c9;
		c7->NextOnFailure = c8; c7->NextOnSuccess = c8;

		// If c8 is in range, then we know c9 is not.
		c8->NextOnFailure = c9; c8->NextOnSuccess = cA;
		c9->NextOnFailure = c9->NextOnSuccess = cA;

		// If cA is in range, then we know cB and cC are not.
		cA->NextOnFailure = cB; cA->NextOnSuccess = cD;
		cB->NextOnFailure = cC; cB->NextOnSuccess = cC;

		// If cC is in range, then we know cD is not.
		cC->NextOnFailure = cD; cC->NextOnSuccess = nullptr;
		cD->NextOnFailure = cD->NextOnSuccess = nullptr;

		POINTS_3D[i] = c0;
	}



	LatticePoint4D latticePoints[256];
	for (int i = 0; i < 256; i++)
	{
		int cx = ((i >> 0) & 3) - 1;
		int cy = ((i >> 2) & 3) - 1;
		int cz = ((i >> 4) & 3) - 1;
		int cw = ((i >> 6) & 3) - 1;
		latticePoints[i] = create4DPoint(cx, cy, cz, cw);
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < lengths[i]; j++)
		{
			POINTS_4D[i][j] = latticePoints[lookup4DPregen[i][j]];
		}
	}
}

SimplexInfo::~SimplexInfo()
{
}

LatticePoint2D create2DPoint(int x, int y) {
	float offset = (x + y) * STRETCH_2D;
	LatticePoint2D new_point{ x, y, -x - offset, -y - offset };
	return new_point;
}

LatticePoint4D create4DPoint(int x, int y, int z, int w) {
	float offset = (x + y + z + w) * STRETCH_4D;
	LatticePoint4D new_point{ x, y, z, w, -x - offset, -y - offset, -z - offset, -w - offset };
	return new_point;
}