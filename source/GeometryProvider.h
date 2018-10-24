#ifndef GEOMETRYPROVIDER_H
#define GEOMETRYPROVIDER_H

#include <vector>
#include <array>

class GeometryProvider
{
public:
	GeometryProvider()
	{
	}

	/// abstract class
	virtual ~GeometryProvider()
	{
	}

	template<typename T>
	static void Quad(std::vector<T>& vertices, std::vector<int>& indices)
	{
		int startingIndex = (int)indices.size();

		float halfSize = 0.5f;

		std::array<float,8> coords = 
		{
			-1.f, +1.f
			,
			+1.f, +1.f
			,
			+1.f, -1.f
			,
			-1.f, -1.f
		};


		std::array<int, 6> faces =
		{
			0, 1, 2
			,
			2, 3, 0
		};

		indices.insert(end(indices), begin(faces), end(faces));

		for (int i = 0; i < coords.size(); i += 2)
		{
			T vert;
			vert.Position = Vector3(coords[i], coords[i + 1], 0) * halfSize;
			vertices.push_back(vert);
		}



	}



private:
};


#endif