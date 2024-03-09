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
        for (int j = 0; j < matrix.size(); j++)
        {
            if (matrix[i][j] != 0) { edges.push_back({ matrix[i][j],i,j,0 }); } //вес. один конец. другой. посещен / не посещен
        }
    }
    //сортировка
    for (int i = 0; i < (edges.size() - 1); i++)
    {
        for (int j = i + 1; j < edges.size(); j++)
        {
            if (edges[i][0] > edges[j][0]) { std::swap(edges[i], edges[j]); }
        }
    }
    return edges;
}

void deikstra(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>> edges, int startV = 0)
{
    std::vector<int> visited{};

    std::vector<std::vector<std::vector<int>>> dist{};
    for (int i = 0; i < matrix.size(); i++)
    {
        dist.push_back({});
        for (int j = 0; j < matrix.size(); j++)
        {
            dist[i].push_back({});
            dist[i][j].push_back({});
            dist[i][j][0] = 9999;
            // дефолтный вес вершины значит что до нее нельзя добраться
        }
    }
    dist[0][startV][0] = 0;
    dist[0][startV].push_back(startV); //вторым числом записываем то откуда пришли;

    int vertexFrom = startV;
    for (int i = 1; i < matrix.size(); i++)
    {
        // отбираем соседей
        for (std::vector<int> edge : edges)
        {
            if (edge[1] == vertexFrom and find(visited.begin(), visited.end(), edge[2]) == visited.end()) //добавить условие не помещяемости визитед 
            {
              
                if (dist[i - 1][edge[2]][0] <= (dist[i - 1][edge[1]][0] + edge[0]))
                {
                   
                    dist[i][edge[2]] = dist[i - 1][edge[2]];
                    
                }
                else
                {
                    dist[i][edge[2]] = { dist[i - 1][edge[1]][0] + edge[0] , edge[1] };
                }          
            }
        }
        //переносим значения ячеек которые не были затронуты входе просмотра ребер но были заполнены до этого
        for (int j = 0; j < matrix.size(); j++)
        {
            if (dist[i][j][0] == 9999 and dist[i-1][j][0] != 9999)
            {
                dist[i][j] = dist[i - 1][j];
            }
        }
        
        // заполняем базовый случай текущей вершины соседей которой мы рассматривали, тк далее ее значения не будут меняться
        for (int j = i; j < matrix.size(); j++)
        {
            dist[j][vertexFrom] = dist[j - 1][vertexFrom];
        }
        //старую помещаем в визитед
        visited.push_back(vertexFrom);

        //выбираем следующюю наимельную вершину(наимельшая не визиьтед)
        int cnt = 9999;
        for (int j = 0; j < matrix.size(); j++)
        {
            if ((find(visited.begin(), visited.end(), j) == visited.end()) and (cnt > dist[i][j][0]))
            {
                vertexFrom = j;
                cnt = dist[i][j][0];
            }
        }
    }

    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << "Vertex: " << i << "; dist: " << dist[matrix.size() - 1][i][0] << "; put: ";
        
        std::vector<int> pput{};
        int ind = i;
        for (int j = matrix.size() - 1; j > -1; j--)
        {
            pput.push_back(dist[j][ind][1]);
            ind = dist[j][ind][1];
            
        }

        for (int k = pput.size()-1; k >= 0; k--)
        {
            std::cout << pput[k] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    //нумеркция в матрице с нуля аыаывывывмывм
    std::vector<std::vector<int>> adjMatr = readMatrixFromFile("matrix.txt");
    printMatrix(adjMatr);

    std::vector<std::vector<int>> edges = edgeSort(adjMatr);
    deikstra(adjMatr, edges,6);
}

