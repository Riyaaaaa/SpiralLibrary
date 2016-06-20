//
//  AlphaBeta.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/09.
//
//

#ifndef AlphaBeta_h
#define AlphaBeta_h

#include<vector>
#include<algorithm>
#include"ReversiStream.h"
#include"../Container/Pair.hpp"

template<class Derived, class Field, class HandSelector, class Answer>
struct AlphaBetaState {
    typedef HandSelector HandSelector_t;
    typedef typename HandSelector::Hand_t Hand_t;
    typedef Field Field_t;
    typedef Answer Answer_t;
    
    AlphaBetaState(float alpha, float beta, bool isMyTurn, Hand_t hand):
    _alpha(alpha),
    _beta(beta),
    _isMyTurn(isMyTurn),
    _hand(hand),
    _eval(isMyTurn ? -1e6 : 1e6)
    {
        static_assert(std::is_same<decltype(std::declval<Derived>().getNextFiled(std::declval<Field>(), std::declval<Answer_t>())), Field>::value, "getNextField function is not defined");
        static_assert(std::is_same<decltype(std::declval<Derived>().getHands(std::declval<Field>())), std::vector<Answer_t>>::value, "getHands function is not defined");
        static_assert(std::is_same<decltype(std::declval<Derived>().calcEval(std::declval<Field>())), float>::value, "calcEval function is not defined");
    }
    
    bool isPruning(float eval) {
        if(_isMyTurn) {
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
        if(_isMyTurn) {
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
    
    Hand_t _hand;
    bool _isMyTurn;
    float _alpha, _beta;
    float _eval;
};

template<class FieldState>
class AlphaBeta {
public:
    typedef typename FieldState::HandSelector_t HandSelector;
    typedef typename FieldState::Field_t Field;
    typedef typename FieldState::Hand_t Hand;
    typedef typename FieldState::Answer_t Answer;
    
    AlphaBeta(HandSelector selector):
    _selector(selector){
        
    }
    
    Answer operator()(const Field& field, int maxDepth) {
        std::priority_queue<libspiral::Pair<Answer, float>, std::vector<libspiral::Pair<Answer, float>>, libspiral::secondLessOrder> evalPriority;
        FieldState state(-1e6, 1e6, true, _selector(true));
        std::vector<Answer> nextHands;
        nextHands = state.getHands(field);
        
        for(auto && ans : nextHands) {
            float eval;
            auto nextField = state.getNextFiled(field, ans);
            
            eval = impl(nextField, -1e6, 1e6, 1, maxDepth);
            evalPriority.push(libspiral::make_pair(ans, eval));
        }
        
        return evalPriority.top().first;
    }
private:
    float impl(Field field, float alpha, float beta, int depth, int maxDepth) {
        FieldState state(alpha, beta, depth % 2 == 0, _selector(depth % 2 == 0));
        std::vector<Answer> nextHands = state.getHands(field);
        
        for(auto ans: nextHands) {
            float eval;
            auto nextField = state.getNextFiled(field, ans);
            if(depth >= maxDepth) {
                eval = state.calcEval(nextField);
            }
            else {
                eval = impl(nextField, state.getAlpha(), state.getBeta(), depth + 1, maxDepth);
            }
            if(state.isPruning(eval)) {
                return eval;
            }
            state.setEval(eval);
        }
        return state.getEval();
    }
    
    HandSelector _selector;
};

#endif /* AlphaBeta_h */
