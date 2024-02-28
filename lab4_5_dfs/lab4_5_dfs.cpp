#include <iostream>
#include <vector>
#include <map>
#include <string>

enum class g_type { DIRECTED, UNDIRECTED };
struct Graph
{
    std::map<int, std::vector<int>> adjacency_list;
    int Vertex;
    g_type graph_type;
    std::map<int, int> visited;
    std::vector<int> topological_order;

    std::map<int, std::vector<int>> adjacency_list_inverted;
        

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
    void dfs(int component, int v)
    {
        visited.find(v)->second = component;

        for (int i = 0; i < (adjacency_list.find(v)->second).size(); i++)
        {
            if (visited.find(adjacency_list[v][i])->second == 0)
            {
                dfs(component, adjacency_list[v][i]);
            }
        }
    }
    void find_connectivity_component_undirected()
    {
        for (auto iter{ adjacency_list.begin() }; iter != adjacency_list.end(); iter++)
        {
            visited.insert(std::pair<int, int>{iter->first, 0});
        }
        int component = 0;
        for (auto iter{ visited.begin() }; iter != visited.end(); iter++)
        {
            if (iter->second == 0)
            {
                component += 1;
                dfs(component, iter->first);
            }
        }

        for (auto iter{ visited.begin() }; iter != visited.end(); iter++)
        {
            std::cout << iter->first << " : " << iter->second << std::endl;
        }

    }


    void find_connectivity_component_directed()
    {
        //заполняем инвертированный список смежности 
        for (auto iter{ adjacency_list.begin() }; iter != adjacency_list.end(); iter++)
        {
            adjacency_list_inverted[iter->first] = {};
        }
        for (auto iter{ adjacency_list.begin() }; iter != adjacency_list.end(); iter++)
        {
            for (int i = 0; i < iter->second.size(); i++)
            {
                adjacency_list_inverted[iter->second[i]].push_back(iter->first);
            }
        }

        for (auto iter{ adjacency_list.begin() }; iter != adjacency_list.end(); iter++)
        {
            visited.insert(std::pair<int, int>{iter->first, 0});
        }

        int component = 0;
        // проходимся дфс по инверитрованному списку чтоб получить топологический порядок
        for (auto iter{ visited.begin() }; iter != visited.end(); iter++)
        {
            if (iter->second == 0)
            {   
                component += 1;
                dfs_topo_order(component, iter->first, adjacency_list_inverted);
            }
        }
        // обнуляем список почещенных вершин
        for (auto iter{ adjacency_list.begin() }; iter != adjacency_list.end(); iter++)
        {
            visited[iter->first] = 0;
        }

        component = 0;
        //запускаем обычный дфс в топологическом порядке
        for (int i = (topological_order.size() - 1) ; i >= 0; i--)
        {
            if (visited[topological_order[i]] == 0)
            {
                component += 1;
                dfs(component, topological_order[i]);
            }
        }
        

        for (auto iter{ visited.begin() }; iter != visited.end(); iter++)
        {
            std::cout << iter->first << " : " << iter->second << std::endl;
        }

    }
    

    void dfs_topo_order(int component, int v, std::map<int, std::vector<int>>& list)
    {
        visited.find(v)->second = component;

        for (int i = 0; i < (list.find(v)->second).size(); i++)
        {
            if (visited.find(list[v][i])->second == 0)
            {
                dfs_topo_order(component, list[v][i], list);
            }
        }
        topological_order.push_back(v);
    }


};
int main()
{
    Graph gr(g_type::UNDIRECTED);
    gr.addVertex(1);
    gr.addVertex(2);
    gr.addVertex(3);
    gr.addVertex(4);
    gr.addVertex(5);
    gr.addVertex(6);
    gr.addEdge(1, 2);
    gr.addEdge(1, 3);
    gr.addEdge(3, 2);
    gr.addEdge(3, 4);
    
    gr.find_connectivity_component_undirected();
    std::cout << "____________________" << std::endl;
    Graph dirgr(g_type::DIRECTED);
    dirgr.addVertex(1);
    dirgr.addVertex(2);
    dirgr.addVertex(3);
    dirgr.addVertex(4);
    dirgr.addVertex(5);
    dirgr.addVertex(6);
    dirgr.addVertex(7);

    dirgr.addEdge(2,3);
    dirgr.addEdge(1,2);
    dirgr.addEdge(4,1);
    dirgr.addEdge(2,4);
    dirgr.addEdge(5,4);
    dirgr.addEdge(5,7);
    dirgr.addEdge(5,6);
    dirgr.addEdge(6,7);
    dirgr.find_connectivity_component_directed();

}
