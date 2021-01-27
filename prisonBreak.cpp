#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

// https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/prison-break-5/
class PrisonBreak
{
	vector<vector<int>> _v;
	vector<vector<bool>> _visited;
	stack<size_t> _r;
	stack<size_t> _c;
	vector<pair<int, int>> _dirs;
	size_t _rows, _cols;
	size_t _ways = 0;
public:
	PrisonBreak(vector<vector<int>>& v) : _v(v), _r(stack<size_t>()), _c(stack<size_t>())
	{
		if (_v.empty()) throw std::exception("Can't be empty");
		_visited = vector<vector<bool>>(_v.size(), vector<bool>(_v[0].size(), false));
		_rows = _v.size();
		_cols = _v[0].size();
		for (size_t r = 0; r < _rows; ++r)
			for (size_t c = 0; c < _cols; ++c)
				_visited[r][c] = _v[r][c] == 1;

		_dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	}

	void dfs(size_t r, size_t c)
	{
		if (r == _rows - 1 && c == _cols - 1)
		{
			//printf("Reached\n");
			++_ways;
			return;
		}
		_visited[r][c] = true;
		_r.push(r); _c.push(c);
		//printf("%zu %zu\n", r, c);

		for (auto& dir : _dirs)
		{
			const int dx = dir.first, dy = dir.second;
			if ((r == 0 && dx == -1) || (r == _rows - 1 && dx == 1) || 
				  (c == 0 && dy == -1) || (c == _cols - 1 && dy == 1)) continue;

			const size_t rNew = r + dx, cNew = c + dy;
			if (_visited[rNew][cNew]) continue;
			
			dfs(rNew, cNew);
		}

		const size_t rVis = _r.top();
		const size_t cVis = _c.top();
		_r.pop(); _c.pop();
		_visited[rVis][cVis] = false;
	}
	
	size_t breakWays()
	{
		if (_v[_rows - 1][_cols - 1] == 1)
			return 0;
		
		dfs(0, 0);
		return _ways;
	}
};

void printVec(const vector<int>& v) {
	printf("%zu: ", v.size());
	for (size_t i : v)
		printf("%d, ", i);
	printf("\n");
}

int main() {

	vector<vector<int>> v{ { 0, 0, 0, 1 },
												 { 0, 0, 0, 0 },
												 { 1, 1, 1, 0 },
												 { 1, 0, 0, 0 } };
	v = { { 0, 1, 1, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 0, 0, 0 },
				{ 0, 1, 0, 0 } };

	v = { { 0, 1, 1, 0, 1 },
				{ 0, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 0 },
				{ 0, 1, 0, 0, 0 } };
	
	for (const auto& row : v)
		printVec(row);

	PrisonBreak p{ v };

	const size_t ways = p.breakWays();
	printf("Ways: %zu\n", ways);

	return 0;
}