#pragma once
#include "structs.h"

struct recData
{
	vector2D centeredDimensions;
	color col;
	float depth;

	static const recData scaleRec(recData r, vector2D scalingFactors)
	{
		recData result = r;

		result.centeredDimensions.w *= scalingFactors.w;
		result.centeredDimensions.h *= scalingFactors.h;

		return result;
	}
};


class RecDrawer
{
public:
	RecDrawer(recData givenRec, vector2D givenPos, vector2D givenScale = { 1.0f, 1.0f }){ rec = givenRec; pos = givenPos; scale = givenScale; };

	void draw() const
	{
		recData scaledRec = recData::scaleRec(rec, scale);

		glLoadIdentity();

		glBegin(GL_QUADS);

		//set color
		glColor3f(scaledRec.col.r, scaledRec.col.g, scaledRec.col.b);

		//top right
		glVertex3f(pos.x + scaledRec.centeredDimensions.w, pos.y + scaledRec.centeredDimensions.h, scaledRec.depth);

		//bottom right
		glVertex3f(pos.x + scaledRec.centeredDimensions.w, pos.y - scaledRec.centeredDimensions.h, scaledRec.depth);

		//bottom left
		glVertex3f(pos.x - scaledRec.centeredDimensions.w, pos.y - scaledRec.centeredDimensions.h, scaledRec.depth);

		//top left
		glVertex3f(pos.x - scaledRec.centeredDimensions.w, pos.y + scaledRec.centeredDimensions.h, scaledRec.depth);

		glEnd();
	}

	void setRec(recData givenRec){ rec = givenRec; }
	void setPos(vector2D givenPos){ pos = givenPos; }

private:
	recData rec;
	vector2D pos;
	vector2D scale;
};