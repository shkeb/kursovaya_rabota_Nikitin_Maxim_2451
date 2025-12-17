#pragma once

#include <iostream>
#include <vector>

class Graph {
private:
    int numVertices_;
    std::vector<std::vector<int>> adjacencyList_; // храним граф ввиде списка смежности вершины с соседями
    void dfs(int v, std::vector<int>& topologicalAnswer, std::vector<bool>& used); //принимаем v заполняем анс в обратном порядке проверяем помещенные вершины ищем топологическую сортировку 
public:
    Graph(const std::string& filename); // считываем граф из файла
    std::vector<int> TopologicalSort(); // ищем сортировку
    void WriteGraph(const std::string& filename, const std::vector<int>& order) const;
};
