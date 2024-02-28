#include <iostream>
#include <fstream>
#include <vector>
#include <map>

std::vector<std::vector<int>> readMatrixFromFile(const std::string& filename) {
    std::vector<std::vector<int>> matrix;
    std::ifstream file(filename);
    if (file.is_open()) 
    {
        int value;
        while (file >> value) 
        {
            matrix.emplace_back();
            matrix.back().push_back(value);
            while (file.peek() == ' ') 
            {
                file.ignore();
                file >> value;
                matrix.back().push_back(value);
            }
        }
        file.close();
    }
    return matrix;
}
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) 
    {
        for (int value : row) 
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> edgeSort(const std::vector<std::vector<int>>& matrix)
{
   
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = (i+1); j < matrix.size(); j++)
        {
            if (matrix[i][j] != 0){ edges.push_back({ matrix[i][j],i,j,0 }); }
        }
    }
    for (int i = 0; i < (edges.size() - 1); i++)
    {
        for (int j = i + 1; j < edges.size(); j++)
        {
            if (edges[i][0] > edges[j][0]) { std::swap(edges[i], edges[j]); }
        }
    }
    return edges;
}

void kruskala(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& edges)
{
    std::vector<std::vector<int>> vertexArr;
    for (int i = 0; i < matrix.size(); i++)
    {
        vertexArr.push_back({ i });
    }

    while (vertexArr.size() > 1)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            // тут долженибыть вайл вертексарр сайз не равен 1
            int indInVertexArr_a; // ищем в каком множестве vertexArr edges[i][1] (первый конец ребра)
            int indInVertexArr_b; // ищем в каком множестве vertexArr edges[i][2] (второй конец ребра)
            for (int j = 0; j < vertexArr.size(); j++)
            {
                for (int k = 0; k < vertexArr[j].size(); k++)
                {
                    if (edges[i][1] == vertexArr[j][k])
                    {
                        indInVertexArr_a = j;
                    }
                    if (edges[i][2] == vertexArr[j][k])
                    {
                        indInVertexArr_b = j;
                    }
                }
            }

            if (indInVertexArr_a != indInVertexArr_b) // если индексы неравны то это гарантирует то что нет ребра которое добавит цикл
            {
                std::vector<int> curVector{};
                for (int elem : vertexArr[indInVertexArr_a])
                {
                    curVector.push_back(elem);
                }
                for (int elem : vertexArr[indInVertexArr_b])
                {
                    curVector.push_back(elem);
                }
                vertexArr.erase(vertexArr.begin() + indInVertexArr_b);
                vertexArr[indInVertexArr_a] = curVector;
                edges[i][3] = 1; //значит что мы включили ребро в покрывающее дерево
            }
        }

    }
}
int main()
{
    //int vertex;
    std::string fileName = "matrix.txt";
    std::vector<std::vector<int>> AdjacencyMatrix = readMatrixFromFile(fileName);
    printMatrix(AdjacencyMatrix);
    std::vector<std::vector<int>> e = edgeSort(AdjacencyMatrix);
    kruskala(AdjacencyMatrix, e);

    int TreeMass = 0;
    for (int i = 0; i < e.size(); i++)
    {
        std::cout << "Edge mass = " << e[i][0] << "; From " << e[i][1] << " to " << e[i][2] << "; in tree: " << e[i][3] << std::endl;;
        if (e[i][3] == 1) { TreeMass += e[i][0]; }
    }
    std::cout << "Tree mass = " << TreeMass << std::endl;
}


