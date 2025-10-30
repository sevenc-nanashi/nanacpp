# NanaCpp

自分用AtCoder C++テンプレート。

## 機能一覧

- `features/core.hpp`：型エイリアスや`each`/`rep`などのマクロで反復処理や型宣言を簡潔化
- `features/input.hpp`：ベクタやペア向けの入力ヘルパーで標準入力の定型コードを削減
- `features/debug.hpp`：`ONLINE_JUDGE`切り替え対応の`dbg`マクロ群でローカルデバッグを効率化
- `features/pair.hpp`：ハッシュ対応の`hpair`で`unordered_map`/`unordered_set`にペアを安全に格納
- `features/array_sum.hpp`：累積和`ArraySum`クラスで区間和クエリを即座に計算
- `features/bisect.hpp`：条件判定関数を受け取る`bisect_first`/`bisect_last`で二分探索をテンプレ化
- `features/imos.hpp`：区間加算を効率化する`Imos`クラスで差分配列を構築
- `features/tally.hpp`：`map`ベースの`tally`関数で要素頻度をカウント
