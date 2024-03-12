#include <iostream>
#include <vector>
#include <map>
#include <string>
// пусть у нас есть неориентированный связный граф
// если можно пройти по всем ребрам так чтобы посещены были все вершины и в конце пути мы возвращяемся в стартовую вершину, причем каждое ребро можно и нужно пройти лишь 1 раз
// то тогда перед нами эйлеров граф
// теорема:
// чтобы граф был эйлеровым, неодходимо, чтобы в каждую вершину входило четное количество ребер
// 
//поиск эйлерова цикла осуществляется с помощью модификации алгоритма дфс в неориентированном графе
//поэтому буду использовать предыдущие лабы
enum class g_type { DIRECTED, UNDIRECTED };
struct Graph
{
    std::map<int, std::vector<int>> adjacency_list;
    int Vertex;
    g_type graph_type;
    std::map<int, int> visited;
   

public:
    Graph(g_type type)
    {
        graph_type = type;
    }
    void addVertex(int name)
    {
        if ((adjacency_list.find(name)) == adjacency_list.end())
        {
            adjacency_list[name] = {};
            Vertex = adjacency_list.size();
        }
        else { std::cout << "it's already in graph" << std::endl; }
    }

    void addEdge(int name1, int name2)
    {
        if ((adjacency_list.find(name1)) == adjacency_list.end() or (adjacency_list.find(name2)) == adjacency_list.end())
        {
            std::cout << "Unknown vertex" << std::endl;
        }

        adjacency_list.find(name1)->second.push_back(name2); // .second используется для доступа ко значению, а .first к ключу

        if (graph_type == g_type::UNDIRECTED)
        {
            adjacency_list.find(name2)->second.push_back(name1);
        }
    }
    
    void dfs(int v, int from, bool& hasCycle, std::vector<int>& path)
    {
        visited.find(v)->second = 1;
        path.push_back(v);// сохраняем путь по которому двигался дфс
        for (int i = 0; i < (adjacency_list.find(v)->second).size(); i++)
        {
            if (from == adjacency_list[v][i]) // запрещаем ходить в обратном направлении ( для этого в параметрах функции так же передаем последний элемент из которого запускался текущий рекурсионный слой)
            {
                continue;
            }
            else if (visited.find(adjacency_list[v][i])->second == 0)
            {
                dfs(adjacency_list[v][i], v, hasCycle, path);               
            }
            else if (visited.find(adjacency_list[v][i])->second == 1)
            {
                hasCycle = true;
            }
        }
  
        visited.find(v)->second = 2;
    }

    bool eylerCycle()
    {
        bool hasCycle = false;
        std::vector<int> path{};
        for (auto vert : adjacency_list)
        {
            if (vert.second.size() % 2 == 1) { return false; }
        }
        for (auto iter{ adjacency_list.begin() }; iter != adjacency_list.end(); iter++)
        {
            visited.insert(std::pair<int, int>{iter->first, 0});
        }
        
        for (auto iter{ visited.begin() }; iter != visited.end(); iter++)
        {
            if (iter->second == 0)
            {
                
                dfs( iter->first, -1, hasCycle, path);
            }
        }

        if (hasCycle == true)
        {
            std::cout << "path: ";
            for (int i = 0; i < path.size(); i++)
            {
                std::cout << path[i] << " ";
            }
            std::cout << std::endl;
        }

        return hasCycle;

    }
};


int main()
{
    Graph gr(g_type::UNDIRECTED);
    gr.addVertex(1);
    gr.addVertex(2);
    gr.addVertex(3);
    gr.addVertex(4);
   /* gr.addVertex(5);
    gr.addVertex(6);*/
    gr.addEdge(1, 2);
    gr.addEdge(2, 3);
    gr.addEdge(3, 4);
    gr.addEdge(4, 1);

    bool cycle = gr.eylerCycle();
    if (cycle)
    {
        std::cout << "yes" << std::endl;
    }
    else { std::cout << "no" << std::endl; }
    
    Graph gr2(g_type::UNDIRECTED);
    for (int i = 1; i < 11; i++)
    {
        gr2.addVertex(i);
    }
    for (int i = 1; i < 10; i++)
    {
        gr2.addEdge(i, i+1);
    }
    gr2.addEdge(10, 1);
    gr2.addEdge(2, 4);
    gr2.addEdge(4, 6);
    gr2.addEdge(6, 8);
    gr2.addEdge(8, 10);
    gr2.addEdge(10, 2);

    bool cycle2 = gr2.eylerCycle();
    if (cycle2)
    {
        std::cout << "yes" << std::endl;
    }
    else { std::cout << "no" << std::endl; }

    Graph gr3(g_type::UNDIRECTED);
    for (int i = 1; i < 11; i++)
    {
        gr3.addVertex(i);
    }
    for (int i = 1; i < 10; i++)
    {
        gr3.addEdge(i, i + 1);
    }
    gr3.addEdge(10, 1);
    gr3.addEdge(2, 4);
    gr3.addEdge(4, 6);
    gr3.addEdge(6, 8);
    
    bool cycle3 = gr3.eylerCycle();
    if (cycle3)
    {
        std::cout << "yes" << std::endl;
    }
    else { std::cout << "no" << std::endl; }
  
}
