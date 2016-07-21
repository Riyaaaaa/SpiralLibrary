//
//  AlphaBetaAlgorithm.h
//  HyperReversi
//
//  Created by Toshiki Suizu on 2016/06/09.
//
//

#ifndef AlphaBetaAlgorithm_h
#define AlphaBetaAlgorithm_h

#include <vector>
#include <algorithm>
#include "../Container/Pair.hpp"

template<class Field, class Index>
struct AlphaBetaNodeState {
    
    typedef Field Field_t;
    typedef Index Index_t;
    
    bool _turn;
    float _alpha;
    float _beta;
    float _eval;
    
    AlphaBetaNodeState(bool turn, float alpha, float beta)
    : _turn(turn),
    _alpha(alpha),
    _beta(beta),
    _eval(turn ? -FLT_MAX : FLT_MAX)
    {
        
    }
    
    virtual std::vector<Index> getEnableHands(const Field& field) = 0;
    virtual bool isFinished(const Field& field, const std::vector<Index>& enableHands) = 0;
    virtual Field getNextField(const Field& field, Index hand) = 0;
    virtual float eval(const Field& field, int turn) = 0;
    virtual float endEval(const Field& field, int turn) = 0;
    virtual int calcTurn(const Field& field) = 0;
    
    bool isPruning(float eval) {
        if(_turn) {
            if(eval >= _beta) {
                return true;
            }
        }
        else {
            if(eval <= _alpha) {
                return true;
            }
        }
        return false;
    }
    
    void setEval(float eval) {
        if(_turn) {
            if(eval > _eval) {
                _eval = eval;
                _alpha = std::max(_alpha, _eval);
            }
        }
        else {
            if(eval < _eval) {
                _eval = eval;
                _beta = std::min(_beta, _eval);
            }
        }
    }
    
    float getEval() {
        return _eval;
    }
    
    float getAlpha() {
        return _alpha;
    }
    
    float getBeta() {
        return _beta;
    }
    
};

template<class NodeState>
struct AlphaBetaAlgorithm {
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
        if (enableHands.empty()) { //パスの場合
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

#endif /* AlphaBetaAlgorithm_h */
