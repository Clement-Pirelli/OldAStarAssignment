#include "Astarrer.h"
#include "Grid.h"
#include <unordered_map>
#include <cassert>
#include <algorithm>

struct bestScoreData
{
	int bestCost = {};
	int bestIndex = {};
};

static bestScoreData getBestScoreData(const std::vector<Node> &givenVec)
{
	int bestCost = INT_MAX;
	int bestIndex = 0;
	size_t vecSize = givenVec.size();
	//search vector for the node with the least cost in it
	for (size_t i = 0; i < vecSize; i++)
	{
		const float curF = givenVec[i].f;
		if (curF < bestCost)
		{
			bestCost = curF;
			bestIndex = static_cast<int>(i);
		}
	}

	return bestScoreData{ bestCost, bestIndex };
}

static std::vector<vector2DInt> setPathFromNodeMap(const vector2DInt &endPosition, const vector2DInt &startPosition, std::unordered_map<vector2DInt, vector2DInt> &positionsToParent, size_t reserveHeuristic)
{
	std::vector<vector2DInt> result = {};
	bool done = false;
	vector2DInt currentPosition = endPosition;

	do
	{
		result.push_back(currentPosition);

		done = positionsToParent.count(currentPosition) == 0; //if the current position doesn't map to any other position, we're done
		const vector2DInt &parent = positionsToParent[currentPosition];
		done |= parent == startPosition;
		
		assert(done || !(currentPosition == parent));

		currentPosition = parent;

	} while (!done);

	std::reverse(result.begin(), result.end());
	return result;
}

std::vector<vector2DInt> Astarrer::findPath(const vector2DInt &start, const vector2DInt &destination, const Grid& grid)
{
	//if the starting or destination cells are invalid, simply return an empty path
	if (grid.getCell(start) == nullptr 
		|| grid.getCell(destination) == nullptr 
		|| grid.getCell(destination)->type == Cell::CELL_TYPE::IMPASSABLE) return {};
	
	//manhattan distance
	const int startH = destination.x - start.x + destination.y - start.y;
	const int absStartH = abs(startH);

	std::vector<Node> openNodes = {};
	openNodes.reserve(absStartH);
	openNodes.emplace_back(startH, 0, startH, start);
	
	std::unordered_map<vector2DInt, vector2DInt> positionsToParent = {};
	positionsToParent.reserve(absStartH);

	while (openNodes.size() > 0)
	{
		const bestScoreData bestScore =	getBestScoreData(openNodes);
		
		const Node currentNode = openNodes[bestScore.bestIndex];
		openNodes.erase(openNodes.begin() + bestScore.bestIndex);

		//recalculate the best score without the current node
		const bestScoreData recalculatedBestScore = getBestScoreData(openNodes);

		Cell *currentCell = grid.getCell(currentNode.pos);

		//check all directions from the selected node
		//if there's something there and it's not in the open or closed lists, add it to the open list
		for (int i = 0; i < DIRECTION::COUNT; i++)
		{
			const vector2DInt direction = vector2DInt::getDirectionVector(static_cast<DIRECTION>(i));

			const Cell *chosenCell = grid.getCell(currentCell->gridPos + direction);

			//if we're out of bounds, the cell is impassable or we've already visited this position, continue
			if (chosenCell == nullptr 
				|| chosenCell->type == Cell::IMPASSABLE 
				|| positionsToParent.count(chosenCell->gridPos) > 0) continue;

			const int cost = (chosenCell->type == Cell::MOUNTAIN) ? Cell::MOUNTAIN_COST : Cell::GRASS_COST;
			const int neighborG = currentNode.g + cost;

			//again, manhattan distance
			const int neighborH = destination.x - chosenCell->gridPos.x + destination.y - chosenCell->gridPos.y;

			const Node neighborNode = Node(neighborG + neighborH, neighborG, neighborH, chosenCell->gridPos);
			positionsToParent.insert({neighborNode.pos, currentNode.pos});

			//if the position of the node is the destination, we're done!
			if (chosenCell->gridPos == destination)
			{
				//set the path, then return true : we've found a path!
				return setPathFromNodeMap(destination, start, positionsToParent, absStartH);
			}

			//add the neighbor to the open list if it's the best cost yet
			openNodes.push_back(neighborNode);
			
		}
	}

	return {};
}