#include "LineRenderer.h"

LineRenderer::LineRenderer(std::vector<vector2D> givenPoints, color givenCol, float givenDepth)
{
	points = givenPoints;
	col = givenCol;
	depth = givenDepth;
}

void LineRenderer::draw() const
{
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	glColor3f(col.r, col.g, col.b);
	for (const vector2D& point : points)
	{
		glVertex3f(point.x, point.y, depth);
	}
	glEnd();
}
