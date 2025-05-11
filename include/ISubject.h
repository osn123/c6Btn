#pragma once

#include <vector>
#include <algorithm> // std::remove と std::vector::erase のため

// 前方宣言
#include "IObserver.h" // Include the full definition of IObserver
class Button; // notifyメソッドがButton*を渡す場合

class ISubject {
protected:
    std::vector<IObserver*> m_observers;

public:
    virtual ~ISubject() = default; // 仮想デストラクタ

    virtual void attach(IObserver* observer) {
        // オプション: observerが既に存在するかチェックすることも可能
        m_observers.push_back(observer);
    }

    virtual void detach(IObserver* observer) {
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
    }

    // 登録された全てのObserverに通知 (Button自身を渡す)
    virtual void notify(Button* button) { 
        for (IObserver* observer : m_observers) {
            if (observer) { // 基本的なnullチェック
                observer->onNotify(button);
            }
        }
    }
};
