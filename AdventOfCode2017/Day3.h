#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

namespace Day3
{
#pragma region General
	struct Point
	{
		Point() {}
		Point(int x, int y) : X(x), Y(y) {}
		int X = 0, Y = 0;
	};

	bool operator== (const Point &p1, const Point &p2)
	{
		return (p1.X == p2.X && p1.Y == p2.Y);
	}

	bool operator< (const Point &p1, const Point &p2)
	{
		return tie(p1.X, p1.Y) < tie(p2.X, p2.Y);
	}

	// The puzzle input
	const int _puzzleInput = 361527;

	// A map containing all numbers and their respective positions
	map<int, Point> _numberPositions = map<int, Point>();
	map<Point, int> _positionNumbers = map<Point, int>();

	int ManhattanDistance(Point p1, Point p2)
	{
		return (abs(p1.X - p2.X) + abs(p1.Y - p2.Y));
	}

	void GenerateSpiralMemory()
	{
		int step = 1, stepProgression = 0, xCoord = 0, yCoord = 0;
		bool horizontal = true;
		int direction = 1; // (Horizontal: left <-> right. Vertical: up <-> down)
		for (int i = 1; i < _puzzleInput + 1; ++i)
		{
			// Add the current number on the current position
			_numberPositions.insert({ i, Point(xCoord, yCoord) });

			// Calculate the next numbers position
			(horizontal) ? xCoord += direction : yCoord += direction;

			// Increment step progression
			++stepProgression;

			// If this step has now been completed,
			if (stepProgression == step)
			{
				// Flip the direction
				horizontal = !horizontal;

				// Reset the step progression
				stepProgression = 0;

				// When switched back from vertical to horizontal:
				// * the step should be incremented
				// * the direction changes (Horizontal: left <-> right. Vertical: up <-> down)
				if (horizontal)
				{
					++step;
					direction *= -1;
				}
			}
		}
	}

	int NeighbourValueSum(Point source)
	{
		return _positionNumbers[Point(source.X - 1, source.Y + 1)] + _positionNumbers[Point(source.X, source.Y + 1)] + _positionNumbers[Point(source.X + 1, source.Y + 1)] + // top row neighbors
			_positionNumbers[Point(source.X - 1, source.Y)] + _positionNumbers[Point(source.X + 1, source.Y)] + // same row neighbors
			_positionNumbers[Point(source.X - 1, source.Y - 1)] + _positionNumbers[Point(source.X, source.Y - 1)] + _positionNumbers[Point(source.X + 1, source.Y - 1)]; // bottom row neighbors
	}

	void GenerateSpiralMemory2()
	{
		int step = 1, stepProgression = 0, xCoord = 0, yCoord = 0;
		bool horizontal = true;
		int direction = 1; // (Horizontal: left <-> right. Vertical: up <-> down)

		// Infinite loop. Is broken as soon as an answer to the puzzle is found
		for (;;)
		{
			// Add the current number on the current position
			Point currentPoint = Point(xCoord, yCoord);
			int neighbourValueSum = NeighbourValueSum(currentPoint);

			if (neighbourValueSum > _puzzleInput)
			{
				std::cout << "Day 2 Part 2 answer is: " << neighbourValueSum << std::endl;
				break;
			}

			// Set the current point's value so it can be used to calculate the next point's value
			// If the currentPoint is the starting point, set it to 1. Important to do this within the loop to keep the traversion intact.
			_positionNumbers[currentPoint] = (currentPoint == Point(0, 0)) ? 1 : neighbourValueSum;

			// Traverse the spiral
			// Calculate the next numbers position
			(horizontal) ? xCoord += direction : yCoord += direction;

			// Increment step progression
			++stepProgression;

			// If this step has now been completed,
			if (stepProgression == step)
			{
				// Flip the direction
				horizontal = !horizontal;

				// Reset the step progression
				stepProgression = 0;

				// When switched back from vertical to horizontal:
				// * the step should be incremented
				// * the direction changes (Horizontal: left <-> right. Vertical: up <-> down)
				if (horizontal)
				{
					++step;
					direction *= -1;
				}
			}
		}
	}

#pragma endregion

#pragma region Part1

	void Part1()
	{
		GenerateSpiralMemory();
		std::cout << "Day 2 Part 1 answer is:" << ManhattanDistance(Point(0, 0), _numberPositions[_puzzleInput]) << std::endl;
	}
#pragma endregion

#pragma region Part2
	void Part2()
	{
		GenerateSpiralMemory2();
	}
#pragma endregion
}