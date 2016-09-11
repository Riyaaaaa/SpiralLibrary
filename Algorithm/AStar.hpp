/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef AStar_h
#define AStar_h

#include <vector>
#include <queue>

#include "../Common/Macro.h"
#include "../Structure/Index.hpp"

NS_LIBSPIRAL_BEGIN

struct Node {
    int cost;
    int heuristicsCost;
    int score;
    
    libspiral::Index index, prev;
    
    bool operator<(const Node& rhs) const {
        return score < rhs.score;
    }
    
    bool operator>(const Node& rhs) const {
        return score > rhs.score;
    }
};

template<class Derived, class Map>
struct IRater {
    typedef Map map_t;
    
    int heuristics(const map_t& map, Index index, Index end) {
        return static_cast<Derived&>(this)->heuristics(map, index);
    }
    
    std::vector<Index> getIndexes(const map_t& map, Index index, Index end){
        return static_cast<Derived&>(this)->getIndexes(map, index);
    }
};

template<class Rater>
class AStar {
public:
    typedef typename Rater::map_t map_t;
public:
    AStar(Index start, Index end) :
    _start(start), _end(end) {}
    
    std::vector<Index> search(const map_t& map) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;
        
        queue.push(calcNode(map, _start, Index(-1, -1), 0));
        
        while(!queue.empty()) {
            auto node = queue.top();
            std::vector<Index> indexes = _rater.getIndexes(map, node.index, _end);
            for(auto && newindex : indexes) {
                if(newindex == _end) {
                    _searchedMap.insert(std::make_pair(_end, calcNode(map, newindex, node.index, node.cost + 1)));
                    return structPath();
                }
                auto it = _searchedMap.find(newindex);
                if(it == _searchedMap.end()) {
                    auto newnode = calcNode(map, newindex, node.index, node.cost + 1);
                    _searchedMap.insert(std::make_pair(newnode.index, newnode));
                   queue.push(newnode);
                }
            }
            queue.pop();
        }
        
        return std::vector<Index>{};
    }
    
    Node calcNode(const map_t& map, Index index, Index prev, int cost) {
        Node node;
        
        node.cost = cost;
        node.heuristicsCost = _rater.heuristics(map, index, _end);
        node.score = node.cost + node.heuristicsCost;
        node.index = index;
        node.prev = prev;
        
        return node;
    }
    
    std::vector<Index> structPath() {
        Node node = _searchedMap[_end];
        std::vector<Index> path = {_end};
        while(node.prev != _start) {
            node = _searchedMap[node.prev];
            path.push_back(node.index);
        }
        
        return path;
    }
    
    std::unordered_map<Index, Node, IndexHash<libspiral::pow(2, 16)>> _searchedMap;
    
    Index _start, _end;
    Rater _rater;
};


NS_LIBSPIRAL_END

#endif /* AStar_h */
