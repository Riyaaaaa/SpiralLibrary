/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef AlphaBetaAlgorithm_h
#define AlphaBetaAlgorithm_h

#include <vector>
#include <algorithm>
#include "AlphaBetaNodeState.hpp"
#include "../Container/Pair.hpp"
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template<class NodeState>
struct AlphaBeta {
    typedef typename NodeState::Field_t Field;
    typedef typename NodeState::Index_t Index;
    
public:
    template<class... NodeArgs>
    Index operator()(const Field& field, int maxDepth, NodeArgs&&... args) {
        auto node = NodeState(true, -FLT_MAX, FLT_MAX, std::forward<NodeArgs>(args)...);
        auto enableHands = node.getEnableHands(field);
        
        _turn = node.calcTurn(field);
        std::vector<libspiral::Pair<Index, float>> evalPriority;
        
        for(auto enableHand : enableHands) {
            auto nextField = node.getNextField(field, enableHand);
            float eval = search(nextField, false, -FLT_MAX, FLT_MAX, 1, maxDepth, std::forward<NodeArgs>(args)...);
            evalPriority.push_back(libspiral::make_pair(enableHand, maxDepth % 2 == 0 ? eval : -eval));
        }
        std::sort(evalPriority.begin(), evalPriority.end(), libspiral::secondGreaterOrder{});
        
        return evalPriority.front().first;
    }
    
private:
    template<class... NodeArgs>
    float search(Field field, bool turn, float alpha, float beta, int depth, int maxDepth,  NodeArgs&&... args) {

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
            auto nextField = node.getNextField(field, enableHand);
            float eval = search(nextField, !turn, node.getAlpha(), node.getBeta(), depth + 1, maxDepth, std::forward<NodeArgs>(args)...);
            if (node.isPruning(eval)) {
                return eval;
            }
            node.setEval(eval);
        }
        return node.getEval();
    }
    
    int _turn;
};

NS_LIBSPIRAL_END

#endif /* AlphaBetaAlgorithm_h */
