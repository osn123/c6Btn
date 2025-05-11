#pragma once

// 前方宣言 (循環参照を避けるため)
class Button; 

class IObserver {
public:
    virtual ~IObserver() = default; // 適切なクリーンアップのための仮想デストラクタ
    // Subjectから変更通知を受け取るメソッド
    // Buttonポインタにより、ObserverはどのButtonから通知が来たかを知ることができる
    virtual void onNotify(Button* button) = 0;
};
