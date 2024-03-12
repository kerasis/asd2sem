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

bool canColor(std::vector<std::vector<int>>& graph, std::vector<int>& color, int v, int colors) 
{
    int cntVertex = graph.size();
    for (int c = 1; c <= colors; c++)
    {
        bool isSafe = true;
        for (int i = 0; i < cntVertex; i++) 
        {
            if (graph[v][i] && color[i] == c)  //проверка на то можно ли покрасить вершину в цвет
            {
                isSafe = false;
                break;
            }
        }
        if (isSafe) 
        {
            color[v] = c;
            if (v == cntVertex - 1 || canColor(graph, color, v + 1, colors)) { return true; } //проспатривается последняя вершина -> если с условиями ок то можно раскрасить
            color[v] = 0;
        }
    }
    return false;
}

bool colorGraph(std::vector<std::vector<int>>& graph, int colors) // в способе раскраски будет 1 из вариантов где количество цветов равно хроматическому числу графа 
{
    //множество с одним множеством цвета можно разбить на разные цвета (только так чтоб оно не пересекалось с множеством других цветов
    int cntVertex = graph.size();
    std::vector<int> color(cntVertex, 0);
    if (!canColor(graph, color, 0, colors) or (cntVertex < colors))
    {
        std::cout << "Graph couldn't be colored with " << colors << " colors." << std::endl;
        return false;
    }
    std::cout << "Graph colored with " << colors << " colors " << std::endl;
    for (int i = 0; i < cntVertex; i++)
    {
        std::cout << "Vertex " << i << " -> color " << color[i] << std::endl;
    }
    return true;
}

int main()
{
    std::string fileName = "matrix.txt";
    std::vector<std::vector<int>> AdjacencyMatrix = readMatrixFromFile(fileName);
    printMatrix(AdjacencyMatrix);
    colorGraph(AdjacencyMatrix, 6);

    std::string fileName2 = "matrix2.txt";
    std::vector<std::vector<int>> AdjacencyMatrix2 = readMatrixFromFile(fileName2);
    printMatrix(AdjacencyMatrix2);
    colorGraph(AdjacencyMatrix2, 4);
}

