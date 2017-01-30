#ifndef AsyncTask_hpp
#define AsyncTask_hpp

#include <functional>
#include <atomic>
#include <thread>
#include "cocos2d.h"

namespace utility {
    class AsyncTask final
    {
        using Callback = std::function<void(bool)>;

        template<typename... Args>
        class Task final
        {
            using TaskType = std::function<bool(Args...)>;
            using BindedFunc = decltype(std::bind(std::declval<TaskType>(),
                                                  std::declval<Args>()...));

        private:
            std::atomic<bool> _isEnd;
            bool _result;
            BindedFunc _task;
            Callback _callback;

        public:
            Task(const TaskType &task, const Callback &callback, Args&&... args) :
              _isEnd(false)
            , _result(false)
            , _callback(callback)
            , _task(task, std::forward<Args>(args)...) {}

            void update(const float dt) {
                if(_isEnd.load()) {
                    if(_callback) {
                        _callback(_result);
                    }
                    cocos2d::Director::getInstance()->getScheduler()->unscheduleUpdate(this);
                    delete this;
                }
            }

            inline void run() {
                _result = _task();
                _isEnd.store(true);
            }

            ~Task() = default;
        };

    private:
        AsyncTask(const AsyncTask &) = delete;
        AsyncTask &operator=(const AsyncTask &) = delete;

    public:
        template<typename F, typename... Args>
        AsyncTask(const F &func, const Callback &callback, Args&&... args)
        {
            Task<Args...> *task = new Task<Args...>(func, callback, std::forward<Args>(args)...);
            cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(task, 1024, false);
            
            std::thread th([task]() {
                task->run();
            });
            
            th.detach();
        }
        
        ~AsyncTask() = default;
    };

}

#endif /* AsyncTask_hpp */
