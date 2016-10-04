//
//  DiffManagedAlphaBeta.hpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/10/04.
//
//

#ifndef DiffManagedAlphaBeta_h
#define DiffManagedAlphaBeta_h

#include <vector>
#include <algorithm>
#include "AlphaBetaNodeState.hpp"
#include "../Container/Pair.hpp"
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template<class NodeState>
struct DiffManagedAlphaBeta {
    typedef typename NodeState::Field_t Field;
    typedef typename NodeState::Index_t Index;
    
public:
    template<class... NodeArgs>
    Index operator()(Field& field, int maxDepth, NodeArgs&&... args) {
        auto node = NodeState(true, -FLT_MAX, FLT_MAX, std::forward<NodeArgs>(args)...);
        auto enableHands = node.getEnableHands(field);
        
        _turn = node.calcTurn(field);
        std::vector<libspiral::Pair<Index, float>> evalPriority;
        
        for(auto enableHand : enableHands) {
            auto task = node.done(field, enableHand);
            float eval = search(field, false, -FLT_MAX, FLT_MAX, 1, maxDepth, std::forward<NodeArgs>(args)...);
            evalPriority.push_back(libspiral::make_pair(enableHand, maxDepth % 2 == 0 ? eval : -eval));
            node.undo(field, task);
        }
        std::sort(evalPriority.begin(), evalPriority.end(), libspiral::secondGreaterOrder{});
        
        return evalPriority.front().first;
    }
    
private:
    template<class... NodeArgs>
    float search(Field& field, bool turn, float alpha, float beta, int depth, int maxDepth,  NodeArgs&&... args) {
        
        auto node = NodeState(turn, alpha, beta, std::forward<NodeArgs>(args)...);
        auto enableHands = node.getEnableHands(field);
        
        if (node.isFinished(field, enableHands)) {
            return node.endEval(field, _turn + depth);
        }
        if (depth >= maxDepth) {
            return node.eval(field, _turn + depth);
        }
        if (enableHands.empty()) {
            return search(field, !turn, alpha, beta, depth + 1, maxDepth, std::forward<NodeArgs>(args)...);
        }
        for(auto enableHand : enableHands) {
            auto task = node.done(field, enableHand);
            history.push(task);
            float eval = search(field, !turn, node.getAlpha(), node.getBeta(), depth + 1, maxDepth, std::forward<NodeArgs>(args)...);
            node.undo(field, task);
            if (node.isPruning(eval)) {
                return eval;
            }
            node.setEval(eval);
        }
        return node.getEval();
    }
    
    int _turn;
    static typename NodeState::DiffStack_t history;
};

template<class NodeState>
typename NodeState::DiffStack_t DiffManagedAlphaBeta<NodeState>::history;

NS_LIBSPIRAL_END

#endif /* DiffManagedAlphaBeta_h */
