#include "collShapeUnitTest.hpp"

void collShapeUnitTest (void)
{
	std::cout << "\nContructor for cCollPoint";
	cCollPoint point;
	std::cout << "\nConstructors for cCollLine";
	cCollLine line1(1432,1,20,-40.234),
			  line2(cVector2(1432,1),cVector2(20,-40.234)),
			  line3(vUnitVector(cVector2(-1412,-41.234)));
	std::cout << "\nConstructors for cCollTri";
	cCollTri tri1(cVector2(-120,1.1236),cVector2(49.3,-435),cVector2(1,1)),
			 tri2(-120,1.1236,49.3,-435,1,1);
	std::cout << "\nConstructors for cCollAabb";
	cCollAabb aabb1(10,10);
	std::cout << "\nConstructors for cCollPoly";
	std::vector<cVector2> points;
	points.push_back(cVector2(0,0));
	points.push_back(cVector2(-0.75,0));
	points.push_back(cVector2(-0.75,-0.5));
	points.push_back(cVector2(-0.75,-1));
	points.push_back(cVector2(0,-1));
	points.push_back(cVector2(1,-43.234324));
	points.push_back(cVector2(0,0));
	cCollPoly poly1(points);
	std::cout << "\nConstructor for cCollCircle";
	cCollCircle circle1(20.234);

	std::cout << "\nTesting operator== with poly1/poly1";
	bool result;
	poly1 == poly1 ? result = true : result = false;
	std::cout << "\n" << result;
	std::cout << "\nTesting operator== with line1/line2 (should be true)";
	line1 == line2 ? result = true : result = false;
	std::cout << "\n" << result;
	std::cout << "\nTesting operator== with line1/line3 (should be true)";
	line1 == line3 ? result = true : result = false;
	std::cout << "\n" << result;
	std::cout << "\nTesting operator== with tri1/aabb1 (should be false)";
	tri1 == aabb1 ? result = true : result = false;
	std::cout << "\n" << result;
}
