#include <iostream>
#include<string>
#include <vector>

using namespace std;

 class MergeSort
{
public:
	vector<int> MergeSortAlgorithm(vector<int> v) throw (string);
private:
	vector<int> merge(vector<int> v1, vector<int> v2);
};

vector<int> MergeSort::MergeSortAlgorithm(vector<int> v) throw(string)
{
	if (v.size() == 0) throw ("No hay elementos que ordenar en el vector. ");
	if (v.size() == 1) return  v;
	else 
	{
		vector<int> rightArray, leftArray, resultArray;

		int middleIndex = v.size() / 2;

		for (int i = 0; i < middleIndex - 1; i++)
		{
			leftArray.push_back(v[i]);
		}

		for (int i = middleIndex; i < v.size(); i++)
		{
			rightArray.push_back(v[i]);
		}

		rightArray = MergeSortAlgorithm(rightArray);
		leftArray = MergeSortAlgorithm(leftArray);
		
		if (leftArray[leftArray.size()-1] <= rightArray[0])
		{
			leftArray.push_back(rightArray[0]);
			return leftArray;
		}

		resultArray = merge(rightArray, leftArray);
	}

}

vector<int> MergeSort::merge(vector<int> v1, vector<int> v2)
{
	vector<int> resultArray;

	while (v1.size() > 0 && v2.size() > 0)
	{
		if (v1[0] <= v2[0])
		{
			resultArray.push_back(v1[0]);
			v1.erase(v1.begin());
		}
		else
		{
			resultArray.push_back(v2[0]);
			v2.erase(v2.begin());
		}
	}

	if (v1.size() > 0)
	{
		resultArray.insert(resultArray.end(),v1.begin(),v1.end());
	}

	if (v2.size() > 0)
	{
		resultArray.insert(resultArray.end(), v2.begin(), v2.end());
	}
	return resultArray;
}

int main()
{
	vector<int> v = { 3,25,2,5,6785,345,74,2 };

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}

	MergeSort mg;
	v = mg.MergeSortAlgorithm(v);
	
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
}