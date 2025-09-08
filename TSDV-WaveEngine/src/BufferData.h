#include <vector>
#include "Vector3.h"

using namespace std;

struct BufferData
{
	unsigned int vertexCount;

	unsigned int type;

	vector<float> vertex;

	vector<int> indices;
};