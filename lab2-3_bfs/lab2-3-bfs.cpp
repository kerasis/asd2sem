#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>
// вводится файл в котором первой строкой указывается размерность матрицы смежности
// а затем вся матрица
class Graph
{
    std::vector<std::vector<int>> adjacency_list;
    int Vertex;
    
public:

    Graph(std::string s_file)
    {
        std::string str;
        std::ifstream file(s_file);
        std::getline(file, str);
        Vertex = atoi(str.c_str());
        for (int i = 0; i < Vertex; i++)
        {
            adjacency_list.push_back({});
        }

        for (int i = 0; i < Vertex; i++)
        {
            std::getline(file, str);
            str.erase(remove(str.begin(), str.end(), ' '), str.end());
            
            for (int j = 0; j < str.size(); j++)
            {
                if (str[j] != '0')
                {
                    adjacency_list[i].push_back(j);
                }
            }
            str = "";        
        }
        file.close();
    }

    std::vector<int> bfs(int start_Vertex)
    {
        std::vector<int> visited(Vertex);
        std::vector<int> distantion(Vertex);
        std::queue<int> q;

        for (int i = 0; i < distantion.size(); i++)
        {
            distantion[i] = 999999;
        }
           
        visited[start_Vertex] = 1;
        distantion[start_Vertex] = 0;
        q.push(start_Vertex);

        while (!q.empty())
        {
            int cur_Vertex = q.front();
            q.pop();

            for (int vert_connected_with_cur_vert : adjacency_list[cur_Vertex])
            {
                if (visited[vert_connected_with_cur_vert] == 0)
                {
                    visited[vert_connected_with_cur_vert] = 1;
                    distantion[vert_connected_with_cur_vert] = 1 + distantion[cur_Vertex];
                    q.push(vert_connected_with_cur_vert);
                }
            }
        }
        return distantion;
    }
    std::vector<int> find_connectivity_component()
    {
        int component = 0;
        std::vector<int> visited(Vertex);
        std::vector<int> component_table(Vertex);
        std::queue<int> q;

        for (int i = 0; i < Vertex; i++)
        {
            if (visited[i] != 1)
            {
                component += 1;
                visited[i] = 1;
                q.push(i);

                while (!q.empty())
                {
                    int cur_Vertex = q.front();
                    q.pop();
                    component_table[cur_Vertex] = component;

                    for (int vert_connected_with_cur_vert : adjacency_list[cur_Vertex])
                    {
                        if (visited[vert_connected_with_cur_vert] == 0)
                        {
                            visited[vert_connected_with_cur_vert] = 1;
                            q.push(vert_connected_with_cur_vert);
                        }
                    }
                }
            }
        }
        return component_table;
    }

    
};
int main()
{
    std::string file = "matrix.txt";
    Graph gr(file);
    std::vector<int> dist = gr.bfs(0);
    for (int i = 0; i < dist.size(); i++)
    {
        std::cout << i << " : " << dist[i] << std::endl;
    }
    std::cout << std::endl;
    std::vector<int> comp = gr.find_connectivity_component();
    for (int i = 0; i < comp.size(); i++)
    {
        std::cout << i << " : " << comp[i] << std::endl;
    }
}
