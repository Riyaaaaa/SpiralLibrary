//
//  AlphaBetaNodeState.hpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/10/04.
//
//

#ifndef AlphaBetaNodeState_h
#define AlphaBetaNodeState_h

#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

namespace detail {
    template<class Field, class Index>
    struct AlphaBetaNodeStateBase {
        typedef Field Field_t;
        typedef Index Index_t;
        
        bool _turn;
        float _alpha;
        float _beta;
        float _eval;
        
        AlphaBetaNodeStateBase(bool turn, float alpha, float beta)
        : _turn(turn),
        _alpha(alpha),
        _beta(beta),
        _eval(turn ? -FLT_MAX : FLT_MAX)
        {
            
        }
        
        virtual ~AlphaBetaNodeStateBase() = default;
        
        virtual std::vector<Index> getEnableHands(const Field& field) = 0;
        virtual bool isFinished(const Field& field, const std::vector<Index>& enableHands) = 0;
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
}

template<class Field, class Index>
struct AlphaBetaNodeState : detail::AlphaBetaNodeStateBase<Field, Index> {
    AlphaBetaNodeState(bool turn, float alpha, float beta) : detail::AlphaBetaNodeStateBase<Field, Index>(turn, alpha, beta) {}
    
    virtual Field getNextField(const Field& field, Index hand) = 0;
    virtual ~AlphaBetaNodeState() = default;
};

template<class Field, class DiffStack, class Index>
struct ABDiffNodeState : detail::AlphaBetaNodeStateBase<Field, Index> {
    typedef DiffStack DiffStack_t;
    
    ABDiffNodeState(bool turn, float alpha, float beta) : detail::AlphaBetaNodeStateBase<Field, Index>(turn, alpha, beta) {}
    
    virtual typename DiffStack::Task done(Field& field, Index hand) = 0;
    virtual void undo(Field& field, const typename DiffStack::Task& task) = 0;
    virtual ~ABDiffNodeState() = default;
};

NS_LIBSPIRAL_END

#endif /* AlphaBetaNodeState_h */
