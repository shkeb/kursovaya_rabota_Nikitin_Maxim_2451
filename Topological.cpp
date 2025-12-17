#include "Topological.h"
#include <algorithm>
#include <fstream>
#include <vector>
Graph::Graph(const std::string& filename) { 

    std::ifstream inputFile(filename);

    inputFile >> numVertices_; 

    adjacencyList_.resize(numVertices_);

    for (int i = 0; i < numVertices_; ++i) {
        for (int j = 0; j < numVertices_; ++j) {
            int value;
            inputFile >> value; 
            if (value == 1) 
                adjacencyList_[i].push_back(j); 
        }
    }
}

void Graph::dfs(int v, std::vector<int>& topologicalAnswer, std::vector<bool>& used) { 
    used[v] = true; 
    for (auto u : adjacencyList_[v]) { 
        if (!used[u]) 
            dfs(u, topologicalAnswer, used); 
    }
    topologicalAnswer.push_back(v); // как только обошли всех соседей вершины добавляем ее в топологическую сортировку
}


std::vector<int> Graph::TopologicalSort() { // метод для получения сортировки
    std::vector<bool> used(numVertices_); // массив, чтобы понимать использованная вершина или нет
    std::vector<int> topologicalAnswer; // массив ответа
    for (int i = 0; i < numVertices_; ++i) { // проходимся по всем вершинам
        if (!used[i]) // если не были еще в вершине
            dfs(i, topologicalAnswer, used); // запускаем от нее обход в глубину
    }
    std::reverse(topologicalAnswer.begin(), topologicalAnswer.end()); // переворачиваем массив ответа
    return topologicalAnswer;
}


void Graph::WriteGraph(const std::string& filename, const std::vector<int>& order) const { // метод для записи в файл
    std::ofstream outputFile(filename); // открыли файл вывода

    outputFile << "digraph G {" << std::endl; // объявление начала графа
    outputFile << "  rankdir=LR;" << std::endl; // граф должен стараться расположить вершины слева направо
    outputFile << "  nodesep=0.5;" << std::endl; // минимальное расстояние между узлами 
    outputFile << "  ranksep=1.0;" << std::endl; // Увеличим расстояние между рангами для читаемости

    for (int i = 0; i < numVertices_; ++i) {
        outputFile << "  " << i << " [label=\"Official " << i << "\"];" << std::endl; // создаем каждую вершину графа
    }

    for (int u = 0; u < numVertices_; ++u) {
        for (int v : adjacencyList_[u]) {
            outputFile << "  " << u << " -> " << v << ";" << std::endl; // Для каждой пары (u, v), где есть ребро, эта строка определяет ориентированное ребро 
        }
    }

    outputFile << std::endl;
    outputFile << "  // One possible order:" << std::endl;

    outputFile << "  subgraph cluster_visual_order {" << std::endl; // начало определения графа 
    outputFile << "    label=\"Execution Order\";" << std::endl; // заголовок картинки
    outputFile << "    node [style=filled, color=lightgrey, shape=box];" << std::endl; // параметры стиля вершин
    outputFile << "    edge [constraint=false, color=black, style=dashed];" << std::endl; // параметры стиля ребер
    outputFile << "    ";
    for (size_t i = 0; i < order.size(); ++i) {
        outputFile << "    " << order[i];
        if (i < order.size() - 1) {
            outputFile << " -> "; // добавляет ребра из i вершины в другие, информация о всех ребрах была введена заранее
        }
    }
    outputFile << " [style=invis];" << std::endl; // ребра которые не входят в сортировку делаем невидимыми
    outputFile << "  }" << std::endl;

    outputFile << "}" << std::endl;

    return;
}