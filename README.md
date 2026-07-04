# NanaCpp

自分用AtCoder C++テンプレート。

## 機能一覧

- `features/core.hpp`：型エイリアスや`each`/`rep`などのマクロで反復処理や型宣言を簡潔化
- `features/input.hpp`：ベクタやペア向けの入力ヘルパーで標準入力の定型コードを削減
- `features/debug.hpp`：`ONLINE_JUDGE`切り替え対応の`dbg`マクロ群でローカルデバッグを効率化
- `features/pair.hpp`：ハッシュ対応の`hpair`で`unordered_map`/`unordered_set`にペアを安全に格納
- `features/array_sum.hpp`：累積和`ArraySum`クラスで区間和クエリを即座に計算
- `features/cumulative_sum_2d.hpp`：2次元累積和`CumulativeSum2D`クラスで長方形領域の総和をO(1)で取得
- `features/sum.hpp`：コンテナ内の要素の総和を求める`sum`関数を提供
- `features/vec_map.hpp`：コンテナ内の要素を変換する`vec_map`/`vec_map_inplace`関数を提供
- `features/sort_by.hpp`：指定したキーでコンテナを並べ替える`sort_by`/`sort_by_desc`関数を提供
- `features/bisect.hpp`：条件判定関数を受け取る半開区間用`bisect_first`/`bisect_last`、閉区間用`bisect_first_closed`/`bisect_last_closed`で二分探索をテンプレ化
- `features/imos.hpp`：区間加算を効率化する`Imos`クラスで差分配列を構築
- `features/imos_2d.hpp`：2次元Imos法の`Imos2D`クラスで長方形加算をまとめて反映
- `features/interval_set.hpp`：重複/隣接区間をまとめて管理し、追加・削除時に被覆長を返す`IntervalSet`クラス
- `features/key_packer.hpp`：複数の非負整数を各次元の最大値に基づいて1つの整数キーへ変換する`KeyPacker`クラス
- `features/rarray.hpp`：Ruby風のArray。
- `features/rrange.hpp`：Ruby風のRangeで整数列を簡潔に生成
- `features/prime.hpp`：コピー不可な`PrimeSieve`クラスで篩ベースの素数判定や素因数分解を提供
- `features/print.hpp`：`std::cout << value << '\n'を簡略化する`print`関数
- `features/tally.hpp`：`map`ベースの`tally`関数で要素頻度をカウント
