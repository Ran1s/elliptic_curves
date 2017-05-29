#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include "elliptic_curves.h"
#include <string>
#include <algorithm>
#include <cassert>
#include <sstream>
//#include "finite_group.h"

std::string const FILE_FORMAT = ".csv";
std::string const DELIM = ";";
std::string const ENDL = "\n";

bool single_generator(std::vector<ec_point> points, ec_point & generator, std::vector<int> & orders)
{
	orders.assign(points.size(), 1);
	int ind = 0;
	bool generator_found = false;
	for (auto point : points)
	{
		std::vector<ec_point> generated_points;

		generated_points.push_back(ec_point(point.get_a(), point.get_b(), finite_number(point.get_p(), 0), finite_number(point.get_p(), 0), true));

		auto k_point = point;
		ec_point null(point.get_a(), point.get_b(), point.get_x(), point.get_y(), true);
		while (k_point != null)
		{
			generated_points.push_back(k_point);
			k_point += point;
			orders[ind]++;
		}
		size_t size = generated_points.size();
		std::sort(generated_points.begin(), generated_points.end());
		generated_points.resize(std::distance(generated_points.begin(), std::unique(generated_points.begin(), generated_points.end())));

		if (!generator_found && generated_points.size() == points.size() && size == points.size())
		{
			generator = point;
			generator_found = true;
			//return true;
		}
		ind++;
	}
	return generator_found;
}

bool double_generator(std::vector<ec_point> points, std::pair<ec_point, ec_point> & generator)
{
	for (auto point1 : points)
	{
		std::vector<ec_point> generated_points1;
		auto k_point1 = point1;
		ec_point null(point1.get_a(), point1.get_b(), point1.get_x(), point1.get_y(), true);
		while (k_point1 != null)
		{
			generated_points1.push_back(k_point1);
			k_point1 += point1;
		}
		generated_points1.push_back(ec_point(point1.get_a(), point1.get_b(), finite_number(point1.get_p(), 0), finite_number(point1.get_p(), 0), true));
		sort(generated_points1.begin(), generated_points1.end());
		for (auto point2 : points)
		{
			if (point1 != point2 && !std::binary_search(generated_points1.begin(), generated_points1.end(), point2))
			{
				std::vector<ec_point> generated_points2;
				auto k_point2 = point2;
				ec_point null(point2.get_a(), point2.get_b(), point2.get_x(), point2.get_y(), true);
				while (k_point2 != null)
				{
					// Проверка на пересечение
					generated_points2.push_back(k_point2);
					k_point2 += point2;
				}
				generated_points2.push_back(ec_point(point2.get_a(), point2.get_b(), finite_number(point2.get_p(), 0), finite_number(point2.get_p(), 0), true));

				/*generated_points2.insert(generated_points2.end(), generated_points1.begin(), generated_points1.end());
				size_t size = generated_points2.size();
				std::sort(generated_points2.begin(), generated_points2.end());
				generated_points2.resize(std::distance(generated_points2.begin(), std::unique(generated_points2.begin(), generated_points2.end())));*/
				if (generated_points2.size() * generated_points1.size() == points.size())
				{
					generator = { point1, point2 };
					return true;
				}
			}
		}
		
	}
	return false;
}

void compute_the_number_of_the_points()
{
	for (auto p : primes(modulo(1000)))
	{
		std::ofstream out(std::to_string(int(p)) + FILE_FORMAT);
		out << "   b";
		for (auto b : p)
		{
			out << DELIM << int(b);
		}
		out << ENDL;
		out << "a" << ENDL;
		for (auto a : p)
		{
			out << int(a) << DELIM;
			for (auto b : p)
			{
				std::map<finite_number, std::vector<finite_number>> m;
				for (auto x : p)
				{
					m[pow(x, 3) + a * x + b].push_back(x);
				}
				std::vector<ec_point> v;
				for (auto y : p)
				{
					auto y2 = pow(y, 2);
					for (auto x : m[y2])
					{
						v.push_back(ec_point(a, b, x, y));
					}
				}
				//check the singular curves
				if ((4 * long long(pow(long long(a), 3)) + 27 * long long(pow(long long(b), 2))) % p == 0)
				{
					out << -1 << DELIM;
				}
				else
				{
					out << v.size() + 1 << DELIM;					
				}
			}
			out << ENDL;
		}
	}
}


void compute_generator_or_mult_of_groups()
{
	//system("mkdir isomorphism");
	system("mkdir isomorphism\\orders");
	auto pr = primes(modulo(3));
	for (auto it = pr.begin() + 1; it != pr.end(); it++)
	{
		auto p = *it;
		system(("mkdir isomorphism\\orders\\" + std::to_string(p)).c_str());
		std::ofstream out("isomorphism/" + std::to_string(int(p)) + FILE_FORMAT);
		out << "   b";
		for (auto b : p)
		{
			out << DELIM << int(b);
		}
		out << ENDL;
		out << "a" << ENDL;
		for (auto a : p)
		{
			out << int(a) << DELIM;
			for (auto b : p)
			{
				std::map<finite_number, std::vector<finite_number>> m;
				for (auto x : p)
				{
					m[pow(x, 3) + a * x + b].push_back(x);
				}
				std::vector<ec_point> v;
				for (auto y : p)
				{
					auto y2 = pow(y, 2);
					for (auto x : m[y2])
					{
						v.push_back(ec_point(a, b, x, y));
					}
				}
				ec_point null(a, b, finite_number(p, 0), finite_number(p, 0), true);
				v.push_back(null);
				if ((4 * long long(pow(long long(a), 3)) + 27 * long long(pow(long long(b), 2))) % p == 0)
				{
					out << "-1" << DELIM;
				}
				else
				{
					ec_point gen(true);
					std::vector<int> orders;
					if (!single_generator(v, gen, orders))
					{
						int max_order_index = std::max_element(orders.begin(), orders.end()) - orders.begin();
						assert(int(v.size()) % orders[max_order_index] == 0);
						int k = orders[max_order_index];
						int m = int(v.size()) / k;
						out << "Z" << k << "xZ" << m << DELIM;
					}
					else
					{
						out << int(gen.get_x()) << " " << int(gen.get_y()) << DELIM;
					}
					std::ofstream out_orders("isomorphism/orders/" + std::to_string(p) + "/" + std::to_string(a) + " " + std::to_string(b) + FILE_FORMAT);
					for (size_t i = 0; i < v.size(); i++)
					{
						if (v[i] != null)
						{
							out_orders << int(v[i].get_x()) << " " << int(v[i].get_y()) << DELIM << orders[i] << ENDL;
						}						
					}
				}
			}
			out << ENDL;
		}
	}
}

std::vector<std::string> split(const std::string & s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string element;
	while (std::getline(ss, element, delim))
	{
		result.push_back(element);
	}
	return result;
}

void separate_elliptic_curves()
{
	//system("mkdir isomorphism");
	system("mkdir distribution2");
	
	auto pr = primes(120);
	for (auto it = pr.begin() + 1; it != pr.end(); it++)
	{
		auto p = *it;
		std::ifstream distribution_in("distribution/" + std::to_string(int(p)) + FILE_FORMAT);
		std::ifstream isomorphism_in("isomorphism/" + std::to_string(int(p)) + FILE_FORMAT);
		

		//system(("mkdir distribution2\\" + std::to_string(p)).c_str());

		std::ofstream out("distribution2/" + std::to_string(int(p)) + FILE_FORMAT);
		out << "   b";
		for (int b = 0; b < p; b++)
		{
			out << DELIM << b;
		}

		std::string distribution_string;
		std::string isomorphism_string;
		std::getline(distribution_in, distribution_string);
		std::getline(isomorphism_in, isomorphism_string);
		std::getline(distribution_in, distribution_string);
		std::getline(isomorphism_in, isomorphism_string);

		out << ENDL;
		out << "a" << ENDL;
		for (int a = 0; a < p; a++)
		{
			out << a << DELIM;
			std::getline(distribution_in, distribution_string);
			std::getline(isomorphism_in, isomorphism_string);
			auto distribution_values = split(distribution_string, ';');
			auto isomorphism_values = split(isomorphism_string, ';');
			distribution_values.erase(distribution_values.begin());
			isomorphism_values.erase(isomorphism_values.begin());
			for (int b = 0; b < p; b++)
			{
				if (distribution_values[b] == "-1")
				{
					out << "0;";
					continue;
				}
				if (isomorphism_values[b][0] == 'Z')
				{
					out << "-" << distribution_values[b];
				}
				else
				{
					out << distribution_values[b];
				}
				out << DELIM;
			}
			out << ENDL;
		}
	}
}

struct point_order
{
	int order;
	int x, y;
	bool operator<(const point_order & point_order)
	{
		return order < point_order.order;
	}
};


void orders_for_the_same_isomorphism()
{
	system("mkdir isomorphism2");
	std::ofstream report("isomorphism2/report.txt");
	auto pr = primes(120);
	for (auto it = pr.begin() + 1; it != pr.end(); it++)
	{
		auto p = *it;
		std::ifstream isomorphism_in("isomorphism/" + std::to_string(int(p)) + FILE_FORMAT);

		std::string isomorphism_string;
		std::getline(isomorphism_in, isomorphism_string);
		std::getline(isomorphism_in, isomorphism_string);

		std::map<std::string, std::vector<std::pair<int, int>>> same_pair_of_isomorphism;

		for (int a = 0; a < p; a++)
		{
			std::getline(isomorphism_in, isomorphism_string);
			auto isomorphism_values = split(isomorphism_string, ';');
			isomorphism_values.erase(isomorphism_values.begin());
			for (int b = 0; b < p; b++)
			{				
				if (isomorphism_values[b][0] == 'Z')
				{
					same_pair_of_isomorphism[isomorphism_values[b]].push_back({ a, b });
				}
			}
		}

		system(("mkdir isomorphism2\\" + std::to_string(p)).c_str());
		for (auto pair_z : same_pair_of_isomorphism)
		{
			std::ofstream out("isomorphism2/" + std::to_string(p) + "/" + pair_z.first + FILE_FORMAT);
			std::vector<std::vector<point_order>> out_by_string;
			for (auto ec : pair_z.second)
			{
				out << "a: " << ec.first << " b: " << ec.second << ";;;";
				std::ifstream points_in("isomorphism/orders/" + std::to_string(p) + "/" + std::to_string(ec.first) + " " + std::to_string(ec.second) + FILE_FORMAT);
				std::vector<point_order> points_orders;
				std::string item;
				while (std::getline(points_in, item))
				{
					auto values = split(item, ';');
					auto point_values = split(values[0], ' ');
					point_order point_order_value = { stoi(values[1]), stoi(point_values[0]), stoi(point_values[1])};
					
					points_orders.push_back(point_order_value);
				}
				std::sort(points_orders.begin(), points_orders.end());
				out_by_string.push_back(points_orders);
			}
			out << ENDL;
			for (size_t i = 0; i < out_by_string[0].size(); i++)
			{
				for (size_t j = 0; j < pair_z.second.size(); j++)
				{
					if (j > 0)
					{
						if (out_by_string[j][i].order != out_by_string[j - 1][i].order)
						{
							report << "elliptic curves with parametres a1: " + std::to_string(pair_z.second[j - 1].first) + "b1: " + std::to_string(pair_z.second[j - 1].second) + "a2: " + std::to_string(pair_z.second[j].first) + "b2: " + std::to_string(pair_z.second[j].second) + " have different orders" << std::endl;
						}
					}
					out << out_by_string[j][i].x << " " << out_by_string[j][i].y << DELIM << out_by_string[j][i].order << ";;";
				}
				out << ENDL;
			}
		}		
	}
}

void f()
{
	auto pr = primes(120);
	std::ofstream out("distribution2/info" + FILE_FORMAT);
	out << "p" << DELIM << "all" << DELIM << "singular" << DELIM << "with_generator" << DELIM << "without_generator" << ENDL;
	for (auto it = pr.begin() + 1; it != pr.end(); it++)
	{
		auto p = *it;
		std::ifstream distribution_in("distribution2/" + std::to_string(int(p)) + FILE_FORMAT);



		int count_all = 0;
		int count_singular = 0;
		int count_with_generator = 0;
		int count_without_generator = 0;

		std::string distribution_string;
		std::getline(distribution_in, distribution_string);
		std::getline(distribution_in, distribution_string);

		for (int a = 0; a < p; a++)
		{
			std::getline(distribution_in, distribution_string);
			auto distribution_values = split(distribution_string, ';');
			distribution_values.erase(distribution_values.begin());
			for (int b = 0; b < p; b++)
			{
				count_all++;
				if (distribution_values[b] == "")
				{
					count_singular++;
					continue;
				}
				else if (distribution_values[b][0] == '-')
				{
					count_without_generator++;
				}
				else
				{
					count_with_generator++;
				}
			}
			
		}
		out << p << DELIM << count_all << DELIM << count_singular << DELIM << count_with_generator << DELIM << count_without_generator << ENDL;
	}
}


int main()
{
	std::ios::sync_with_stdio(false);
	f();
	/*f2();*/
	//ec_point p(finite_number(23, 1), finite_number(23, 1), finite_number(23, 0), finite_number(23, 1));
	//ec_point q(finite_number(23, 1), finite_number(23, 1), finite_number(23, 0), finite_number(23, -1), true);
	//for (int i = 0; i < 30; i++)
	//{
	//	q += p;
	//	std::cout << q << std::endl;
	//	
	//}

	//modulo p(3);
	//finite_number a(p, 2), b(p, 0);
	//std::map<finite_number, std::vector<finite_number>> m;
	//for (auto x : p)
	//{
	//	m[pow(x, 3) + a * x + b].push_back(x);
	//}
	//std::vector<ec_point> v;
	//for (auto y : p)
	//{
	//	auto y2 = pow(y, 2);
	//	for (auto x : m[y2])
	//	{
	//		v.push_back(ec_point(a, b, x, y));
	//	}
	//}
	//std::pair<ec_point, ec_point> gen;
	//if (double_generator(v, gen))
	//{
	//	std::cout << gen.first << std::endl << gen.second << std::endl;
	//}


	//modulo p = 7;
	//finite_number a(p, 2), b(p, 6);
	//std::map<finite_number, std::vector<finite_number>> m;
	//for (auto x : p)
	//{
	//	m[pow(x, 3) + a * x + b].push_back(x);
	//}
	//std::vector<ec_point> v;
	//for (auto y : p)
	//{
	//	auto y2 = pow(y, 2);
	//	for (auto x : m[y2])
	//	{
	//		v.push_back(ec_point(a, b, x, y));
	//	}
	//}
	//int zxcvxcv = 5;
	//v;
	

	//for (modulo p = 0; p <= 1000; p++)
	//{
	//	for (auto a : p)
	//	{
	//		for (auto b : p)
	//		{
	//			std::map<finite_number, std::vector<finite_number>> m;
	//			for (auto x : p)
	//			{
	//				m[pow(x, 3) + a * x + b].push_back(x);
	//			}
	//			std::vector<ec_point> v;
	//			for (auto y : p)
	//			{
	//				auto y2 = pow(y, 2);
	//				for (auto x : m[y2])
	//				{
	//					v.push_back(ec_point(a, b, x, y));
	//				}
	//			}
	//		}
	//	}
	//}
    return 0;
}

