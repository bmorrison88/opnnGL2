#include "GridPoint.h"

void GridPoint::clearPath()
{
	F = G = 0;
	inPath = false;
	from = -1;
}

void GridPoint::reset(bool andPosition)
{
	F = G = 0;
	if (andPosition)
	{
		for(int i = 0; i < 2; i++)
		{
			position[i] = -1;
			previous[i] = -1;
		}
	}
	for (int i = 0; i < 9; i++)
		edges[i] = false;
	inPath = false;
	from = -1;
}

bool GridPoint::operator == (GridPoint &rhs)
{
	for (int i = 0; i < 2; i++)
	{
		if (position[i] != rhs.position[i])
			return false;
	}
	return true;
}

void GridPoint::operator = (GridPoint &rhs)
{
	F = rhs.F;
	G = rhs.G;
	for (int i = 0; i < 2; i++)
	{
		position[i] = rhs.position[i];
		previous[i] = rhs.previous[i];
	}
	for (int i = 0; i < 9; i++)
		edges[i] = rhs.edges[i];
}

bool GridPoint::operator < (GridPoint &rhs)
{
	return (F < rhs.F);
}

void GridPoint::setEdge(int e, bool b)
{
	if ((e >= 0) && (e < 9))
		edges[e] = b;
}

bool GridPoint::getEdge(int e)
{
	if ((e >= 0) && (e < 9))
		return edges[e];
	else
		return false;
}

void GridPoint::setPrevious(int p[])
{
	for (int i = 0; i < 2; i++)
		previous[i] = p[i];
}

void GridPoint::getPrevious(int p[])
{
	for (int i = 0; i < 2; i++)
		p[i] = previous[i];
}

void GridPoint::getPosition(int p[])
{
	for (int i = 0; i < 2; i++)
		p[i] = position[i];
}

void GridPoint::setPosition(int p[])
{
	for (int i = 0; i < 2; i++)
		position[i] = p[i];
}

GridPoint::GridPoint(const GridPoint& g)
{
	F = g.F;
	G = g.G;
	for (int i = 0; i < 2; i++)
	{
		position[i] = g.position[i];
		previous[i] = g.previous[i];
	}
	for (int i = 0; i < 9; i++)
		edges[i] = g.edges[i];
	inPath = g.inPath;
	from = g.from;
}

GridPoint::GridPoint()
{
	reset(true);
}