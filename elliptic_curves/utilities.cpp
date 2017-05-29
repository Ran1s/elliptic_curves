#include "utilities.h"

//bool single_generator(std::vector<ec_point> points, ec_point & generator)
//{
//	for (auto point : points)
//	{
//		std::vector<ec_point> generated_points;
//		auto k_point = point;
//		ec_point null(true);
//		while (k_point != null)
//		{
//			generated_points.push_back(k_point);
//			k_point += point;
//		}
//		std::sort(generated_points.begin(), generated_points.end());
//		generated_points.resize(std::distance(generated_points.begin(), std::unique(generated_points.begin(), generated_points.end())));
//		if (generated_points.size() == points.size())
//		{
//			generator = point;
//			return true;
//		}
//	}
//	return false;
//}
